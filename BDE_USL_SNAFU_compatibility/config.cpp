class CfgPatches
{
    class BDE_USL_SNAFU_compatibility
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "BDE_UnderSlungLaunchers",
            "SNAFU_Scripts",
            "GCGN_HK416",
            "GCGN_M110",
            "GCGN_M249",
            "ACR_CFG",
            "HK416_CFG",
            "SNHK417_CFG",
            "IA2_CFG",
            "MK18_CFG",
            "SNSA58_CFG",
            "SCAR_CFG",
            "SNAFU_AK12A",
            "SNAFU_AK19",
            "SNAFU_AK308",
            "SNAFU_CZ805_CFG",
            "SNAFU_KAC_CFG",
            "SNAFURSASS",
            "SNAFU_SR25",
            "SNAFU_ADAR_Modular",
            "SNAFU_AR15_Modular",
            "SNAFUDSA_SA58",
            "SNAFU_M4300AC_Modular",
            "SNAFU_M4_Modular",
            "SNAFUMDAR",
            "SNAFU_MK47_Modular",
            "SNAFU_SAINT_Modular",
            "SNAFU_SAINT_Modular_762",
            "Snafu_ScarH",
            "SNAFUASh12",
            "SNAFUAUG",
            "SNAFUFAMAS",
            "SNAFUHoneyBadger",
            "SNAFUMk12",
            "SNAFUSA80",
            "SNAFUThompsonMk2"
        };
    };
};

class CfgMods
{
    class BDE_USL_SNAFU_compatibility
    {
        dir = "BDE_USL_SNAFU_compatibility";
        name = "BDE USL - SNAFU Weapons Compatibility";
        author = "Beldum";
        version = "2.0.0";
        type = "mod";
        dependencies[] = {"World"};

        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"BDE_USL_SNAFU_compatibility/Scripts/4_World"};
            };
        };
    };
};

class Mode_Single;
class Mode_SemiAuto;

class CfgWeapons
{
    class Rifle_Base;
    class SNAFU_ADAR_Modular_Base;
    class SNAFU_Saint_Base;
    class SNAFU_M4300_Modular_Base;
    class SNAFU_AR15_Modular_Base;
    class SNAFU_MK47Base;
    class SNAFU_Saint308_Base;
    class SNAFU_M4_Modular_Base;

    class GCGN_M249_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "SNAFUM249Bipod";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"SNAFUM249HG"};
        BDE_M203AllowedHandguards[] = {"SNAFU_M249HG"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_M249HG"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod", "FGRIP"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class GCGN_HK416_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class GCGN_M110_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_ADAR_Modular16_GUN : SNAFU_ADAR_Modular_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10", "weaponHGSNAFU14", "weaponHGSNAFU16"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_Saint556_Gun : SNAFU_Saint_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_M4300AC_10_GUN : SNAFU_M4300_Modular_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_M4300AC_14_GUN : SNAFU_M4300_Modular_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10", "weaponHGSNAFU14"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_M4300AC_16_GUN : SNAFU_M4300_Modular_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10", "weaponHGSNAFU14", "weaponHGSNAFU16"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_AR15_Modular16_GUN : SNAFU_AR15_Modular_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10", "weaponHGSNAFU14", "weaponHGSNAFU16"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFUMDAR_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_MK4710Gun : SNAFU_MK47Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_MK4716Gun : SNAFU_MK47Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10", "weaponHGSNAFU14", "weaponHGSNAFU16"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFUMDARSBR_Black : SNAFUMDAR_Base
    {
        modes[] = {"FullAuto", "SemiAuto"};
        BDE_USL_Compatible = 0;
        BDE_USL_Types[] = {};
    };

    class SNAFUMDARCAR_Black : SNAFUMDAR_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher"};
        BDE_USL_Types[] = {"BDE_M203"};
    };

    class SNAFUDSASA58_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203"};
        BDE_USL_HandguardSlots[] = {"SNAFUDSASA58"};
        BDE_M203AllowedHandguards[] = {"SNAFU_DSAHG2"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_DSAHG2"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_Saint_Gun : SNAFU_Saint308_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_M4556_Modular10_GUN : SNAFU_M4_Modular_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_M4556_Modular14_GUN : SNAFU_M4_Modular_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10", "weaponHGSNAFU14"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_M4556_Modular16_GUN : SNAFU_M4_Modular_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"weaponHGSNAFU10", "weaponHGSNAFU14", "weaponHGSNAFU16"};
        BDE_M203AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_HGMlok", "SNAFU_HGMlok_Tan", "SNAFU_HG625", "SNAFU_MK10"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
};
    class Snafu_ScarH_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_KAC_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFURSASS_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_CZ805_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "Burst", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_SR25_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFUFAMAS_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "Burst", "SemiAuto"};
        BDE_USL_Compatible = 0;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFUMk12_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFUAUG_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto"};
        BDE_USL_Compatible = 0;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFUASh12_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFUThompsonMk2_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto"};
        BDE_USL_Compatible = 0;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFUSA80_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_AK308_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "Burst", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"SNAFUWeaponHandguardAK"};
        BDE_M203AllowedHandguards[] = {"SNAFU_AK_HG"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_AK_HG"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_AK12A_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "Burst", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"SNAFUWeaponHandguardAK"};
        BDE_M203AllowedHandguards[] = {"SNAFU_AK_HG"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_AK_HG"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNAFU_AK19_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "Burst", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {"SNAFUWeaponHandguardAK"};
        BDE_M203AllowedHandguards[] = {"SNAFU_AK_HG"};
        BDE_Six12AllowedHandguards[] = {"SNAFU_AK_HG"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SCAR_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class MK18_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNHK417_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class HK416_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class ACR_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class SNSA58_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class IA2_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "SNAFU";
        BDE_USL_LauncherSlot = "FGRIP";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlots[] = {};
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_BlockedSlots[] = {"weaponGripKAAR", "weaponGripCQR", "snafuweaponBipod"};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class BDE_UnderSlungLauncher_Base;
    class BDE_M203 : BDE_UnderSlungLauncher_Base
    {
        inventorySlot[] += {"FGRIP", "SNAFUM249Bipod"};
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.17, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
            class SNAFUM249Bipod
            {
                position[] = {-0.02, -0.2, 0};
                orientation[] = {0, 0, 90};
            };
        };
    };

    class BDE_M203_SNAFU_Back : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.14, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_M203_SNAFU_B1 : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.14, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_M203_SNAFU_B2 : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.07, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_M203_SNAFU_MK47 : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.11, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_M203_SNAFU_KAC_Forward : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.20, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };


    class BDE_Six12 : BDE_UnderSlungLauncher_Base
    {
        inventorySlot[] += {"FGRIP", "SNAFUM249Bipod"};
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.17, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
            class SNAFUM249Bipod
            {
                position[] = {-0.02, -0.2, 0};
                orientation[] = {0, 0, 90};
            };
        };
    };

    class BDE_Six12_FDE;

    class BDE_Six12_SNAFU_Back : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.14, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_SNAFU_Back_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.14, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_SNAFU_B1 : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.14, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_SNAFU_B1_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.14, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_SNAFU_B2 : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.07, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_SNAFU_B2_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.07, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_SNAFU_MK47 : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.11, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_SNAFU_MK47_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.11, 0.025, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_GP25 : BDE_UnderSlungLauncher_Base
    {
        inventorySlot[] += {"FGRIP", "SNAFUM249Bipod"};
        class InventorySlotsOffsets
        {
            class FGRIP
            {
                position[] = {-0.11, 0.005, 0};
                orientation[] = {0, 0, 0};
            };
            class SNAFUM249Bipod
            {
                position[] = {-0.02, -0.2, 0};
                orientation[] = {0, 0, 90};
            };
        };
    };
};

class CfgVehicles
{
    class BDE_GP25_ButtPad;
    class BDE_USL_M203_ButtPad_VanillaAK;
    class BDE_USL_Six12_ButtPad_VanillaAK;

    class BDE_USL_SNAFU_GP25_ButtPad : BDE_GP25_ButtPad
    {
        scope = 1;

        class InventorySlotsOffsets
        {
            class BDE_GP25_ButtPad
            {
                position[] = {-0.08, 0.012, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_SNAFU_M203_ButtPad : BDE_USL_M203_ButtPad_VanillaAK
    {
        scope = 1;

        class InventorySlotsOffsets
        {
            class BDE_M203_ButtPad
            {
                position[] = {0, 0.012, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_SNAFU_Six12_ButtPad : BDE_USL_Six12_ButtPad_VanillaAK
    {
        scope = 1;

        class InventorySlotsOffsets
        {
            class BDE_Six12_ButtPad
            {
                position[] = {0.03, -0.017, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };
};
