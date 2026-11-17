modded class Ammo_40mm_Base
{
    protected bool m_BDE_USL_EjectedPhysicsSleepPending;
    protected bool m_BDE_USL_EjectedTouchedGround;
    protected bool m_BDE_USL_EjectedSleepQueued;
    protected int m_BDE_USL_EjectedEarliestSleepTime;
    protected PlayerBase m_BDE_USL_EjectedSourcePlayer;

    void BDE_USL_MarkEjectedForPhysicsSleep(PlayerBase sourcePlayer)
    {
        if (!GetGame().IsServer())
            return;

        m_BDE_USL_EjectedPhysicsSleepPending = true;
        m_BDE_USL_EjectedTouchedGround = false;
        m_BDE_USL_EjectedSleepQueued = false;
        m_BDE_USL_EjectedEarliestSleepTime = GetGame().GetTime() + BDE_USL_EJECT_MIN_DYNAMIC_TIME_MS;
        m_BDE_USL_EjectedSourcePlayer = sourcePlayer;
    }

    override void EOnContact(IEntity other, Contact extra)
    {
        super.EOnContact(other, extra);
        BDE_USL_HandleEjectedGroundContact(other, extra);
    }

    protected void BDE_USL_HandleEjectedGroundContact(IEntity other, Contact extra)
    {
        if (!GetGame().IsServer() || !m_BDE_USL_EjectedPhysicsSleepPending || IsSetForDeletion())
            return;

        if (GetHierarchyParent() || !dBodyIsSet(this) || !dBodyIsActive(this))
            return;

        if (m_BDE_USL_EjectedSourcePlayer)
        {
            if (other == m_BDE_USL_EjectedSourcePlayer)
                return;

            EntityAI otherEntity;

            if (Class.CastTo(otherEntity, other) && otherEntity.GetHierarchyRootPlayer() == m_BDE_USL_EjectedSourcePlayer)
                return;
        }

        if (extra && Math.AbsFloat(extra.Normal[1]) < BDE_USL_EJECT_GROUND_NORMAL_MIN_Y)
            return;

        m_BDE_USL_EjectedTouchedGround = true;
        BDE_USL_TrySleepEjectedPhysics();
    }

    protected void BDE_USL_TrySleepEjectedPhysics()
    {
        if (!GetGame().IsServer() || !m_BDE_USL_EjectedPhysicsSleepPending || !m_BDE_USL_EjectedTouchedGround || IsSetForDeletion())
            return;

        if (GetHierarchyParent())
        {
            m_BDE_USL_EjectedPhysicsSleepPending = false;
            m_BDE_USL_EjectedSleepQueued = false;
            m_BDE_USL_EjectedSourcePlayer = null;
            return;
        }

        int remainingMs = m_BDE_USL_EjectedEarliestSleepTime - GetGame().GetTime();

        if (remainingMs > 0)
        {
            if (!m_BDE_USL_EjectedSleepQueued)
            {
                m_BDE_USL_EjectedSleepQueued = true;
                GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(BDE_USL_DisableEjectedPhysics, remainingMs, false);
            }

            return;
        }

        BDE_USL_DisableEjectedPhysics();
    }

    protected void BDE_USL_DisableEjectedPhysics()
    {
        m_BDE_USL_EjectedSleepQueued = false;

        if (!GetGame().IsServer() || !m_BDE_USL_EjectedPhysicsSleepPending || !m_BDE_USL_EjectedTouchedGround || IsSetForDeletion())
            return;

        if (GetHierarchyParent())
        {
            m_BDE_USL_EjectedPhysicsSleepPending = false;
            m_BDE_USL_EjectedSourcePlayer = null;
            return;
        }

        int remainingMs = m_BDE_USL_EjectedEarliestSleepTime - GetGame().GetTime();

        if (remainingMs > 0)
        {
            m_BDE_USL_EjectedSleepQueued = true;
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(BDE_USL_DisableEjectedPhysics, remainingMs, false);
            return;
        }

        if (!dBodyIsSet(this))
            return;

        // An earlier contact is not proof the item has settled; it may be falling again.
        Physics ejectedPhysics = GetPhysics();

        if (!ejectedPhysics)
            return;

        if (ejectedPhysics.GetVelocity().LengthSq() > 0.01)
        {
            m_BDE_USL_EjectedSleepQueued = true;
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(BDE_USL_DisableEjectedPhysics, 250, false);
            return;
        }

        SetVelocity(this, vector.Zero);
        dBodySetAngularVelocity(this, vector.Zero);
        dBodyActive(this, ActiveState.INACTIVE);
        m_BDE_USL_EjectedPhysicsSleepPending = false;
        m_BDE_USL_EjectedSourcePlayer = null;
    }

    override bool CanBeCombined(EntityAI other_item, bool reservation_check = true, bool stack_max_limit = false)
    {
        Weapon_Base host = Weapon_Base.Cast(other_item);

        if (host && host.BDE_USL_CanDirectLoadAttachedRound(this, reservation_check))
            return true;

        BDE_UnderSlungLauncher_Base launcher = BDE_UnderSlungLauncher_Base.Cast(other_item);

        if (launcher && launcher.BDE_USL_CanDirectLoadRound(this, reservation_check))
        {
            if (launcher.IsKindOf("BDE_M203") || launcher.BDE_USL_ShouldUseAttachedCustomAnimation())
                return true;
        }

        return super.CanBeCombined(other_item, reservation_check, stack_max_limit);
    }

    override void CombineItems(ItemBase other_item, bool use_stack_max = true)
    {
        Weapon_Base host = Weapon_Base.Cast(other_item);

        if (host && host.BDE_USL_CanDirectLoadAttachedRound(this, false))
        {
            BDE_UnderSlungLauncher_Base attachedLauncher = host.BDE_USL_GetLauncher();

            if (attachedLauncher && attachedLauncher.BDE_USL_ShouldUseAttachedCustomAnimation())
            {
                PlayerBase player = PlayerBase.Cast(host.GetHierarchyRootPlayer());

                if (GetGame().IsClient() && player && GetGame().GetPlayer() == player)
                    player.BDE_USL_ClientBeginSpecificReload(attachedLauncher, this);
                else if (GetGame().IsServer())
                    attachedLauncher.BDE_USL_ServerRequestOwnerSpecificReload(this);

                return;
            }

            if (attachedLauncher && GetGame().IsServer())
                attachedLauncher.BDE_USL_ServerLoadSpecificRound(this);

            return;
        }

        BDE_UnderSlungLauncher_Base launcher = BDE_UnderSlungLauncher_Base.Cast(other_item);

        if (launcher && launcher.BDE_USL_CanDirectLoadRound(this, false))
        {
            Weapon_Base launcherHost = Weapon_Base.Cast(launcher.GetHierarchyParent());

            if (launcherHost && launcher.BDE_USL_ShouldUseAttachedCustomAnimation())
            {
                PlayerBase launcherPlayer = PlayerBase.Cast(launcherHost.GetHierarchyRootPlayer());

                if (GetGame().IsClient() && launcherPlayer && GetGame().GetPlayer() == launcherPlayer)
                    launcherPlayer.BDE_USL_ClientBeginSpecificReload(launcher, this);
                else if (GetGame().IsServer())
                    launcher.BDE_USL_ServerRequestOwnerSpecificReload(this);

                return;
            }

            if (launcher.IsKindOf("BDE_M203") && GetGame().IsServer())
                launcher.BDE_USL_ServerLoadSpecificRound(this);

            if (launcher.IsKindOf("BDE_M203"))
                return;
        }

        super.CombineItems(other_item, use_stack_max);
    }
}

class Ammo_40mm_Empty extends ItemBase
{
    protected bool m_BDE_USL_EjectedPhysicsSleepPending;
    protected bool m_BDE_USL_EjectedTouchedGround;
    protected bool m_BDE_USL_EjectedSleepQueued;
    protected int m_BDE_USL_EjectedEarliestSleepTime;
    protected PlayerBase m_BDE_USL_EjectedSourcePlayer;

    void BDE_USL_MarkEjectedForPhysicsSleep(PlayerBase sourcePlayer)
    {
        if (!GetGame().IsServer())
            return;

        m_BDE_USL_EjectedPhysicsSleepPending = true;
        m_BDE_USL_EjectedTouchedGround = false;
        m_BDE_USL_EjectedSleepQueued = false;
        m_BDE_USL_EjectedEarliestSleepTime = GetGame().GetTime() + BDE_USL_EJECT_MIN_DYNAMIC_TIME_MS;
        m_BDE_USL_EjectedSourcePlayer = sourcePlayer;
    }

    override void EOnContact(IEntity other, Contact extra)
    {
        super.EOnContact(other, extra);

        if (!GetGame().IsServer() || !m_BDE_USL_EjectedPhysicsSleepPending || IsSetForDeletion())
            return;

        if (GetHierarchyParent() || !dBodyIsSet(this) || !dBodyIsActive(this))
            return;

        if (m_BDE_USL_EjectedSourcePlayer)
        {
            if (other == m_BDE_USL_EjectedSourcePlayer)
                return;

            EntityAI otherEntity;

            if (Class.CastTo(otherEntity, other) && otherEntity.GetHierarchyRootPlayer() == m_BDE_USL_EjectedSourcePlayer)
                return;
        }

        if (extra && Math.AbsFloat(extra.Normal[1]) < BDE_USL_EJECT_GROUND_NORMAL_MIN_Y)
            return;

        m_BDE_USL_EjectedTouchedGround = true;
        BDE_USL_TrySleepEjectedPhysics();
    }

    protected void BDE_USL_TrySleepEjectedPhysics()
    {
        if (!GetGame().IsServer() || !m_BDE_USL_EjectedPhysicsSleepPending || !m_BDE_USL_EjectedTouchedGround || IsSetForDeletion())
            return;

        if (GetHierarchyParent())
        {
            m_BDE_USL_EjectedPhysicsSleepPending = false;
            m_BDE_USL_EjectedSleepQueued = false;
            m_BDE_USL_EjectedSourcePlayer = null;
            return;
        }

        int remainingMs = m_BDE_USL_EjectedEarliestSleepTime - GetGame().GetTime();

        if (remainingMs > 0)
        {
            if (!m_BDE_USL_EjectedSleepQueued)
            {
                m_BDE_USL_EjectedSleepQueued = true;
                GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(BDE_USL_DisableEjectedPhysics, remainingMs, false);
            }

            return;
        }

        BDE_USL_DisableEjectedPhysics();
    }

    protected void BDE_USL_DisableEjectedPhysics()
    {
        m_BDE_USL_EjectedSleepQueued = false;

        if (!GetGame().IsServer() || !m_BDE_USL_EjectedPhysicsSleepPending || !m_BDE_USL_EjectedTouchedGround || IsSetForDeletion())
            return;

        if (GetHierarchyParent())
        {
            m_BDE_USL_EjectedPhysicsSleepPending = false;
            m_BDE_USL_EjectedSourcePlayer = null;
            return;
        }

        int remainingMs = m_BDE_USL_EjectedEarliestSleepTime - GetGame().GetTime();

        if (remainingMs > 0)
        {
            m_BDE_USL_EjectedSleepQueued = true;
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(BDE_USL_DisableEjectedPhysics, remainingMs, false);
            return;
        }

        if (!dBodyIsSet(this))
            return;

        // An earlier contact is not proof the item has settled; it may be falling again.
        Physics ejectedPhysics = GetPhysics();

        if (!ejectedPhysics)
            return;

        if (ejectedPhysics.GetVelocity().LengthSq() > 0.01)
        {
            m_BDE_USL_EjectedSleepQueued = true;
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(BDE_USL_DisableEjectedPhysics, 250, false);
            return;
        }

        SetVelocity(this, vector.Zero);
        dBodySetAngularVelocity(this, vector.Zero);
        dBodyActive(this, ActiveState.INACTIVE);
        m_BDE_USL_EjectedPhysicsSleepPending = false;
        m_BDE_USL_EjectedSourcePlayer = null;
    }
}

class Ammo_VOG25 extends Ammo_40mm_Explosive
{
    override bool CanBeCombined(EntityAI other_item, bool reservation_check = true, bool stack_max_limit = false)
    {
        BDE_GP25 gp25 = BDE_GP25.Cast(other_item);

        if (gp25 && !Weapon_Base.Cast(gp25.GetHierarchyParent()) && gp25.BDE_USL_CanDirectLoadRound(this, reservation_check))
            return true;

        return super.CanBeCombined(other_item, reservation_check, stack_max_limit);
    }

    override void CombineItems(ItemBase other_item, bool use_stack_max = true)
    {
        BDE_GP25 gp25 = BDE_GP25.Cast(other_item);

        if (gp25 && !Weapon_Base.Cast(gp25.GetHierarchyParent()) && gp25.BDE_USL_CanDirectLoadRound(this, false))
        {
            PlayerBase player = PlayerBase.Cast(gp25.GetHierarchyRootPlayer());

            if (GetGame().IsClient() && player && GetGame().GetPlayer() == player)
                gp25.BDE_USL_ClientRequestLoadSpecificRound(this);
            else if (GetGame().IsServer())
                gp25.BDE_USL_ServerLoadSpecificRound(this);

            return;
        }

        super.CombineItems(other_item, use_stack_max);
    }
}
