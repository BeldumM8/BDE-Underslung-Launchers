#ifdef S_GUNPLAY
modded class PropertyModifiers
{
    override protected void applyAttachmentsModifiers()
    {
        super.applyAttachmentsModifiers();

        bool ownerIsUSL = m_OwnerItem && m_OwnerItem.IsKindOf("BDE_UnderSlungLauncher_Base");
        int attachmentCount = m_OwnerItem.GetInventory().AttachmentCount();

        for (int i = 0; i < attachmentCount; i++)
        {
            EntityAI attachment = m_OwnerItem.GetInventory().GetAttachmentFromIndex(i);

            if (!attachment)
                continue;

            if (ownerIsUSL || attachment.IsKindOf("BDE_UnderSlungLauncher_Base"))
                BDE_USL_ApplyNestedAttachmentModifiers(attachment);
        }
    }

    protected void BDE_USL_ApplyNestedAttachmentModifiers(EntityAI parent)
    {
        int attachmentCount = parent.GetInventory().AttachmentCount();

        for (int i = 0; i < attachmentCount; i++)
        {
            EntityAI attachment = parent.GetInventory().GetAttachmentFromIndex(i);

            if (!attachment)
                continue;

            applyAttachmentModifiers(attachment);
            BDE_USL_ApplyNestedAttachmentModifiers(attachment);
        }
    }
}

modded class ItemBase
{
    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
        BDE_USL_RefreshOuterWeaponModifiers();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        BDE_USL_RefreshOuterWeaponModifiers();
    }

    protected void BDE_USL_RefreshOuterWeaponModifiers()
    {
        EntityAI cursor = this;
        Weapon_Base outerWeapon = null;
        bool hasUSLAncestor = false;

        while (cursor)
        {
            if (cursor.IsKindOf("BDE_UnderSlungLauncher_Base"))
                hasUSLAncestor = true;

            Weapon_Base weapon = Weapon_Base.Cast(cursor);

            if (weapon)
                outerWeapon = weapon;

            cursor = cursor.GetHierarchyParent();
        }

        Weapon_Base selfWeapon = Weapon_Base.Cast(this);

        if (!hasUSLAncestor || !outerWeapon || outerWeapon == selfWeapon)
            return;

        outerWeapon.GetPropertyModifierObject().UpdateModifiers();
    }
}
#endif
