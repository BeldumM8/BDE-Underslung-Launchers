class BDE_FN40 extends BDE_M203
{
    override string BDE_USL_GetHUDShortName() { return "FN40"; }

    override BDE_M203_Barrel BDE_M203_GetBarrel()
    {
        return BDE_FN40_Barrel.Cast(FindAttachmentBySlotName("BDE_FN40_Barrel"));
    }

    bool BDE_FN40_IsInStandalone()
    {
        EntityAI parent = GetHierarchyParent();
        return parent && (parent.IsKindOf("BDE_FN40_StandaloneMount") || parent.IsKindOf("BDE_FN40_StandaloneMount_Weapon"));
    }

    bool BDE_FN40_HasUsableHandle()
    {
        if (BDE_FN40_IsInStandalone())
            return !GetHierarchyParent().IsRuined();
        EntityAI handle = FindAttachmentBySlotName("BDE_FN40_Handle");
        return handle && !handle.IsSetForDeletion() && !handle.IsRuined();
    }

    override bool CanFire()
    {
        return BDE_M203_HasUsableBarrel() && BDE_FN40_HasUsableHandle() && !BDE_M203_IsTubeOpen() && super.CanFire();
    }

    override bool BDE_USL_CanFireAttachedFromHost(Weapon_Base host)
    {
        return BDE_FN40_HasUsableHandle() && !BDE_M203_IsTubeOpen() && super.BDE_USL_CanFireAttachedFromHost(host);
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;
        if (parent.IsKindOf("BDE_FN40_StandaloneMount") || parent.IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
            return !FindAttachmentBySlotName("BDE_FN40_Handle") && !BDE_USL_IsManipulationActive();
        string hostType = parent.GetType();
        if (hostType != "M4A1" && hostType != "SCARH" && hostType != "SCARH_Black")
            return false;
        return super.CanPutAsAttachment(parent);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!attachment || BDE_USL_IsManipulationActive())
            return false;
        string slotName = InventorySlots.GetSlotName(slotId);
        if (slotName == "BDE_FN40_Handle")
            return !BDE_FN40_IsInStandalone() && attachment.IsKindOf("BDE_FN40_Handle") && super.CanReceiveAttachment(attachment, slotId);
        if (slotName == "BDE_FN40_Barrel")
            return attachment.IsKindOf("BDE_FN40_Barrel") && super.CanReceiveAttachment(attachment, slotId);
        return false;
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        return !BDE_USL_IsManipulationActive() && super.CanDetachAttachment(parent);
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
        BDE_M203_ApplyTubeAnimation();
        BDE_M203_NotifyHostOperationalStateChanged();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        if (slot_name == "BDE_FN40_Barrel")
            BDE_M203_CancelReloadTubeSequence(true);
        BDE_M203_NotifyHostOperationalStateChanged();
    }

    override void BDE_M203_RequestButtPadRefresh() {}
    override void BDE_M203_QueueRailSightFoldRefresh() {}

    override void OnDebugSpawn()
    {
        if (!BDE_M203_HasBarrel())
        {
            string barrelType = "BDE_FN40_Barrel";
            if (GetType() == "BDE_FN40_FDE")
                barrelType = "BDE_FN40_Barrel_FDE";
            GetInventory().CreateAttachment(barrelType);
        }
        if (!BDE_FN40_IsInStandalone() && !FindAttachmentBySlotName("BDE_FN40_Handle"))
        {
            string handleType = "BDE_FN40_Handle";
            if (GetType() == "BDE_FN40_FDE")
                handleType = "BDE_FN40_Handle_FDE";
            GetInventory().CreateAttachment(handleType);
        }
        super.OnDebugSpawn();
    }
}

class BDE_FN40_FDE extends BDE_FN40 {}

class BDE_FN40_Barrel extends BDE_M203_Barrel
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent || !parent.IsKindOf("BDE_FN40"))
            return false;
        return super.CanPutAsAttachment(parent);
    }
}
class BDE_FN40_Barrel_FDE extends BDE_FN40_Barrel {}

class BDE_FN40_Handle extends Inventory_Base
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        BDE_FN40 body = BDE_FN40.Cast(parent);
        return body && !body.BDE_FN40_IsInStandalone() && !body.BDE_USL_IsManipulationActive() && super.CanPutAsAttachment(parent);
    }
    override bool CanDetachAttachment(EntityAI parent)
    {
        BDE_FN40 body = BDE_FN40.Cast(parent);
        return body && !body.BDE_USL_IsManipulationActive() && super.CanDetachAttachment(parent);
    }
    override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);
        BDE_FN40 body = BDE_FN40.Cast(GetHierarchyParent());
        if (body)
            body.BDE_M203_NotifyHostOperationalStateChanged();
    }
}
class BDE_FN40_Handle_FDE extends BDE_FN40_Handle {}
