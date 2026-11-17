modded class BDE_Six12
{
    protected bool m_BDE_USL_SNAFUSix12VariantSwapInProgress;

    override void EEInit()
    {
        super.EEInit();
        BDE_USL_SNAFU_RequestSix12VariantRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_USL_SNAFU_RequestSix12VariantRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_USL_SNAFU_RequestSix12VariantRefresh();
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        BDE_USL_SNAFU_RequestSix12VariantRefresh();
    }

    protected bool BDE_USL_SNAFU_IsManagedSix12Variant()
    {
        string typeName = GetType();

        if (typeName == "BDE_Six12" || typeName == "BDE_Six12_FDE")
            return true;

        return typeName == "BDE_Six12_SNAFU_Back" || typeName == "BDE_Six12_SNAFU_Back_FDE" || typeName == "BDE_Six12_SNAFU_B1" || typeName == "BDE_Six12_SNAFU_B1_FDE" || typeName == "BDE_Six12_SNAFU_B2" || typeName == "BDE_Six12_SNAFU_B2_FDE" || typeName == "BDE_Six12_SNAFU_MK47" || typeName == "BDE_Six12_SNAFU_MK47_FDE";
    }

    protected bool BDE_USL_SNAFU_IsSix12FDE()
    {
        return IsKindOf("BDE_Six12_FDE");
    }

    protected int BDE_USL_SNAFU_GetSix12VariantForHost(Weapon_Base host)
    {
        if (!host)
            return 0;

        if (host.IsKindOf("SNAFU_MK4716Gun"))
            return 4;

        if (host.IsKindOf("SNAFU_AR15_Modular16_GUN") || host.IsKindOf("SNAFU_M4556_Modular16_GUN") || host.IsKindOf("SNAFU_M4556_Modular14_GUN"))
            return 2;

        if (host.IsKindOf("GCGN_HK416_Base") || host.IsKindOf("GCGN_M110_Base") || host.IsKindOf("HK416_Base") || host.IsKindOf("SNHK417_Base") || host.IsKindOf("MK18_Base") || host.IsKindOf("ACR_Base") || host.IsKindOf("SNAFUSA80_Base") || host.IsKindOf("SNAFUMk12_Base") || host.IsKindOf("SNAFURSASS_Base") || host.IsKindOf("Snafu_ScarH_Base") || host.IsKindOf("SNAFU_Saint_Base") || host.IsKindOf("SNAFU_M4556_Modular10_GUN"))
            return 1;

        if (host.IsKindOf("SNAFU_SR25_Base"))
            return 3;

        return 0;
    }

    override bool BDE_Six12_IsReceiverSwapInProgress()
    {
        return m_BDE_USL_SNAFUSix12VariantSwapInProgress || super.BDE_Six12_IsReceiverSwapInProgress();
    }

    override void BDE_Six12_RequestButtPadRefresh()
    {
        if (m_BDE_USL_SNAFUSix12VariantSwapInProgress)
            return;

        super.BDE_Six12_RequestButtPadRefresh();
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (m_BDE_USL_SNAFUSix12VariantSwapInProgress)
            return true;

        return super.CanDetachAttachment(parent);
    }

    protected void BDE_USL_SNAFU_RequestSix12VariantRefresh()
    {
        if (!GetGame().IsServer() || m_BDE_USL_SNAFUSix12VariantSwapInProgress || IsSetForDeletion())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_SNAFU_RefreshSix12Variant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_SNAFU_RefreshSix12Variant, 150, false);
    }

    protected void BDE_USL_SNAFU_RefreshSix12Variant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || m_BDE_USL_SNAFUSix12VariantSwapInProgress)
            return;

        if (!BDE_USL_SNAFU_IsManagedSix12Variant())
            return;

        bool useFDE = BDE_USL_SNAFU_IsSix12FDE();
        string targetType = "BDE_Six12";

        if (useFDE)
            targetType = "BDE_Six12_FDE";

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host && !BDE_USL_SNAFU_CompatibilityState.HostAllowsLauncher(host, "BDE_Six12"))
        {
            m_BDE_USL_SNAFUSix12VariantSwapInProgress = true;
            host.GetInventory().DropEntity(InventoryMode.SERVER, host, this);
            m_BDE_USL_SNAFUSix12VariantSwapInProgress = false;
            return;
        }

        int variant = BDE_USL_SNAFU_GetSix12VariantForHost(host);

        if (variant == 1)
        {
            targetType = "BDE_Six12_SNAFU_B1";
            if (useFDE)
                targetType = "BDE_Six12_SNAFU_B1_FDE";
        }
        else if (variant == 2)
        {
            targetType = "BDE_Six12_SNAFU_B2";
            if (useFDE)
                targetType = "BDE_Six12_SNAFU_B2_FDE";
        }
        else if (variant == 3)
        {
            targetType = "BDE_Six12_SNAFU_Back";
            if (useFDE)
                targetType = "BDE_Six12_SNAFU_Back_FDE";
        }
        else if (variant == 4)
        {
            targetType = "BDE_Six12_SNAFU_MK47";
            if (useFDE)
                targetType = "BDE_Six12_SNAFU_MK47_FDE";
        }

        if (GetType() == targetType)
        {
            BDE_Six12_RequestCylinderVisualRefresh();
            BDE_Six12_RequestButtPadRefresh();
            return;
        }

        m_BDE_USL_SNAFUSix12VariantSwapInProgress = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(this, targetType, owner);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_SNAFUSix12VariantSwapInProgress = false;
    }
}
