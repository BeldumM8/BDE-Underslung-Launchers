class BDE_M203_StandAloneMountSwapLambda : TurnItemIntoItemLambda
{
    void BDE_M203_StandAloneMountSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player)
    {
    }

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

        BDE_M203_StandAloneMount itemMount = BDE_M203_StandAloneMount.Cast(new_item);

        if (itemMount)
        {
            itemMount.BDE_M203_PostSwapRefresh();
            return;
        }

        BDE_M203_StandAloneMount_Weapon weaponMount = BDE_M203_StandAloneMount_Weapon.Cast(new_item);

        if (weaponMount)
            weaponMount.BDE_M203_PostSwapRefresh();
    }
}

class BDE_M203_StandAloneMount extends Inventory_Base
{
    override void EEInit()
    {
        super.EEInit();
        BDE_M203_QueueRearSightFoldRefresh();
        BDE_M203_RequestVariantRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_M203_QueueRearSightFoldRefresh();
        BDE_M203_RequestVariantRefresh();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == "weaponOptics")
        {
            BDE_M203_QueueRearSightFoldRefresh();
        }

        if (slot_name == "BDE_M203_Body")
            BDE_M203_RequestVariantRefresh();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (slot_name == "weaponOptics")
        {
            BDE_M203_QueueRearSightFoldRefresh();
        }

        if (slot_name == "BDE_M203_Body")
            BDE_M203_RequestVariantRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_M203_QueueRearSightFoldRefresh();
        BDE_M203_RequestVariantRefresh();
    }

    void BDE_M203_PostSwapRefresh()
    {
        BDE_M203_QueueRearSightFoldRefresh();
        BDE_M203_RequestVariantRefresh();
    }

    void BDE_M203_RequestVariantRefresh()
    {
        if (!GetGame().IsServer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_RefreshVariant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_RefreshVariant, 75, false);
    }

    protected void BDE_M203_RefreshVariant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        if (!FindAttachmentBySlotName("BDE_M203_Body"))
            return;

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_M203_StandAloneMountSwapLambda lambda = new BDE_M203_StandAloneMountSwapLambda(this, "BDE_M203_StandAloneMount_Weapon", owner);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }

    protected void BDE_M203_QueueRearSightFoldRefresh()
    {
        BDE_M203_RearSight rearSight = BDE_M203_RearSight.Cast(FindAttachmentBySlotName("weaponOptics"));

        if (rearSight)
            rearSight.BDE_M203_QueueFoldRefresh();
    }
}

class BDE_M203_StandAloneMount_Weapon extends M79_Base
{
    override void EEInit()
    {
        super.EEInit();
        BDE_M203_QueueRearSightFoldRefresh();
        BDE_M203_QueueHostChamberClear();
        BDE_M203_RequestVariantRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_M203_QueueRearSightFoldRefresh();
        BDE_M203_QueueHostChamberClear();
        BDE_M203_RequestVariantRefresh();
    }

    override bool CanChamberBullet(int muzzleIndex, Magazine mag)
    {
        return false;
    }

    override void EEAmmoChanged()
    {
        super.EEAmmoChanged();
        BDE_M203_QueueHostChamberClear();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == "weaponOptics")
        {
            BDE_M203_QueueRearSightFoldRefresh();
        }

        if (slot_name == "BDE_M203_Body")
            BDE_M203_RequestVariantRefresh();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (slot_name == "weaponOptics")
        {
            BDE_M203_QueueRearSightFoldRefresh();
        }

        if (slot_name == "BDE_M203_Body")
            BDE_M203_RequestVariantRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_M203_QueueRearSightFoldRefresh();
        BDE_M203_RequestVariantRefresh();
    }

    void BDE_M203_PostSwapRefresh()
    {
        BDE_M203_QueueRearSightFoldRefresh();
        BDE_M203_QueueHostChamberClear();
        BDE_M203_RequestVariantRefresh();
    }

    void BDE_M203_RequestVariantRefresh()
    {
        if (!GetGame().IsServer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_RefreshVariant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_RefreshVariant, 75, false);
    }

    protected void BDE_M203_RefreshVariant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        if (FindAttachmentBySlotName("BDE_M203_Body"))
            return;

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_M203_StandAloneMountSwapLambda lambda = new BDE_M203_StandAloneMountSwapLambda(this, "BDE_M203_StandAloneMount", owner);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }

    protected void BDE_M203_QueueHostChamberClear()
    {
        if (!GetGame().IsServer() && GetGame().IsMultiplayer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_ClearHostChamber);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_ClearHostChamber, 1, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_ClearHostChamber, 250, false);
    }

    protected void BDE_M203_ClearHostChamber()
    {
        if (!GetGame().IsServer() && GetGame().IsMultiplayer())
            return;

        bool changed = false;
        int muzzleCount = GetMuzzleCount();

        for (int muzzleIndex = 0; muzzleIndex < muzzleCount; muzzleIndex++)
        {
            if (IsChamberEmpty(muzzleIndex))
                continue;

            float ammoDamage;
            string ammoType;

            if (PopCartridgeFromChamber(muzzleIndex, ammoDamage, ammoType))
                changed = true;
        }

        if (!changed)
            return;

        RandomizeFSMState();
        Synchronize();
        SetSynchDirty();
    }

    protected void BDE_M203_QueueRearSightFoldRefresh()
    {
        BDE_M203_RearSight rearSight = BDE_M203_RearSight.Cast(FindAttachmentBySlotName("weaponOptics"));

        if (rearSight)
            rearSight.BDE_M203_QueueFoldRefresh();
    }
}
