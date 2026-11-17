class BDE_USL_ShotWear
{
    static void Apply(Weapon_Base receiver, bool fired, float healthBefore, int shotId)
    {
        if (!GetGame().IsServer() || !receiver || !fired || healthBefore <= 0)
            return;

        float healthAfterNative = receiver.GetHealth("", "Health");
        float nativeWear = Math.Max(0.0, healthBefore - healthAfterNative);
        bool allowDamage = receiver.GetAllowDamage();
        if (allowDamage && nativeWear <= 0.0 && healthAfterNative > 0.0)
        {
            float fallback = Math.Max(0.0, receiver.ConfigGetFloat("BDE_USL_FallbackShotWear"));
            receiver.AddHealth("", "Health", -fallback);
        }

        float healthAfter = receiver.GetHealth("", "Health");
        float actualWear = Math.Max(0.0, healthBefore - healthAfter);
        float barrelWear = 0.0;

        ItemBase barrel;
        BDE_M203 m203 = BDE_M203.Cast(receiver);
        if (m203)
            barrel = m203.BDE_M203_GetBarrel();

        if (actualWear > 0.0 && barrel && barrel.IsKindOf("BDE_M203_Barrel") && barrel.GetAllowDamage() && !barrel.IsRuined())
        {
            float barrelBefore = barrel.GetHealth("", "Health");
            barrel.AddHealth("", "Health", -actualWear * 0.5);
            barrelWear = Math.Max(0.0, barrelBefore - barrel.GetHealth("", "Health"));
            barrel.SetSynchDirty();
        }

        receiver.SetSynchDirty();
        if (receiver.ConfigGetInt("BDE_USL_WearDiagnostics"))
            Print("[BDE USL WEAR SERVER] type=" + receiver.GetType() + " shot=" + shotId + " allowDamage=" + allowDamage + " before=" + healthBefore + " nativeAfter=" + healthAfterNative + " after=" + healthAfter + " level=" + receiver.GetHealthLevel() + " barrelWear=" + barrelWear);
    }

    static void LogClient(Weapon_Base receiver)
    {
        if (!GetGame().IsClient() || !receiver || !receiver.ConfigGetInt("BDE_USL_WearDiagnostics"))
            return;

        Print("[BDE USL WEAR CLIENT] type=" + receiver.GetType() + " level=" + receiver.GetHealthLevel());
    }
}
