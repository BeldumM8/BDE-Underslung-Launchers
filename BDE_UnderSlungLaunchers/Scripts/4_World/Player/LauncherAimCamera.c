modded class DayZPlayerImplement
{
    override int CameraHandler(int pCameraMode)
    {
        Weapon_Base host = Weapon_Base.Cast(GetEntityInHands());

        if (host && host.BDE_USL_IsGrozaLauncherADSBlocked())
        {
            m_CameraOptics = false;
            m_CameraIronsight = false;
        }

        if (!m_LiftWeapon_player && !IsWeaponObstructionBlockingADS() && host && host.BDE_USL_ShouldUseLauncherAimView())
        {
            if (m_CameraOptics || m_CameraIronsight)
                return DayZPlayerCameras.DAYZCAMERA_IRONSIGHTS;
        }

        return super.CameraHandler(pCameraMode);
    }

    override void HandleWeapons(float pDt, Entity pInHands, HumanInputController pInputs, out bool pExitIronSights)
    {
        Weapon_Base host = Weapon_Base.Cast(pInHands);
        BDE_UnderSlungLauncher_Base launcher;
        bool launcherModeSelected = false;
        bool zeroingUp = false;
        bool zeroingDown = false;
        ItemOptics attachedOptic;
        int opticZeroingStep = -1;
        ref array<int> hostZeroingSteps = new array<int>;

        bool grozaLauncherMode = false;
        if (host && host.BDE_USL_IsLauncherModeSelected())
        {
            launcher = host.BDE_USL_GetLauncher();
            grozaLauncherMode = launcher && launcher.IsKindOf("BDE_OTS14_Launcher") && !host.GetAttachedOptics();
        }

        if (host && pInputs && host.BDE_USL_IsLauncherModeSelected() && (host.BDE_USL_ShouldUseLauncherAimView() || grozaLauncherMode))
        {
            launcher = host.BDE_USL_GetLauncher();
            launcherModeSelected = launcher && (launcher == host || launcher.GetHierarchyParent() == host);

            if (launcherModeSelected)
            {
                zeroingUp = pInputs.IsZeroingUp();
                zeroingDown = pInputs.IsZeroingDown();

                if (zeroingUp || zeroingDown)
                {
                    attachedOptic = host.GetAttachedOptics();

                    if (attachedOptic)
                        opticZeroingStep = attachedOptic.GetStepZeroing();

                    for (int muzzleIndex = 0; muzzleIndex < host.GetMuzzleCount(); muzzleIndex++)
                        hostZeroingSteps.Insert(host.GetStepZeroing(muzzleIndex));
                }
            }
        }

        super.HandleWeapons(pDt, pInHands, pInputs, pExitIronSights);

        if (host && host.BDE_USL_IsGrozaLauncherADSBlocked())
        {
            pExitIronSights = true;
            m_CameraOptics = false;
            m_CameraIronsight = false;
        }

        if (!launcherModeSelected || (!zeroingUp && !zeroingDown))
            return;

        if (attachedOptic && host.GetAttachedOptics() == attachedOptic && opticZeroingStep >= 0)
            attachedOptic.SetStepZeroing(opticZeroingStep);

        for (int restoreMuzzle = 0; restoreMuzzle < hostZeroingSteps.Count() && restoreMuzzle < host.GetMuzzleCount(); restoreMuzzle++)
        {
            if (hostZeroingSteps[restoreMuzzle] >= 0)
                host.SetStepZeroing(restoreMuzzle, hostZeroingSteps[restoreMuzzle]);
        }

        if (!host.BDE_USL_IsLauncherModeSelected() || host.BDE_USL_GetLauncher() != launcher)
            return;

        if (zeroingUp)
            launcher.BDE_USL_StepAimZeroingUp();

        if (zeroingDown)
            launcher.BDE_USL_StepAimZeroingDown();
    }
}

modded class DayZPlayerCameraIronsights
{
    protected bool m_BDE_USL_WasLauncherAimView;

    protected bool m_BDE_USL_SmoothReady;
    protected Weapon_Base m_BDE_USL_SmoothHost;
    protected BDE_UnderSlungLauncher_Base m_BDE_USL_SmoothLauncher;
    protected float m_BDE_USL_SmoothZero;
    protected vector m_BDE_USL_SmoothTM[4];

    protected void BDE_USL_SmoothSightOffset(float dt, inout vector sightTM[4])
    {
        Weapon_Base host = Weapon_Base.Cast(m_pPlayer.GetEntityInHands());
        BDE_UnderSlungLauncher_Base launcher;
        if (host)
            launcher = host.BDE_USL_GetLauncher();
        if (!launcher)
        {
            m_BDE_USL_SmoothReady = false;
            return;
        }

        float zero = launcher.BDE_USL_GetCurrentAimZeroing();
        bool reset = !m_BDE_USL_SmoothReady || host != m_BDE_USL_SmoothHost || launcher != m_BDE_USL_SmoothLauncher || zero != m_BDE_USL_SmoothZero || dt > 0.25;
        if (!reset)
            reset = vector.DistanceSq(sightTM[3], m_BDE_USL_SmoothTM[3]) > 0.0625 || vector.Dot(sightTM[2], m_BDE_USL_SmoothTM[2]) < 0.5;

        float alpha = 1.0;
        if (!reset)
            alpha = 1.0 - Math.Pow(Math.EULER, -Math.Max(dt, 0.0) / 0.060);

        vector forward = sightTM[2];
        vector up = sightTM[1];
        vector position = sightTM[3];
        if (!reset)
        {
            forward = m_BDE_USL_SmoothTM[2] + (forward - m_BDE_USL_SmoothTM[2]) * alpha;
            up = m_BDE_USL_SmoothTM[1] + (up - m_BDE_USL_SmoothTM[1]) * alpha;
            position = m_BDE_USL_SmoothTM[3] + (position - m_BDE_USL_SmoothTM[3]) * alpha;
        }
        forward.Normalize();
        up = up - forward * vector.Dot(up, forward);
        up.Normalize();
        Math3D.DirectionAndUpMatrix(forward, up, m_BDE_USL_SmoothTM);
        m_BDE_USL_SmoothTM[3] = position;
        for (int i = 0; i < 4; i++)
            sightTM[i] = m_BDE_USL_SmoothTM[i];
        m_BDE_USL_SmoothHost = host;
        m_BDE_USL_SmoothLauncher = launcher;
        m_BDE_USL_SmoothZero = zero;
        m_BDE_USL_SmoothReady = true;
    }

    protected bool BDE_USL_GetLauncherAimHost(out Weapon_Base host)
    {
        host = Weapon_Base.Cast(m_pPlayer.GetEntityInHands());
        return host && host.BDE_USL_ShouldUseLauncherAimView();
    }

    override EntityAI GetCurrentSightEntity()
    {
        Weapon_Base host;

        if (BDE_USL_GetLauncherAimHost(host))
        {
            if (host.BDE_USL_IsStandaloneM203IronSightActive())
                return host;

            return host.BDE_USL_GetLauncher();
        }

        return super.GetCurrentSightEntity();
    }

    override bool GetCurrentSightInfo(out vector camPos, out vector camDir)
    {
        Weapon_Base host;

        if (BDE_USL_GetLauncherAimHost(host))
            return host.BDE_USL_GetLauncherAimCameraPoint(camPos, camDir);

        return super.GetCurrentSightInfo(camPos, camDir);
    }

    protected bool BDE_USL_GetSightCamera130(float pDt, vector cameraWorldTM[4], out vector cameraTM[4])
    {
        Weapon_Base host = Weapon_Base.Cast(m_pPlayer.GetEntityInHands());
        HumanItemAccessor accessor = m_pPlayer.GetItemAccessor();
        if (!host || !accessor)
        {
            return false;
        }

        // Cancel the rendered host pose before asking the native camera code
        // for its bone-relative frame. Do not mix render and simulation bones.
        vector hostWorldTM[4];
        host.GetRenderTransform(hostWorldTM);
        vector sightLocalTM[4];
        Math3D.MatrixInvMultiply4(hostWorldTM, cameraWorldTM, sightLocalTM);
        vector sightBoneTM[4];
        if (!accessor.WeaponGetCameraPointBoneRelative(host, sightLocalTM[3], sightLocalTM[2], m_iBoneIndex, sightBoneTM))
        {
            return false;
        }

        // Track the live sight pose, filtering only its hand-relative offset.
        // Apply aiming/recoil afterwards so player input stays responsive.
        BDE_USL_SmoothSightOffset(pDt, sightBoneTM);

        // Match 1.30 ironsights: apply the aiming model once in camera space.
        vector aimingTM[4];
        Math3D.MatrixIdentity4(aimingTM);
        accessor.WeaponGetAimingModelDirTm(aimingTM);
        Math3D.MatrixMultiply4(aimingTM, sightBoneTM, cameraTM);
        return true;
    }

    protected bool BDE_USL_UpdateGP25WorldSightCamera(float pDt, BDE_GP25 gp25, out DayZPlayerCameraResult pOutResult)
    {
        vector cameraPositionWS;
        vector cameraDirectionPointWS;
        vector cameraUpWS;

        if (!gp25 || !gp25.BDE_GP25_GetVirtualSightCameraWS(cameraPositionWS, cameraDirectionPointWS, cameraUpWS))
            return false;

        vector cameraDirectionWS = cameraDirectionPointWS - cameraPositionWS;
        float directionLength = cameraDirectionWS.Length();

        if (directionLength <= 0.000001)
            return false;

        cameraDirectionWS = cameraDirectionWS * (1.0 / directionLength);

        float minPitch;
        DayZPlayerImplement player = DayZPlayerImplement.Cast(g_Game.GetPlayer());
        if (player && player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE))
            minPitch = CONST_UD_MIN_BACK;
        else
            minPitch = CONST_UD_MIN;

        m_CurrentCameraYaw = UpdateLRAngleUnlocked(m_fLeftRightAngle, m_fLeftRightAngleAdd, CONST_LR_MIN, CONST_LR_MAX, pDt);
        m_CurrentCameraPitch = UpdateUDAngleUnlocked(m_fUpDownAngle, m_fUpDownAngleAdd, minPitch, CONST_UD_MAX, pDt);

        vector cameraWorldTM[4];
        Math3D.DirectionAndUpMatrix(cameraDirectionWS, cameraUpWS, cameraWorldTM);
        cameraWorldTM[3] = cameraPositionWS;

        vector cameraHandRelativeTM[4];
        if (!BDE_USL_GetSightCamera130(pDt, cameraWorldTM, cameraHandRelativeTM))
        {
            return false;
        }

        pOutResult.m_CameraTM[0] = cameraHandRelativeTM[0];
        pOutResult.m_CameraTM[1] = cameraHandRelativeTM[1];
        pOutResult.m_CameraTM[2] = cameraHandRelativeTM[2];
        pOutResult.m_CameraTM[3] = cameraHandRelativeTM[3];

        AdjustCameraParameters(pDt, pOutResult);
        pOutResult.m_iDirectBone = m_iBoneIndex;
        pOutResult.m_iDirectBoneMode = 4;
        pOutResult.m_fUseHeading = 0.0;

        UpdateCameraNV(PlayerBase.Cast(m_pPlayer));

        if (m_CameraShake)
        {
            float shakeX;
            float shakeY;
            m_CameraShake.Update(pDt, shakeX, shakeY);
            DayZPlayerImplement.Cast(m_pPlayer).GetAimingModel().SetCamShakeValues(shakeX, shakeY);
        }

        return true;
    }

    protected bool BDE_USL_UpdateM203RailWorldSightCamera(float pDt, BDE_M203 m203, out DayZPlayerCameraResult pOutResult)
    {
        vector cameraPositionWS;
        vector cameraDirectionPointWS;
        vector cameraUpWS;

        if (!m203 || !m203.BDE_M203_GetRailSightCameraWS(cameraPositionWS, cameraDirectionPointWS, cameraUpWS))
            return false;

        vector cameraDirectionWS = cameraDirectionPointWS - cameraPositionWS;
        float directionLength = cameraDirectionWS.Length();

        if (directionLength <= 0.000001)
            return false;

        cameraDirectionWS = cameraDirectionWS * (1.0 / directionLength);

        float minPitch;
        DayZPlayerImplement player = DayZPlayerImplement.Cast(g_Game.GetPlayer());
        if (player && player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE))
            minPitch = CONST_UD_MIN_BACK;
        else
            minPitch = CONST_UD_MIN;

        m_CurrentCameraYaw = UpdateLRAngleUnlocked(m_fLeftRightAngle, m_fLeftRightAngleAdd, CONST_LR_MIN, CONST_LR_MAX, pDt);
        m_CurrentCameraPitch = UpdateUDAngleUnlocked(m_fUpDownAngle, m_fUpDownAngleAdd, minPitch, CONST_UD_MAX, pDt);

        vector cameraWorldTM[4];
        Math3D.DirectionAndUpMatrix(cameraDirectionWS, cameraUpWS, cameraWorldTM);
        cameraWorldTM[3] = cameraPositionWS;

        vector cameraHandRelativeTM[4];
        if (!BDE_USL_GetSightCamera130(pDt, cameraWorldTM, cameraHandRelativeTM))
        {
            return false;
        }

        pOutResult.m_CameraTM[0] = cameraHandRelativeTM[0];
        pOutResult.m_CameraTM[1] = cameraHandRelativeTM[1];
        pOutResult.m_CameraTM[2] = cameraHandRelativeTM[2];
        pOutResult.m_CameraTM[3] = cameraHandRelativeTM[3];

        AdjustCameraParameters(pDt, pOutResult);
        pOutResult.m_iDirectBone = m_iBoneIndex;
        pOutResult.m_iDirectBoneMode = 4;
        pOutResult.m_fUseHeading = 0.0;

        UpdateCameraNV(PlayerBase.Cast(m_pPlayer));

        if (m_CameraShake)
        {
            float shakeX;
            float shakeY;
            m_CameraShake.Update(pDt, shakeX, shakeY);
            DayZPlayerImplement.Cast(m_pPlayer).GetAimingModel().SetCamShakeValues(shakeX, shakeY);
        }

        return true;
    }

    protected bool BDE_USL_UpdateFN40WorldSightCamera(float pDt, Weapon_Base host, out DayZPlayerCameraResult pOutResult)
    {
        vector cameraPositionWS;
        vector cameraDirectionPointWS;
        vector cameraUpWS;

        if (!host || !host.BDE_USL_GetFN40SightCameraWS(cameraPositionWS, cameraDirectionPointWS, cameraUpWS))
            return false;

        vector cameraDirectionWS = cameraDirectionPointWS - cameraPositionWS;
        float directionLength = cameraDirectionWS.Length();

        if (directionLength <= 0.000001)
            return false;

        cameraDirectionWS = cameraDirectionWS * (1.0 / directionLength);

        float minPitch;
        DayZPlayerImplement player = DayZPlayerImplement.Cast(g_Game.GetPlayer());
        if (player && player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE))
            minPitch = CONST_UD_MIN_BACK;
        else
            minPitch = CONST_UD_MIN;

        m_CurrentCameraYaw = UpdateLRAngleUnlocked(m_fLeftRightAngle, m_fLeftRightAngleAdd, CONST_LR_MIN, CONST_LR_MAX, pDt);
        m_CurrentCameraPitch = UpdateUDAngleUnlocked(m_fUpDownAngle, m_fUpDownAngleAdd, minPitch, CONST_UD_MAX, pDt);

        vector cameraWorldTM[4];
        Math3D.DirectionAndUpMatrix(cameraDirectionWS, cameraUpWS, cameraWorldTM);
        cameraWorldTM[3] = cameraPositionWS;

        vector cameraHandRelativeTM[4];
        if (!BDE_USL_GetSightCamera130(pDt, cameraWorldTM, cameraHandRelativeTM))
        {
            return false;
        }

        pOutResult.m_CameraTM[0] = cameraHandRelativeTM[0];
        pOutResult.m_CameraTM[1] = cameraHandRelativeTM[1];
        pOutResult.m_CameraTM[2] = cameraHandRelativeTM[2];
        pOutResult.m_CameraTM[3] = cameraHandRelativeTM[3];

        AdjustCameraParameters(pDt, pOutResult);
        pOutResult.m_fNearPlane = 0.001;
        pOutResult.m_iDirectBone = m_iBoneIndex;
        pOutResult.m_iDirectBoneMode = 4;
        pOutResult.m_fUseHeading = 0.0;

        UpdateCameraNV(PlayerBase.Cast(m_pPlayer));

        if (m_CameraShake)
        {
            float shakeX;
            float shakeY;
            m_CameraShake.Update(pDt, shakeX, shakeY);
            DayZPlayerImplement.Cast(m_pPlayer).GetAimingModel().SetCamShakeValues(shakeX, shakeY);
        }

        return true;
    }

    override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult)
    {
        Weapon_Base host;
        bool launcherAimView = BDE_USL_GetLauncherAimHost(host);

        if (launcherAimView)
        {
            BDE_GP25 gp25 = BDE_GP25.Cast(host.BDE_USL_GetLauncher());

            if (gp25)
            {
                gp25.BDE_GP25_UpdateSightVisual(true);

                if (BDE_USL_UpdateGP25WorldSightCamera(pDt, gp25, pOutResult))
                {
                    m_BDE_USL_WasLauncherAimView = true;
                    return;
                }
            }

            if (BDE_USL_UpdateFN40WorldSightCamera(pDt, host, pOutResult))
            {
                m_BDE_USL_WasLauncherAimView = true;
                return;
            }

            BDE_M203 m203 = BDE_M203.Cast(host.BDE_USL_GetLauncher());

            if (m203 && !host.IsKindOf("BDE_M203_StandAloneMount_Weapon") && !host.IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
            {
                if (BDE_USL_UpdateM203RailWorldSightCamera(pDt, m203, pOutResult))
                {
                    m_BDE_USL_WasLauncherAimView = true;
                    return;
                }
            }

            vector launcherCamPos;
            vector launcherCamDir;

            if (host.BDE_USL_GetLauncherAimCameraPoint(launcherCamPos, launcherCamDir))
            {
                m_OpticsCamPos = launcherCamPos;
                m_OpticsCamDir = launcherCamDir;
            }
        }
        else if (m_BDE_USL_WasLauncherAimView)
        {
            if (host)
            {
                BDE_GP25 previousGP25 = BDE_GP25.Cast(host.BDE_USL_GetLauncher());

                if (previousGP25)
                    previousGP25.BDE_GP25_UpdateSightVisual(false);
            }

            super.GetCurrentSightInfo(m_OpticsCamPos, m_OpticsCamDir);
        }

        m_BDE_USL_SmoothReady = false;
        m_BDE_USL_WasLauncherAimView = launcherAimView;
        super.OnUpdate(pDt, pOutResult);
    }

    override void SetCameraPP(bool state, DayZPlayerCamera launchedFrom)
    {
        m_BDE_USL_SmoothReady = false;
        super.SetCameraPP(state, launchedFrom);

        Weapon_Base host = Weapon_Base.Cast(m_pPlayer.GetEntityInHands());

        if (!state)
        {
            if (host)
            {
                BDE_GP25 gp25 = BDE_GP25.Cast(host.BDE_USL_GetLauncher());

                if (gp25)
                    gp25.BDE_GP25_UpdateSightVisual(false);
            }

            return;
        }

        if (!host || !host.BDE_USL_ShouldUseLauncherAimView())
            return;

        temp_array = {false, 0.0, 0.0, 0.0, 0.0, 1.0};

        if (m_RequesterADS)
            m_RequesterADS.SetValuesIronsights(temp_array);

        if (m_weaponUsed)
            m_weaponUsed.HideWeaponBarrel(false);
    }
}
