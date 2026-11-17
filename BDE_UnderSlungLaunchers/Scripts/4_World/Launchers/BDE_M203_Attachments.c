class BDE_M203_ButtStock extends ButtstockBase
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;

        if (!parent.IsKindOf("BDE_M203_StandAloneMount") && !parent.IsKindOf("BDE_M203_StandAloneMount_Weapon"))
            return false;

        return super.CanPutAsAttachment(parent);
    }
}

class BDE_M203_Rail_Adapter extends Inventory_Base
{
    override void EEInit()
    {
        super.EEInit();
        BDE_M203_QueueRearSightRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_M203_QueueRearSightRefresh();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_M203_QueueRearSightRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_M203_QueueRearSightRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_M203_QueueRearSightRefresh();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (slot_name == "BDE_M203_RearSight")
            BDE_M203_QueueRearSightRefresh();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (slot_name == "BDE_M203_RearSight")
            BDE_M203_QueueRearSightRefresh();
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        BDE_M203 launcher = BDE_M203.Cast(parent);
        if (!launcher)
            return false;

        Weapon_Base host = Weapon_Base.Cast(launcher.GetHierarchyParent());
        if (host && host.BDE_USL_GetSideRailSight())
            return false;

        return super.CanPutAsAttachment(parent);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        string slotName = InventorySlots.GetSlotName(slotId);

        if (slotName == "BDE_M203_RearSight")
        {
            if (!attachment || !attachment.IsKindOf("BDE_M203_RearSight"))
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        return false;
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (!super.CanDisplayAttachmentSlot(slot_id))
            return false;

        string slotName = InventorySlots.GetSlotName(slot_id);

        return slotName == "BDE_M203_RearSight";
    }

    BDE_M203 BDE_M203_GetLauncher()
    {
        return BDE_M203.Cast(GetHierarchyParent());
    }

    BDE_M203_RearSight BDE_M203_GetRearSight()
    {
        return BDE_M203_RearSight.Cast(FindAttachmentBySlotName("BDE_M203_RearSight"));
    }

    void BDE_M203_QueueRearSightRefresh()
    {
        BDE_M203_RearSight rearSight = BDE_M203_GetRearSight();

        if (rearSight)
            rearSight.BDE_M203_QueueFoldRefresh();
    }
}

class BDE_M203_RearSight extends Inventory_Base
{
    override void EEInit()
    {
        super.EEInit();
        BDE_M203_QueueFrontSight();
        BDE_M203_QueueFoldRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_M203_QueueFrontSight();
        BDE_M203_QueueFoldRefresh();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_M203_QueueFoldRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_M203_QueueFrontSight();
        BDE_M203_QueueFoldRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_M203_QueueFrontSight();
        BDE_M203_QueueFoldRefresh();
    }

    void ~BDE_M203_RearSight()
    {
        if (GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_RefreshFrontSight);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_ApplyFoldState);
        }
    }

    void BDE_M203_QueueFrontSight()
    {
        if (!GetGame().IsServer())
            return;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_RefreshFrontSight);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_RefreshFrontSight, 50, false);
    }

    protected void BDE_M203_RefreshFrontSight()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;
        EntityAI front = FindAttachmentBySlotName("BDE_M203_FrontSight");
        InventoryLocation location = new InventoryLocation;
        bool attached = GetInventory().GetCurrentInventoryLocation(location) && location.GetType() == InventoryLocationType.ATTACHMENT;
        if (attached)
        {
            if (!front)
                GetInventory().CreateAttachment("BDE_M203_FrontSight");
        }
        else if (front)
            GetGame().ObjectDelete(front);
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        if (slot_name == "BDE_M203_FrontSight")
            BDE_M203_QueueFrontSight();
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (InventorySlots.GetSlotName(slot_id) == "BDE_M203_FrontSight")
            return false;
        return super.CanDisplayAttachmentSlot(slot_id);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        return attachment && attachment.IsKindOf("BDE_M203_FrontSight") && super.CanReceiveAttachment(attachment, slotId);
    }

    void BDE_M203_QueueFoldRefresh()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_M203_ApplyFoldState);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_M203_ApplyFoldState, 1, false);
    }

    protected void BDE_M203_ApplyFoldState()
    {
        float phase = 1.0;
        EntityAI parent = GetHierarchyParent();
        Weapon_Base weaponMount = Weapon_Base.Cast(parent);

        if (weaponMount && (weaponMount.IsKindOf("BDE_M203_StandAloneMount_Weapon") || weaponMount.IsKindOf("BDE_FN40_StandaloneMount_Weapon")))
        {
            PlayerBase owner = PlayerBase.Cast(weaponMount.GetHierarchyRootPlayer());

            if (owner && owner.GetEntityInHands() == weaponMount)
                phase = 0.0;
        }
        else
        {
            BDE_M203_Rail_Adapter adapter = BDE_M203_Rail_Adapter.Cast(parent);

            if (adapter)
            {
                BDE_M203 launcher = adapter.BDE_M203_GetLauncher();
                Weapon_Base host = null;

                if (launcher)
                {
                    EntityAI launcherParent = launcher.GetHierarchyParent();

                    if (launcherParent && (launcherParent.IsKindOf("BDE_M203_StandAloneMount") || launcherParent.IsKindOf("BDE_M203_StandAloneMount_Weapon")))
                    {
                        SetAnimationPhase("m203_sight_fold", phase);
                        return;
                    }

                    host = Weapon_Base.Cast(launcherParent);
                }

                if (host && host.BDE_USL_GetLauncher() == launcher && host.BDE_USL_IsLauncherModeSelected())
                    phase = 0.0;
            }
        }

        SetAnimationPhase("m203_sight_fold", phase);
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;

        if (!parent.IsKindOf("BDE_M203_StandAloneMount") && !parent.IsKindOf("BDE_M203_StandAloneMount_Weapon") && !parent.IsKindOf("BDE_M203_Rail_Adapter") && !parent.IsKindOf("BDE_FN40_StandaloneMount") && !parent.IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
            return false;

        BDE_M203_Rail_Adapter adapter = BDE_M203_Rail_Adapter.Cast(parent);
        if (adapter)
        {
            BDE_M203 launcher = adapter.BDE_M203_GetLauncher();
            Weapon_Base host = null;
            if (launcher)
                host = Weapon_Base.Cast(launcher.GetHierarchyParent());
            if (host && host.BDE_USL_GetSideRailSight())
                return false;
        }

        return super.CanPutAsAttachment(parent);
    }
}

class BDE_M203_FrontSight extends Inventory_Base
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;

        if (!parent.IsKindOf("BDE_M203_RearSight"))
            return false;

        return super.CanPutAsAttachment(parent);
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        return false;
    }
}
