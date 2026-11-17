modded class WeaponManipulationActionInput
{
    override bool JustActivate()
    {
        if (m_Player && m_Player.BDE_USL_ShouldOwnManipulationInput())
            return false;

        return super.JustActivate();
    }

    override ActionBase GetAction()
    {
        if (m_Player && m_Player.BDE_USL_ShouldOwnManipulationInput())
            return null;

        return super.GetAction();
    }
}

modded class ContinuousWeaponManipulationActionInput
{
    override bool JustActivate()
    {
        if (m_Player && m_Player.BDE_USL_ShouldOwnManipulationInput())
            return false;

        return super.JustActivate();
    }

    override ActionBase GetAction()
    {
        if (m_Player && m_Player.BDE_USL_ShouldOwnManipulationInput())
            return null;

        return super.GetAction();
    }
}

modded class FirearmActionMechanicManipulate
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (player && player.BDE_USL_ShouldOwnManipulationInput())
            return false;

        return super.ActionCondition(player, target, item);
    }
}
