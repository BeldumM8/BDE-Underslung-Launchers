#ifdef S_GUNPLAY
modded class DayZPlayerCameraIronsights
{
    override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult)
    {
        super.OnUpdate(pDt, pOutResult);

        Weapon_Base host;

        if (BDE_USL_GetLauncherAimHost(host) && m_RequesterADS)
            m_RequesterADS.BDE_USL_ResetLauncherPiP();
    }

    override protected void computeDeadzone(float aimChangeX, float aimChangeY, out float deadzoneX, out float deadzoneY, float pDt)
    {
        Weapon_Base host;

        if (m_pPlayer)
            host = Weapon_Base.Cast(m_pPlayer.GetEntityInHands());

        if (host && (host.IsKindOf("BDE_M203_StandAloneMount_Weapon") || host.IsKindOf("BDE_FN40_StandaloneMount_Weapon")) && host.BDE_USL_ShouldUseLauncherAimView())
        {
            super.computeDeadzone(aimChangeX, aimChangeY, deadzoneX, deadzoneY, pDt);
            return;
        }

        if (BDE_USL_GetLauncherAimHost(host))
        {
            deadzoneX = 0.0;
            deadzoneY = 0.0;
            m_offsetXResetVel[0] = 0.0;
            m_offsetYResetVel[0] = 0.0;
            return;
        }

        super.computeDeadzone(aimChangeX, aimChangeY, deadzoneX, deadzoneY, pDt);
    }

    override void SetCameraPP(bool state, DayZPlayerCamera launchedFrom)
    {
        super.SetCameraPP(state, launchedFrom);

        Weapon_Base host;

        if (state && BDE_USL_GetLauncherAimHost(host) && m_RequesterADS)
            m_RequesterADS.BDE_USL_ResetLauncherPiP();
    }
}

modded class DayZPlayerCameraOptics
{
    override protected void updateLens(float pDt)
    {
        Weapon_Base host;

        if (m_player)
            host = Weapon_Base.Cast(m_player.GetItemInHands());

        if (host && host.BDE_USL_ShouldUseLauncherAimView())
        {
            if (m_RequesterADS)
                m_RequesterADS.BDE_USL_ResetLauncherPiP();

            return;
        }

        super.updateLens(pDt);
    }
}
#endif
