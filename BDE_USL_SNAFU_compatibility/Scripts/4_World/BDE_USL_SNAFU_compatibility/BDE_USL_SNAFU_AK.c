modded class Weapon_Base
{
    override bool BDE_USL_HasValidHandguard(EntityAI launcher)
    {
        string slotsPath = "CfgWeapons " + GetType() + " BDE_USL_HandguardSlots";

        if (!GetGame().ConfigIsExisting(slotsPath))
            return super.BDE_USL_HasValidHandguard(launcher);

        array<string> handguardSlots = new array<string>;
        GetGame().ConfigGetTextArray(slotsPath, handguardSlots);

        if (handguardSlots.Count() == 0)
            return true;

        array<string> allowedHandguards = new array<string>;

        if (launcher && launcher.IsKindOf("BDE_M203"))
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_M203AllowedHandguards", allowedHandguards);
        else if (launcher && launcher.IsKindOf("BDE_Six12"))
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_Six12AllowedHandguards", allowedHandguards);
        else if (launcher && launcher.IsKindOf("BDE_GP25"))
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_GP25AllowedHandguards", allowedHandguards);

        foreach (string handguardSlot : handguardSlots)
        {
            EntityAI handguard = FindAttachmentBySlotName(handguardSlot);

            if (!handguard)
                continue;

            if (allowedHandguards.Count() == 0)
                return true;

            foreach (string allowedHandguard : allowedHandguards)
            {
                if (handguard.IsKindOf(allowedHandguard))
                    return true;
            }
        }

        return false;
    }
}

modded class SNAFU_AK19_Base
{
    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (BDE_USL_IsCompatibleHost())
        {
            string slotName = InventorySlots.GetSlotName(slot_id);

            if (slotName == BDE_USL_GetConfiguredLauncherSlotName())
                return true;
        }

        return super.CanDisplayAttachmentSlot(slot_id);
    }
}
