class BDE_USL_M203_ReloadAnimationCallback extends HumanCommandActionCallback
{
    void BDE_USL_M203_ReloadAnimationCallback()
    {
        EnableCancelCondition(false);
    }

    override void OnFinish(bool pCanceled)
    {
        PlayerBase player = PlayerBase.Cast(GetHuman());

        if (player)
            player.BDE_USL_OnManipulationAnimationFinished(pCanceled);
    }
}

class BDE_USL_M203_UnloadAnimationCallback extends HumanCommandActionCallback
{
    void BDE_USL_M203_UnloadAnimationCallback()
    {
        EnableCancelCondition(false);
    }

    override void OnFinish(bool pCanceled)
    {
        PlayerBase player = PlayerBase.Cast(GetHuman());

        if (player)
            player.BDE_USL_OnManipulationAnimationFinished(pCanceled);
    }
}

class BDE_USL_GP25_ReloadAnimationCallback extends HumanCommandActionCallback
{
    void BDE_USL_GP25_ReloadAnimationCallback()
    {
        EnableCancelCondition(false);
    }

    override void OnFinish(bool pCanceled)
    {
        PlayerBase player = PlayerBase.Cast(GetHuman());

        if (player)
            player.BDE_USL_OnManipulationAnimationFinished(pCanceled);
    }
}

class BDE_USL_GP25_UnloadAnimationCallback extends HumanCommandActionCallback
{
    void BDE_USL_GP25_UnloadAnimationCallback()
    {
        EnableCancelCondition(false);
    }

    override void OnFinish(bool pCanceled)
    {
        PlayerBase player = PlayerBase.Cast(GetHuman());

        if (player)
            player.BDE_USL_OnManipulationAnimationFinished(pCanceled);
    }
}

modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_SETTINGS_SYNC)
        {
            Param6<string, string, string, string, string, int> settingsData;

            if (!ctx.Read(settingsData))
                return;

            if (GetGame().IsClient())
                BDE_USL_SettingsManager.ApplyClientSettings(settingsData.param1, settingsData.param2, settingsData.param3, settingsData.param4, settingsData.param5, settingsData.param6);

            return;
        }

        super.OnRPC(sender, rpc_type, ctx);
    }

    protected bool m_BDE_USL_ManipulationStartPending;
    protected bool m_BDE_USL_ManipulationAnimationActive;
    protected bool m_BDE_USL_ManipulationRaiseOverrideActive;
    protected int m_BDE_USL_ManipulationLowerRequestTime;
    protected int m_BDE_USL_ManipulationAnimationStartTime;
    protected int m_BDE_USL_ManipulationActionType;
    protected int m_BDE_USL_ManipulationDurationMs;
    protected bool m_BDE_USL_ManipulationPlayGrenadeOut;
    protected string m_BDE_USL_ManipulationAmmoVisualType;
    protected Weapon_Base m_BDE_USL_ManipulationHost;
    protected BDE_UnderSlungLauncher_Base m_BDE_USL_ManipulationLauncher;
    protected Magazine m_BDE_USL_ManipulationReloadSource;
    protected EntityAI m_BDE_USL_ReloadCartridgeVisual;

    override bool PredictiveTakeEntityToTargetAttachment(notnull EntityAI target, notnull EntityAI item)
    {
        Weapon_Base host = Weapon_Base.Cast(target);
        BDE_UnderSlungLauncher_Base launcher = BDE_UnderSlungLauncher_Base.Cast(item);

        if (host && launcher)
        {
            int launcherSlotId = host.BDE_USL_GetConfiguredLauncherSlotId();

            if (launcherSlotId == InventorySlots.INVALID)
                return false;

            if (!host.CanReceiveAttachment(launcher, launcherSlotId))
                return false;

            return PredictiveTakeEntityToTargetAttachmentEx(target, item, launcherSlotId);
        }

        return super.PredictiveTakeEntityToTargetAttachment(target, item);
    }

    override bool PredictiveTakeEntityToTargetAttachmentEx(notnull EntityAI target, notnull EntityAI item, int slot)
    {
        Weapon_Base host = Weapon_Base.Cast(target);
        BDE_UnderSlungLauncher_Base launcher = BDE_UnderSlungLauncher_Base.Cast(item);

        if (host && launcher)
        {
            if (!host.BDE_USL_CanAttachLauncher(launcher, slot))
                return false;
        }
        else if (host && host.BDE_USL_IsCompatibleHost())
        {
            if (!host.CanReceiveAttachment(item, slot))
                return false;
        }

        return super.PredictiveTakeEntityToTargetAttachmentEx(target, item, slot);
    }

    BDE_UnderSlungLauncher_Base BDE_USL_GetManipulationLauncher()
    {
        BDE_M203 standaloneM203 = BDE_M203.Cast(GetItemInHands());

        if (standaloneM203)
            return standaloneM203;

        BDE_GP25 standaloneGP25 = BDE_GP25.Cast(GetItemInHands());

        if (standaloneGP25 && !Weapon_Base.Cast(standaloneGP25.GetHierarchyParent()))
            return standaloneGP25;

        Weapon_Base host = Weapon_Base.Cast(GetItemInHands());

        if (!host || !host.BDE_USL_IsLauncherModeSelected())
            return null;

        return host.BDE_USL_GetLauncher();
    }

    BDE_Six12 BDE_USL_GetManipulationSix12()
    {
        Weapon_Base host = Weapon_Base.Cast(GetItemInHands());
        if (!host)
            return null;

        BDE_Six12_StandAloneMount_Weapon standalone = BDE_Six12_StandAloneMount_Weapon.Cast(host);
        if (standalone)
            return standalone.BDE_Six12_GetBody();

        if (!host.BDE_USL_IsSix12ModeSelected())
            return null;

        return host.BDE_USL_GetSix12();
    }

    bool BDE_USL_ShouldOwnManipulationInput()
    {
        if (BDE_USL_GetManipulationLauncher())
            return true;
        return BDE_USL_GetManipulationSix12() != null;
    }

    void BDE_USL_ClearReloadCartridgeVisualSequence()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_ShowReloadCartridgeVisual);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_HideReloadCartridgeVisual);

        if (m_BDE_USL_ReloadCartridgeVisual)
        {
            GetGame().ObjectDelete(m_BDE_USL_ReloadCartridgeVisual);
            m_BDE_USL_ReloadCartridgeVisual = null;
        }
    }

    void BDE_USL_StartReloadCartridgeVisualSequence(string ammoType)
    {
        if (!GetGame().IsClient())
            return;

        BDE_USL_ClearReloadCartridgeVisualSequence();

        if (ammoType == "")
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ShowReloadCartridgeVisual, BDE_USL_M203_RELOAD_HAND_AMMO_MS, false, ammoType);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_HideReloadCartridgeVisual, BDE_USL_M203_RELOAD_INSERT_CLOSE_MS, false);
    }

    void BDE_USL_StartGP25ReloadCartridgeVisualSequence(string ammoType)
    {
        if (!GetGame().IsClient())
            return;

        BDE_USL_ClearReloadCartridgeVisualSequence();

        if (ammoType == "")
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ShowReloadCartridgeVisual, BDE_USL_GP25_RELOAD_HAND_AMMO_MS, false, ammoType);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_HideReloadCartridgeVisual, BDE_USL_GP25_RELOAD_GRENADE_IN_MS, false);
    }

    protected void BDE_USL_ShowReloadCartridgeVisual(string ammoType)
    {
        if (!GetGame().IsClient() || !IsAlive() || ammoType == "")
            return;

        BDE_USL_HideReloadCartridgeVisual();

        int handBone = GetBoneIndexByName(BDE_USL_M203_RELOAD_VISUAL_HAND_BONE);

        if (handBone < 0)
            return;

        Object visualObject = GetGame().CreateObjectEx(ammoType, vector.Zero, ECE_LOCAL | ECE_NOLIFETIME);
        EntityAI visualEntity = EntityAI.Cast(visualObject);

        if (!visualEntity)
        {
            if (visualObject)
                GetGame().ObjectDelete(visualObject);

            return;
        }

        visualEntity.SetTakeable(false);
        visualEntity.SetAllowDamage(false);

        vector localTransform[4];
        Math3D.YawPitchRollMatrix(BDE_USL_M203_RELOAD_VISUAL_HAND_ORIENTATION, localTransform);
        localTransform[3] = BDE_USL_M203_RELOAD_VISUAL_HAND_OFFSET;
        visualEntity.SetTransform(localTransform);

        AddChild(visualEntity, handBone, false);
        m_BDE_USL_ReloadCartridgeVisual = visualEntity;
    }

    protected void BDE_USL_HideReloadCartridgeVisual()
    {
        if (!m_BDE_USL_ReloadCartridgeVisual)
            return;

        GetGame().ObjectDelete(m_BDE_USL_ReloadCartridgeVisual);
        m_BDE_USL_ReloadCartridgeVisual = null;
    }

    protected void BDE_USL_ApplyManipulationRaiseOverride()
    {
        HumanInputController inputController = GetInputController();

        if (!inputController)
            return;

        inputController.ResetADS();
        inputController.OverrideRaise(HumanInputControllerOverrideType.ENABLED, false);
        m_BDE_USL_ManipulationRaiseOverrideActive = true;

        if (IsInIronsights() || IsInOptics())
            ExitSights();
    }

    protected void BDE_USL_ClearManipulationRaiseOverride()
    {
        if (!m_BDE_USL_ManipulationRaiseOverrideActive)
            return;

        HumanInputController inputController = GetInputController();

        if (inputController)
            inputController.OverrideRaise(HumanInputControllerOverrideType.DISABLED, false);

        m_BDE_USL_ManipulationRaiseOverrideActive = false;
    }

    protected void BDE_USL_ClientSendManipulationEjectAtFrame()
    {
        if (!GetGame().IsClient() || GetGame().GetPlayer() != this || !m_BDE_USL_ManipulationAnimationActive)
            return;

        BDE_UnderSlungLauncher_Base launcher = m_BDE_USL_ManipulationLauncher;

        if (!launcher || !m_BDE_USL_ManipulationPlayGrenadeOut)
            return;

        vector muzzleStart;
        vector muzzleEnd;

        if (!launcher.BDE_USL_GetProxyMuzzlePositions(muzzleStart, muzzleEnd))
            return;

        vector ejectPosition = muzzleStart;

        if (launcher.IsKindOf("BDE_GP25"))
            ejectPosition = muzzleEnd;

        vector ejectDirection = muzzleEnd - muzzleStart;

        if (ejectDirection.LengthSq() < 0.000001)
            return;

        ejectDirection.Normalize();
        launcher.BDE_USL_ClientRequestManipulationEject(m_BDE_USL_ManipulationActionType, ejectPosition, ejectDirection);
    }

    protected bool BDE_USL_StartManipulationAnimation()
    {
        if (!GetGame().IsClient() || GetGame().GetPlayer() != this)
            return false;

        Weapon_Base host = m_BDE_USL_ManipulationHost;
        BDE_UnderSlungLauncher_Base launcher = m_BDE_USL_ManipulationLauncher;

        if (!host || !launcher || GetItemInHands() != host)
            return false;

        bool standaloneGP25 = launcher.GetType() == "BDE_GP25" && host == launcher && !Weapon_Base.Cast(launcher.GetHierarchyParent());

        if (!standaloneGP25 && launcher.GetHierarchyParent() != host)
            return false;

        if (!launcher.BDE_USL_ShouldUseCustomManipulationAnimation())
            return false;

        if (IsRaised() || GetCommandModifier_Action())
            return false;

        bool isGP25 = launcher.IsKindOf("BDE_GP25");
        HumanCommandActionCallback callback;

        if (m_BDE_USL_ManipulationActionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
        {
            if (isGP25)
                callback = AddCommandModifier_Action(DayZPlayerConstants.CMD_ACTIONMOD_FISHINGRODRETRACT, BDE_USL_GP25_UnloadAnimationCallback);
            else
                callback = AddCommandModifier_Action(DayZPlayerConstants.CMD_ACTIONMOD_BATONRETRACT, BDE_USL_M203_UnloadAnimationCallback);
        }
        else
        {
            if (isGP25)
                callback = AddCommandModifier_Action(DayZPlayerConstants.CMD_ACTIONMOD_FISHINGRODEXTEND, BDE_USL_GP25_ReloadAnimationCallback);
            else
                callback = AddCommandModifier_Action(DayZPlayerConstants.CMD_ACTIONMOD_BATONEXTEND, BDE_USL_M203_ReloadAnimationCallback);
        }

        if (!callback)
            return false;

        m_BDE_USL_ManipulationAnimationActive = true;
        m_BDE_USL_ManipulationAnimationStartTime = GetGame().GetTime();
        launcher.BDE_USL_SetManipulationActive(true);

        BDE_M203 m203 = BDE_M203.Cast(launcher);
        BDE_GP25 gp25 = BDE_GP25.Cast(launcher);

        if (m203)
        {
            if (m_BDE_USL_ManipulationActionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
                m203.BDE_M203_StartUnloadTubeSequence(m_BDE_USL_ManipulationPlayGrenadeOut);
            else
                m203.BDE_M203_StartReloadTubeSequence(m_BDE_USL_ManipulationPlayGrenadeOut, m_BDE_USL_ManipulationAmmoVisualType);
        }
        else if (gp25)
        {
            if (m_BDE_USL_ManipulationActionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
                gp25.BDE_GP25_StartUnloadSequence(m_BDE_USL_ManipulationPlayGrenadeOut);
            else
                gp25.BDE_GP25_StartReloadSequence(m_BDE_USL_ManipulationAmmoVisualType);
        }

        if (m_BDE_USL_ManipulationPlayGrenadeOut)
        {
            int ejectDelay;

            if (isGP25)
                ejectDelay = BDE_USL_GP25_UNLOAD_GRENADE_OUT_MS;
            else if (m_BDE_USL_ManipulationActionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
                ejectDelay = BDE_USL_M203_UNLOAD_GRENADE_OUT_MS;
            else
                ejectDelay = BDE_USL_M203_RELOAD_GRENADE_OUT_MS;

            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ClientSendManipulationEjectAtFrame, ejectDelay, false);
        }

        launcher.BDE_USL_ClientRequestManipulation(m_BDE_USL_ManipulationActionType, m_BDE_USL_ManipulationReloadSource);
        return true;
    }

    protected void BDE_USL_AbortManipulationStart()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_ClientSendManipulationEjectAtFrame);

        BDE_UnderSlungLauncher_Base launcher = m_BDE_USL_ManipulationLauncher;

        if (launcher)
        {
            launcher.BDE_USL_SetManipulationActive(false);

            BDE_M203 m203 = BDE_M203.Cast(launcher);
            BDE_GP25 gp25 = BDE_GP25.Cast(launcher);

            if (m203)
                m203.BDE_M203_CancelReloadTubeSequence(true);
            else if (gp25)
                gp25.BDE_GP25_CancelReloadSequence();
        }

        m_BDE_USL_ManipulationStartPending = false;
        m_BDE_USL_ManipulationAnimationActive = false;
        m_BDE_USL_ManipulationLowerRequestTime = 0;
        m_BDE_USL_ManipulationAnimationStartTime = 0;
        m_BDE_USL_ManipulationActionType = BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_NONE;
        m_BDE_USL_ManipulationDurationMs = 0;
        m_BDE_USL_ManipulationPlayGrenadeOut = false;
        m_BDE_USL_ManipulationAmmoVisualType = "";
        m_BDE_USL_ManipulationHost = null;
        m_BDE_USL_ManipulationLauncher = null;
        m_BDE_USL_ManipulationReloadSource = null;
        BDE_USL_ClearReloadCartridgeVisualSequence();
        BDE_USL_ClearManipulationRaiseOverride();
    }

    protected void BDE_USL_UpdateManipulationState()
    {
        if (!m_BDE_USL_ManipulationStartPending && !m_BDE_USL_ManipulationAnimationActive)
            return;

        if (!GetGame().IsClient() || GetGame().GetPlayer() != this || !IsAlive())
        {
            BDE_USL_AbortManipulationStart();
            return;
        }

        Weapon_Base host = Weapon_Base.Cast(GetItemInHands());

        if (!host || host != m_BDE_USL_ManipulationHost)
        {
            BDE_USL_AbortManipulationStart();
            return;
        }

        BDE_UnderSlungLauncher_Base launcher;

        if (m_BDE_USL_ManipulationLauncher && host == m_BDE_USL_ManipulationLauncher && host.GetType() == "BDE_GP25")
            launcher = m_BDE_USL_ManipulationLauncher;
        else
            launcher = host.BDE_USL_GetLauncher();

        if (!launcher || launcher != m_BDE_USL_ManipulationLauncher || !launcher.BDE_USL_ShouldUseCustomManipulationAnimation())
        {
            BDE_USL_AbortManipulationStart();
            return;
        }

        BDE_USL_ApplyManipulationRaiseOverride();

        int now = GetGame().GetTime();

        if (m_BDE_USL_ManipulationAnimationActive)
        {
            if (m_BDE_USL_ManipulationAnimationStartTime > 0 && now - m_BDE_USL_ManipulationAnimationStartTime > m_BDE_USL_ManipulationDurationMs + BDE_USL_M203_FINISH_FAILSAFE_MS)
                BDE_USL_OnManipulationAnimationFinished(false);

            return;
        }

        if (now - m_BDE_USL_ManipulationLowerRequestTime > BDE_USL_M203_LOWER_TIMEOUT_MS)
        {
            BDE_USL_AbortManipulationStart();
            return;
        }

        if (IsRaised())
            return;

        HumanCommandWeapons weaponCommand = GetCommandModifier_Weapons();

        if (weaponCommand && weaponCommand.GetRunningAction() != -1 && !weaponCommand.IsActionFinished())
            return;

        if (GetCommandModifier_Action())
            return;

        if (BDE_USL_StartManipulationAnimation())
            m_BDE_USL_ManipulationStartPending = false;
    }

    void BDE_USL_OnManipulationAnimationFinished(bool canceled)
    {
        if (!m_BDE_USL_ManipulationAnimationActive && !m_BDE_USL_ManipulationRaiseOverrideActive)
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_ClientSendManipulationEjectAtFrame);

        BDE_UnderSlungLauncher_Base launcher = m_BDE_USL_ManipulationLauncher;

        if (launcher)
        {
            launcher.BDE_USL_SetManipulationActive(false);

            BDE_M203 m203 = BDE_M203.Cast(launcher);
            BDE_GP25 gp25 = BDE_GP25.Cast(launcher);

            if (m203)
                m203.BDE_M203_CancelReloadTubeSequence(true);
            else if (gp25)
                gp25.BDE_GP25_CancelReloadSequence();
        }

        m_BDE_USL_ManipulationStartPending = false;
        m_BDE_USL_ManipulationAnimationActive = false;
        m_BDE_USL_ManipulationLowerRequestTime = 0;
        m_BDE_USL_ManipulationAnimationStartTime = 0;
        m_BDE_USL_ManipulationActionType = BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_NONE;
        m_BDE_USL_ManipulationDurationMs = 0;
        m_BDE_USL_ManipulationPlayGrenadeOut = false;
        m_BDE_USL_ManipulationAmmoVisualType = "";
        m_BDE_USL_ManipulationHost = null;
        m_BDE_USL_ManipulationLauncher = null;
        m_BDE_USL_ManipulationReloadSource = null;
        BDE_USL_ClearReloadCartridgeVisualSequence();

        BDE_USL_ClearManipulationRaiseOverride();
    }

    bool BDE_USL_ClientBeginManipulation(BDE_UnderSlungLauncher_Base launcher, int actionType)
    {
        if (!GetGame().IsClient() || GetGame().GetPlayer() != this || !launcher)
            return false;

        if (!launcher.BDE_USL_ShouldUseCustomManipulationAnimation())
        {
            launcher.BDE_USL_ClientRequestManipulation(actionType);
            return true;
        }

        if (!IsPlayerInStance(DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT))
        {
            launcher.BDE_USL_ClientRequestManipulation(actionType);
            return true;
        }

        if (m_BDE_USL_ManipulationStartPending || m_BDE_USL_ManipulationAnimationActive || launcher.BDE_USL_IsManipulationActive() || GetCommandModifier_Action())
            return false;

        Weapon_Base host = Weapon_Base.Cast(launcher.GetHierarchyParent());
        bool standaloneGP25 = launcher.GetType() == "BDE_GP25" && !host && GetItemInHands() == launcher;

        if (standaloneGP25)
            host = launcher;
        else if (!host || GetItemInHands() != host || !host.BDE_USL_IsLauncherModeSelected() || host.BDE_USL_GetLauncher() != launcher)
            return false;

        int muzzleIndex = 0;

        if (launcher.GetMuzzleCount() <= muzzleIndex)
            return false;

        bool isGP25 = launcher.IsKindOf("BDE_GP25");
        bool playGrenadeOut = false;
        string ammoVisualType = "";
        m_BDE_USL_ManipulationReloadSource = null;

        if (actionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD)
        {
            if (launcher.BDE_USL_HasLiveRound())
                return false;

            Magazine source = launcher.BDE_USL_FindInventoryRoundForManipulation(this);

            if (!source)
                return false;

            if (!isGP25)
                playGrenadeOut = launcher.IsChamberFiredOut(muzzleIndex);

            ammoVisualType = source.GetType();
            m_BDE_USL_ManipulationReloadSource = source;

            if (isGP25)
                m_BDE_USL_ManipulationDurationMs = BDE_USL_GP25_RELOAD_TOTAL_MS;
            else
                m_BDE_USL_ManipulationDurationMs = BDE_USL_M203_RELOAD_TOTAL_MS;
        }
        else if (actionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
        {
            if (launcher.IsChamberEmpty(muzzleIndex))
                return false;

            if (isGP25)
            {
                playGrenadeOut = !launcher.IsChamberFiredOut(muzzleIndex);
                m_BDE_USL_ManipulationDurationMs = BDE_USL_GP25_UNLOAD_TOTAL_MS;
            }
            else
            {
                playGrenadeOut = true;
                m_BDE_USL_ManipulationDurationMs = BDE_USL_M203_UNLOAD_TOTAL_MS;
            }
        }
        else
        {
            return false;
        }

        m_BDE_USL_ManipulationActionType = actionType;
        m_BDE_USL_ManipulationPlayGrenadeOut = playGrenadeOut;
        m_BDE_USL_ManipulationAmmoVisualType = ammoVisualType;
        m_BDE_USL_ManipulationHost = host;
        m_BDE_USL_ManipulationLauncher = launcher;
        m_BDE_USL_ManipulationStartPending = true;
        m_BDE_USL_ManipulationLowerRequestTime = GetGame().GetTime();
        BDE_USL_ApplyManipulationRaiseOverride();
        BDE_USL_UpdateManipulationState();
        return true;
    }

    bool BDE_USL_ClientBeginSpecificReload(BDE_UnderSlungLauncher_Base launcher, Magazine source)
    {
        if (!GetGame().IsClient() || GetGame().GetPlayer() != this || !launcher || !source)
            return false;

        if (!launcher.BDE_USL_ShouldUseCustomManipulationAnimation())
            return false;

        if (m_BDE_USL_ManipulationStartPending || m_BDE_USL_ManipulationAnimationActive)
            return true;

        Weapon_Base host = Weapon_Base.Cast(launcher.GetHierarchyParent());
        bool standaloneGP25 = launcher.GetType() == "BDE_GP25" && !host && GetItemInHands() == launcher;

        if (standaloneGP25)
            host = launcher;
        else if (!host || GetItemInHands() != host || host.BDE_USL_GetLauncher() != launcher)
            return false;

        if (!IsPlayerInStance(DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT))
            return false;

        if (launcher.BDE_USL_HasLiveRound() || !launcher.BDE_USL_CanDirectLoadRound(source, false))
            return false;

        int muzzleIndex = 0;

        if (launcher.GetMuzzleCount() <= muzzleIndex)
            return false;

        bool isGP25 = launcher.IsKindOf("BDE_GP25");

        InventoryLocation sourceLocation = new InventoryLocation();
        if (source.GetInventory().GetCurrentInventoryLocation(sourceLocation) && sourceLocation.GetType() == InventoryLocationType.GROUND)
            launcher.BDE_USL_ClientReserveGroundRound(source);

        m_BDE_USL_ManipulationActionType = BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD;
        m_BDE_USL_ManipulationPlayGrenadeOut = !isGP25 && launcher.IsChamberFiredOut(muzzleIndex);
        m_BDE_USL_ManipulationAmmoVisualType = source.GetType();
        m_BDE_USL_ManipulationHost = host;
        m_BDE_USL_ManipulationLauncher = launcher;
        m_BDE_USL_ManipulationReloadSource = source;

        if (isGP25)
            m_BDE_USL_ManipulationDurationMs = BDE_USL_GP25_RELOAD_TOTAL_MS;
        else
            m_BDE_USL_ManipulationDurationMs = BDE_USL_M203_RELOAD_TOTAL_MS;

        m_BDE_USL_ManipulationStartPending = true;
        m_BDE_USL_ManipulationLowerRequestTime = GetGame().GetTime();
        BDE_USL_ApplyManipulationRaiseOverride();
        BDE_USL_UpdateManipulationState();
        return true;
    }

    override void HandleADS()
    {
        if (m_BDE_USL_ManipulationStartPending || m_BDE_USL_ManipulationAnimationActive)
        {
            BDE_USL_ApplyManipulationRaiseOverride();

            if (IsInIronsights() || IsInOptics())
                ExitSights();

            return;
        }

        super.HandleADS();
    }

    override void OnCommandHandlerTick(float delta_time, int pCurrentCommandID)
    {
        super.OnCommandHandlerTick(delta_time, pCurrentCommandID);

        if (!GetGame().IsClient() || GetGame().GetPlayer() != this)
            return;

        BDE_USL_UpdateManipulationState();
    }
}
