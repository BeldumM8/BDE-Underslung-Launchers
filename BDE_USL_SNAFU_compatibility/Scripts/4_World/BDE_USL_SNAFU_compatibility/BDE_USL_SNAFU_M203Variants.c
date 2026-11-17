class BDE_USL_SNAFUM203VariantSwapLambda : TurnItemIntoItemLambda
{
    protected bool m_BDE_USL_HadLiveRound;
    protected float m_BDE_USL_ChamberDamage;
    protected string m_BDE_USL_ChamberAmmoType;
    protected string m_BDE_USL_ChamberSourceType;

    void BDE_USL_SNAFUM203VariantSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player, bool hadLiveRound, float chamberDamage, string chamberAmmoType, string chamberSourceType)
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
    protected bool m_BDE_USL_SNAFUVariantSwapInProgress;

    override void EEInit()
    {
        super.EEInit();
        BDE_USL_SNAFU_RequestM203VariantRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_USL_SNAFU_RequestM203VariantRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_USL_SNAFU_RequestM203VariantRefresh();
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        BDE_USL_SNAFU_RequestM203VariantRefresh();
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (m_BDE_USL_SNAFUVariantSwapInProgress)
            return true;

        return super.CanDetachAttachment(parent);
    }

    protected bool BDE_USL_SNAFU_IsManagedM203Variant()
    {
        string typeName = GetType();

        return typeName == "BDE_M203" || typeName == "BDE_M203_SNAFU_Back" || typeName == "BDE_M203_SNAFU_B1" || typeName == "BDE_M203_SNAFU_B2" || typeName == "BDE_M203_SNAFU_MK47" || typeName == "BDE_M203_SNAFU_KAC_Forward";
    }

    protected string BDE_USL_SNAFU_GetM203VariantForHost(Weapon_Base host)
    {
        if (!host)
            return "BDE_M203";

        if (host.IsKindOf("SNAFU_KAC_Base"))
            return "BDE_M203_SNAFU_KAC_Forward";

        if (host.IsKindOf("SNAFU_MK4716Gun"))
            return "BDE_M203_SNAFU_MK47";

        if (host.IsKindOf("SNAFU_AR15_Modular16_GUN") || host.IsKindOf("SNAFU_M4556_Modular16_GUN") || host.IsKindOf("SNAFU_M4556_Modular14_GUN"))
            return "BDE_M203_SNAFU_B2";

        if (host.IsKindOf("GCGN_HK416_Base") || host.IsKindOf("GCGN_M110_Base") || host.IsKindOf("HK416_Base") || host.IsKindOf("SNHK417_Base") || host.IsKindOf("MK18_Base") || host.IsKindOf("ACR_Base") || host.IsKindOf("SNAFUSA80_Base") || host.IsKindOf("SNAFUMk12_Base") || host.IsKindOf("SNAFURSASS_Base") || host.IsKindOf("Snafu_ScarH_Base") || host.IsKindOf("SNAFU_Saint_Base") || host.IsKindOf("SNAFU_M4556_Modular10_GUN"))
            return "BDE_M203_SNAFU_B1";

        if (host.IsKindOf("SNAFU_SR25_Base"))
            return "BDE_M203_SNAFU_Back";

        return "BDE_M203";
    }

    void BDE_USL_SNAFU_RequestM203VariantRefresh()
    {
        if (!GetGame().IsServer())
            return;

        if (m_BDE_USL_SNAFUVariantSwapInProgress)
            return;

        if (!BDE_USL_SNAFU_IsManagedM203Variant())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_SNAFU_RefreshM203Variant, 50, false);
    }

    void BDE_USL_SNAFU_RefreshM203Variant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        if (!BDE_USL_SNAFU_IsManagedM203Variant())
            return;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host && !BDE_USL_SNAFU_CompatibilityState.HostAllowsLauncher(host, "BDE_M203"))
        {
            m_BDE_USL_SNAFUVariantSwapInProgress = true;
            host.GetInventory().DropEntity(InventoryMode.SERVER, host, this);
            m_BDE_USL_SNAFUVariantSwapInProgress = false;
            return;
        }

        string targetType = BDE_USL_SNAFU_GetM203VariantForHost(host);

        if (GetType() == targetType)
            return;

        m_BDE_USL_SNAFUVariantSwapInProgress = true;

        bool hadLiveRound = false;
        float chamberDamage = 0.0;
        string chamberAmmoType = "";
        int muzzleIndex = 0;

        if (GetMuzzleCount() > muzzleIndex && IsChamberFull(muzzleIndex) && !IsChamberFiredOut(muzzleIndex))
            hadLiveRound = GetCartridgeInfo(muzzleIndex, chamberDamage, chamberAmmoType);

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        string chamberSourceType = BDE_USL_GetLoadedMagazineSourceType();
        BDE_USL_SNAFUM203VariantSwapLambda lambda = new BDE_USL_SNAFUM203VariantSwapLambda(this, targetType, owner, hadLiveRound, chamberDamage, chamberAmmoType, chamberSourceType);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_SNAFUVariantSwapInProgress = false;
    }
}
