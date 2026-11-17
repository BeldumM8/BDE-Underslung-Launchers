class BDE_FN40_Sight_Mount extends Inventory_Base
{
    override void EEInit()
    {
        super.EEInit();
        BDE_FN40_QueueSight();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_FN40_QueueSight();
    }

    void ~BDE_FN40_Sight_Mount()
    {
        if (GetGame())
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_FN40_EnsureSight);
    }

    protected void BDE_FN40_QueueSight()
    {
        if (!GetGame().IsServer())
            return;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_FN40_EnsureSight);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_FN40_EnsureSight, 250, false);
    }

    protected void BDE_FN40_EnsureSight()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || FindAttachmentBySlotName("BDE_FN40_Sight"))
            return;
        string sightType = "BDE_FN40_Sight";
        GetInventory().CreateAttachment(sightType);
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        if (slot_name == "BDE_FN40_Sight")
            BDE_FN40_QueueSight();
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;

        if (GetGame().ConfigGetInt("CfgWeapons " + parent.GetType() + " BDE_SideRailCompatible") == 1)
        {
            Weapon_Base host = Weapon_Base.Cast(parent);
            BDE_M203 m203 = null;
            if (host)
                m203 = BDE_M203.Cast(host.BDE_USL_GetLauncher());
            if (m203 && m203.BDE_M203_GetRailAdapter())
                return false;
            return super.CanPutAsAttachment(parent);
        }
        return (parent.IsKindOf("BDE_FN40_StandaloneMount") || parent.IsKindOf("BDE_FN40_StandaloneMount_Weapon")) && !parent.FindAttachmentBySlotName("weaponOptics") && super.CanPutAsAttachment(parent);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        return attachment && attachment.IsKindOf("BDE_FN40_Sight") && super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (InventorySlots.GetSlotName(slot_id) == "BDE_FN40_Sight")
            return false;
        return super.CanDisplayAttachmentSlot(slot_id);
    }
}
