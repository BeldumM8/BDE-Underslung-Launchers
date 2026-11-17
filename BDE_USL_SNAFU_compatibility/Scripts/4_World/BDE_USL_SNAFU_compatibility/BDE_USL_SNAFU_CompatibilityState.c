class BDE_USL_SNAFU_CompatibilityState
{
    static bool HostAllowsLauncher(Weapon_Base host, string launcherType)
    {
        if (!host)
            return true;

        string path = "CfgWeapons " + host.GetType();
        string settingsGroup = "";

        if (!GetGame().ConfigIsExisting(path + " BDE_USL_SettingsGroup"))
            return true;

        GetGame().ConfigGetText(path + " BDE_USL_SettingsGroup", settingsGroup);
        if (settingsGroup != "SNAFU")
            return true;

        TStringArray launcherTypes = {};
        GetGame().ConfigGetTextArray(path + " BDE_USL_Types", launcherTypes);
        return launcherTypes.Find(launcherType) != -1;
    }
}
