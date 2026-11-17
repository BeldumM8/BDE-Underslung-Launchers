modded class CrossHairSelector
{
    override protected void SelectCrossHair()
    {
        if (BDE_USL_ShouldHideLauncherADSCrosshair())
        {
            ShowCrossHair(null);
            return;
        }

        super.SelectCrossHair();
    }

    protected bool BDE_USL_ShouldHideLauncherADSCrosshair()
    {
        if (!m_Player || !m_Player.IsPlayerSelected())
            return false;

        if (!m_Player.IsInIronsights() && !m_Player.IsInOptics())
            return false;

        HumanInputController inputController = m_Player.GetInputController();
        if (inputController && inputController.CameraIsFreeLook())
            return false;

        Weapon_Base host = Weapon_Base.Cast(m_Player.GetItemInHands());
        return host && host.BDE_USL_ShouldUseLauncherAimView();
    }
}
