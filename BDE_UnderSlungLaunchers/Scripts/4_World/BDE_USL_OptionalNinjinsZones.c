// Optional Ninjins Bundle integration lives in 4_World (NOT DayZGame).
// Registered from 5_Mission only when Bundle's compile symbol is present.
// When the Bundle is absent, no Ninjins type is referenced or required.
#ifdef Ninjins_PvP_PvE_Upgraded_Zones
class BDE_USL_NinjinsImpactProtection
{
    static void Register()
    {
        // Avoid duplicated handlers if a mission is restarted.
        ScriptInvoker invoker = BDE_USL_ZoneImpactRouter.GetProtectionCheck();
        invoker.Remove(OnImpactQuery);
        invoker.Insert(OnImpactQuery);
    }

    // Exactly one parameter, matching the 3_Game ScriptInvoker call.
    static void OnImpactQuery(BDE_USL_ZoneImpactQuery query)
    {
        if (!query || query.m_Blocked)
            return;

        Object target = query.m_Target;
        vector position = query.m_Position;
        NinjinsUpgraded_ZoneEngine zoneEngine = NinjinsUpgraded_ZoneEngineModule.GetEngine();

        // Safe zone applies to ALL damage, including explosives without a hit entity.
        if (zoneEngine && zoneEngine.NinjinsUpgraded_IsWorldPositionInActiveSafeZone(position))
        {
            query.m_Blocked = true;
            return;
        }

        // For AoE, let native Ninjins damage callbacks decide target-by-target;
        // don't suppress the whole explosion in a PvE zone (infected still take hits).
        if (query.m_Explosion)
            return;

        PlayerBase player = PlayerBase.Cast(target);
        EntityAI entity = EntityAI.Cast(target);
        if (!player && entity)
            player = PlayerBase.Cast(entity.GetHierarchyRootPlayer());
        if (player && (player.NinjinsUpgraded_IsInSafeZone() || player.NinjinsUpgraded_IsInPvEZone() || player.NinjinsUpgraded_SafeExitActive()))
        {
            query.m_Blocked = true;
            return;
        }
        if (entity && (entity.IsKindOf("DayZInfected") || entity.IsKindOf("AnimalBase")))
            return;

        if (zoneEngine)
        {
            bool inPvp;
            bool inPve;
            zoneEngine.NinjinsUpgraded_FootprintPvpPveAtWorld(position, inPvp, inPve);
            if (inPve)
                query.m_Blocked = true;
        }
    }
}
#endif
