modded class Weapon_Base
{
    bool BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_IsCompatibleHost())
            return true;

        BDE_UnderSlungLauncher_Base launcher = BDE_UnderSlungLauncher_Base.Cast(attachment);

        if (launcher)
        {
            if (!BDE_USL_IsLauncherSlot(slotId))
                return false;

            return BDE_USL_CanAttachLauncher(launcher, slotId);
        }

        BDE_Six12 six12 = BDE_Six12.Cast(attachment);
        if (six12)
        {
            if (!BDE_USL_IsLauncherSlot(slotId))
                return false;

            return BDE_USL_CanAttachSix12(six12, slotId);
        }

        EntityAI mountedUnderbarrel = BDE_USL_GetUnderbarrelEntity();
        if (mountedUnderbarrel && !BDE_USL_CanAttachWithLauncher(mountedUnderbarrel, attachment, slotId))
            return false;

        return true;
    }
}

modded class TF_M4A1_Base
{
    protected void BDE_USL_Flava_M4SetSimpleSelection(string selectionName, bool visible)
    {
        TStringArray selectionNames = new TStringArray;
        ConfigGetTextArray("simpleHiddenSelections", selectionNames);
        int selectionId = selectionNames.Find(selectionName);

        if (selectionId >= 0)
            SetSimpleHiddenSelectionState(selectionId, visible);
    }

    protected bool BDE_USL_Flava_M4HasVanillaRIS()
    {
        EntityAI handguard = FindAttachmentBySlotName("WeaponHandguardM4");

        if (!handguard)
            return false;

        return handguard.IsKindOf("M4_RISHndgrd");
    }

    protected void BDE_USL_Flava_M4ApplyVanillaRISState(bool attached)
    {
        if (attached)
        {
            BDE_USL_Flava_M4SetSimpleSelection("gasBlock_High", true);
            BDE_USL_Flava_M4SetSimpleSelection("gasBlock_Low", false);
            BDE_USL_Flava_M4SetSimpleSelection("long_dd", false);
            BDE_USL_Flava_M4SetSimpleSelection("short_dd", false);
            BDE_USL_Flava_M4SetSimpleSelection("short", true);
            BDE_USL_Flava_M4SetSimpleSelection("geissele", false);
            return;
        }

        BDE_USL_Flava_M4SetSimpleSelection("gasBlock_High", true);
        BDE_USL_Flava_M4SetSimpleSelection("gasBlock_Low", false);
        BDE_USL_Flava_M4SetSimpleSelection("long_dd", false);
        BDE_USL_Flava_M4SetSimpleSelection("short_dd", false);
        BDE_USL_Flava_M4SetSimpleSelection("short", false);
        BDE_USL_Flava_M4SetSimpleSelection("geissele", false);
    }

    override void EEInit()
    {
        super.EEInit();

        if (BDE_USL_Flava_M4HasVanillaRIS())
            BDE_USL_Flava_M4ApplyVanillaRISState(true);
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (item && item.IsKindOf("M4_RISHndgrd"))
            BDE_USL_Flava_M4ApplyVanillaRISState(true);
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (item && item.IsKindOf("M4_RISHndgrd"))
            BDE_USL_Flava_M4ApplyVanillaRISState(false);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        string slotName = InventorySlots.GetSlotName(slot_id);

        if (BDE_USL_GetUnderbarrelEntity() && BDE_USL_IsBlockedSlot(slot_id))
            return false;

        if (BDE_USL_Flava_M4HasVanillaRIS())
        {
            if (slotName == "weaponGrip" || slotName == "weaponBipod" || slotName == "weaponFlashlight")
                return true;
        }

        return super.CanDisplayAttachmentSlot(slot_id);
    }
}

modded class TF_AK74M_Base
{
    bool BDE_USL_Flava_GP25CompatibleAK()
    {
        string hostType = GetType();

        return hostType == "TF_AK101" || hostType == "TF_AK102" || hostType == "TF_AK103" || hostType == "TF_AK104" || hostType == "TF_AK105" || hostType == "TF_AK74M" || hostType == "TF_AKM" || hostType == "TF_AKMN" || hostType == "TF_VPO136";
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (BDE_USL_Flava_GP25CompatibleAK() && InventorySlots.GetSlotName(slot_id) == "weaponGrip")
            return true;

        return super.CanDisplayAttachmentSlot(slot_id);
    }
}

modded class TF_AKM_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_MAR_10_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_SCAR_L_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_SCAR_L_CQC_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_SCAR_H_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_SCAR_H_CQC_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_SCAR_20_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_MK47_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_M16A4_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_SR25_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_SVCh_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_PKM_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_PKP_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

modded class TF_AN94M
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!BDE_USL_Flava_CanReceiveLauncherInConfiguredSlot(attachment, slotId))
            return false;

        return super.CanReceiveAttachment(attachment, slotId);
    }
}

class BDE_USL_FlavaM203VariantSwapLambda : TurnItemIntoItemLambda
{
    protected bool m_BDE_USL_HadLiveRound;
    protected float m_BDE_USL_ChamberDamage;
    protected string m_BDE_USL_ChamberAmmoType;
    protected string m_BDE_USL_ChamberSourceType;

    void BDE_USL_FlavaM203VariantSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player, bool hadLiveRound, float chamberDamage, string chamberAmmoType, string chamberSourceType)
    {
        m_BDE_USL_HadLiveRound = hadLiveRound;
        m_BDE_USL_ChamberDamage = chamberDamage;
        m_BDE_USL_ChamberAmmoType = chamberAmmoType;
        m_BDE_USL_ChamberSourceType = chamberSourceType;
    }

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

        BDE_M203 replacement = BDE_M203.Cast(new_item);

        if (!replacement || !GetGame().IsServer())
            return;

        int muzzleIndex = 0;

        if (m_BDE_USL_HadLiveRound && replacement.GetMuzzleCount() > muzzleIndex && !replacement.IsChamberFull(muzzleIndex))
            replacement.PushCartridgeToChamber(muzzleIndex, m_BDE_USL_ChamberDamage, m_BDE_USL_ChamberAmmoType);

        if (m_BDE_USL_HadLiveRound && m_BDE_USL_ChamberSourceType != "")
            replacement.BDE_USL_SetLoadedMagazineSourceType(m_BDE_USL_ChamberSourceType);

        replacement.RandomizeFSMState();
        replacement.BDE_USL_SyncChamberVisual();
        replacement.Synchronize();
        replacement.SetSynchDirty();
    }
}

modded class BDE_M203
{
    protected bool m_BDE_USL_FlavaVariantSwapInProgress;
    protected bool m_BDE_USL_FlavaM203ButtPadSwapInProgress;

    override void EEInit()
    {
        super.EEInit();
        BDE_USL_Flava_RequestM203VariantRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_USL_Flava_RequestM203VariantRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_USL_Flava_RequestM203VariantRefresh();
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        BDE_USL_Flava_RequestM203VariantRefresh();
    }

    protected bool BDE_USL_Flava_IsManagedM203Variant()
    {
        string typeName = GetType();

        return typeName == "BDE_M203" || typeName == "BDE_USL_M203_Flava_AN94M" || typeName == "BDE_USL_M203_Flava_M16A4" || typeName == "BDE_USL_M203_Flava_SVCh";
    }

    override void BDE_M203_RequestButtPadRefresh()
    {
        if (m_BDE_USL_FlavaM203ButtPadSwapInProgress)
            return;

        super.BDE_M203_RequestButtPadRefresh();
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (m_BDE_USL_FlavaVariantSwapInProgress)
            return true;

        return super.CanDetachAttachment(parent);
    }

    void BDE_USL_Flava_RequestM203VariantRefresh()
    {
        if (!GetGame().IsServer())
            return;

        if (m_BDE_USL_FlavaVariantSwapInProgress)
            return;

        if (!BDE_USL_Flava_IsManagedM203Variant())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Flava_RefreshM203Variant, 50, false);
    }

    void BDE_USL_Flava_RefreshM203Variant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        if (!BDE_USL_Flava_IsManagedM203Variant())
            return;

        string targetType = "BDE_M203";
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host)
        {
            string hostType = host.GetType();

            if (hostType == "TF_AN94M")
                targetType = "BDE_USL_M203_Flava_AN94M";
            else if (hostType == "TF_M4A1" || hostType == "TF_M4A1_CQBR" || host.IsKindOf("TF_M16A4_Base"))
                targetType = "BDE_USL_M203_Flava_M16A4";
            else if (host.IsKindOf("TF_SVCh_Base"))
                targetType = "BDE_USL_M203_Flava_SVCh";
        }

        if (GetType() == targetType)
        {
            BDE_M203_RequestButtPadRefresh();
            return;
        }

        m_BDE_USL_FlavaVariantSwapInProgress = true;

        bool hadLiveRound = false;
        float chamberDamage = 0.0;
        string chamberAmmoType = "";
        int muzzleIndex = 0;

        if (GetMuzzleCount() > muzzleIndex && IsChamberFull(muzzleIndex) && !IsChamberFiredOut(muzzleIndex))
            hadLiveRound = GetCartridgeInfo(muzzleIndex, chamberDamage, chamberAmmoType);

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        string chamberSourceType = BDE_USL_GetLoadedMagazineSourceType();
        BDE_USL_FlavaM203VariantSwapLambda lambda = new BDE_USL_FlavaM203VariantSwapLambda(this, targetType, owner, hadLiveRound, chamberDamage, chamberAmmoType, chamberSourceType);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_FlavaVariantSwapInProgress = false;
    }

    override protected void BDE_M203_RefreshButtPad()
    {
        super.BDE_M203_RefreshButtPad();

        if (m_BDE_USL_FlavaM203ButtPadSwapInProgress || !GetGame().IsServer() || IsSetForDeletion())
            return;

        EntityAI buttPad = FindAttachmentBySlotName("BDE_M203_ButtPad");
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!buttPad || !host)
            return;

        string hostType = host.GetType();
        string targetPadType = "";

        if (BDE_USL_Flava_M203IsShortAK(hostType))
            targetPadType = "BDE_USL_GP25_ButtPad_FlavaShortAK";
        else if (BDE_USL_Flava_M203IsFullLengthAK(hostType))
            targetPadType = "BDE_USL_GP25_ButtPad_FlavaAK";
        else
            return;

        if (buttPad.GetType() == targetPadType)
            return;

        m_BDE_USL_FlavaM203ButtPadSwapInProgress = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(buttPad, targetPadType, owner);
        lambda.SetTransferParams(true, true, true);
        buttPad.GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_FlavaM203ButtPadSwapInProgress = false;
    }

    protected bool BDE_USL_Flava_M203IsShortAK(string hostType)
    {
        return hostType == "TF_AK102" || hostType == "TF_AK104" || hostType == "TF_AK105";
    }

    protected bool BDE_USL_Flava_M203IsFullLengthAK(string hostType)
    {
        return hostType == "TF_AK101" || hostType == "TF_AK103" || hostType == "TF_AK74M" || hostType == "TF_AKM" || hostType == "TF_AKMN" || hostType == "TF_VPO136";
    }

    protected bool BDE_USL_Flava_M203HasPlasticAKButtstock(Weapon_Base host)
    {
        if (!host)
            return false;

        EntityAI buttstock = host.FindAttachmentBySlotName("weaponButtstockAK");

        if (!buttstock)
            return false;

        return buttstock.IsKindOf("AK_PlasticBttstck");
    }

    override protected bool BDE_M203_HostSupportsButtPad()
    {
        if (super.BDE_M203_HostSupportsButtPad())
            return true;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!host)
            return false;

        string hostType = host.GetType();

        if (!BDE_USL_Flava_M203IsFullLengthAK(hostType) && !BDE_USL_Flava_M203IsShortAK(hostType))
            return false;

        return BDE_USL_Flava_M203HasPlasticAKButtstock(host);
    }
}

modded class BDE_Six12
{
    protected bool m_BDE_USL_FlavaSix12VariantSwapInProgress;
    protected bool m_BDE_USL_FlavaSix12ButtPadSwapInProgress;

    override void EEInit()
    {
        super.EEInit();
        BDE_USL_Flava_RequestSix12VariantRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_USL_Flava_RequestSix12VariantRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_USL_Flava_RequestSix12VariantRefresh();
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        BDE_USL_Flava_RequestSix12VariantRefresh();
    }

    protected bool BDE_USL_Flava_IsManagedSix12Variant()
    {
        string typeName = GetType();
        if (typeName == "BDE_Six12" || typeName == "BDE_Six12_FDE")
            return true;
        if (typeName == "BDE_USL_Six12_Flava_M16A4" || typeName == "BDE_USL_Six12_Flava_M16A4_FDE")
            return true;
        if (typeName == "BDE_USL_Six12_Flava_SVCh" || typeName == "BDE_USL_Six12_Flava_SVCh_FDE")
            return true;
        return false;
    }

    protected bool BDE_USL_Flava_IsSix12FDE()
    {
        return IsKindOf("BDE_Six12_FDE");
    }

    override bool BDE_Six12_IsReceiverSwapInProgress()
    {
        return m_BDE_USL_FlavaSix12VariantSwapInProgress;
    }

    override void BDE_Six12_RequestButtPadRefresh()
    {
        if (m_BDE_USL_FlavaSix12VariantSwapInProgress || m_BDE_USL_FlavaSix12ButtPadSwapInProgress)
            return;

        super.BDE_Six12_RequestButtPadRefresh();
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (m_BDE_USL_FlavaSix12VariantSwapInProgress)
            return true;

        return super.CanDetachAttachment(parent);
    }

    protected void BDE_USL_Flava_RequestSix12VariantRefresh()
    {
        if (!GetGame().IsServer() || m_BDE_USL_FlavaSix12VariantSwapInProgress || IsSetForDeletion())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_Flava_RefreshSix12Variant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Flava_RefreshSix12Variant, 150, false);
    }

    protected void BDE_USL_Flava_RefreshSix12Variant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || m_BDE_USL_FlavaSix12VariantSwapInProgress)
            return;
        if (!BDE_USL_Flava_IsManagedSix12Variant())
            return;

        bool useFDE = BDE_USL_Flava_IsSix12FDE();
        string targetType = "BDE_Six12";
        if (useFDE)
            targetType = "BDE_Six12_FDE";

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (host)
        {
            string hostType = host.GetType();
            if (hostType == "TF_M4A1" || hostType == "TF_M4A1_CQBR" || host.IsKindOf("TF_M16A4_Base"))
            {
                targetType = "BDE_USL_Six12_Flava_M16A4";
                if (useFDE)
                    targetType = "BDE_USL_Six12_Flava_M16A4_FDE";
            }
            else if (host.IsKindOf("TF_SVCh_Base"))
            {
                targetType = "BDE_USL_Six12_Flava_SVCh";
                if (useFDE)
                    targetType = "BDE_USL_Six12_Flava_SVCh_FDE";
            }
        }

        if (GetType() == targetType)
        {
            BDE_Six12_RequestCylinderVisualRefresh();
            BDE_Six12_RequestButtPadRefresh();
            return;
        }

        m_BDE_USL_FlavaSix12VariantSwapInProgress = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(this, targetType, owner);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_FlavaSix12VariantSwapInProgress = false;
    }

    override protected void BDE_Six12_RefreshButtPad()
    {
        super.BDE_Six12_RefreshButtPad();

        if (m_BDE_USL_FlavaSix12ButtPadSwapInProgress || !GetGame().IsServer() || IsSetForDeletion())
            return;

        EntityAI buttPad = FindAttachmentBySlotName("BDE_Six12_ButtPad");
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!buttPad || !host)
            return;

        string hostType = host.GetType();
        string targetPadType = "";

        if (BDE_USL_Flava_Six12IsShortAK(hostType))
            targetPadType = "BDE_USL_GP25_ButtPad_FlavaShortAK";
        else if (BDE_USL_Flava_Six12IsFullLengthAK(hostType))
            targetPadType = "BDE_USL_GP25_ButtPad_FlavaAK";
        else
            return;

        if (buttPad.GetType() == targetPadType)
            return;

        m_BDE_USL_FlavaSix12ButtPadSwapInProgress = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(buttPad, targetPadType, owner);
        lambda.SetTransferParams(true, true, true);
        buttPad.GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_FlavaSix12ButtPadSwapInProgress = false;
    }

    protected bool BDE_USL_Flava_Six12IsShortAK(string hostType)
    {
        return hostType == "TF_AK102" || hostType == "TF_AK104" || hostType == "TF_AK105";
    }

    protected bool BDE_USL_Flava_Six12IsFullLengthAK(string hostType)
    {
        return hostType == "TF_AK101" || hostType == "TF_AK103" || hostType == "TF_AK74M" || hostType == "TF_AKM" || hostType == "TF_AKMN" || hostType == "TF_VPO136";
    }

    protected bool BDE_USL_Flava_Six12HasPlasticAKButtstock(Weapon_Base host)
    {
        if (!host)
            return false;

        EntityAI buttstock = host.FindAttachmentBySlotName("weaponButtstockAK");
        if (!buttstock)
            return false;

        return buttstock.IsKindOf("AK_PlasticBttstck");
    }

    override protected bool BDE_Six12_HostSupportsButtPad()
    {
        if (super.BDE_Six12_HostSupportsButtPad())
            return true;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!host)
            return false;

        string hostType = host.GetType();
        if (!BDE_USL_Flava_Six12IsFullLengthAK(hostType) && !BDE_USL_Flava_Six12IsShortAK(hostType))
            return false;

        return BDE_USL_Flava_Six12HasPlasticAKButtstock(host);
    }
}

modded class BDE_GP25
{
    protected bool m_BDE_USL_FlavaVariantSwapInProgress;
    protected bool m_BDE_USL_FlavaButtPadSwapInProgress;

    override void BDE_GP25_RequestVariantRefresh()
    {
        if (m_BDE_USL_FlavaVariantSwapInProgress || m_BDE_USL_FlavaButtPadSwapInProgress)
            return;

        super.BDE_GP25_RequestVariantRefresh();
    }

    override void BDE_GP25_RefreshVariant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        super.BDE_GP25_RefreshVariant();

        if (IsSetForDeletion())
            return;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        string targetType = "BDE_GP25";

        if (host && BDE_USL_Flava_IsShortAK(host.GetType()))
            targetType = "BDE_USL_GP25_Flava_ShortAK";

        if (GetType() != targetType)
        {
            m_BDE_USL_FlavaVariantSwapInProgress = true;

            bool hadLiveRound = false;
            float chamberDamage = 0.0;
            string chamberAmmoType = "";
            int muzzleIndex = 0;

            if (GetMuzzleCount() > muzzleIndex && IsChamberFull(muzzleIndex) && !IsChamberFiredOut(muzzleIndex))
                hadLiveRound = GetCartridgeInfo(muzzleIndex, chamberDamage, chamberAmmoType);

            PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
            string chamberSourceType = BDE_USL_GetLoadedMagazineSourceType();
            BDE_GP25_TypeSwapLambda lambda = new BDE_GP25_TypeSwapLambda(this, targetType, owner, hadLiveRound, chamberDamage, chamberAmmoType, chamberSourceType);
            lambda.SetTransferParams(true, true, true);
            GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
            m_BDE_USL_FlavaVariantSwapInProgress = false;
            return;
        }

        BDE_USL_Flava_RefreshButtPadVariant();
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (m_BDE_USL_FlavaVariantSwapInProgress)
            return true;

        return super.CanDetachAttachment(parent);
    }

    protected void BDE_USL_Flava_RefreshButtPadVariant()
    {
        if (m_BDE_USL_FlavaButtPadSwapInProgress)
            return;

        EntityAI buttPad = FindAttachmentBySlotName("BDE_GP25_ButtPad");

        if (!buttPad)
            return;

        string targetPadType = "BDE_GP25_ButtPad";
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host)
        {
            string hostType = host.GetType();

            if (BDE_USL_Flava_IsShortAK(hostType))
                targetPadType = "BDE_USL_GP25_ButtPad_FlavaShortAK";
            else if (BDE_USL_Flava_IsFullLengthAK(hostType))
                targetPadType = "BDE_USL_GP25_ButtPad_FlavaAK";
        }

        if (buttPad.GetType() == targetPadType)
            return;

        m_BDE_USL_FlavaButtPadSwapInProgress = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(buttPad, targetPadType, owner);
        lambda.SetTransferParams(true, true, true);
        buttPad.GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_FlavaButtPadSwapInProgress = false;
    }

    protected bool BDE_USL_Flava_IsShortAK(string hostType)
    {
        return hostType == "TF_AK102" || hostType == "TF_AK104" || hostType == "TF_AK105";
    }

    protected bool BDE_USL_Flava_IsFullLengthAK(string hostType)
    {
        return hostType == "TF_AK101" || hostType == "TF_AK103" || hostType == "TF_AK74M" || hostType == "TF_AKM" || hostType == "TF_AKMN" || hostType == "TF_VPO136";
    }

    protected bool BDE_USL_Flava_HasPlasticAKButtstock(Weapon_Base host)
    {
        if (!host)
            return false;

        EntityAI buttstock = host.FindAttachmentBySlotName("weaponButtstockAK");

        if (!buttstock)
            return false;

        return buttstock.IsKindOf("AK_PlasticBttstck");
    }

    override protected bool BDE_GP25_HostSupportsButtPad()
    {
        if (super.BDE_GP25_HostSupportsButtPad())
            return true;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!host)
            return false;

        string hostType = host.GetType();

        if (!BDE_USL_Flava_IsFullLengthAK(hostType) && !BDE_USL_Flava_IsShortAK(hostType))
            return false;

        return BDE_USL_Flava_HasPlasticAKButtstock(host);
    }
}

modded class BDE_GP25_ButtPad
{
    override void EEInit()
    {
        super.EEInit();
        BDE_USL_Flava_QueueDetachedPadNormalize();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_USL_Flava_QueueDetachedPadNormalize();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_USL_Flava_QueueDetachedPadNormalize();
    }

    protected void BDE_USL_Flava_QueueDetachedPadNormalize()
    {
        if (!GetGame().IsServer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_Flava_NormalizeDetachedPad);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Flava_NormalizeDetachedPad, 100, false);
    }

    protected void BDE_USL_Flava_NormalizeDetachedPad()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        EntityAI parent = GetHierarchyParent();

        if (BDE_GP25.Cast(parent) || BDE_M203.Cast(parent) || BDE_Six12.Cast(parent))
            return;

        if (GetType() == "BDE_GP25_ButtPad")
            return;

        InventoryLocation padLocation = new InventoryLocation();
        if (!GetInventory().GetCurrentInventoryLocation(padLocation) || !padLocation.IsValid() || padLocation.GetType() == InventoryLocationType.UNKNOWN)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_Flava_NormalizeDetachedPad);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Flava_NormalizeDetachedPad, 100, false);
            return;
        }

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(this, "BDE_GP25_ButtPad", owner);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }
}
