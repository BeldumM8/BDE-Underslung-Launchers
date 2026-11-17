#ifdef Ninjins_PvP_PvE_Upgraded_Zones
modded class PlayerBase
{
    protected static const int BDE_USL_RPC_NINJINS_FIRE_NOTICE = 581219;
    protected int m_BDE_USL_NextNinjinsFireNoticeRequest;

    bool BDE_USL_NinjinsCanFire()
    {
        if (NinjinsUpgraded_IsWeaponFireAllowedForCurrentRuntime())
            return true;

        if (GetGame().IsServer())
        {
            NinjinsUpgraded_SendBlockedWeaponNoticeIfDue();
        }
        else if (GetGame().GetPlayer() == this)
        {
            // Ninjin's notice is server-only. Request it without sending a fire RPC.
            int now = GetGame().GetTime();
            if (now >= m_BDE_USL_NextNinjinsFireNoticeRequest)
            {
                m_BDE_USL_NextNinjinsFireNoticeRequest = now + 1000;
                GetGame().RPCSingleParam(this, BDE_USL_RPC_NINJINS_FIRE_NOTICE, new Param1<bool>(true), true);
            }
        }

        return false;
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type != BDE_USL_RPC_NINJINS_FIRE_NOTICE)
        {
            super.OnRPC(sender, rpc_type, ctx);
            return;
        }

        if (!GetGame().IsServer() || !sender || !GetIdentity())
            return;
        if (sender.GetId() != GetIdentity().GetId())
            return;

        Weapon_Base host = Weapon_Base.Cast(GetItemInHands());
        if (!host)
            return;
        if (!host.BDE_USL_IsLauncherModeSelected() && !host.BDE_USL_IsSix12ModeSelected() && !BDE_Six12_StandAloneMount_Weapon.Cast(host) && !BDE_UnderSlungLauncher_Base.Cast(host))
            return;

        // Recheck server zone state; the client cannot authorize firing or a notice.
        if (!NinjinsUpgraded_IsWeaponFireAllowedForCurrentRuntime())
            NinjinsUpgraded_SendBlockedWeaponNoticeIfDue();
    }
}
#endif
