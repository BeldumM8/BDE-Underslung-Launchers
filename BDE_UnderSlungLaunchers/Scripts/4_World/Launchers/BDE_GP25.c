class BDE_GP25_TypeSwapLambda : TurnItemIntoItemLambda
{
    protected bool m_BDE_USL_HadLiveRound;
    protected float m_BDE_USL_ChamberDamage;
    protected string m_BDE_USL_ChamberAmmoType;
    protected string m_BDE_USL_ChamberSourceType;

    void BDE_GP25_TypeSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player, bool hadLiveRound, float chamberDamage, string chamberAmmoType, string chamberSourceType)
    {
        m_BDE_USL_HadLiveRound = hadLiveRound;
        m_BDE_USL_ChamberDamage = chamberDamage;
        m_BDE_USL_ChamberAmmoType = chamberAmmoType;
        m_BDE_USL_ChamberSourceType = chamberSourceType;
    }

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

        BDE_GP25 replacement = BDE_GP25.Cast(new_item);
        if (replacement)
            replacement.BDE_GP25_FinalizeTypeSwapChamber(m_BDE_USL_HadLiveRound, m_BDE_USL_ChamberDamage, m_BDE_USL_ChamberAmmoType, m_BDE_USL_ChamberSourceType);
    }
}

class BDE_GP25_SightSwapLambda : TurnItemIntoItemLambda
{
    void BDE_GP25_SightSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player)
    {
    }

    override protected bool CanExecuteLambda()
    {
        return m_OldItem != null;
    }
}

class BDE_GP25 extends BDE_UnderSlungLauncher_Base
{
    protected bool m_BDE_GP25_SightSwapInProgress;

    override bool BDE_USL_IsRoundAllowed(Magazine source)
    {
        return BDE_USL_SettingsManager.IsVOG25MagazineAllowed(source);
    }

    override bool CanChamberBullet(int muzzleIndex, Magazine mag)
    {
        if (!BDE_USL_SettingsManager.IsVOG25MagazineAllowed(mag))
            return false;

        if (mag && mag.IsKindOf("Ammo_VOG25"))
        {
            if (muzzleIndex < 0 || muzzleIndex >= GetMuzzleCount())
                return false;

            return IsChamberEmpty(muzzleIndex) || IsChamberFiredOut(muzzleIndex);
        }

        return super.CanChamberBullet(muzzleIndex, mag);
    }

    override bool CanFire()
    {
        if (!super.CanFire())
            return false;

        return BDE_USL_IsChamberAmmoAllowed(GetCurrentMuzzle());
    }

    protected void BDE_GP25_PlayReloadHandlingSound(string soundSet)
    {
        if (!GetGame().IsClient())
            return;

        EffectSound reloadSound = SEffectManager.PlaySound(soundSet, GetPosition());

        if (reloadSound)
            reloadSound.SetAutodestroy(true);
    }

    void BDE_GP25_PlayReloadGrenadeOutSound()
    {
        BDE_GP25_PlayReloadHandlingSound("BDE_M203_Reload_GrenadeOut_SoundSet");
    }

    void BDE_GP25_PlayReloadGrenadeInSound()
    {
        BDE_GP25_PlayReloadHandlingSound("BDE_M203_Reload_GrenadeIn_SoundSet");
    }

    void BDE_GP25_StartReloadSequence(string ammoVisualType = "")
    {
        if (!GetGame().IsClient())
            return;

        BDE_GP25_CancelReloadSequence();

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (player)
            player.BDE_USL_StartGP25ReloadCartridgeVisualSequence(ammoVisualType);

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_PlayReloadGrenadeInSound, BDE_USL_GP25_RELOAD_GRENADE_IN_MS, false);
    }

    void BDE_GP25_StartUnloadSequence(bool playGrenadeOut)
    {
        if (!GetGame().IsClient())
            return;

        BDE_GP25_CancelReloadSequence();

        if (playGrenadeOut)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_PlayReloadGrenadeOutSound, BDE_USL_GP25_UNLOAD_GRENADE_OUT_MS, false);
    }

    void BDE_GP25_CancelReloadSequence()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_PlayReloadGrenadeOutSound);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_PlayReloadGrenadeInSound);

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (player)
            player.BDE_USL_ClearReloadCartridgeVisualSequence();
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_GP25_RequestVariantRefresh();
        BDE_GP25_QueueAttachmentVisualRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_GP25_RequestVariantRefresh();
        BDE_GP25_QueueAttachmentVisualRefresh();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_GP25_QueueAttachmentVisualRefresh();
    }

    bool BDE_GP25_HasStandaloneButtStock()
    {
        return FindAttachmentBySlotName("BDE_GP25_ButtStock") != null;
    }

    bool BDE_GP25_CanUseButtPad()
    {
        return BDE_GP25_HostSupportsButtPad();
    }

    protected bool BDE_GP25_ParentHasCarrySlot(EntityAI parent)
    {
        if (!parent)
            return false;

        TStringArray attachmentSlots = new TStringArray;
        parent.ConfigGetTextArray("attachments", attachmentSlots);
        return attachmentSlots.Find("Shoulder") >= 0 || attachmentSlots.Find("Melee") >= 0;
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;

        if (BDE_GP25_ParentHasCarrySlot(parent))
            return true;

        if (BDE_GP25_HasStandaloneButtStock() && Weapon_Base.Cast(parent))
            return false;

        return super.CanPutAsAttachment(parent);
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (Weapon_Base.Cast(parent) && FindAttachmentBySlotName("BDE_GP25_ButtPad"))
            return false;

        return super.CanDetachAttachment(parent);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        string slotName = InventorySlots.GetSlotName(slotId);

        if (slotName == "BDE_GP25_Sight")
        {
            if (!attachment || !attachment.IsKindOf("BDE_GP25_Sight"))
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        if (slotName == "BDE_GP25_ButtPad")
        {
            if (!attachment || !attachment.IsKindOf("BDE_GP25_ButtPad") || !BDE_GP25_CanUseButtPad())
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        if (slotName == "BDE_GP25_ButtStock")
        {
            if (Weapon_Base.Cast(GetHierarchyParent()))
                return false;

            if (!attachment || !attachment.IsKindOf("BDE_GP25_ButtStock"))
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        return super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (!super.CanDisplayAttachmentSlot(slot_id))
            return false;

        string slot_name = InventorySlots.GetSlotName(slot_id);

        if (slot_name == "BDE_GP25_Sight")
            return false;

        if (slot_name == "BDE_GP25_ButtStock")
        {
            if (Weapon_Base.Cast(GetHierarchyParent()))
                return false;

            return true;
        }

        if (slot_name == "BDE_GP25_ButtPad")
        {
            if (FindAttachmentBySlotName("BDE_GP25_ButtPad"))
                return true;

            return BDE_GP25_CanUseButtPad();
        }

        return true;
    }

    override bool CanBeCombined(EntityAI other_item, bool reservation_check = true, bool stack_max_limit = false)
    {
        Magazine source = Magazine.Cast(other_item);

        if (source && BDE_USL_ShouldUseAttachedCustomAnimation() && BDE_USL_CanDirectLoadRound(source, reservation_check))
            return true;

        if (source && GetType() == "BDE_GP25" && !Weapon_Base.Cast(GetHierarchyParent()) && BDE_USL_CanDirectLoadRound(source, reservation_check))
            return true;

        return super.CanBeCombined(other_item, reservation_check, stack_max_limit);
    }

    override void CombineItems(ItemBase other_item, bool use_stack_max = true)
    {
        Magazine source = Magazine.Cast(other_item);

        if (source && BDE_USL_ShouldUseAttachedCustomAnimation() && BDE_USL_CanDirectLoadRound(source, false))
        {
            Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
            PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

            if (host && player)
            {
                if (GetGame().IsClient() && GetGame().GetPlayer() == player)
                    player.BDE_USL_ClientBeginSpecificReload(this, source);
                else if (GetGame().IsServer())
                    BDE_USL_ServerRequestOwnerSpecificReload(source);

                return;
            }
        }

        if (source && !Weapon_Base.Cast(GetHierarchyParent()) && BDE_USL_CanDirectLoadRound(source, false))
        {
            PlayerBase standalonePlayer = PlayerBase.Cast(GetHierarchyRootPlayer());

            if (GetGame().IsClient() && standalonePlayer && GetGame().GetPlayer() == standalonePlayer)
                standalonePlayer.BDE_USL_ClientBeginSpecificReload(this, source);
            else if (GetGame().IsServer())
                BDE_USL_ServerRequestOwnerSpecificReload(source);

            return;
        }

        super.CombineItems(other_item, use_stack_max);
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);

        BDE_GP25_RequestVariantRefresh();
        BDE_GP25_QueueAttachmentVisualRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        BDE_GP25_CancelReloadSequence();
        super.OnWasDetached(parent, slot_id);

        BDE_GP25_RequestVariantRefresh();
        BDE_GP25_QueueAttachmentVisualRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_GP25_RequestVariantRefresh();
        BDE_GP25_QueueAttachmentVisualRefresh();
    }

    void BDE_GP25_NotifyHostButtstockChanged()
    {
        BDE_GP25_RequestVariantRefresh();
    }

    void BDE_GP25_RequestVariantRefresh()
    {
        if (!GetGame().IsServer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_RefreshVariant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_RefreshVariant, 50, false);
    }

    void BDE_GP25_RefreshVariant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        BDE_GP25_RefreshIntegralSight();
        BDE_GP25_RefreshStandaloneButtStock();
        BDE_GP25_RefreshButtPad();
    }

    protected void BDE_GP25_RefreshIntegralSight()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        string targetSightType = "BDE_GP25_Sight";
        if (BDE_GP25_IsLauncherModeActive())
            targetSightType = "BDE_GP25_Sight_Unfolded";

        EntityAI sight = FindAttachmentBySlotName("BDE_GP25_Sight");

        if (!sight)
        {
            GetInventory().CreateAttachment(targetSightType);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_UpdateSightZeroVisual, 1, false);
            return;
        }

        if (sight.GetType() == targetSightType)
        {
            BDE_GP25_UpdateSightZeroVisual();
            return;
        }

        if (m_BDE_GP25_SightSwapInProgress)
            return;

        InventoryLocation sightLocation = new InventoryLocation();
        if (!sight.GetInventory().GetCurrentInventoryLocation(sightLocation) || !sightLocation.IsValid() || sightLocation.GetType() != InventoryLocationType.ATTACHMENT || sightLocation.GetParent() != this)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_RefreshIntegralSight);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_RefreshIntegralSight, 100, false);
            return;
        }

        m_BDE_GP25_SightSwapInProgress = true;

        BDE_GP25_SightSwapLambda lambda = new BDE_GP25_SightSwapLambda(sight, targetSightType, null);
        lambda.SetTransferParams(true, true, true);
        sight.GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_FinishSightSwapGuard);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_FinishSightSwapGuard, 100, false);
    }

    protected void BDE_GP25_FinishSightSwapGuard()
    {
        m_BDE_GP25_SightSwapInProgress = false;
        BDE_GP25_UpdateSightZeroVisual();
    }

    void BDE_GP25_RequestSightVariantRefresh()
    {
        if (!GetGame().IsServer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_RefreshIntegralSight);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_RefreshIntegralSight, 100, false);
    }

    bool BDE_GP25_IsSightSwapInProgress()
    {
        return m_BDE_GP25_SightSwapInProgress;
    }

    protected void BDE_GP25_RefreshStandaloneButtStock()
    {
        if (!Weapon_Base.Cast(GetHierarchyParent()))
            return;

        EntityAI buttStock = FindAttachmentBySlotName("BDE_GP25_ButtStock");

        if (buttStock)
            GetInventory().DropEntity(InventoryMode.SERVER, this, buttStock);
    }

    protected void BDE_GP25_RefreshButtPad()
    {
    }

    protected bool BDE_GP25_HostSupportsButtPad()
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

    void BDE_GP25_QueueAttachmentVisualRefresh()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_RefreshAttachmentVisuals);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_RefreshAttachmentVisuals, 1, false);
    }

    protected void BDE_GP25_RefreshAttachmentVisuals()
    {
        BDE_GP25_ButtStock buttStock = BDE_GP25_ButtStock.Cast(FindAttachmentBySlotName("BDE_GP25_ButtStock"));

        if (buttStock)
            buttStock.BDE_GP25_QueueStockRefresh();

        BDE_GP25_UpdateSightZeroVisual();
    }

    void BDE_GP25_UpdateSightZeroVisual()
    {
        BDE_GP25_Sight sight = BDE_GP25_Sight.Cast(FindAttachmentBySlotName("BDE_GP25_Sight"));

        if (!sight)
            return;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        bool launcherModeActive = false;
        float zeroPhase = 0.0;

        if (host)
            launcherModeActive = host.BDE_USL_IsLauncherModeSelected();
        else
            launcherModeActive = BDE_USL_IsLauncherModeSelected();

        if (launcherModeActive)
        {
            float maxSightAngle = BDE_USL_GetAimMaxAngle();
            float ballisticAngle = BDE_USL_CalculateLauncherAimAngle(this);

            if (maxSightAngle > 0.0)
                zeroPhase = Math.Clamp(ballisticAngle / maxSightAngle, 0.0, 1.0);
        }

        sight.BDE_GP25_SetZeroTarget(zeroPhase);
    }

    protected bool BDE_GP25_ReadVirtualSightVector(string configName, out vector value)
    {
        value = vector.Zero;
        array<float> values = new array<float>;
        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " " + configName, values);

        if (values.Count() < 3)
            return false;

        value = Vector(values[0], values[1], values[2]);
        return true;
    }

    bool BDE_GP25_GetVirtualSightPointsLS(out vector cameraPosition, out vector cameraDirectionPoint, out vector pivotStart, out vector pivotEnd)
    {
        cameraPosition = vector.Zero;
        cameraDirectionPoint = vector.Zero;
        pivotStart = vector.Zero;
        pivotEnd = vector.Zero;

        if (!BDE_GP25_ReadVirtualSightVector("BDE_GP25_VirtualSightCameraPos", cameraPosition))
            return false;

        if (!BDE_GP25_ReadVirtualSightVector("BDE_GP25_VirtualSightCameraDir", cameraDirectionPoint))
            return false;

        if (!BDE_GP25_ReadVirtualSightVector("BDE_GP25_VirtualSightPivotStart", pivotStart))
            return false;

        if (!BDE_GP25_ReadVirtualSightVector("BDE_GP25_VirtualSightPivotEnd", pivotEnd))
            return false;

        vector pivotAxis = pivotEnd - pivotStart;
        float pivotLength = pivotAxis.Length();

        if (pivotLength <= 0.000001)
            return false;

        pivotAxis = pivotAxis * (1.0 / pivotLength);

        BDE_GP25_Sight sight = BDE_GP25_Sight.Cast(FindAttachmentBySlotName("BDE_GP25_Sight"));
        float zeroPhase = 0.0;

        if (sight)
            zeroPhase = Math.Clamp(sight.GetAnimationPhase("gp25_sight_zero"), 0.0, 1.0);

        float zeroAngleRadians = (-BDE_USL_GetAimMaxAngle() * zeroPhase) * Math.DEG2RAD;
        float cosAngle = Math.Cos(zeroAngleRadians);
        float sinAngle = Math.Sin(zeroAngleRadians);

        cameraPosition = BDE_GP25_RotatePointAroundAxisSafe(pivotStart, cameraPosition, pivotAxis, cosAngle, sinAngle);
        cameraDirectionPoint = BDE_GP25_RotatePointAroundAxisSafe(pivotStart, cameraDirectionPoint, pivotAxis, cosAngle, sinAngle);
        return true;
    }

    protected vector BDE_GP25_RotatePointAroundAxisSafe(vector pivot, vector position, vector axis, float cosAngle, float sinAngle)
    {
        vector offset = position - pivot;

        float dotValue = (axis[0] * offset[0]) + (axis[1] * offset[1]) + (axis[2] * offset[2]);

        float crossX = (axis[1] * offset[2]) - (axis[2] * offset[1]);
        float crossY = (axis[2] * offset[0]) - (axis[0] * offset[2]);
        float crossZ = (axis[0] * offset[1]) - (axis[1] * offset[0]);
        vector crossValue = Vector(crossX, crossY, crossZ);

        vector rotatedOffset = (offset * cosAngle) + (crossValue * sinAngle) + (axis * (dotValue * (1.0 - cosAngle)));
        return pivot + rotatedOffset;
    }

    bool BDE_GP25_GetVirtualSightCameraPoint(out vector cameraPosition, out vector cameraDirection)
    {
        cameraPosition = vector.Zero;
        cameraDirection = vector.Zero;

        vector cameraDirectionPoint;
        vector pivotStart;
        vector pivotEnd;

        if (!BDE_GP25_GetVirtualSightPointsLS(cameraPosition, cameraDirectionPoint, pivotStart, pivotEnd))
            return false;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host)
        {
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

                cameraPosition = cameraPosition.Multiply4(slotTransform);
                cameraDirectionPoint = cameraDirectionPoint.Multiply4(slotTransform);
            }
        }

        cameraDirection = cameraDirectionPoint - cameraPosition;

        if (cameraDirection.LengthSq() < 0.000001)
            return false;

        cameraDirection.Normalize();

        float cameraBackOffset = GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " BDE_GP25_VirtualSightCameraBackOffset");
        if (cameraBackOffset < 0.0)
            cameraBackOffset = 0.0;

        cameraPosition = cameraPosition - (cameraDirection * cameraBackOffset);
        return true;
    }

    bool BDE_GP25_GetVirtualSightPointsWS(out vector cameraPositionWS, out vector cameraDirectionPointWS, out vector pivotStartWS, out vector pivotEndWS)
    {
        cameraPositionWS = vector.Zero;
        cameraDirectionPointWS = vector.Zero;
        pivotStartWS = vector.Zero;
        pivotEndWS = vector.Zero;

        vector cameraPositionLS;
        vector cameraDirectionPointLS;
        vector pivotStartLS;
        vector pivotEndLS;

        if (!BDE_GP25_GetVirtualSightPointsLS(cameraPositionLS, cameraDirectionPointLS, pivotStartLS, pivotEndLS))
            return false;

        vector adjustedTransform[4];
        BDE_USL_GetAdjustedAttachmentTransform(adjustedTransform);

        cameraPositionWS = cameraPositionLS.Multiply4(adjustedTransform);
        cameraDirectionPointWS = cameraDirectionPointLS.Multiply4(adjustedTransform);
        pivotStartWS = pivotStartLS.Multiply4(adjustedTransform);
        pivotEndWS = pivotEndLS.Multiply4(adjustedTransform);
        return true;
    }

    bool BDE_GP25_GetVirtualSightCameraWS(out vector cameraPositionWS, out vector cameraDirectionPointWS, out vector cameraUpWS)
    {
        cameraPositionWS = vector.Zero;
        cameraDirectionPointWS = vector.Zero;
        cameraUpWS = vector.Zero;

        vector sightPositionWS;
        vector sightDirectionPointWS;
        vector pivotStartWS;
        vector pivotEndWS;

        if (!BDE_GP25_GetVirtualSightPointsWS(sightPositionWS, sightDirectionPointWS, pivotStartWS, pivotEndWS))
            return false;

        vector sightDirectionWS = sightDirectionPointWS - sightPositionWS;
        float directionLength = sightDirectionWS.Length();

        if (directionLength <= 0.000001)
            return false;

        sightDirectionWS = sightDirectionWS * (1.0 / directionLength);

        vector pivotAxisWS = pivotEndWS - pivotStartWS;
        float pivotLength = pivotAxisWS.Length();

        if (pivotLength <= 0.000001)
            return false;

        pivotAxisWS = pivotAxisWS * (1.0 / pivotLength);

        float upX = (pivotAxisWS[1] * sightDirectionWS[2]) - (pivotAxisWS[2] * sightDirectionWS[1]);
        float upY = (pivotAxisWS[2] * sightDirectionWS[0]) - (pivotAxisWS[0] * sightDirectionWS[2]);
        float upZ = (pivotAxisWS[0] * sightDirectionWS[1]) - (pivotAxisWS[1] * sightDirectionWS[0]);
        cameraUpWS = Vector(upX, upY, upZ);

        float upLength = cameraUpWS.Length();

        if (upLength <= 0.000001)
            return false;

        cameraUpWS = cameraUpWS * (1.0 / upLength);

        float cameraBackOffset = GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " BDE_GP25_VirtualSightCameraBackOffset");
        if (cameraBackOffset < 0.0)
            cameraBackOffset = 0.0;

        cameraPositionWS = sightPositionWS - (sightDirectionWS * cameraBackOffset);
        cameraDirectionPointWS = sightDirectionPointWS;
        return true;
    }

    override bool BDE_USL_StepAimZeroingUp()
    {
        bool changed = super.BDE_USL_StepAimZeroingUp();

        if (changed)
            BDE_GP25_UpdateSightZeroVisual();

        return changed;
    }

    override bool BDE_USL_StepAimZeroingDown()
    {
        bool changed = super.BDE_USL_StepAimZeroingDown();

        if (changed)
            BDE_GP25_UpdateSightZeroVisual();

        return changed;
    }

    protected bool BDE_GP25_IsLauncherModeActive()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host)
            return host.BDE_USL_IsLauncherModeSelected();

        return BDE_USL_IsLauncherModeSelected();
    }

    void BDE_GP25_UpdateSightVisual(bool adsActive)
    {
        BDE_GP25_RequestSightVariantRefresh();
        BDE_GP25_UpdateSightZeroVisual();
    }

    void BDE_GP25_FinalizeTypeSwapChamber(bool hadLiveRound, float chamberDamage, string chamberAmmoType, string chamberSourceType)
    {
        if (!GetGame().IsServer())
            return;

        int muzzleIndex = 0;
        bool liveBefore = false;
        bool restored = false;

        if (GetMuzzleCount() > muzzleIndex)
            liveBefore = IsChamberFull(muzzleIndex) && !IsChamberFiredOut(muzzleIndex);

        if (hadLiveRound && !liveBefore && chamberAmmoType != "" && GetMuzzleCount() > muzzleIndex)
        {
            if (!IsChamberEmpty(muzzleIndex))
            {
                float oldDamage;
                string oldAmmoType;
                PopCartridgeFromChamber(muzzleIndex, oldDamage, oldAmmoType);
            }

            restored = PushCartridgeToChamber(muzzleIndex, chamberDamage, chamberAmmoType);
        }

        if (hadLiveRound && chamberSourceType != "")
            BDE_USL_SetLoadedMagazineSourceType(chamberSourceType);

        RandomizeFSMState();
        BDE_USL_SyncChamberVisual();
        Synchronize();
        SetSynchDirty();

        bool liveAfter = false;

        if (GetMuzzleCount() > muzzleIndex)
            liveAfter = IsChamberFull(muzzleIndex) && !IsChamberFiredOut(muzzleIndex);
    }
}
