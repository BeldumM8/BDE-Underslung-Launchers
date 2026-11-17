class BDE_FN40_StandaloneMountSwapLambda : TurnItemIntoItemLambda
{
    protected EntityAI m_FN40_Old;
    void BDE_FN40_StandaloneMountSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player)
    {
        m_FN40_Old = old_item;
    }

    override void OnAbort()
    {
        super.OnAbort();
        BDE_FN40_StandaloneMount item = BDE_FN40_StandaloneMount.Cast(m_FN40_Old);
        if (item)
            item.BDE_FN40_SwapAborted();
        BDE_FN40_StandaloneMount_Weapon weapon = BDE_FN40_StandaloneMount_Weapon.Cast(m_FN40_Old);
        if (weapon)
            weapon.BDE_FN40_SwapAborted();
    }

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

        BDE_FN40_StandaloneMount itemMount = BDE_FN40_StandaloneMount.Cast(new_item);

        if (itemMount)
        {
            itemMount.BDE_FN40_PostSwapRefresh();
            return;
        }

        BDE_FN40_StandaloneMount_Weapon weaponMount = BDE_FN40_StandaloneMount_Weapon.Cast(new_item);

        if (weaponMount)
            weaponMount.BDE_FN40_PostSwapRefresh();
    }
}

class BDE_FN40_StandaloneMount extends Inventory_Base
{
    protected bool m_FN40_Swapping;

    void BDE_FN40_SwapAborted()
    {
        m_FN40_Swapping = false;
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!attachment)
            return false;
        string slotName = InventorySlots.GetSlotName(slotId);
        if (slotName == "BDE_FN40_Body")
        {
            BDE_FN40 body = BDE_FN40.Cast(attachment);
            return body && !body.FindAttachmentBySlotName("BDE_FN40_Handle") && !body.BDE_USL_IsManipulationActive() && super.CanReceiveAttachment(attachment, slotId);
        }
        if (slotName == "BDE_FN40_Sight_Mount")
            return attachment.IsKindOf("BDE_FN40_Sight_Mount") && !FindAttachmentBySlotName("weaponOptics") && super.CanReceiveAttachment(attachment, slotId);
        if (slotName == "weaponOptics")
            return !FindAttachmentBySlotName("BDE_FN40_Sight_Mount") && super.CanReceiveAttachment(attachment, slotId);
        return false;
    }

    string BDE_FN40_GetSwapType()
    {
        if (GetType() == "BDE_FN40_StandaloneMount_FDE")
            return "BDE_FN40_StandaloneMount_Weapon_FDE";
        return "BDE_FN40_StandaloneMount_Weapon";
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_FN40_QueueRearSightFoldRefresh();
        BDE_FN40_RequestVariantRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_FN40_QueueRearSightFoldRefresh();
        BDE_FN40_RequestVariantRefresh();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == "BDE_FN40_Sight_Mount" || slot_name == "weaponOptics")
        {
            BDE_FN40_QueueRearSightFoldRefresh();
        }

        if (slot_name == "BDE_FN40_Body")
            BDE_FN40_RequestVariantRefresh();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (slot_name == "BDE_FN40_Sight_Mount" || slot_name == "weaponOptics")
        {
            BDE_FN40_QueueRearSightFoldRefresh();
        }

        if (slot_name == "BDE_FN40_Body")
            BDE_FN40_RequestVariantRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_FN40_QueueRearSightFoldRefresh();
        BDE_FN40_RequestVariantRefresh();
    }

    void BDE_FN40_PostSwapRefresh()
    {
        m_FN40_Swapping = false;
        BDE_FN40_QueueRearSightFoldRefresh();
        BDE_FN40_RequestVariantRefresh();
    }

    void BDE_FN40_RequestVariantRefresh()
    {
        if (!GetGame().IsServer() && GetGame().IsMultiplayer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_FN40_RefreshVariant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_FN40_RefreshVariant, 75, false);
    }

    protected void BDE_FN40_RefreshVariant()
    {
        if ((!GetGame().IsServer() && GetGame().IsMultiplayer()) || IsSetForDeletion() || m_FN40_Swapping)
            return;

        if (!FindAttachmentBySlotName("BDE_FN40_Body"))
            return;

        InventoryLocation location = new InventoryLocation;
        if (!GetInventory().GetCurrentInventoryLocation(location) || location.GetType() == InventoryLocationType.UNKNOWN)
            return;
        m_FN40_Swapping = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_FN40_StandaloneMountSwapLambda lambda = new BDE_FN40_StandaloneMountSwapLambda(this, BDE_FN40_GetSwapType(), owner);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }

    protected void BDE_FN40_QueueRearSightFoldRefresh()
    {
        EntityAI sightMount = FindAttachmentBySlotName("BDE_FN40_Sight_Mount");
        if (sightMount)
        {
            BDE_FN40_Sight sight = BDE_FN40_Sight.Cast(sightMount.FindAttachmentBySlotName("BDE_FN40_Sight"));
            if (sight)
                sight.BDE_FN40_RefreshFold();
        }
        BDE_M203_RearSight ladder = BDE_M203_RearSight.Cast(FindAttachmentBySlotName("weaponOptics"));
        if (ladder)
            ladder.BDE_M203_QueueFoldRefresh();
    }
}

class BDE_FN40_StandaloneMount_Weapon extends M79_Base
{
    protected bool m_FN40_Swapping;

    void BDE_FN40_SwapAborted()
    {
        m_FN40_Swapping = false;
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!attachment)
            return false;
        string slotName = InventorySlots.GetSlotName(slotId);
        if (slotName == "BDE_FN40_Body")
        {
            BDE_FN40 body = BDE_FN40.Cast(attachment);
            return body && !body.FindAttachmentBySlotName("BDE_FN40_Handle") && !body.BDE_USL_IsManipulationActive() && super.CanReceiveAttachment(attachment, slotId);
        }
        if (slotName == "BDE_FN40_Sight_Mount")
            return attachment.IsKindOf("BDE_FN40_Sight_Mount") && !FindAttachmentBySlotName("weaponOptics") && super.CanReceiveAttachment(attachment, slotId);
        if (slotName == "weaponOptics")
            return !FindAttachmentBySlotName("BDE_FN40_Sight_Mount") && super.CanReceiveAttachment(attachment, slotId);
        return false;
    }

    string BDE_FN40_GetSwapType()
    {
        if (GetType() == "BDE_FN40_StandaloneMount_Weapon_FDE")
            return "BDE_FN40_StandaloneMount_FDE";
        return "BDE_FN40_StandaloneMount";
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_FN40_QueueRearSightFoldRefresh();
        BDE_FN40_QueueHostChamberClear();
        BDE_FN40_RequestVariantRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_FN40_QueueRearSightFoldRefresh();
        BDE_FN40_QueueHostChamberClear();
        BDE_FN40_RequestVariantRefresh();
    }

    override bool CanChamberBullet(int muzzleIndex, Magazine mag)
    {
        return false;
    }

    override void EEAmmoChanged()
    {
        super.EEAmmoChanged();
        BDE_FN40_QueueHostChamberClear();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == "BDE_FN40_Sight_Mount" || slot_name == "weaponOptics")
        {
            BDE_FN40_QueueRearSightFoldRefresh();
        }

        if (slot_name == "BDE_FN40_Body")
            BDE_FN40_RequestVariantRefresh();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (slot_name == "BDE_FN40_Sight_Mount" || slot_name == "weaponOptics")
        {
            BDE_FN40_QueueRearSightFoldRefresh();
        }

        if (slot_name == "BDE_FN40_Body")
            BDE_FN40_RequestVariantRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_FN40_QueueRearSightFoldRefresh();
        BDE_FN40_RequestVariantRefresh();
    }

    void BDE_FN40_PostSwapRefresh()
    {
        m_FN40_Swapping = false;
        BDE_FN40_QueueRearSightFoldRefresh();
        BDE_FN40_QueueHostChamberClear();
        BDE_FN40_RequestVariantRefresh();
    }

    void BDE_FN40_RequestVariantRefresh()
    {
        if (!GetGame().IsServer() && GetGame().IsMultiplayer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_FN40_RefreshVariant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_FN40_RefreshVariant, 75, false);
    }

    protected void BDE_FN40_RefreshVariant()
    {
        if ((!GetGame().IsServer() && GetGame().IsMultiplayer()) || IsSetForDeletion() || m_FN40_Swapping)
            return;

        if (FindAttachmentBySlotName("BDE_FN40_Body"))
            return;

        InventoryLocation location = new InventoryLocation;
        if (!GetInventory().GetCurrentInventoryLocation(location) || location.GetType() == InventoryLocationType.UNKNOWN)
            return;
        m_FN40_Swapping = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_FN40_StandaloneMountSwapLambda lambda = new BDE_FN40_StandaloneMountSwapLambda(this, BDE_FN40_GetSwapType(), owner);
        lambda.SetTransferParams(true, true, true);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }

    protected void BDE_FN40_QueueHostChamberClear()
    {
        if (!GetGame().IsServer() && GetGame().IsMultiplayer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_FN40_ClearHostChamber);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_FN40_ClearHostChamber, 1, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_FN40_ClearHostChamber, 250, false);
    }

    protected void BDE_FN40_ClearHostChamber()
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

    protected void BDE_FN40_QueueRearSightFoldRefresh()
    {
        EntityAI sightMount = FindAttachmentBySlotName("BDE_FN40_Sight_Mount");
        if (sightMount)
        {
            BDE_FN40_Sight sight = BDE_FN40_Sight.Cast(sightMount.FindAttachmentBySlotName("BDE_FN40_Sight"));
            if (sight)
                sight.BDE_FN40_RefreshFold();
        }
        BDE_M203_RearSight ladder = BDE_M203_RearSight.Cast(FindAttachmentBySlotName("weaponOptics"));
        if (ladder)
            ladder.BDE_M203_QueueFoldRefresh();
    }
}

class BDE_FN40_StandaloneMount_FDE extends BDE_FN40_StandaloneMount {}
class BDE_FN40_StandaloneMount_Weapon_FDE extends BDE_FN40_StandaloneMount_Weapon {}
