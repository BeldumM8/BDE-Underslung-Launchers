class BDE_M203 extends BDE_UnderSlungLauncher_Base
{
    protected bool m_BDE_M203_TubeOpen;

    void BDE_M203()
    {
        m_BDE_M203_TubeOpen = false;
        RegisterNetSyncVariableBool("m_BDE_M203_TubeOpen");
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_M203_RequestButtPadRefresh();
        BDE_M203_QueueRailSightFoldRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_M203_RequestButtPadRefresh();
        BDE_M203_QueueRailSightFoldRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_M203_RequestButtPadRefresh();
        BDE_M203_QueueRailSightFoldRefresh();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();

        BDE_M203_ApplyTubeAnimation();
        BDE_M203_QueueRailSightFoldRefresh();
    }

    BDE_M203_Barrel BDE_M203_GetBarrel()
    {
        return BDE_M203_Barrel.Cast(FindAttachmentBySlotName("BDE_M203_Barrel"));
    }

    override vector BDE_USL_GetProxyMuzzleEndOffset()
    {
        vector muzzleEnd = super.BDE_USL_GetProxyMuzzleEndOffset();
        BDE_M203_Barrel barrel = BDE_M203_GetBarrel();
        if (!barrel || !barrel.IsKindOf("BDE_M203_Short_Barrel"))
            return muzzleEnd;

        vector boreDirection = muzzleEnd - super.BDE_USL_GetProxyMuzzleStartOffset();
        float boreLength = boreDirection.Length();
        if (boreLength > 0.06775825)
            muzzleEnd = muzzleEnd - (boreDirection * (0.06775825 / boreLength));
        return muzzleEnd;
    }

    BDE_M203_Rail_Adapter BDE_M203_GetRailAdapter()
    {
        return BDE_M203_Rail_Adapter.Cast(FindAttachmentBySlotName("BDE_M203_RailAdapter"));
    }

    BDE_M203_RearSight BDE_M203_GetRailRearSight()
    {
        BDE_M203_Rail_Adapter adapter = BDE_M203_GetRailAdapter();

        if (!adapter || adapter.IsSetForDeletion())
            return null;

        return adapter.BDE_M203_GetRearSight();
    }

    bool BDE_M203_HasRailSightSystem()
    {
        BDE_M203_Rail_Adapter adapter = BDE_M203_GetRailAdapter();

        if (!adapter || adapter.IsSetForDeletion())
            return false;

        BDE_M203_RearSight rearSight = adapter.BDE_M203_GetRearSight();

        if (!rearSight || rearSight.IsSetForDeletion())
            return false;

        return rearSight.FindAttachmentBySlotName("BDE_M203_FrontSight") != null;
    }

    void BDE_M203_QueueRailSightFoldRefresh()
    {
        BDE_M203_Rail_Adapter adapter = BDE_M203_GetRailAdapter();

        if (adapter)
            adapter.BDE_M203_QueueRearSightRefresh();
    }

    protected bool BDE_M203_ReadRailSightVector(string configName, out vector value)
    {
        value = vector.Zero;
        array<float> values = new array<float>;
        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " " + configName, values);

        if (values.Count() < 3)
            return false;

        value = Vector(values[0], values[1], values[2]);
        return true;
    }

    protected string BDE_M203_GetRailRearSightConfigName()
    {
        float zeroing = BDE_USL_GetCurrentAimZeroing();

        if (zeroing >= 225.0)
            return "BDE_M203_RailSightRear6";
        if (zeroing >= 175.0)
            return "BDE_M203_RailSightRear5";
        if (zeroing >= 125.0)
            return "BDE_M203_RailSightRear4";
        if (zeroing >= 75.0)
            return "BDE_M203_RailSightRear3";
        if (zeroing >= 25.0)
            return "BDE_M203_RailSightRear2";
        return "BDE_M203_RailSightRear1";
    }

    bool BDE_M203_GetRailSightPointsLS(out vector rearPoint, out vector frontPoint)
    {
        rearPoint = vector.Zero;
        frontPoint = vector.Zero;

        if (!BDE_M203_HasRailSightSystem())
            return false;

        if (!BDE_M203_ReadRailSightVector(BDE_M203_GetRailRearSightConfigName(), rearPoint))
            return false;

        return BDE_M203_ReadRailSightVector("BDE_M203_RailSightFront", frontPoint);
    }

    bool BDE_M203_GetRailSightCameraPoint(out vector cameraPosition, out vector cameraDirection)
    {
        cameraPosition = vector.Zero;
        cameraDirection = vector.Zero;

        vector rearPoint;
        vector frontPoint;

        if (!BDE_M203_GetRailSightPointsLS(rearPoint, frontPoint))
            return false;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!host || host.IsKindOf("BDE_M203_StandAloneMount_Weapon"))
            return false;

        vector slotPosition;
        vector slotOrientation;
        string slotName;

        if (BDE_USL_GetCurrentInventorySlotOffset(slotPosition, slotOrientation, slotName))
        {
            vector slotRotation[3];
            Math3D.YawPitchRollMatrix(slotOrientation, slotRotation);

            vector slotTransform[4];
            slotTransform[0] = slotRotation[0];
            slotTransform[1] = slotRotation[1];
            slotTransform[2] = slotRotation[2];
            slotTransform[3] = slotPosition;

            rearPoint = rearPoint.Multiply4(slotTransform);
            frontPoint = frontPoint.Multiply4(slotTransform);
        }

        cameraDirection = frontPoint - rearPoint;

        if (cameraDirection.LengthSq() < 0.000001)
            return false;

        cameraDirection.Normalize();

        float cameraBackOffset = GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " BDE_M203_RailSightCameraBackOffset");
        if (cameraBackOffset < 0.0)
            cameraBackOffset = 0.0;

        cameraPosition = rearPoint - (cameraDirection * cameraBackOffset);
        return true;
    }

    bool BDE_M203_GetRailSightCameraWS(out vector cameraPositionWS, out vector cameraDirectionPointWS, out vector cameraUpWS)
    {
        cameraPositionWS = vector.Zero;
        cameraDirectionPointWS = vector.Zero;
        cameraUpWS = vector.Zero;

        vector rearPointLS;
        vector frontPointLS;

        if (!BDE_M203_GetRailSightPointsLS(rearPointLS, frontPointLS))
            return false;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!host || host.IsKindOf("BDE_M203_StandAloneMount_Weapon"))
            return false;

        vector adjustedTransform[4];
        BDE_USL_GetAdjustedAttachmentTransform(adjustedTransform);

        vector rearPointWS = rearPointLS.Multiply4(adjustedTransform);
        vector frontPointWS = frontPointLS.Multiply4(adjustedTransform);
        vector upPointWS = (rearPointLS + vector.Up).Multiply4(adjustedTransform);
        vector sightDirectionWS = frontPointWS - rearPointWS;
        float directionLength = sightDirectionWS.Length();

        if (directionLength <= 0.000001)
            return false;

        sightDirectionWS = sightDirectionWS * (1.0 / directionLength);
        cameraUpWS = upPointWS - rearPointWS;
        cameraUpWS = cameraUpWS - (sightDirectionWS * vector.Dot(cameraUpWS, sightDirectionWS));
        float upLength = cameraUpWS.Length();

        if (upLength <= 0.000001)
            return false;

        cameraUpWS = cameraUpWS * (1.0 / upLength);

        float cameraBackOffset = GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " BDE_M203_RailSightCameraBackOffset");
        if (cameraBackOffset < 0.0)
            cameraBackOffset = 0.0;

        cameraPositionWS = rearPointWS - (sightDirectionWS * cameraBackOffset);
        cameraDirectionPointWS = frontPointWS;
        return true;
    }

    bool BDE_M203_HasBarrel()
    {
        BDE_M203_Barrel barrel = BDE_M203_GetBarrel();

        if (!barrel || barrel.IsSetForDeletion())
            return false;

        return true;
    }

    bool BDE_M203_HasUsableBarrel()
    {
        BDE_M203_Barrel barrel = BDE_M203_GetBarrel();

        if (!barrel || barrel.IsSetForDeletion() || barrel.IsRuined())
            return false;

        return true;
    }

    bool BDE_M203_CanUseButtPad()
    {
        return BDE_M203_HostSupportsButtPad();
    }

    void BDE_M203_NotifyHostButtstockChanged()
    {
        BDE_M203_RequestButtPadRefresh();
    }

    void BDE_M203_RequestButtPadRefresh()
    {
        if (!GetGame().IsServer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_RefreshButtPad);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_RefreshButtPad, 50, false);
    }

    protected void BDE_M203_RefreshButtPad()
    {
        EntityAI buttPad = FindAttachmentBySlotName("BDE_M203_ButtPad");
        if (!buttPad)
            return;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!host)
            return;

        string hostType = host.GetType();
        if (hostType != "AKM" && hostType != "AK74" && hostType != "AK101")
            return;

        string targetType = "BDE_USL_M203_ButtPad_VanillaAK";
        if (buttPad.GetType() == targetType)
            return;

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_USL_ButtPadSwapLambda lambda = new BDE_USL_ButtPadSwapLambda(buttPad, targetType, owner);
        lambda.SetTransferParams(true, true, false);
        buttPad.GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }

    protected bool BDE_M203_HostSupportsButtPad()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!host)
            return false;

        if (!host.IsKindOf("AKM_Base") && !host.IsKindOf("AK74_Base") && !host.IsKindOf("AK101_Base"))
            return false;

        EntityAI buttstock = host.FindAttachmentBySlotName("weaponButtstockAK");

        if (!buttstock)
            return false;

        return buttstock.IsKindOf("AK_PlasticBttstck");
    }

    void BDE_M203_NotifyHostOperationalStateChanged()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host)
            host.BDE_USL_RefreshLauncherModeState();
    }

    override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);
        BDE_M203_NotifyHostOperationalStateChanged();
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (parent && parent.IsKindOf("BDE_M203_StandAloneMount"))
            return true;

        return super.CanPutAsAttachment(parent);
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (FindAttachmentBySlotName("BDE_M203_ButtPad"))
            return false;

        return super.CanDetachAttachment(parent);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        string slotName = InventorySlots.GetSlotName(slotId);

        if (slotName == "BDE_M203_ButtPad")
        {
            if (!attachment || !attachment.IsKindOf("BDE_GP25_ButtPad") || !BDE_M203_CanUseButtPad())
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        if (slotName == "BDE_M203_RailAdapter")
        {
            if (!attachment || !attachment.IsKindOf("BDE_M203_Rail_Adapter"))
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        return super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (!super.CanDisplayAttachmentSlot(slot_id))
            return false;

        string slotName = InventorySlots.GetSlotName(slot_id);

        if (slotName == "BDE_M203_ButtPad")
        {
            if (FindAttachmentBySlotName("BDE_M203_ButtPad"))
                return true;

            return BDE_M203_CanUseButtPad();
        }

        return true;
    }

    override bool CanChamberBullet(int muzzleIndex, Magazine mag)
    {
        if (!BDE_M203_HasUsableBarrel())
            return false;

        return super.CanChamberBullet(muzzleIndex, mag);
    }

    override bool BDE_USL_CanDirectLoadRound(Magazine source, bool reservationCheck = true)
    {
        if (!BDE_M203_HasUsableBarrel())
            return false;

        return super.BDE_USL_CanDirectLoadRound(source, reservationCheck);
    }

    override Magazine BDE_USL_FindInventoryRoundForManipulation(PlayerBase player)
    {
        if (!BDE_M203_HasUsableBarrel())
            return null;

        return super.BDE_USL_FindInventoryRoundForManipulation(player);
    }

    override bool BDE_USL_CanFireAttachedFromHost(Weapon_Base host)
    {
        if (!super.BDE_USL_CanFireAttachedFromHost(host))
            return false;

        BDE_M203_Barrel barrel = BDE_M203_GetBarrel();

        if (!barrel || barrel.IsSetForDeletion() || barrel.IsRuined())
            return false;

        if (host && host.IsKindOf("BDE_M203_StandAloneMount_Weapon") && host.IsRuined())
            return false;

        return true;
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == "BDE_M203_Barrel")
        {
            BDE_M203_ApplyTubeAnimation();
            BDE_M203_NotifyHostOperationalStateChanged();
        }
        else if (slot_name == "BDE_M203_ButtPad")
        {
            BDE_M203_RequestButtPadRefresh();
        }
        else if (slot_name == "BDE_M203_RailAdapter")
        {
            BDE_M203_QueueRailSightFoldRefresh();
        }
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (slot_name == "BDE_M203_Barrel")
        {
            BDE_M203_CancelReloadTubeSequence(true);
            BDE_M203_NotifyHostOperationalStateChanged();
        }
        else if (slot_name == "BDE_M203_ButtPad")
        {
            BDE_M203_RequestButtPadRefresh();
        }
        else if (slot_name == "BDE_M203_RailAdapter")
        {
            BDE_M203_QueueRailSightFoldRefresh();
        }
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_M203_RequestButtPadRefresh();
        BDE_M203_QueueRailSightFoldRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        BDE_M203_CancelReloadTubeSequence(true);
        super.OnWasDetached(parent, slot_id);
        BDE_M203_RequestButtPadRefresh();
        BDE_M203_QueueRailSightFoldRefresh();
    }

    override void OnDebugSpawn()
    {
        if (!BDE_M203_HasBarrel())
            GetInventory().CreateAttachment("BDE_M203_Barrel");

        super.OnDebugSpawn();
    }

    bool BDE_M203_IsTubeOpen()
    {
        return m_BDE_M203_TubeOpen;
    }

    void BDE_M203_SetTubeOpen(bool open)
    {
        m_BDE_M203_TubeOpen = open;
        BDE_M203_ApplyTubeAnimation();

        if (GetGame().IsServer())
            SetSynchDirty();
    }

    protected void BDE_M203_ApplyTubeAnimation()
    {
        BDE_M203_Barrel barrel = BDE_M203_GetBarrel();

        if (!barrel)
            return;

        float targetPhase = 0.0;

        if (m_BDE_M203_TubeOpen)
            targetPhase = 1.0;

        barrel.SetAnimationPhase("m203_tube_open", targetPhase);
    }

    protected void BDE_M203_PlayReloadHandlingSound(string soundSet)
    {
        if (!GetGame().IsClient())
            return;

        EffectSound reloadSound = SEffectManager.PlaySound(soundSet, GetPosition());

        if (reloadSound)
            reloadSound.SetAutodestroy(true);
    }

    void BDE_M203_OpenTubeReloadStep()
    {
        BDE_M203_SetTubeOpen(true);
        BDE_M203_PlayReloadHandlingSound("BDE_M203_Reload_ChargeOpen_SoundSet");
    }

    void BDE_M203_PlayReloadGrenadeOutSound()
    {
        BDE_M203_PlayReloadHandlingSound("BDE_M203_Reload_GrenadeOut_SoundSet");
    }

    void BDE_M203_PlayReloadGrenadeInSound()
    {
        BDE_M203_PlayReloadHandlingSound("BDE_M203_Reload_GrenadeIn_SoundSet");
    }

    void BDE_M203_CloseTubeReloadStep()
    {
        BDE_M203_SetTubeOpen(false);
        BDE_M203_PlayReloadHandlingSound("BDE_M203_Reload_ChargeClose_SoundSet");
    }

    void BDE_M203_StartReloadTubeSequence(bool playGrenadeOut, string ammoVisualType = "")
    {
        if (!GetGame().IsClient())
            return;

        BDE_M203_CancelReloadTubeSequence(false);

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (player)
            player.BDE_USL_StartReloadCartridgeVisualSequence(ammoVisualType);

        BDE_M203_SetTubeOpen(false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_OpenTubeReloadStep, BDE_USL_M203_RELOAD_TUBE_OPEN_MS, false);

        if (playGrenadeOut)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_PlayReloadGrenadeOutSound, BDE_USL_M203_RELOAD_GRENADE_OUT_MS, false);

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_PlayReloadGrenadeInSound, BDE_USL_M203_RELOAD_GRENADE_IN_MS, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_CloseTubeReloadStep, BDE_USL_M203_RELOAD_INSERT_CLOSE_MS, false);
    }

    void BDE_M203_StartUnloadTubeSequence(bool playGrenadeOut)
    {
        if (!GetGame().IsClient())
            return;

        BDE_M203_CancelReloadTubeSequence(false);
        BDE_M203_SetTubeOpen(false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_OpenTubeReloadStep, BDE_USL_M203_UNLOAD_TUBE_OPEN_MS, false);

        if (playGrenadeOut)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_PlayReloadGrenadeOutSound, BDE_USL_M203_UNLOAD_GRENADE_OUT_MS, false);

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_CloseTubeReloadStep, BDE_USL_M203_UNLOAD_TUBE_CLOSE_MS, false);
    }

    void BDE_M203_CancelReloadTubeSequence(bool forceClosed = true)
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_OpenTubeReloadStep);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_PlayReloadGrenadeOutSound);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_PlayReloadGrenadeInSound);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_CloseTubeReloadStep);

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (player)
            player.BDE_USL_ClearReloadCartridgeVisualSequence();

        if (forceClosed)
            BDE_M203_SetTubeOpen(false);
    }

    vector BDE_M203_GetCasingEjectPosition()
    {
        return BDE_USL_LocalToWorld(BDE_M203_GetCasingEjectOffset());
    }

    vector BDE_M203_GetCasingEjectOffset()
    {
        array<float> values = new array<float>;

        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " BDE_USL_CasingEjectOffset", values);

        if (values.Count() < 3)
            return "0 0 0";

        return Vector(values[0], values[1], values[2]);
    }

    override bool CanBeCombined(EntityAI other_item, bool reservation_check = true, bool stack_max_limit = false)
    {
        Magazine source = Magazine.Cast(other_item);

        if (source && BDE_USL_CanDirectLoadRound(source, reservation_check))
            return true;

        return super.CanBeCombined(other_item, reservation_check, stack_max_limit);
    }

    override void CombineItems(ItemBase other_item, bool use_stack_max = true)
    {
        Magazine source = Magazine.Cast(other_item);

        if (source && BDE_USL_CanDirectLoadRound(source, false))
        {
            Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

            if (host && BDE_USL_ShouldUseAttachedM203Animation())
            {
                PlayerBase player = PlayerBase.Cast(host.GetHierarchyRootPlayer());

                if (GetGame().IsClient() && player && GetGame().GetPlayer() == player)
                    player.BDE_USL_ClientBeginSpecificReload(this, source);
                else if (GetGame().IsServer())
                    BDE_USL_ServerRequestOwnerSpecificReload(source);

                return;
            }

            if (GetGame().IsServer())
                BDE_USL_ServerLoadSpecificRound(source);

            return;
        }

        super.CombineItems(other_item, use_stack_max);
    }
}
