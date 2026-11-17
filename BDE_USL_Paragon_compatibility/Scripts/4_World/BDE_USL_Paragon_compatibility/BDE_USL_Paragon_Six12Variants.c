modded class BDE_Six12
{
    protected bool m_BDE_USL_ParagonSix12VariantSwapInProgress;

    override void EEInit()
    {
        super.EEInit();
        BDE_USL_Paragon_RequestSix12VariantRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_USL_Paragon_RequestSix12VariantRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_USL_Paragon_RequestSix12VariantRefresh();
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        BDE_USL_Paragon_RequestSix12VariantRefresh();
    }

    protected bool BDE_USL_Paragon_IsManagedSix12Variant()
    {
        string typeName = GetType();

        if (typeName == "BDE_Six12" || typeName == "BDE_Six12_FDE")
            return true;

        if (typeName == "BDE_Six12_Paragon_AR15" || typeName == "BDE_Six12_Paragon_AR15_FDE")
            return true;

        if (typeName == "BDE_Six12_Paragon_Aero" || typeName == "BDE_Six12_Paragon_Aero_FDE")
            return true;

        if (typeName == "BDE_Six12_Paragon_MK14" || typeName == "BDE_Six12_Paragon_MK14_FDE")
            return true;

        if (typeName == "BDE_Six12_Paragon_B1" || typeName == "BDE_Six12_Paragon_B1_FDE")
            return true;

        return typeName == "BDE_Six12_Paragon_B2" || typeName == "BDE_Six12_Paragon_B2_FDE";
    }

    protected bool BDE_USL_Paragon_IsSix12FDE()
    {
        return IsKindOf("BDE_Six12_FDE");
    }

    override bool BDE_Six12_IsReceiverSwapInProgress()
    {
        return m_BDE_USL_ParagonSix12VariantSwapInProgress || super.BDE_Six12_IsReceiverSwapInProgress();
    }

    override void BDE_Six12_RequestButtPadRefresh()
    {
        if (m_BDE_USL_ParagonSix12VariantSwapInProgress)
            return;

        super.BDE_Six12_RequestButtPadRefresh();
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (m_BDE_USL_ParagonSix12VariantSwapInProgress)
            return true;

        return super.CanDetachAttachment(parent);
    }

    protected void BDE_USL_Paragon_RequestSix12VariantRefresh()
    {
        if (!GetGame().IsServer() || m_BDE_USL_ParagonSix12VariantSwapInProgress || IsSetForDeletion())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_Paragon_RefreshSix12Variant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Paragon_RefreshSix12Variant, 150, false);
    }

    protected void BDE_USL_Paragon_RefreshSix12Variant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || m_BDE_USL_ParagonSix12VariantSwapInProgress)
            return;

        if (!BDE_USL_Paragon_IsManagedSix12Variant())
            return;

        bool useFDE = BDE_USL_Paragon_IsSix12FDE();
        string targetType = "BDE_Six12";

        if (useFDE)
            targetType = "BDE_Six12_FDE";

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host && !BDE_USL_Paragon_CompatibilityState.HostAllowsLauncher(host, "BDE_Six12"))
        {
            m_BDE_USL_ParagonSix12VariantSwapInProgress = true;
            host.GetInventory().DropEntity(InventoryMode.SERVER, host, this);
            m_BDE_USL_ParagonSix12VariantSwapInProgress = false;
            return;
        }

        if (host)
        {
            if (host.IsKindOf("Paragon_MDR_Base") || host.IsKindOf("Paragon_SA58_Base") || host.IsKindOf("Paragon_M110_Base") || host.GetType() == "Paragon_AR15")
            {
                targetType = "BDE_Six12_Paragon_B1";
                if (useFDE)
                    targetType = "BDE_Six12_Paragon_B1_FDE";
            }
            else if (host.IsKindOf("Paragon_Scar_Base") || host.IsKindOf("Paragon_SR25_Base") || host.IsKindOf("Paragon_HK_Base"))
            {
                targetType = "BDE_Six12_Paragon_B2";
                if (useFDE)
                    targetType = "BDE_Six12_Paragon_B2_FDE";
            }
        }

        if (GetType() == targetType)
        {
            BDE_Six12_RequestCylinderVisualRefresh();
            BDE_Six12_RequestButtPadRefresh();
            return;
        }

        m_BDE_USL_ParagonSix12VariantSwapInProgress = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        TurnItemIntoItemLambda lambda = new TurnItemIntoItemLambda(this, targetType, owner);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_ParagonSix12VariantSwapInProgress = false;
    }
}
