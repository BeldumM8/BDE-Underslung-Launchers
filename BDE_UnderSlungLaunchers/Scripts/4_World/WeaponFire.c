modded class WeaponFire
{
    protected bool BDE_USL_IsSix12StandaloneHost()
    {
        return m_weapon && m_weapon.IsKindOf("BDE_Six12_StandAloneMount_Weapon");
    }

    protected bool BDE_USL_ShouldInterceptAttachedFire()
    {
        if (!m_weapon)
            return false;

        if (BDE_USL_IsSix12StandaloneHost())
            return true;

        return m_weapon.BDE_USL_IsLauncherModeSelected() || m_weapon.BDE_USL_IsSix12ModeSelected();
    }

    protected void BDE_USL_FireAttached(WeaponEventBase e)
    {
        if (!m_weapon)
            return;

        m_dtAccumulator = 0;
        PlayerBase player = PlayerBase.Cast(m_weapon.GetHierarchyRootPlayer());
        if (!player && e)
            player = PlayerBase.Cast(e.m_player);

        BDE_Six12 six12;
        if (BDE_USL_IsSix12StandaloneHost())
        {
            BDE_Six12_StandAloneMount_Weapon six12Mount = BDE_Six12_StandAloneMount_Weapon.Cast(m_weapon);
            if (six12Mount)
                six12 = six12Mount.BDE_Six12_GetBody();
        }
        else
        {
            six12 = m_weapon.BDE_USL_GetSix12();
        }

        if (six12)
        {
            six12.BDE_Six12_ClientFireAttachedFromHost(m_weapon, player);
            return;
        }

        if (m_weapon.BDE_USL_IsSix12ModeSelected())
            return;

        BDE_UnderSlungLauncher_Base launcher = m_weapon.BDE_USL_GetLauncher();
        if (launcher)
            launcher.BDE_USL_ClientFireAttachedFromHost(m_weapon, player);
    }

    override void OnEntry(WeaponEventBase e)
    {
        if (e && BDE_USL_ShouldInterceptAttachedFire())
        {
            BDE_USL_FireAttached(e);
            return;
        }

        super.OnEntry(e);
    }
}

modded class WeaponFireAndChamber
{
    override void OnEntry(WeaponEventBase e)
    {
        if (e && BDE_USL_ShouldInterceptAttachedFire())
        {
            BDE_USL_FireAttached(e);
            return;
        }

        super.OnEntry(e);
    }
}

modded class WeaponFireAndChamberFromInnerMagazine
{
    override void OnEntry(WeaponEventBase e)
    {
        if (e && BDE_USL_ShouldInterceptAttachedFire())
        {
            BDE_USL_FireAttached(e);
            return;
        }

        super.OnEntry(e);
    }
}

modded class WeaponFireWithEject
{
    override void OnEntry(WeaponEventBase e)
    {
        if (e && BDE_USL_ShouldInterceptAttachedFire())
        {
            BDE_USL_FireAttached(e);
            return;
        }

        super.OnEntry(e);
    }
}

modded class WeaponActionDryFire
{
    override void Action(WeaponEventBase e)
    {
        if (m_weapon)
        {
            BDE_Six12 six12;
            if (m_weapon.IsKindOf("BDE_Six12_StandAloneMount_Weapon"))
            {
                BDE_Six12_StandAloneMount_Weapon mount = BDE_Six12_StandAloneMount_Weapon.Cast(m_weapon);
                if (mount)
                    six12 = mount.BDE_Six12_GetBody();
            }
            else if (m_weapon.BDE_USL_IsSix12ModeSelected())
            {
                six12 = m_weapon.BDE_USL_GetSix12();
            }

            if (six12)
            {
                if (GetGame().IsClient())
                {
                    PlayerBase six12Player = PlayerBase.Cast(m_weapon.GetHierarchyRootPlayer());
                    six12.BDE_Six12_ClientFireAttachedFromHost(m_weapon, six12Player);
                }
                return;
            }

            if (m_weapon.BDE_USL_IsSix12ModeSelected())
                return;

            if (m_weapon.BDE_USL_IsLauncherModeSelected())
            {
                BDE_UnderSlungLauncher_Base launcher = m_weapon.BDE_USL_GetLauncher();
                if (launcher)
                {
                    if (launcher.BDE_USL_IsManipulationActive())
                        return;

                    if (GetGame().IsClient())
                    {
                        PlayerBase dryFirePlayer = PlayerBase.Cast(m_weapon.GetHierarchyRootPlayer());
                        launcher.BDE_USL_ClientPlayDryFire(dryFirePlayer);
                    }
                    return;
                }
            }
        }

        super.Action(e);
    }
}
