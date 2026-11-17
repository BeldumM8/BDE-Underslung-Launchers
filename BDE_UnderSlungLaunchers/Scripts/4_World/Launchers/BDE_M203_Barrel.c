class BDE_M203_Barrel extends Inventory_Base
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent || !parent.IsKindOf("BDE_M203"))
            return false;

        return super.CanPutAsAttachment(parent);
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        BDE_M203 launcher = BDE_M203.Cast(parent);

        if (launcher)
        {
            if (launcher.BDE_USL_IsManipulationActive())
                return false;

            if (launcher.BDE_USL_HasLiveRound())
                return false;
        }

        return super.CanDetachAttachment(parent);
    }

    override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
    {
        super.EEHealthLevelChanged(oldLevel, newLevel, zone);

        BDE_M203 launcher = BDE_M203.Cast(GetHierarchyParent());

        if (launcher)
            launcher.BDE_M203_NotifyHostOperationalStateChanged();
    }
}
