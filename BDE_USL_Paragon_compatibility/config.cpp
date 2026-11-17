class CfgPatches
{
    class BDE_USL_Paragon_compatibility
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "BDE_UnderSlungLaunchers",
            "Paragon_MDR",
            "Paragon_SR25",
            "Paragon_Scar",
            "Paragon_AR15",
            "Paragon_HK",
            "Paragon_M110",
            "Paragon_SA58",
            "Paragon_Scar_H",
            "Paragon_Scar_L"
        };
    };
};

class CfgMods
{
    class BDE_USL_Paragon_compatibility
    {
        dir = "BDE_USL_Paragon_compatibility";
        name = "BDE USL - Paragon Compatibility";
        author = "Beldum";
        version = "2.0.0";
        type = "mod";
        dependencies[] = {"World"};

        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"BDE_USL_Paragon_compatibility/Scripts/4_World"};
            };
        };
    };
};

class Mode_Single;
class Mode_SemiAuto;

class CfgWeapons
{
    class Paragon_MDR_Base;
    class Paragon_MDR_Black : Paragon_MDR_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_MDR_Tan : Paragon_MDR_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_SR25_Base;
    class Paragon_SR25_Black : Paragon_SR25_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_SR25_Green : Paragon_SR25_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_SR25_Tan : Paragon_SR25_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_Scar_Base;
    class Paragon_Scar : Paragon_Scar_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_Scar_Black : Paragon_Scar_Base
    {
        modes[] = {"SemiAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_AR15_Base;
    class Paragon_AR15 : Paragon_AR15_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_Aero_Base;

    class Paragon_HK_Base;
    class Paragon_HK : Paragon_HK_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_M110_Base;
    class Paragon_M110_Black : Paragon_M110_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_M110_Green : Paragon_M110_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_M110_Tan : Paragon_M110_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_MK14_Base;

    class Paragon_SA58_Base;
    class Paragon_SA58 : Paragon_SA58_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_Scar_H_Base;
    class Paragon_Scar_H : Paragon_Scar_H_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class Paragon_Scar_L_Base;
    class Paragon_Scar_L : Paragon_Scar_L_Base
    {
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        BDE_USL_SettingsGroup = "Paragon";
        BDE_USL_LauncherSlot = "Paragon_Grip";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
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
            reloadTime = 0.35;
            dispersion = 0.01;
        };
    };

    class BDE_UnderSlungLauncher_Base;
    class BDE_M203 : BDE_UnderSlungLauncher_Base
    {
        inventorySlot[] += {"Paragon_Grip"};
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.13, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_M203_Paragon_AR15 : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.16, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_M203_Paragon_Aero : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.10, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_M203_Paragon_MK14 : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.10, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };


    class BDE_M203_Paragon_B1 : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.16, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_M203_Paragon_B2 : BDE_M203
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.19, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12 : BDE_UnderSlungLauncher_Base
    {
        inventorySlot[] += {"Paragon_Grip"};
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.13, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_FDE;

    class BDE_Six12_Paragon_AR15 : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.16, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_Paragon_AR15_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.16, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_Paragon_Aero : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.10, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_Paragon_Aero_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.10, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_Paragon_MK14 : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.10, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_Paragon_MK14_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.10, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };


    class BDE_Six12_Paragon_B1 : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.16, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_Paragon_B1_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.16, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_Paragon_B2 : BDE_Six12
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.19, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_Paragon_B2_FDE : BDE_Six12_FDE
    {
        scope = 1;
        class InventorySlotsOffsets
        {
            class Paragon_Grip
            {
                position[] = {0.19, 0.0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

};
