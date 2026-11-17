class BDE_Six12_ProxyGeometry
{
    static bool GetSlotProxyTransform(EntityAI host, string slotName, out vector proxyTransform[4])
    {
        proxyTransform[0] = "1 0 0";
        proxyTransform[1] = "0 1 0";
        proxyTransform[2] = "0 0 1";
        proxyTransform[3] = vector.Zero;

        if (!host || slotName == "")
            return false;

        LOD lod = host.GetLODByName(LOD.NAME_VIEW);
        if (!lod)
            return false;

        array<Selection> selections = new array<Selection>;
        lod.GetSelections(selections);
        if (!selections || selections.Count() == 0)
            return false;

        int childCount = GetGame().ConfigGetChildrenCount("CfgNonAIVehicles");
        for (int childIndex = 0; childIndex < childCount; childIndex++)
        {
            string childName;
            GetGame().ConfigGetChildName("CfgNonAIVehicles", childIndex, childName);

            string inventorySlotName;
            GetGame().ConfigGetText("CfgNonAIVehicles " + childName + " inventorySlot", inventorySlotName);
            if (inventorySlotName != slotName)
                continue;

            string modelPath;
            GetGame().ConfigGetText("CfgNonAIVehicles " + childName + " model", modelPath);
            if (modelPath.Length() <= 4)
                continue;

            modelPath = modelPath.Substring(0, modelPath.Length() - 4);
            modelPath.ToLower();

            for (int selectionIndex = 0; selectionIndex < selections.Count(); selectionIndex++)
            {
                Selection selection = selections[selectionIndex];
                if (!selection)
                    continue;

                string selectionName = selection.GetName();
                selectionName.ToLower();
                if (!selectionName.Contains(modelPath))
                    continue;

                vector origin = selection.GetVertexPosition(lod, 0);
                vector proxyYRaw = selection.GetVertexPosition(lod, 1) - origin;
                vector proxyZRaw = selection.GetVertexPosition(lod, 2) - origin;

                float proxyYLength = proxyYRaw.Length();
                float proxyZLength = proxyZRaw.Length();
                if (proxyYLength <= 0.0001 || proxyZLength <= 0.0001)
                    continue;

                vector proxyY = proxyYRaw * (1.0 / proxyYLength);
                vector proxyZ = proxyZRaw * (1.0 / proxyZLength);

                vector proxyX = proxyY * proxyZ;

                float proxyXLength = proxyX.Length();
                if (proxyXLength <= 0.0001)
                    continue;

                proxyX = proxyX * (1.0 / proxyXLength);

                float proxyScale = ((proxyYLength * 0.5) + proxyZLength) * 0.5;

                proxyTransform[0] = proxyX * proxyScale;
                proxyTransform[1] = proxyY * proxyScale;
                proxyTransform[2] = proxyZ * proxyScale;
                proxyTransform[3] = origin;
                return true;
            }
        }

        return false;
    }
}

class BDE_Six12 extends RifleSingleShotManual_Base
{
    protected int m_BDE_Six12_LastDryFireTime;
    protected bool m_BDE_Six12_MagazineSwapInProgress;
    protected bool m_BDE_Six12_ReloadActive;
    protected Magazine m_BDE_Six12_ReloadSource;
    protected bool m_BDE_Six12_ReloadSourceLocked;
    protected bool m_BDE_Six12_ReloadStopRequested;
    protected bool m_BDE_Six12_ReloadLoadedRoundThisSequence;
    protected int m_BDE_Six12_CylinderRotationLockUntil;

    void BDE_Six12()
    {
        RegisterNetSyncVariableBool("m_BDE_Six12_ReloadActive");
    }

    protected void BDE_Six12_LogReload(string message)
    {
        Print("[BDE SIX12 RELOAD] " + GetType() + " @" + this + " " + message);
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_Six12_RequestCylinderVisualRefresh();
        BDE_Six12_RequestButtPadRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_Six12_RequestCylinderVisualRefresh();
        BDE_Six12_RequestButtPadRefresh();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_USL_ShotWear.LogClient(this);
        BDE_Six12_UpdateCylinderVisual();
    }

    override void EEAmmoChanged()
    {
        super.EEAmmoChanged();
        BDE_Six12_UpdateCylinderVisual();
    }

    override void OnDebugSpawn()
    {
        if (!GetGame().IsServer())
            return;

        EntityAI debugParent = GetHierarchyParent();
        bool standaloneDebug = debugParent && (debugParent.IsKindOf("BDE_Six12_StandAloneMount") || debugParent.IsKindOf("BDE_Six12_StandAloneMount_Weapon"));

        if (!standaloneDebug && !FindAttachmentBySlotName("BDE_Six12_ShortBarrel"))
            GetInventory().CreateAttachment("BDE_Six12_ShortBarrel");

        BDE_Six12_EnsureCylinderVisual();
        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        if (mag)
        {
            mag.ServerSetAmmoCount(0);
            for (int i = 0; i < 6; i++)
                mag.ServerStoreCartridge(0.0, "Bullet_12GaugePellets");
            mag.SetSynchDirty();
            mag.BDE_Six12_UpdateVisuals();
        }

        BDE_Six12_ServerNormalizeLegacyChamber();
        RandomizeFSMState();
        Synchronize();
        SetSynchDirty();
        BDE_Six12_UpdateCylinderVisual();
    }

    int BDE_Six12_GetAmmoMax()
    {
        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        if (mag)
            return mag.GetAmmoMax();
        return 6;
    }

    int BDE_Six12_GetAmmoCount()
    {
        return BDE_Six12_GetInternalRoundCount();
    }

    int BDE_Six12_GetChamberedRoundCount()
    {
        return 0;
    }

    int BDE_Six12_GetInternalRoundCount()
    {
        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        if (!mag)
            return 0;
        return Math.Clamp(mag.GetAmmoCount(), 0, mag.GetAmmoMax());
    }

    string BDE_Six12_GetHUDShortName()
    {
        return "SIX12";
    }

    string BDE_Six12_GetEngineProjectileType(string magazineProjectileType)
    {
        return magazineProjectileType;
    }

    string BDE_Six12_GetMagazineProjectileType(string engineProjectileType)
    {
        return engineProjectileType;
    }

    override RecoilBase SpawnRecoilObject()
    {
        return new SiagaRecoil(this);
    }

    bool BDE_Six12_HasLoadedMagazine()
    {
        if (IsRuined())
            return false;
        return BDE_Six12_GetInternalRoundCount() > 0;
    }

    protected bool BDE_Six12_IsFDEVariant()
    {
        return IsKindOf("BDE_Six12_FDE");
    }

    BDE_Six12_Magazine BDE_Six12_GetMagazine()
    {
        return BDE_Six12_Magazine.Cast(FindAttachmentBySlotName("BDE_Six12_Magazine"));
    }

    bool BDE_Six12_IsMagazineSwapInProgress()
    {
        return m_BDE_Six12_MagazineSwapInProgress;
    }

    bool BDE_Six12_IsReloadActive()
    {
        return m_BDE_Six12_ReloadActive;
    }

    void BDE_Six12_RequestCylinderVisualRefresh()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_EnsureCylinderVisual);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_EnsureCylinderVisual, 75, false);
    }

    protected void BDE_Six12_MigrateLegacyInternalRounds(BDE_Six12_Magazine mag)
    {
        if (!GetGame().IsServer() || !mag || mag.GetAmmoCount() >= mag.GetAmmoMax())
            return;

        while (GetInternalMagazineCartridgeCount(0) > 0 && mag.GetAmmoCount() < mag.GetAmmoMax())
        {
            float ammoDamage;
            string ammoType;
            if (!PopCartridgeFromInternalMagazine(0, ammoDamage, ammoType))
                break;
            if (!mag.ServerStoreCartridge(ammoDamage, ammoType))
            {
                PushCartridgeToInternalMagazine(0, ammoDamage, ammoType);
                break;
            }
        }

        mag.SetSynchDirty();
    }

    protected void BDE_Six12_ServerNormalizeLegacyChamber()
    {
        if (!GetGame().IsServer() || GetMuzzleCount() <= 0)
            return;

        int muzzleIndex = 0;
        if (IsChamberEmpty(muzzleIndex))
            return;

        float ammoDamage;
        string ammoType;
        bool firedOut = IsChamberFiredOut(muzzleIndex);
        if (!PopCartridgeFromChamber(muzzleIndex, ammoDamage, ammoType))
            return;

        if (!firedOut && ammoType != "")
        {
            BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
            if (mag && mag.GetAmmoCount() < mag.GetAmmoMax())
            {
                mag.ServerStoreCartridge(ammoDamage, BDE_Six12_GetMagazineProjectileType(ammoType));
                mag.SetSynchDirty();
                mag.BDE_Six12_UpdateVisuals();
            }
        }

        RandomizeFSMState();
        Synchronize();
        SetSynchDirty();
    }

    void BDE_Six12_EnsureCylinderVisual()
    {
        if (IsSetForDeletion())
            return;

        EntityAI current = FindAttachmentBySlotName("BDE_Six12_Magazine");
        BDE_Six12_Magazine mag = BDE_Six12_Magazine.Cast(current);
        if (mag)
        {
            BDE_Six12_MigrateLegacyInternalRounds(mag);
            BDE_Six12_ServerNormalizeLegacyChamber();
            mag.BDE_Six12_UpdateVisuals();
            return;
        }

        BDE_Six12_CylinderVisual oldVisual = BDE_Six12_CylinderVisual.Cast(current);
        if (oldVisual && GetGame().IsServer())
        {
            oldVisual.DeleteSafe();
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_EnsureCylinderVisual, 25, false);
            return;
        }

        if (!GetGame().IsServer() || current)
            return;

        string magazineType = "BDE_Six12_Magazine";
        if (BDE_Six12_IsFDEVariant())
            magazineType = "BDE_Six12_Magazine_FDE";

        mag = BDE_Six12_Magazine.Cast(GetInventory().CreateAttachment(magazineType));
        if (mag)
        {
            BDE_Six12_MigrateLegacyInternalRounds(mag);
            BDE_Six12_ServerNormalizeLegacyChamber();
            mag.BDE_Six12_UpdateVisuals();
            SetSynchDirty();
        }
    }

    void BDE_Six12_UpdateCylinderVisual()
    {
        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        if (mag)
            mag.BDE_Six12_UpdateVisuals();
        else if (GetGame().IsServer() && !m_BDE_Six12_MagazineSwapInProgress && !BDE_Six12_IsReceiverSwapInProgress())
            BDE_Six12_RequestCylinderVisualRefresh();
    }

    bool BDE_Six12_HasHandle()
    {
        return FindAttachmentBySlotName("BDE_Six12_Handle") != null;
    }

    bool BDE_Six12_HasShortBarrel()
    {
        return FindAttachmentBySlotName("BDE_Six12_ShortBarrel") != null;
    }

    bool BDE_Six12_CanUseButtPad()
    {
        return BDE_Six12_HostSupportsButtPad();
    }

    void BDE_Six12_NotifyHostButtstockChanged()
    {
        BDE_Six12_RequestButtPadRefresh();
    }

    void BDE_Six12_RequestButtPadRefresh()
    {
        if (!GetGame().IsServer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_RefreshButtPad);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_RefreshButtPad, 50, false);
    }

    protected void BDE_Six12_RefreshButtPad()
    {
        EntityAI buttPad = FindAttachmentBySlotName("BDE_Six12_ButtPad");
        if (!buttPad)
            return;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!host)
            return;

        string hostType = host.GetType();
        if (hostType != "AKM" && hostType != "AK74" && hostType != "AK101")
            return;

        string targetType = "BDE_USL_Six12_ButtPad_VanillaAK";
        if (buttPad.GetType() == targetType)
            return;

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_USL_ButtPadSwapLambda lambda = new BDE_USL_ButtPadSwapLambda(buttPad, targetType, owner);
        lambda.SetTransferParams(true, true, false);
        buttPad.GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }

    protected bool BDE_Six12_HostSupportsButtPad()
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

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_Six12_RequestButtPadRefresh();
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (FindAttachmentBySlotName("BDE_Six12_ButtPad"))
            return false;

        return super.CanDetachAttachment(parent);
    }

    bool BDE_Six12_IsReceiverSwapInProgress()
    {
        return false;
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (attachment && attachment.IsKindOf("BDE_Six12_Magazine"))
            return BDE_Six12_IsReceiverSwapInProgress();

        if (attachment && attachment.IsKindOf("BDE_Six12_CylinderVisual"))
            return BDE_Six12_IsReceiverSwapInProgress();

        return super.CanReleaseAttachment(attachment);
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;

        if (parent.IsKindOf("BDE_Six12_StandAloneMount") || parent.IsKindOf("BDE_Six12_StandAloneMount_Weapon"))
        {
            if (BDE_Six12_HasShortBarrel())
                return false;

            return true;
        }

        Weapon_Base host = Weapon_Base.Cast(parent);
        if (host)
        {
            if (!super.CanPutAsAttachment(parent))
                return false;

            return host.BDE_USL_CanAttachSix12ToConfiguredSlot(this);
        }

        return super.CanPutAsAttachment(parent);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!attachment)
            return false;

        string slotName = InventorySlots.GetSlotName(slotId);
        if (slotName == "BDE_Six12_Magazine")
        {
            if (!attachment.IsKindOf("BDE_Six12_Magazine"))
                return false;

            return FindAttachmentBySlotName("BDE_Six12_Magazine") == null;
        }

        if (slotName == "BDE_Six12_ButtPad")
        {
            if (!attachment.IsKindOf("BDE_GP25_ButtPad") || !BDE_Six12_CanUseButtPad())
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        if (attachment.IsKindOf("BDE_Six12_ShortBarrel"))
        {
            EntityAI parent = GetHierarchyParent();
            if (parent && (parent.IsKindOf("BDE_Six12_StandAloneMount") || parent.IsKindOf("BDE_Six12_StandAloneMount_Weapon")))
                return false;
        }

        return super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanBeCombined(EntityAI other_item, bool reservation_check = true, bool stack_max_limit = false)
    {
        Magazine sourceAmmo = Magazine.Cast(other_item);
        if (sourceAmmo && BDE_Six12_CanDirectLoadAmmo(sourceAmmo, reservation_check))
            return true;

        return super.CanBeCombined(other_item, reservation_check, stack_max_limit);
    }

    override void CombineItems(ItemBase other_item, bool use_stack_max = true)
    {
        Magazine sourceAmmo = Magazine.Cast(other_item);
        if (sourceAmmo && BDE_Six12_CanDirectLoadAmmo(sourceAmmo, false))
        {
            BDE_Six12_RequestSpecificAmmo(sourceAmmo);
            return;
        }

        super.CombineItems(other_item, use_stack_max);
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (!super.CanDisplayAttachmentSlot(slot_id))
            return false;

        string slotName = InventorySlots.GetSlotName(slot_id);

        if (slotName == "BDE_Six12_ButtPad")
        {
            if (FindAttachmentBySlotName("BDE_Six12_ButtPad"))
                return true;

            return BDE_Six12_CanUseButtPad();
        }

        if (slotName == "BDE_Six12_ShortBarrel")
        {
            EntityAI parent = GetHierarchyParent();
            if (parent && (parent.IsKindOf("BDE_Six12_StandAloneMount") || parent.IsKindOf("BDE_Six12_StandAloneMount_Weapon")))
                return false;
        }

        return true;
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == "BDE_Six12_Magazine")
        {
            BDE_Six12_UpdateCylinderVisual();
        }
        else if (slot_name == "BDE_Six12_Handle" || slot_name == "BDE_Six12_ShortBarrel")
        {
            BDE_Six12_NotifyStandaloneParentChanged();
            BDE_Six12_NotifyHostConfigurationChanged();
        }
        else if (slot_name == "BDE_Six12_ButtPad")
        {
            BDE_Six12_RequestButtPadRefresh();
        }
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (slot_name == "BDE_Six12_Magazine")
        {
            if (GetGame().IsServer() && !m_BDE_Six12_MagazineSwapInProgress && !BDE_Six12_IsReceiverSwapInProgress())
                BDE_Six12_RequestCylinderVisualRefresh();
        }
        else if (slot_name == "BDE_Six12_Handle" || slot_name == "BDE_Six12_ShortBarrel")
        {
            BDE_Six12_NotifyStandaloneParentChanged();
            BDE_Six12_NotifyHostConfigurationChanged();
        }
        else if (slot_name == "BDE_Six12_ButtPad")
        {
            BDE_Six12_RequestButtPadRefresh();
        }
    }

    protected void BDE_Six12_NotifyHostConfigurationChanged()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (host && !host.IsKindOf("BDE_Six12_StandAloneMount_Weapon"))
            host.BDE_USL_RefreshLauncherModeState();
    }

    protected void BDE_Six12_NotifyStandaloneParentChanged()
    {
        EntityAI parent = GetHierarchyParent();

        BDE_Six12_StandAloneMount itemMount = BDE_Six12_StandAloneMount.Cast(parent);
        if (itemMount)
        {
            itemMount.BDE_Six12_RequestVariantRefresh();
            return;
        }

        BDE_Six12_StandAloneMount_Weapon weaponMount = BDE_Six12_StandAloneMount_Weapon.Cast(parent);
        if (weaponMount)
            weaponMount.BDE_Six12_RequestVariantRefresh();
    }

    bool BDE_Six12_ShouldUseAttachedCustomReloadAnimation()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!host || host.IsKindOf("BDE_Six12_StandAloneMount_Weapon"))
            return false;

        string path = "CfgWeapons " + host.GetType() + " BDE_USL_Six12CustomReloadAnimation";
        return GetGame().ConfigIsExisting(path) && GetGame().ConfigGetInt(path) == 1;
    }

    void BDE_Six12_BeginCylinderRotationLock(int durationMs = BDE_USL_SIX12_CYLINDER_ROTATION_MS)
    {
        int now = GetGame().GetTime();
        int newLockUntil = now + durationMs;

        if (newLockUntil > m_BDE_Six12_CylinderRotationLockUntil)
            m_BDE_Six12_CylinderRotationLockUntil = newLockUntil;
    }

    bool BDE_Six12_IsCylinderRotating()
    {
        return GetGame().GetTime() < m_BDE_Six12_CylinderRotationLockUntil;
    }

    bool BDE_Six12_IsFireCycleLocked()
    {
        return m_BDE_Six12_ReloadActive || BDE_Six12_IsCylinderRotating();
    }

    bool BDE_Six12_CanFireFromHost(Weapon_Base host)
    {
        if (!host || IsRuined() || m_BDE_Six12_ReloadActive || BDE_Six12_IsCylinderRotating())
            return false;

        if (!BDE_Six12_HasLoadedMagazine())
            return false;

        if (host.IsKindOf("BDE_Six12_StandAloneMount_Weapon"))
        {
            BDE_Six12_StandAloneMount_Weapon mount = BDE_Six12_StandAloneMount_Weapon.Cast(host);
            if (!mount || mount.BDE_Six12_GetBody() != this)
                return false;

            if (!BDE_Six12_HasHandle() || BDE_Six12_HasShortBarrel())
                return false;

            return mount.FindAttachmentBySlotName("BDE_Six12_LongBarrel") != null;
        }

        if (host.BDE_USL_GetSix12() != this || !host.BDE_USL_IsSix12ModeSelected())
            return false;

        return BDE_Six12_HasShortBarrel();
    }

    protected bool BDE_Six12_GetCurrentInventorySlotOffset(out vector slotPosition, out vector slotOrientation)
    {
        slotPosition = vector.Zero;
        slotOrientation = vector.Zero;

        int slotId;
        string slotName;
        if (!GetInventory().GetCurrentAttachmentSlotInfo(slotId, slotName) || slotName == "")
            return false;

        string configPath = "CfgWeapons " + GetType() + " InventorySlotsOffsets " + slotName;
        array<float> positionValues = new array<float>;
        array<float> orientationValues = new array<float>;
        GetGame().ConfigGetFloatArray(configPath + " position", positionValues);
        GetGame().ConfigGetFloatArray(configPath + " orientation", orientationValues);

        if (positionValues.Count() >= 3)
            slotPosition = Vector(positionValues[0], positionValues[1], positionValues[2]);
        if (orientationValues.Count() >= 3)
            slotOrientation = Vector(orientationValues[0], orientationValues[1], orientationValues[2]);

        return true;
    }

    protected void BDE_Six12_GetAdjustedAttachmentTransform(out vector adjustedTransform[4])
    {
        GetRenderTransform(adjustedTransform);
    }

    protected vector BDE_Six12_GetConfigVector(string key)
    {
        array<float> values = new array<float>;
        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " " + key, values);
        if (values.Count() < 3)
            return vector.Zero;
        return Vector(values[0], values[1], values[2]);
    }

    bool BDE_Six12_GetMuzzlePointsWS(Weapon_Base host, out vector muzzleStart, out vector muzzleEnd)
    {
        BDE_Six12_StandAloneMount_Weapon mount = BDE_Six12_StandAloneMount_Weapon.Cast(host);
        if (mount)
            return mount.BDE_Six12_GetMuzzlePointsWS(muzzleStart, muzzleEnd);

        if (!host)
            return false;

        vector localStart = BDE_Six12_GetConfigVector("BDE_USL_AttachedMuzzleStart");
        vector localEnd = BDE_Six12_GetConfigVector("BDE_USL_AttachedMuzzleEnd");

        vector transform[4];
        BDE_Six12_GetAdjustedAttachmentTransform(transform);
        muzzleStart = localStart.Multiply4(transform);
        muzzleEnd = localEnd.Multiply4(transform);
        return true;
    }

    protected bool BDE_Six12_LoadTransientEngineChamber(bool serverSide, out bool acquiredFromMagazine)
    {
        acquiredFromMagazine = false;

        int muzzleIndex = 0;
        if (GetMuzzleCount() <= muzzleIndex)
            return false;

        if (!IsChamberEmpty(muzzleIndex))
        {
            float staleDamage;
            string staleType;
            bool staleFiredOut = IsChamberFiredOut(muzzleIndex);
            if (PopCartridgeFromChamber(muzzleIndex, staleDamage, staleType) && !staleFiredOut && staleType != "")
            {
                BDE_Six12_Magazine staleMag = BDE_Six12_GetMagazine();
                if (staleMag && staleMag.GetAmmoCount() < staleMag.GetAmmoMax())
                    staleMag.BDE_Six12_RestoreRound(serverSide, staleDamage, staleType);
            }
        }

        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        if (!mag || mag.GetAmmoCount() <= 0)
            return false;

        float ammoDamage;
        string ammoType;
        if (!mag.BDE_Six12_ConsumeRound(serverSide, ammoDamage, ammoType))
            return false;

        string engineAmmoType = BDE_Six12_GetEngineProjectileType(ammoType);
        if (!PushCartridgeToChamber(muzzleIndex, ammoDamage, engineAmmoType))
        {
            mag.BDE_Six12_RestoreRound(serverSide, ammoDamage, ammoType);
            return false;
        }

        acquiredFromMagazine = true;

        return true;
    }

    protected bool BDE_Six12_PrepareRound(bool serverSide, out bool acquiredFromMagazine)
    {
        bool prepared = BDE_Six12_LoadTransientEngineChamber(serverSide, acquiredFromMagazine);
        if (prepared)
        {
            int fireIntervalMs = Math.Ceil(GetReloadTime(0) * 1000.0);
            if (fireIntervalMs < BDE_USL_SIX12_CYLINDER_ROTATION_MS)
                fireIntervalMs = BDE_USL_SIX12_CYLINDER_ROTATION_MS;
            BDE_Six12_BeginCylinderRotationLock(fireIntervalMs);
        }

        return prepared;
    }

    protected void BDE_Six12_FinishRound(bool serverSide, bool fired, bool acquiredFromMagazine)
    {
        int muzzleIndex = 0;
        if (GetMuzzleCount() <= muzzleIndex)
            return;

        if (!IsChamberEmpty(muzzleIndex))
        {
            float ammoDamage;
            string ammoType;
            bool firedOut = IsChamberFiredOut(muzzleIndex);

            if (PopCartridgeFromChamber(muzzleIndex, ammoDamage, ammoType))
            {
                if (!fired && acquiredFromMagazine && !firedOut && ammoType != "")
                {
                    BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
                    if (mag)
                        mag.BDE_Six12_RestoreRound(serverSide, ammoDamage, BDE_Six12_GetMagazineProjectileType(ammoType));
                }
            }
        }

        BDE_Six12_UpdateCylinderVisual();
    }

    protected BDE_Six12_Magazine BDE_Six12_FindLoadedSpareMagazine(PlayerBase player)
    {
        if (!player)
            return null;

        array<EntityAI> items = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        BDE_Six12_Magazine current = BDE_Six12_GetMagazine();
        BDE_Six12_Magazine best;
        int bestCount = 0;

        foreach (EntityAI entity : items)
        {
            BDE_Six12_Magazine candidate = BDE_Six12_Magazine.Cast(entity);
            if (!candidate || candidate == current || candidate.GetAmmoCount() <= 0)
                continue;

            if (candidate.GetHierarchyParent() && candidate.GetHierarchyParent().IsKindOf("BDE_Six12"))
                continue;

            if (!best || candidate.GetAmmoCount() > bestCount)
            {
                best = candidate;
                bestCount = candidate.GetAmmoCount();
            }
        }

        string bestType = "NULL";
        int bestAmmoCount = -1;
        if (best)
        {
            bestType = best.GetType();
            bestAmmoCount = best.GetAmmoCount();
        }
        BDE_Six12_LogReload("loaded-spare scan selected=" + best + " type=" + bestType + " count=" + bestAmmoCount);
        return best;
    }

    protected Magazine BDE_Six12_FindCompatibleAmmo(PlayerBase player, BDE_Six12_Magazine targetMagazine)
    {
        if (!player || !targetMagazine)
            return null;

        array<EntityAI> items = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI entity : items)
        {
            if (!entity || entity.IsKindOf("BDE_Six12_Magazine"))
                continue;

            Magazine ammoPile = Magazine.Cast(entity);
            ItemBase ammoItem = ItemBase.Cast(entity);
            if (!ammoPile || !ammoItem || ammoPile.GetAmmoCount() <= 0)
                continue;

            if (targetMagazine.IsCompatiableAmmo(ammoItem))
                return ammoPile;
        }

        return null;
    }

    protected void BDE_Six12_SetReloadActive(bool state)
    {
        m_BDE_Six12_ReloadActive = state;
        SetSynchDirty();
    }

    protected void BDE_Six12_ServerBroadcastReloadFX(float slidePhase, float rotationPhase)
    {
        if (!GetGame().IsServer())
            return;

        Param2<float, float> data = new Param2<float, float>(slidePhase, rotationPhase);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_SIX12_RELOAD_FX, data, true, NULL);
    }

    protected void BDE_Six12_ServerSetMagazinePose(float slidePhase, float rotationPhase)
    {
        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        if (mag)
            mag.BDE_Six12_SetVisualPose(slidePhase, rotationPhase);

        BDE_Six12_BeginCylinderRotationLock();
        BDE_Six12_ServerBroadcastReloadFX(slidePhase, rotationPhase);
    }

    bool BDE_Six12_CanDirectSwapMagazine(BDE_Six12_Magazine source, bool reservationCheck = true)
    {
        return false;
    }

    bool BDE_Six12_CanDirectLoadAmmo(Magazine source, bool reservationCheck = true)
    {
        if (!source || source.IsKindOf("BDE_Six12_Magazine") || source.GetAmmoCount() <= 0 || m_BDE_Six12_ReloadActive)
            return false;

        BDE_Six12_Magazine target = BDE_Six12_GetMagazine();
        if (!target || target.GetAmmoCount() >= target.GetAmmoMax())
            return false;

        ItemBase sourceItem = ItemBase.Cast(source);
        if (!sourceItem || !target.IsCompatiableAmmo(sourceItem))
            return false;

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
        if (!player)
            return false;

        Man sourceOwner = source.GetHierarchyRootPlayer();
        if (sourceOwner && sourceOwner != player)
            return false;
        if (!sourceOwner && vector.Distance(source.GetPosition(), player.GetPosition()) > 3.0)
            return false;

        return true;
    }

    protected bool BDE_Six12_ValidateInventoryInteractionOwner(PlayerIdentity sender, EntityAI source, out PlayerBase player, out Weapon_Base host)
    {
        player = PlayerBase.Cast(GetHierarchyRootPlayer());
        host = Weapon_Base.Cast(GetHierarchyParent());
        if (!sender || !player || !source)
            return false;

        PlayerIdentity identity = player.GetIdentity();
        if (!identity || identity.GetId() != sender.GetId())
            return false;

        Man sourceOwner = source.GetHierarchyRootPlayer();
        if (sourceOwner && sourceOwner != player)
            return false;
        if (!sourceOwner && vector.Distance(source.GetPosition(), player.GetPosition()) > 3.0)
            return false;

        return true;
    }

    protected bool BDE_Six12_ServerSwapMagazine(PlayerBase player, BDE_Six12_Magazine spare)
    {
        BDE_Six12_LogReload("magazine swap ignored: permanent-cylinder mode");
        return false;
    }

    void BDE_Six12_ClientRequestReload(Weapon_Base host, PlayerBase player)
    {
        if (!GetGame().IsClient() || !host || !player || m_BDE_Six12_ReloadActive)
            return;
        if (GetGame().GetPlayer() != player || player.GetItemInHands() != host)
            return;

        BDE_Six12_LogReload("client Charge Fire Mechanism request host=" + host + " player=" + player);
        Param1<int> data = new Param1<int>(0);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_SIX12_RELOAD_REQUEST, data, true);
    }

    void BDE_Six12_ClientRequestReloadStop(Weapon_Base host, PlayerBase player)
    {
        if (!GetGame().IsClient() || !host || !player)
            return;
        if (GetGame().GetPlayer() != player || player.GetItemInHands() != host)
            return;

        Param1<int> data = new Param1<int>(0);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_SIX12_RELOAD_RELEASE, data, true);
    }

    void BDE_Six12_RequestSpecificMagazine(BDE_Six12_Magazine source)
    {
        return;
    }

    void BDE_Six12_RequestSpecificAmmo(Magazine source)
    {
        if (!source || !BDE_Six12_CanDirectLoadAmmo(source, false))
            return;

        if (GetGame().IsClient())
        {
            Param1<EntityAI> data = new Param1<EntityAI>(source);
            GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_SIX12_LOAD_SPECIFIC_AMMO, data, true);
            return;
        }

        if (GetGame().IsServer())
        {
            PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
            Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
            BDE_Six12_ServerBeginLooseReload(player, host, source, true);
        }
    }

    protected void BDE_Six12_ServerBeginLooseReload(PlayerBase player, Weapon_Base host, Magazine preferredSource = null, bool lockToSource = false)
    {
        if (!GetGame().IsServer() || m_BDE_Six12_ReloadActive || !player)
            return;

        BDE_Six12_Magazine current = BDE_Six12_GetMagazine();
        if (!current || current.GetAmmoCount() >= current.GetAmmoMax())
            return;

        Magazine ammoPile = preferredSource;
        if (ammoPile)
        {
            if (!BDE_Six12_CanDirectLoadAmmo(ammoPile, false))
                return;
        }
        else
        {
            ammoPile = BDE_Six12_FindCompatibleAmmo(player, current);
            if (!ammoPile)
                return;
        }

        if (!host || player.GetItemInHands() != host)
        {
            if (!lockToSource)
                return;

            while (current.GetAmmoCount() < current.GetAmmoMax() && ammoPile.GetAmmoCount() > 0)
            {
                float directDamage;
                string directType;
                if (!ammoPile.ServerAcquireCartridge(directDamage, directType))
                    break;
                if (!current.ServerStoreCartridge(directDamage, directType))
                {
                    ammoPile.ServerStoreCartridge(directDamage, directType);
                    break;
                }
            }
            ammoPile.SetSynchDirty();
            current.SetSynchDirty();
            current.BDE_Six12_UpdateVisuals();
            return;
        }

        m_BDE_Six12_ReloadSource = ammoPile;
        m_BDE_Six12_ReloadSourceLocked = lockToSource;
        m_BDE_Six12_ReloadStopRequested = false;
        m_BDE_Six12_ReloadLoadedRoundThisSequence = false;
        BDE_Six12_SetReloadActive(true);
        current.BDE_Six12_UpdateBulletSelections();
        float bottomPhase = current.BDE_Six12_GetNextEmptyBottomPhase();
        BDE_Six12_ServerSetMagazinePose(1.0, bottomPhase);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_ServerLooseReloadStep, BDE_USL_SIX12_CYLINDER_ROTATION_MS, false, player, host);
    }

    protected void BDE_Six12_ServerBeginReload(PlayerIdentity sender)
    {
        if (!GetGame().IsServer() || m_BDE_Six12_ReloadActive)
            return;

        PlayerBase player;
        Weapon_Base host;
        if (!BDE_Six12_ValidateFireOwner(sender, player, host))
            return;

        BDE_Six12_ServerNormalizeLegacyChamber();
        BDE_Six12_LogReload("server Charge Fire Mechanism accepted sender=" + sender + " player=" + player + " host=" + host);

        BDE_Six12_Magazine current = BDE_Six12_GetMagazine();
        if (!current)
        {
            BDE_Six12_EnsureCylinderVisual();
            current = BDE_Six12_GetMagazine();
            if (!current)
                return;
        }

        BDE_Six12_LogReload("Charge Fire Mechanism: permanent cylinder; using loose ammo only");
        BDE_Six12_ServerBeginLooseReload(player, host, null, false);
    }

    protected void BDE_Six12_ServerRequestReloadStop(PlayerIdentity sender)
    {
        if (!GetGame().IsServer() || !m_BDE_Six12_ReloadActive || m_BDE_Six12_ReloadSourceLocked)
            return;

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!sender || !player || !host)
            return;

        PlayerIdentity identity = player.GetIdentity();
        if (!identity || identity.GetId() != sender.GetId() || player.GetItemInHands() != host)
            return;

        m_BDE_Six12_ReloadStopRequested = true;
        BDE_Six12_LogReload("Charge Fire Mechanism released; finish current shell then stop");

        if (m_BDE_Six12_ReloadLoadedRoundThisSequence)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_ServerLooseReloadStep);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_ServerFinishLooseReload);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_ServerFinishLooseReload, BDE_USL_SIX12_CYLINDER_ROTATION_MS, false);
        }
    }

    protected void BDE_Six12_ServerLooseReloadStep(PlayerBase player, Weapon_Base host)
    {
        if (!GetGame().IsServer() || !m_BDE_Six12_ReloadActive || !player || !host)
            return;

        if (m_BDE_Six12_ReloadStopRequested && m_BDE_Six12_ReloadLoadedRoundThisSequence)
        {
            BDE_Six12_ServerFinishLooseReload();
            return;
        }

        if (player.GetItemInHands() != host)
        {
            BDE_Six12_ServerFinishLooseReload();
            return;
        }

        BDE_Six12_StandAloneMount_Weapon reloadMount = BDE_Six12_StandAloneMount_Weapon.Cast(host);
        if (reloadMount)
        {
            if (reloadMount.BDE_Six12_GetBody() != this)
            {
                BDE_Six12_ServerFinishLooseReload();
                return;
            }
        }
        else if (host.BDE_USL_GetSix12() != this || (!m_BDE_Six12_ReloadSourceLocked && !host.BDE_USL_IsSix12ModeSelected()))
        {
            BDE_Six12_ServerFinishLooseReload();
            return;
        }

        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        if (!mag || mag.GetAmmoCount() >= mag.GetAmmoMax())
        {
            BDE_Six12_ServerFinishLooseReload();
            return;
        }

        Magazine ammoPile = m_BDE_Six12_ReloadSource;
        if (ammoPile)
        {
            ItemBase reloadAmmoItem = ItemBase.Cast(ammoPile);
            if (!reloadAmmoItem || ammoPile.GetAmmoCount() <= 0 || !mag.IsCompatiableAmmo(reloadAmmoItem))
            {
                BDE_Six12_ServerFinishLooseReload();
                return;
            }
        }
        else
        {
            ammoPile = BDE_Six12_FindCompatibleAmmo(player, mag);
            if (!ammoPile)
            {
                BDE_Six12_ServerFinishLooseReload();
                return;
            }
            m_BDE_Six12_ReloadSource = ammoPile;
        }

        float ammoDamage;
        string ammoType;
        if (!ammoPile.ServerAcquireCartridge(ammoDamage, ammoType))
        {
            BDE_Six12_ServerFinishLooseReload();
            return;
        }

        if (!mag.ServerStoreCartridge(ammoDamage, ammoType))
        {
            ammoPile.ServerStoreCartridge(ammoDamage, ammoType);
            BDE_Six12_ServerFinishLooseReload();
            return;
        }

        ammoPile.SetSynchDirty();
        mag.SetSynchDirty();
        mag.BDE_Six12_UpdateBulletSelections();
        m_BDE_Six12_ReloadLoadedRoundThisSequence = true;

        if (!m_BDE_Six12_ReloadSourceLocked && ammoPile.GetAmmoCount() <= 0)
            m_BDE_Six12_ReloadSource = null;

        if (mag.GetAmmoCount() >= mag.GetAmmoMax() || (m_BDE_Six12_ReloadStopRequested && !m_BDE_Six12_ReloadSourceLocked))
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_ServerFinishLooseReload, BDE_USL_SIX12_CYLINDER_ROTATION_MS, false);
            return;
        }

        float nextBottomPhase = mag.BDE_Six12_GetNextEmptyBottomPhase();
        BDE_Six12_ServerSetMagazinePose(1.0, nextBottomPhase);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_ServerLooseReloadStep, 500, false, player, host);
    }

    protected void BDE_Six12_ServerFinishLooseReload()
    {
        if (!GetGame().IsServer() || !m_BDE_Six12_ReloadActive)
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_ServerLooseReloadStep);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_ServerFinishLooseReload);

        m_BDE_Six12_ReloadSource = null;
        m_BDE_Six12_ReloadSourceLocked = false;
        m_BDE_Six12_ReloadStopRequested = false;
        m_BDE_Six12_ReloadLoadedRoundThisSequence = false;

        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        float topPhase = 0.0;
        if (mag)
        {
            mag.BDE_Six12_UpdateBulletSelections();
            topPhase = mag.BDE_Six12_GetFirstLoadedTopPhase();
        }

        BDE_Six12_ServerSetMagazinePose(1.0, topPhase);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_ServerSeatMagazine, BDE_USL_SIX12_CYLINDER_ROTATION_MS, false, topPhase);
    }

    protected void BDE_Six12_ServerSeatMagazine(float topPhase)
    {
        if (!GetGame().IsServer() || !m_BDE_Six12_ReloadActive)
            return;

        BDE_Six12_ServerSetMagazinePose(0.0, topPhase);

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_ServerCompleteReload);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_ServerCompleteReload, BDE_USL_SIX12_CYLINDER_ROTATION_MS, false);
    }

    protected void BDE_Six12_ServerCompleteReload()
    {
        if (!GetGame().IsServer() || !m_BDE_Six12_ReloadActive)
            return;

        BDE_Six12_SetReloadActive(false);

        BDE_Six12_Magazine mag = BDE_Six12_GetMagazine();
        if (mag)
        {
            mag.BDE_Six12_UpdateVisuals();
            BDE_Six12_ServerBroadcastReloadFX(0.0, mag.BDE_Six12_GetFirstLoadedTopPhase());
        }
    }

    protected bool BDE_Six12_FireWithWatchdog(Weapon_Base host, vector muzzlePosition, vector shotDirection, vector inheritedVelocity, int shotId, out vector projectilePosition)
    {
        float projectileClearance = 0.0;
        if (host)
            projectileClearance = host.BDE_USL_GetProjectileSpawnClearance();

        projectilePosition = muzzlePosition + (shotDirection * projectileClearance);
        float chamberDamage = 0.0;
        string ammoType = "";
        GetCartridgeInfo(0, chamberDamage, ammoType);

        float launchSpeed = 0.0;
        if (ammoType != "")
            launchSpeed = GetGame().ConfigGetFloat("CfgAmmo " + ammoType + " initSpeed") * GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " initSpeedMultiplier");

        if (GetGame().IsServer() && ammoType != "")
        {
            string hostMode = "none";
            int hostMuzzle = -1;
            int hostModeIndex = -1;
            if (host)
            {
                hostMuzzle = host.GetCurrentMuzzle();
                hostModeIndex = host.GetCurrentMode(hostMuzzle);
                hostMode = host.GetCurrentModeName(hostMuzzle);
            }
            Print("[BDE SIX12 TELEMETRY] PRE_FIRE_STATE shotId=" + shotId + " host=" + host + " hostMuzzle=" + hostMuzzle + " hostModeIndex=" + hostModeIndex + " hostMode=" + hostMode + " receiverMuzzle=" + GetCurrentMuzzle() + " receiverMode=" + GetCurrentModeName(GetCurrentMuzzle()));
            GetGame().BDE_USL_RegisterSix12Shot(this, host, ammoType, projectilePosition, shotDirection, inheritedVelocity, launchSpeed, shotId);
        }

        float healthBefore = GetHealth("", "Health");
        bool fired = Fire(0, projectilePosition, shotDirection, inheritedVelocity);
        BDE_USL_ShotWear.Apply(this, fired, healthBefore, shotId);
        if (GetGame().IsServer())
            Print("[BDE SIX12 HEALTH] shotId=" + shotId + " fired=" + fired + " before=" + healthBefore + " after=" + GetHealth("", "Health") + " max=" + GetMaxHealth("", "Health") + " ruined=" + IsRuined());

        if (GetGame().IsServer() && ammoType != "")
        {
            GetGame().BDE_USL_MarkSix12FireResult(shotId, this, ammoType, fired);
            if (host)
                Print("[BDE SIX12 TELEMETRY] POST_FIRE_STATE shotId=" + shotId + " host=" + host + " hostMuzzle=" + host.GetCurrentMuzzle() + " hostModeIndex=" + host.GetCurrentMode(host.GetCurrentMuzzle()) + " hostMode=" + host.GetCurrentModeName(host.GetCurrentMuzzle()) + " fired=" + fired);
        }

        return fired;
    }

    protected void BDE_Six12_LogHostModeState(string stage, Weapon_Base host, int shotId)
    {
        if (!host)
            return;

        int muzzleIndex = host.GetCurrentMuzzle();
        int modeIndex = -1;
        string modeName = "none";

        if (muzzleIndex >= 0 && muzzleIndex < host.GetMuzzleCount())
        {
            modeIndex = host.GetCurrentMode(muzzleIndex);
            modeName = host.GetCurrentModeName(muzzleIndex);
        }

        Print("[BDE SIX12 TELEMETRY] " + stage + " shotId=" + shotId + " host=" + host + " hostMuzzle=" + muzzleIndex + " hostModeIndex=" + modeIndex + " hostMode=" + modeName + " six12Operational=" + host.BDE_USL_IsSix12Operational(this) + " receiverHealth=" + GetHealth("", "Health") + " ruined=" + IsRuined() + " deleting=" + IsSetForDeletion() + " handle=" + BDE_Six12_HasHandle() + " shortBarrel=" + BDE_Six12_HasShortBarrel());
    }

    protected void BDE_Six12_LogDelayedHostModeState(Weapon_Base host, int shotId)
    {
        BDE_Six12_LogHostModeState("POST_CLEANUP_DELAYED", host, shotId);
    }

    void BDE_Six12_ClientPlayDryFire(PlayerBase player)
    {
        if (!GetGame().IsClient() || !player || GetGame().GetPlayer() != player)
            return;

        int now = GetGame().GetTime();
        if (m_BDE_Six12_LastDryFireTime > 0 && now - m_BDE_Six12_LastDryFireTime < 150)
            return;
        m_BDE_Six12_LastDryFireTime = now;

        DryFire(0);
    }

    protected void BDE_Six12_PlayEnvironmentSound(string soundSet, vector position)
    {
        EffectSound sound = SEffectManager.PlaySoundEnviroment(soundSet, position);
        if (sound)
            sound.SetAutodestroy(true);
        else
            Print("[BDE SIX12 SOUND] PlaySoundEnviroment failed for " + soundSet + " at " + position);
    }

    protected void BDE_Six12_PlayShotFX(vector muzzlePosition, vector shotDirection)
    {
        if (GetGame().IsDedicatedServer())
            return;

        BDE_Six12_PlayEnvironmentSound("BDE_Six12_Shot_SoundSet", muzzlePosition);
        BDE_Six12_PlayEnvironmentSound("BDE_Six12_Tail_SoundSet", muzzlePosition);
        BDE_Six12_PlayEnvironmentSound("BDE_Six12_InteriorTail_SoundSet", muzzlePosition);
        BDE_Six12_PlayEnvironmentSound("BDE_Six12_Slapback_SoundSet", muzzlePosition);
        BDE_Six12_PlayEnvironmentSound("BDE_Six12_Tail_2D_SoundSet", muzzlePosition);
        BDE_Six12_PlayEnvironmentSound("BDE_Six12_Shot_Interior_SoundSet", muzzlePosition);

        int muzzleParticleId = ParticleList.GetParticleIDByName("weapon_shot_mp133_01");
        if (muzzleParticleId <= 0)
            muzzleParticleId = ParticleList.GUN_MP133;

        if (muzzleParticleId > 0)
        {
            Particle muzzleParticle = ParticleManager.GetInstance().PlayInWorld(muzzleParticleId, muzzlePosition);
            if (muzzleParticle)
            {
                vector particleOrientation = shotDirection.VectorToAngles();
                particleOrientation[0] = particleOrientation[0] + 90.0;
                muzzleParticle.SetOrientation(particleOrientation);
            }
        }
    }

    protected void BDE_Six12_ServerBroadcastShotFX(PlayerIdentity shooter, vector muzzlePosition, vector shotDirection, int shotId)
    {
        if (!GetGame().IsServer())
            return;

        string shooterId = "";
        if (shooter)
            shooterId = shooter.GetId();

        Param4<vector, vector, string, int> fxData = new Param4<vector, vector, string, int>(muzzlePosition, shotDirection, shooterId, shotId);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_SIX12_FIRE_FX, fxData, true, NULL);
    }

    bool BDE_Six12_ClientFireAttachedFromHost(Weapon_Base host, PlayerBase player)
    {
        if (!GetGame().IsClient() || !host || !player)
            return false;
        if (GetGame().GetPlayer() != player || player.GetItemInHands() != host)
            return false;

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
        if (!player.BDE_USL_NinjinsCanFire())
            return false;
#endif

        if (BDE_Six12_IsFireCycleLocked())
            return false;

        if (!BDE_Six12_CanFireFromHost(host))
        {
            BDE_Six12_ClientPlayDryFire(player);
            return false;
        }

        bool acquiredFromMagazine;
        if (!BDE_Six12_PrepareRound(false, acquiredFromMagazine))
        {
            BDE_Six12_ClientPlayDryFire(player);
            return false;
        }

        vector muzzleStart;
        vector muzzleEnd;
        if (!BDE_Six12_GetMuzzlePointsWS(host, muzzleStart, muzzleEnd))
        {
            BDE_Six12_FinishRound(false, false, acquiredFromMagazine);
            return false;
        }

        vector shotDirection = muzzleEnd - muzzleStart;
        float length = shotDirection.Length();
        if (length <= 0.001)
        {
            BDE_Six12_FinishRound(false, false, acquiredFromMagazine);
            return false;
        }
        shotDirection = shotDirection * (1.0 / length);
        vector inheritedVelocity = GetVelocity(player);
        int shotId = GetGame().GetTime();

        Param4<vector, vector, vector, int> data = new Param4<vector, vector, vector, int>(muzzleEnd, shotDirection, inheritedVelocity, shotId);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_SIX12_FIRE_ATTACHED, data, true);

        vector projectilePosition;
        bool fired = BDE_Six12_FireWithWatchdog(host, muzzleEnd, shotDirection, inheritedVelocity, shotId, projectilePosition);
        if (fired)
        {
            OnFire(0);
            BDE_Six12_PlayShotFX(muzzleEnd, shotDirection);

            DayZPlayerImplement playerImplement = player;
            if (playerImplement)
                playerImplement.GetAimingModel().SetRecoil(this);
        }

        BDE_Six12_FinishRound(false, fired, acquiredFromMagazine);
        BDE_Six12_LogHostModeState("POST_CLEANUP_CLIENT", host, shotId);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_LogDelayedHostModeState, 50, false, host, shotId);
        return fired;
    }

    protected bool BDE_Six12_ValidateFireOwner(PlayerIdentity sender, out PlayerBase player, out Weapon_Base host)
    {
        player = PlayerBase.Cast(GetHierarchyRootPlayer());
        host = Weapon_Base.Cast(GetHierarchyParent());
        if (!sender || !player || !host)
            return false;

        PlayerIdentity identity = player.GetIdentity();
        if (!identity || identity.GetId() != sender.GetId() || player.GetItemInHands() != host)
            return false;

        if (host.IsKindOf("BDE_Six12_StandAloneMount_Weapon"))
        {
            BDE_Six12_StandAloneMount_Weapon mount = BDE_Six12_StandAloneMount_Weapon.Cast(host);
            return mount && mount.BDE_Six12_GetBody() == this;
        }

        return host.BDE_USL_GetSix12() == this && host.BDE_USL_IsSix12ModeSelected();
    }

    protected void BDE_Six12_ServerFireAttached(PlayerIdentity sender, vector muzzlePosition, vector shotDirection, vector clientInheritedVelocity, int shotId)
    {
        if (!GetGame().IsServer())
            return;

        PlayerBase player;
        Weapon_Base host;
        if (!BDE_Six12_ValidateFireOwner(sender, player, host) || !BDE_Six12_CanFireFromHost(host))
            return;

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
        if (!player.BDE_USL_NinjinsCanFire())
            return;
#endif
        if (vector.Distance(muzzlePosition, player.GetPosition()) > 3.0)
            return;

        float directionLength = shotDirection.Length();
        if (directionLength <= 0.001)
            return;
        shotDirection = shotDirection * (1.0 / directionLength);

        bool acquiredFromMagazine;
        if (!BDE_Six12_PrepareRound(true, acquiredFromMagazine))
            return;

        vector serverVelocity = GetVelocity(player);
        vector inheritedVelocity = serverVelocity;
        if (vector.Distance(clientInheritedVelocity, serverVelocity) <= 5.0)
            inheritedVelocity = clientInheritedVelocity;

        vector projectilePosition;
        bool fired = BDE_Six12_FireWithWatchdog(host, muzzlePosition, shotDirection, inheritedVelocity, shotId, projectilePosition);
        if (fired)
        {
            OnFire(0);
            BDE_Six12_ServerBroadcastShotFX(sender, muzzlePosition, shotDirection, shotId);
        }

        BDE_Six12_FinishRound(true, fired, acquiredFromMagazine);
        BDE_Six12_LogHostModeState("POST_CLEANUP_SERVER", host, shotId);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_LogDelayedHostModeState, 50, false, host, shotId);
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_SIX12_SWAP_SPECIFIC_MAGAZINE)
        {
            Param1<EntityAI> swapData = new Param1<EntityAI>(null);
            ctx.Read(swapData);
            if (GetGame().IsServer())
                BDE_Six12_LogReload("ignored legacy exact-mag swap RPC; cylinder is permanent");
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_SIX12_LOAD_SPECIFIC_AMMO)
        {
            Param1<EntityAI> ammoData = new Param1<EntityAI>(null);
            if (!ctx.Read(ammoData) || !GetGame().IsServer())
                return;

            Magazine sourceAmmo = Magazine.Cast(ammoData.param1);
            PlayerBase ammoPlayer;
            Weapon_Base ammoHost;
            if (sourceAmmo && BDE_Six12_ValidateInventoryInteractionOwner(sender, sourceAmmo, ammoPlayer, ammoHost) && BDE_Six12_CanDirectLoadAmmo(sourceAmmo, false))
                BDE_Six12_ServerBeginLooseReload(ammoPlayer, ammoHost, sourceAmmo, true);
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_SIX12_RELOAD_REQUEST)
        {
            Param1<int> reloadData = new Param1<int>(0);
            if (ctx.Read(reloadData))
                BDE_Six12_ServerBeginReload(sender);
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_SIX12_RELOAD_RELEASE)
        {
            Param1<int> releaseData = new Param1<int>(0);
            if (ctx.Read(releaseData))
                BDE_Six12_ServerRequestReloadStop(sender);
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_SIX12_RELOAD_FX)
        {
            Param2<float, float> reloadFX = new Param2<float, float>(0.0, 0.0);
            if (!ctx.Read(reloadFX) || GetGame().IsDedicatedServer())
                return;

            BDE_Six12_Magazine reloadMag = BDE_Six12_GetMagazine();
            if (reloadMag)
            {
                reloadMag.BDE_Six12_UpdateBulletSelections();
                reloadMag.BDE_Six12_SetVisualPose(reloadFX.param1, reloadFX.param2);
                BDE_Six12_BeginCylinderRotationLock();
            }
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_SIX12_FIRE_ATTACHED)
        {
            Param4<vector, vector, vector, int> data = new Param4<vector, vector, vector, int>(vector.Zero, vector.Zero, vector.Zero, -1);
            if (ctx.Read(data))
                BDE_Six12_ServerFireAttached(sender, data.param1, data.param2, data.param3, data.param4);
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_SIX12_FIRE_FX)
        {
            Param4<vector, vector, string, int> fxData = new Param4<vector, vector, string, int>(vector.Zero, vector.Zero, "", -1);
            if (!ctx.Read(fxData) || GetGame().IsDedicatedServer())
                return;

            PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
            if (localPlayer && localPlayer.GetIdentity() && localPlayer.GetIdentity().GetId() == fxData.param3)
                return;

            BDE_Six12_PlayShotFX(fxData.param1, fxData.param2);
        }
    }
}

class BDE_Six12_FDE extends BDE_Six12
{
}

class BDE_Six12_Handle extends Inventory_Base
{
}
class BDE_Six12_Handle_FDE extends BDE_Six12_Handle
{
}
class BDE_Six12_LongBarrel extends Inventory_Base
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (parent && (parent.IsKindOf("BDE_Six12_StandAloneMount") || parent.IsKindOf("BDE_Six12_StandAloneMount_Weapon")))
        {
            if (!parent.FindAttachmentBySlotName("BDE_Six12"))
                return false;
        }
        return super.CanPutAsAttachment(parent);
    }
}

class BDE_Six12_ShortBarrel extends Inventory_Base
{
}
