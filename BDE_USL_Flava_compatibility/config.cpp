class CfgPatches
{
    class BDE_USL_Flava_compatibility
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "BDE_UnderSlungLaunchers",
            "DZ_Weapons_Supports",
            "script_a",
            "TF_M4",
            "TF_ADAR215",
            "TF_AK101",
            "TF_AK102",
            "TF_AK74M",
            "TF_AK104",
            "TF_AK105",
            "TF_AKM",
            "TF_AKMN",
            "TF_AN94",
            "TF_VPO136",
            "TF_MAR_10",
            "TF_SCAR_MK16",
            "TF_SCAR_L_CQC",
            "TF_SCAR_H",
            "TF_SCAR_H_CQC",
            "TF_SCAR_MK20",
            "TF_Mk47_Mutant",
            "TF_M16A4",
            "TF_SR25",
            "TF_SVCh",
            "TF_PKM",
            "TF_PKP"
        };
    };
};

class CfgMods
{
    class BDE_USL_Flava_compatibility
    {
        dir = "BDE_USL_Flava_compatibility";
        name = "BDE USL - Flava Weapons Compatibility";
        author = "BDE";
        version = "2.0.0";
        type = "mod";
        dependencies[] = {"World"};

        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"BDE_USL_Flava_compatibility/Scripts/4_World"};
            };
        };
    };
};

class CfgSlots
{
    class Slot_weaponBipod
    {
        name = "weaponBipod";
        displayName = "$STR_weaponBipod";
        ghostIcon = "set:TF image:bipod";
    };
};

class Mode_Single;
class Mode_SemiAuto;

class CfgWeapons
{
    class Rifle_Base;

    class TF_M4A1_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardM4";
        BDE_M203AllowedHandguards[] =
        {
            "TF_M4_KACHndgrd_RIS",
            "TF_M4_DD9Hndgrd_RIS_FDE",
            "TF_M4_DD12Hndgrd_RIS_FDE",
            "TF_M4_DDFSPHndgrd_RIS_FDE",
            "TF_M16_KACHndgrd_RIS",
            "M4_RISHndgrd",
            "M4_RISHndgrd_Black",
            "M4_RISHndgrd_Green"
        };
        BDE_Six12AllowedHandguards[] =
        {
            "TF_M4_KACHndgrd_RIS",
            "TF_M4_DD9Hndgrd_RIS_FDE",
            "TF_M4_DD12Hndgrd_RIS_FDE",
            "TF_M4_DDFSPHndgrd_RIS_FDE",
            "TF_M16_KACHndgrd_RIS",
            "M4_RISHndgrd",
            "M4_RISHndgrd_Black",
            "M4_RISHndgrd_Green"
        };
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod", "weaponBayonet"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_ADAR2_15_Base : TF_M4A1_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
    };

    class TF_AK101_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod", "weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_ProjectileSpawnClearance = 0.50;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
        };
    };

    class TF_AK102_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_AK103_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod", "weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_ProjectileSpawnClearance = 0.50;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
        };
    };

    class TF_AK104_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_AK105_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_AK74M_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod", "weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_ProjectileSpawnClearance = 0.50;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
        };
    };

    class TF_AKM_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod", "weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_ProjectileSpawnClearance = 0.50;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
        };
    };

    class TF_AKMN_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod", "weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_ProjectileSpawnClearance = 0.50;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
        };
    };

    class TF_AKM : TF_AKM_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
    };

    class TF_AKMN : TF_AKMN_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
    };

    class TF_VPO136_Base : TF_AKM_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_Six12AllowedHandguards[] = {"TF_AK_ZenitB30B31Hndgrd_RIS", "TF_AK_ZenitB10MB19Hndgrd_RIS", "AK_RailHndgrd", "AK_RailHndgrd_Black", "AK_RailHndgrd_Green"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod", "weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_ProjectileSpawnClearance = 0.50;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
        };
    };

    class TF_MAR_10_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_SCAR_L_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "weaponStndHndgrdSCAR";
        BDE_M203AllowedHandguards[] = {"TF_SCAR_StndHndgrd", "TF_SCAR_ADDHndgrd"};
        BDE_Six12AllowedHandguards[] = {"TF_SCAR_StndHndgrd", "TF_SCAR_ADDHndgrd"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_SCAR_L_CQC_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "weaponStndHndgrdSCAR";
        BDE_M203AllowedHandguards[] = {"TF_SCAR_StndHndgrd", "TF_SCAR_ADDHndgrd"};
        BDE_Six12AllowedHandguards[] = {"TF_SCAR_StndHndgrd", "TF_SCAR_ADDHndgrd"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_SCAR_H_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "weaponStndHndgrdSCAR";
        BDE_M203AllowedHandguards[] = {"TF_SCAR_StndHndgrd", "TF_SCAR_ADDHndgrd"};
        BDE_Six12AllowedHandguards[] = {"TF_SCAR_StndHndgrd", "TF_SCAR_ADDHndgrd"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_SCAR_H_CQC_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "weaponStndHndgrdSCAR";
        BDE_M203AllowedHandguards[] = {"TF_SCAR_StndHndgrd", "TF_SCAR_ADDHndgrd"};
        BDE_Six12AllowedHandguards[] = {"TF_SCAR_StndHndgrd", "TF_SCAR_ADDHndgrd"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_SCAR_20_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_MK47_CQBR_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardMK47";
        BDE_M203AllowedHandguards[] = {"TF_AR10_KACHndgrd_RIS", "TF_AR10_NoveskeHndgrd_Short_RIS", "TF_AR10_NoveskeHndgrd_Long_RIS"};
        BDE_Six12AllowedHandguards[] = {"TF_AR10_KACHndgrd_RIS", "TF_AR10_NoveskeHndgrd_Short_RIS", "TF_AR10_NoveskeHndgrd_Long_RIS"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_MK47_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardMK47";
        BDE_M203AllowedHandguards[] = {"TF_AR10_KACHndgrd_RIS", "TF_AR10_NoveskeHndgrd_Short_RIS", "TF_AR10_NoveskeHndgrd_Long_RIS"};
        BDE_Six12AllowedHandguards[] = {"TF_AR10_KACHndgrd_RIS", "TF_AR10_NoveskeHndgrd_Short_RIS", "TF_AR10_NoveskeHndgrd_Long_RIS"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_M16A4_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Burst", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardM4";
        BDE_M203AllowedHandguards[] =
        {
            "TF_M4_KACHndgrd_RIS",
            "TF_M4_DD9Hndgrd_RIS_FDE",
            "TF_M4_DD12Hndgrd_RIS_FDE",
            "TF_M4_DDFSPHndgrd_RIS_FDE",
            "TF_M16_KACHndgrd_RIS",
            "M4_RISHndgrd",
            "M4_RISHndgrd_Black",
            "M4_RISHndgrd_Green"
        };
        BDE_Six12AllowedHandguards[] =
        {
            "TF_M4_KACHndgrd_RIS",
            "TF_M4_DD9Hndgrd_RIS_FDE",
            "TF_M4_DD12Hndgrd_RIS_FDE",
            "TF_M4_DDFSPHndgrd_RIS_FDE",
            "TF_M16_KACHndgrd_RIS",
            "M4_RISHndgrd",
            "M4_RISHndgrd_Black",
            "M4_RISHndgrd_Green"
        };
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod", "weaponBayonet"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_SR25_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardMK47";
        BDE_M203AllowedHandguards[] = {"TF_AR10_KACHndgrd_RIS", "TF_AR10_NoveskeHndgrd_Short_RIS", "TF_AR10_NoveskeHndgrd_Long_RIS"};
        BDE_Six12AllowedHandguards[] = {"TF_AR10_KACHndgrd_RIS", "TF_AR10_NoveskeHndgrd_Short_RIS", "TF_AR10_NoveskeHndgrd_Long_RIS"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_SVCh_Base : Rifle_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBipod"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_PKM_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardPKM";
        BDE_M203AllowedHandguards[] = {"TF_PKM_ZenitB50Hndgrd_RIS", "TF_PKP_CNCC46Hndgrd_RIS"};
        BDE_Six12AllowedHandguards[] = {"TF_PKM_ZenitB50Hndgrd_RIS", "TF_PKP_CNCC46Hndgrd_RIS"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };

    class TF_PKP_Base : Rifle_Base
    {
        modes[] = {"FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponGrip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "WeaponHandguardPKM";
        BDE_M203AllowedHandguards[] = {"TF_PKM_ZenitB50Hndgrd_RIS", "TF_PKP_CNCC46Hndgrd_RIS"};
        BDE_Six12AllowedHandguards[] = {"TF_PKM_ZenitB50Hndgrd_RIS", "TF_PKP_CNCC46Hndgrd_RIS"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
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
        };
    };
    class TF_AN94_Base;
    class TF_AN94M : TF_AN94_Base
    {
        modes[] = {"SemiAuto", "Burst", "FullAuto", "Launcher"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "TacticalFlava";
        BDE_USL_LauncherSlot = "weaponBipod";
        BDE_USL_Types[] = {"BDE_M203", "BDE_GP25"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};
        BDE_USL_ProjectileSpawnClearance = 0.2;

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };
    };

    class BDE_UnderSlungLauncher_Base;

    class BDE_M203 : BDE_UnderSlungLauncher_Base
    {
        inventorySlot[] += {"weaponGrip"};

        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.1, 0.028, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_M203_Flava_AN94M : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class weaponBipod
            {
                position[] = {0.03, 0.136, 0};
                orientation[] = {0, 0, -90};
            };
        };
    };

    class BDE_Six12 : BDE_UnderSlungLauncher_Base
    {
        inventorySlot[] += {"weaponGrip"};

        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.1, 0.028, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_FDE;

    class BDE_USL_Six12_Flava_M16A4 : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.08, 0.028, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_Six12_Flava_M16A4_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.08, 0.028, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_Six12_Flava_SVCh : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.08, 0.028, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_Six12_Flava_SVCh_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.08, 0.028, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_GP25 : BDE_UnderSlungLauncher_Base
    {
        inventorySlot[] += {"weaponGrip"};
        modes[] = {"Launcher"};

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            soundSetShot[] =
            {
                "M79_Shot_SoundSet",
                "M79_Tail_SoundSet",
                "M79_InteriorTail_SoundSet",
                "M79_Slapback_SoundSet",
                "M79_Tail_2D_SoundSet",
                "M79_Shot_Interior_SoundSet"
            };
            soundSetShotExt[] =
            {
                {
                    "IZH18_silencerHomeMade_SoundSet",
                    "IZH18_silencerHomeMadeTail_SoundSet",
                    "IZH18_silencerInteriorHomeMadeTail_SoundSet"
                }
            };
            envShootingDecrease = 0.05;
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.13, 0.016, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_GP25_Flava_ShortAK : BDE_GP25
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.16, 0.016, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_M203_Flava_M16A4 : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.08, 0.028, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_M203_Flava_SVCh : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class weaponGrip
            {
                position[] = {0.08, 0.028, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };
};

class CfgVehicles
{
    class Inventory_Base;
    class BDE_GP25_ButtPad;

    class BDE_USL_GP25_ButtPad_FlavaAK : BDE_GP25_ButtPad
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class BDE_GP25_ButtPad
            {
                position[] = {0, -0.011, 0};
                orientation[] = {0, 0, 0};
            };

            class BDE_M203_ButtPad
            {
                position[] = {0.03, -0.023, 0};
                orientation[] = {0, 0, 0};
            };

            class BDE_Six12_ButtPad
            {
                position[] = {0.03, -0.023, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_USL_GP25_ButtPad_FlavaShortAK : BDE_GP25_ButtPad
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class BDE_GP25_ButtPad
            {
                position[] = {-0.04, -0.011, 0};
                orientation[] = {0, 0, 0};
            };

            class BDE_M203_ButtPad
            {
                position[] = {0.02, -0.023, 0};
                orientation[] = {0, 0, 0};
            };

            class BDE_Six12_ButtPad
            {
                position[] = {0.02, -0.023, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };
    class M4_RISHndgrd : Inventory_Base
    {
        IsRis = 1;
        hasRailFunctionality = 1;
    };

    class M4_RISHndgrd_Black : M4_RISHndgrd
    {
        IsRis = 1;
        hasRailFunctionality = 1;
    };

    class M4_RISHndgrd_Green : M4_RISHndgrd
    {
        IsRis = 1;
        hasRailFunctionality = 1;
    };
};
