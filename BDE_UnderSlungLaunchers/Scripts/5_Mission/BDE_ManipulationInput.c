modded class MissionGameplay
{
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        BDE_USL_HandleManipulationInput();
    }

    protected void BDE_USL_HandleManipulationInput()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

        if (!player || !player.BDE_USL_ShouldOwnManipulationInput())
            return;

        UAInput manipulationInput = GetUApi().GetInputByName("UAReloadMagazine");

        if (!manipulationInput)
            return;

        BDE_Six12 six12 = player.BDE_USL_GetManipulationSix12();
        if (six12)
        {
            Weapon_Base six12Host = Weapon_Base.Cast(player.GetItemInHands());

            if (manipulationInput.LocalHoldBegin())
                six12.BDE_Six12_ClientRequestReload(six12Host, player);

            if (manipulationInput.LocalRelease())
                six12.BDE_Six12_ClientRequestReloadStop(six12Host, player);

            return;
        }

        BDE_UnderSlungLauncher_Base launcher = player.BDE_USL_GetManipulationLauncher();
        if (!launcher)
            return;

        if (manipulationInput.LocalDoubleClick())
        {
            player.BDE_USL_ClientBeginManipulation(launcher, BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD);
            return;
        }

        if (manipulationInput.LocalHoldBegin())
            player.BDE_USL_ClientBeginManipulation(launcher, BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD);
    }
}
