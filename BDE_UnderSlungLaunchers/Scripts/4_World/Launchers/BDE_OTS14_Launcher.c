class BDE_OTS14_Launcher : BDE_GP25
{
    override bool BDE_USL_IsRoundAllowed(Magazine source)
    {
        return BDE_USL_SettingsManager.IsVOG25MagazineAllowed(source);
    }

    override bool CanChamberBullet(int muzzleIndex, Magazine mag)
    {
        if (!BDE_USL_SettingsManager.IsVOG25MagazineAllowed(mag))
            return false;

        return super.CanChamberBullet(muzzleIndex, mag);
    }

    override void BDE_GP25_UpdateSightVisual(bool adsActive)
    {
    }

    override float BDE_USL_GetAimFallbackZeroing()
    {
        return 0;
    }

    protected bool BDE_OTS14_IsMountedOnGroza()
    {
        EntityAI host = GetHierarchyParent();
        if (!host || !host.IsKindOf("BDE_OTS14_Groza_Base"))
        {
            return false;
        }

        return host.FindAttachmentBySlotName("BDE_OTS14_Launcher") == this;
    }

    override bool CanFire()
    {
        return BDE_OTS14_IsMountedOnGroza() && super.CanFire();
    }

    override bool BDE_USL_CanFireAttachedFromHost(Weapon_Base host)
    {
        if (!BDE_OTS14_IsMountedOnGroza() || host != GetHierarchyParent())
        {
            return false;
        }

        return super.BDE_USL_CanFireAttachedFromHost(host);
    }

    override string BDE_USL_GetHUDShortName()
    {
        return "Groza GL";
    }

    override void BDE_GP25_RefreshVariant()
    {
    }

    override void BDE_GP25_RequestSightVariantRefresh()
    {
        BDE_GP25_RequestVariantRefresh();
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent || !parent.IsKindOf("BDE_OTS14_Groza_Base"))
        {
            return false;
        }

        return super.CanPutAsAttachment(parent);
    }

    override bool BDE_GP25_GetVirtualSightPointsLS(out vector cameraPosition, out vector cameraDirectionPoint, out vector pivotStart, out vector pivotEnd)
    {
        EntityAI host = GetHierarchyParent();
        float distance = BDE_USL_GetCurrentAimZeroing();
        if (!BDE_OTS14_IsMountedOnGroza() || distance <= 0 || host.FindAttachmentBySlotName("BDE_OTS14_Sight"))
        {
            return false;
        }

        string notch = "groza_gl_100";
        if (distance >= 250)
        {
            notch = "groza_gl_250";
        }
        else if (distance >= 200)
        {
            notch = "groza_gl_200";
        }
        else if (distance >= 150)
        {
            notch = "groza_gl_150";
        }

        if (!MemoryPointExists("groza_gl_rear") || !MemoryPointExists(notch))
        {
            return false;
        }
        cameraPosition = GetMemoryPointPos("groza_gl_rear");
        cameraDirectionPoint = GetMemoryPointPos(notch);

        pivotStart = "0 0 0.03";
        pivotEnd = "0 0 -0.03";
        return true;
    }
};

modded class ModItemRegisterCallbacks
{
    override void RegisterPistol(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterPistol(pType, pBehavior);

        pType.AddItemInHandsProfileIK("BDE_OTS14_Launcher", "BDE_UnderSlungLaunchers/Animations/GP25/player_main_gp25.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_GP25_Standalone_IK.anm", "dz/anims/anm/player/reloads/Flaregun/w_Flaregun_states.anm");
    }
};

class BDE_OTS14_LauncherSight : Inventory_Base
{
    protected float m_BDE_OTS14_LastFoldPhase = -1;

    override void EEInit()
    {
        super.EEInit();
        SetAnimationPhaseNow("groza_sight_fold", 1);
        m_BDE_OTS14_LastFoldPhase = 1;
    }

    void BDE_OTS14_SetFoldPhase(float phase)
    {
        if (phase != m_BDE_OTS14_LastFoldPhase)
        {
            SetAnimationPhase("groza_sight_fold", phase);
            m_BDE_OTS14_LastFoldPhase = phase;
        }
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        return false;
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        return false;
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        return parent && parent.IsKindOf("BDE_OTS14_Launcher") && super.CanPutAsAttachment(parent);
    }
};
