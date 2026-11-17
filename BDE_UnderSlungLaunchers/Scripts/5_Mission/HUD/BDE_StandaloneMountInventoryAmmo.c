modded class Icon
{
    override void CheckIsWeapon()
    {
        super.CheckIsWeapon();

        Weapon_Base host = Weapon_Base.Cast(m_Obj);
        if (!host || (!host.IsKindOf("BDE_M203_StandAloneMount_Weapon") && !host.IsKindOf("BDE_FN40_StandaloneMount_Weapon")))
            return;

        BDE_USL_LoadStandaloneM203AmmoIconImages();
    }

    protected void BDE_USL_LoadStandaloneM203AmmoIconImages()
    {
        if (!m_AmmoIcons)
            return;

        for (int i = 0; i < m_AmmoIcons.Count(); i++)
        {
            ImageWidget ammoIcon = m_AmmoIcons.Get(i);
            if (!ammoIcon)
                continue;

            ammoIcon.LoadImageFile(0, "set:dayz_gui image:cartridge_shell");
            ammoIcon.LoadImageFile(1, "set:dayz_gui image:shell_shell");
            ammoIcon.LoadImageFile(2, "set:dayz_gui image:jam_shell");
        }
    }

    override void RefreshMuzzleIcon()
    {
        Weapon_Base host = Weapon_Base.Cast(GetObject());
        if (!host || (!host.IsKindOf("BDE_M203_StandAloneMount_Weapon") && !host.IsKindOf("BDE_FN40_StandaloneMount_Weapon")))
        {
            super.RefreshMuzzleIcon();
            return;
        }

        if (!m_AmmoIcons || m_AmmoIcons.Count() == 0)
            return;

        for (int i = 0; i < m_AmmoIcons.Count(); i++)
        {
            ImageWidget staleIcon = m_AmmoIcons.Get(i);
            if (staleIcon)
                staleIcon.Show(false);
        }

        BDE_M203 launcher = BDE_M203.Cast(host.BDE_USL_GetLauncher());
        if (!launcher || launcher.GetMuzzleCount() <= 0 || !launcher.IsChamberFull(0))
            return;

        ImageWidget ammoIcon = m_AmmoIcons.Get(0);
        if (!ammoIcon)
            return;

        ammoIcon.Show(true);

        if (launcher.IsJammed())
            ammoIcon.SetImage(2);
        else if (launcher.IsChamberFiredOut(0))
            ammoIcon.SetImage(1);
        else
            ammoIcon.SetImage(0);
    }
}

modded class SlotsIcon
{
    override void CheckIsWeapon()
    {
        super.CheckIsWeapon();

        Weapon_Base host = Weapon_Base.Cast(m_Obj);
        if (!host || (!host.IsKindOf("BDE_M203_StandAloneMount_Weapon") && !host.IsKindOf("BDE_FN40_StandaloneMount_Weapon")))
            return;

        BDE_USL_LoadStandaloneM203AmmoIconImages();
    }

    protected void BDE_USL_LoadStandaloneM203AmmoIconImages()
    {
        if (!m_AmmoIcons)
            return;

        for (int i = 0; i < m_AmmoIcons.Count(); i++)
        {
            ImageWidget ammoIcon = m_AmmoIcons.Get(i);
            if (!ammoIcon)
                continue;

            ammoIcon.LoadImageFile(0, "set:dayz_gui image:cartridge_shell");
            ammoIcon.LoadImageFile(1, "set:dayz_gui image:shell_shell");
            ammoIcon.LoadImageFile(2, "set:dayz_gui image:jam_shell");
        }
    }

    override void RefreshMuzzleIcon()
    {
        Weapon_Base host = Weapon_Base.Cast(GetObject());
        if (!host || (!host.IsKindOf("BDE_M203_StandAloneMount_Weapon") && !host.IsKindOf("BDE_FN40_StandaloneMount_Weapon")))
        {
            super.RefreshMuzzleIcon();
            return;
        }

        if (!m_AmmoIcons || m_AmmoIcons.Count() == 0)
            return;

        for (int i = 0; i < m_AmmoIcons.Count(); i++)
        {
            ImageWidget staleIcon = m_AmmoIcons.Get(i);
            if (staleIcon)
                staleIcon.Show(false);
        }

        BDE_M203 launcher = BDE_M203.Cast(host.BDE_USL_GetLauncher());
        if (!launcher || launcher.GetMuzzleCount() <= 0 || !launcher.IsChamberFull(0))
            return;

        ImageWidget ammoIcon = m_AmmoIcons.Get(0);
        if (!ammoIcon)
            return;

        ammoIcon.Show(true);

        if (launcher.IsJammed())
            ammoIcon.SetImage(2);
        else if (launcher.IsChamberFiredOut(0))
            ammoIcon.SetImage(1);
        else
            ammoIcon.SetImage(0);
    }
}
