class BDE_USL_ParagonM203VariantSwapLambda : TurnItemIntoItemLambda
{
    protected bool m_BDE_USL_HadLiveRound;
    protected float m_BDE_USL_ChamberDamage;
    protected string m_BDE_USL_ChamberAmmoType;
    protected string m_BDE_USL_ChamberSourceType;

    void BDE_USL_ParagonM203VariantSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player, bool hadLiveRound, float chamberDamage, string chamberAmmoType, string chamberSourceType)
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
    protected bool m_BDE_USL_ParagonVariantSwapInProgress;

    override void EEInit()
    {
        super.EEInit();
        BDE_USL_Paragon_RequestM203VariantRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_USL_Paragon_RequestM203VariantRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_USL_Paragon_RequestM203VariantRefresh();
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        BDE_USL_Paragon_RequestM203VariantRefresh();
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        if (m_BDE_USL_ParagonVariantSwapInProgress)
            return true;

        return super.CanDetachAttachment(parent);
    }

    protected bool BDE_USL_Paragon_IsManagedM203Variant()
    {
        string typeName = GetType();

        return typeName == "BDE_M203" || typeName == "BDE_M203_Paragon_AR15" || typeName == "BDE_M203_Paragon_Aero" || typeName == "BDE_M203_Paragon_MK14" || typeName == "BDE_M203_Paragon_B1" || typeName == "BDE_M203_Paragon_B2";
    }

    void BDE_USL_Paragon_RequestM203VariantRefresh()
    {
        if (!GetGame().IsServer())
            return;

        if (m_BDE_USL_ParagonVariantSwapInProgress)
            return;

        if (!BDE_USL_Paragon_IsManagedM203Variant())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Paragon_RefreshM203Variant, 50, false);
    }

    void BDE_USL_Paragon_RefreshM203Variant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        if (!BDE_USL_Paragon_IsManagedM203Variant())
            return;

        string targetType = "BDE_M203";
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host && !BDE_USL_Paragon_CompatibilityState.HostAllowsLauncher(host, "BDE_M203"))
        {
            m_BDE_USL_ParagonVariantSwapInProgress = true;
            host.GetInventory().DropEntity(InventoryMode.SERVER, host, this);
            m_BDE_USL_ParagonVariantSwapInProgress = false;
            return;
        }

        if (host)
        {
            if (host.IsKindOf("Paragon_MDR_Base") || host.IsKindOf("Paragon_SA58_Base") || host.IsKindOf("Paragon_M110_Base") || host.GetType() == "Paragon_AR15")
                targetType = "BDE_M203_Paragon_B1";
            else if (host.IsKindOf("Paragon_Scar_Base") || host.IsKindOf("Paragon_SR25_Base") || host.IsKindOf("Paragon_HK_Base"))
                targetType = "BDE_M203_Paragon_B2";
        }

        if (GetType() == targetType)
            return;

        m_BDE_USL_ParagonVariantSwapInProgress = true;

        bool hadLiveRound = false;
        float chamberDamage = 0.0;
        string chamberAmmoType = "";
        int muzzleIndex = 0;

        if (GetMuzzleCount() > muzzleIndex && IsChamberFull(muzzleIndex) && !IsChamberFiredOut(muzzleIndex))
            hadLiveRound = GetCartridgeInfo(muzzleIndex, chamberDamage, chamberAmmoType);

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        string chamberSourceType = BDE_USL_GetLoadedMagazineSourceType();
        BDE_USL_ParagonM203VariantSwapLambda lambda = new BDE_USL_ParagonM203VariantSwapLambda(this, targetType, owner, hadLiveRound, chamberDamage, chamberAmmoType, chamberSourceType);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
        m_BDE_USL_ParagonVariantSwapInProgress = false;
    }
}
