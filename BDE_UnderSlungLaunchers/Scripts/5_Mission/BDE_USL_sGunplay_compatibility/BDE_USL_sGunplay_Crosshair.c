#ifdef S_GUNPLAY
modded class SCrosshair
{
    override protected bool canShowDynamicCrosshair()
    {
        Weapon_Base host;
        if (BDE_USL_GetLauncherADSHost(host))
            return false;

        return super.canShowDynamicCrosshair();
    }

    override void onUpdate(float deltaTime)
    {
        super.onUpdate(deltaTime);

        Weapon_Base host;
        if (!BDE_USL_GetLauncherADSHost(host))
            return;

        if (m_dynamicCrosshair)
            m_dynamicCrosshair.Show(false);
    }

    protected bool BDE_USL_GetLauncherADSHost(out Weapon_Base host)
    {
        host = null;

        if (!m_player || !m_player.IsFireWeaponRaised())
            return false;

        if (!m_player.IsInIronsights() && !m_player.IsInOptics())
            return false;

        HumanInputController inputController = m_player.GetInputController();
        if (inputController && inputController.CameraIsFreeLook())
            return false;

        host = Weapon_Base.Cast(m_player.GetItemInHands());
        return host && host.BDE_USL_ShouldUseLauncherAimView();
    }
}
#endif
