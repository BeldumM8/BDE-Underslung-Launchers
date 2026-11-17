class CfgPatches
{
    class BDE_USL_sGunplay_compatibility
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"BDE_UnderSlungLaunchers", "sGunplay"};
    };
};

class CfgMods
{
    class BDE_USL_sGunplay_compatibility
    {
        dir = "BDE_USL_sGunplay_compatibility";
        name = "BDE USL - sGunplay Compatibility";
        author = "Beldum";
        version = "2.1.0";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"BDE_USL_sGunplay_compatibility/Scripts/3_Game"};
            };

            class worldScriptModule
            {
                value = "";
                files[] = {"BDE_USL_sGunplay_compatibility/Scripts/4_World"};
            };

            class missionScriptModule
            {
                value = "";
                files[] = {"BDE_USL_sGunplay_compatibility/Scripts/5_Mission"};
            };
        };
    };
};
