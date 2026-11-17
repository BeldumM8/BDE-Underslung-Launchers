modded class MissionServer
{
    override void OnMissionStart()
    {
        super.OnMissionStart();
#ifdef Ninjins_PvP_PvE_Upgraded_Zones
        BDE_USL_NinjinsImpactProtection.Register();
#endif
        BDE_USL_SettingsManager.InitializeServer();
    }

    override void OnClientReadyEvent(PlayerIdentity identity, PlayerBase player)
    {
        super.OnClientReadyEvent(identity, player);
        BDE_USL_SettingsManager.SendSettingsToClient(player, identity);
    }
};
