modded class Ammunition_Base
{
    protected BDE_Six12 BDE_Six12_ResolveInteractionTarget(EntityAI other_item)
    {
        BDE_Six12 direct = BDE_Six12.Cast(other_item);
        if (direct)
            return direct;

        Weapon_Base host = Weapon_Base.Cast(other_item);
        if (host)
            return host.BDE_USL_GetSix12InteractionTarget();

        return null;
    }

    override bool CanBeCombined(EntityAI other_item, bool reservation_check = true, bool stack_max_limit = false)
    {
        BDE_Six12 target = BDE_Six12_ResolveInteractionTarget(other_item);
        if (target && target.BDE_Six12_CanDirectLoadAmmo(this, reservation_check))
            return true;

        return super.CanBeCombined(other_item, reservation_check, stack_max_limit);
    }

    override void CombineItems(ItemBase other_item, bool use_stack_max = true)
    {
        BDE_Six12 target = BDE_Six12_ResolveInteractionTarget(other_item);
        if (target && target.BDE_Six12_CanDirectLoadAmmo(this, false))
        {
            target.BDE_Six12_RequestSpecificAmmo(this);
            return;
        }

        super.CombineItems(other_item, use_stack_max);
    }
}
