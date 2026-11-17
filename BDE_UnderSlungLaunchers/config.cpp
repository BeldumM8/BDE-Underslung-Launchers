class CfgPatches
{
    class BDE_UnderSlungLaunchers
    {
        units[] =
        {
            "BDE_FN40",
            "BDE_FN40_FDE",
            "BDE_FN40_Barrel",
            "BDE_FN40_Barrel_FDE",
            "BDE_FN40_Handle",
            "BDE_FN40_Handle_FDE",
            "BDE_FN40_Sight",
            "BDE_FN40_Sight_FDE",
            "BDE_FN40_Sight_Mount",
            "BDE_FN40_StandaloneMount",
            "BDE_FN40_StandaloneMount_FDE",
            "BDE_M203",
            "BDE_GP25",
            "BDE_GP25_ButtPad",
            "BDE_GP25_ButtStock",
            "BDE_GP25_Sight",
            "BDE_GP25_Sight_Unfolded",
            "Ammo_VOG25",
            "Ammo_VOG25_Smoke_Red",
            "Ammo_VOG25_Smoke_Green",
            "Ammo_VOG25_Smoke_White",
            "Ammo_VOG25_Smoke_Black",
            "Ammo_40mm_Empty",
            "BDE_M203_Barrel",
            "BDE_M203_Short_Barrel",
            "BDE_M203_ButtStock",
            "BDE_M203_FrontSight",
            "BDE_M203_RearSight",
            "BDE_M203_Rail_Adapter",
            "BDE_M203_StandAloneMount",
            "BDE_Six12",
            "BDE_Six12_FDE",
            "BDE_Six12_Handle",
            "BDE_Six12_Handle_FDE",
            "BDE_Six12_LongBarrel",
            "BDE_Six12_ShortBarrel",
            "BDE_Six12_StandAloneMount",
            "BDE_Six12_StandAloneMount_FDE",
            "BDE_Six12_Magazine",
            "BDE_Six12_Magazine_FDE"
        };
        weapons[] =
        {
            "BDE_FN40",
            "BDE_FN40_FDE",
            "BDE_FN40_StandaloneMount_Weapon",
            "BDE_FN40_StandaloneMount_Weapon_FDE",
            "BDE_M203_StandAloneMount_Weapon",
            "BDE_Six12",
            "BDE_Six12_FDE",
            "BDE_Six12_StandAloneMount_Weapon",
            "BDE_Six12_StandAloneMount_Weapon_FDE"
        };
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Scripts",
            "DZ_Anims_Anm_Player",
            "DZ_Anims_Cfg",
            "DZ_Weapons_Firearms_M4",
            "DZ_Weapons_Firearms_SCARH",
            "DZ_Weapons_Optics",
            "DZ_Weapons_Supports",
            "DZ_Weapons_Ammunition",
            "DZ_Weapons_Magazines",
            "DZ_Weapons_Projectiles",
            "DZ_Weapons_Explosives",
            "DZ_Weapons_Launchers_M79",
            "DZ_Weapons_Launchers_M203",
            "DZ_Weapons_Launchers_GP25",
            "DZ_Weapons_Firearms_AKM",
            "DZ_Weapons_Firearms_AK101",
            "DZ_Weapons_Firearms_AK74",
            "DZ_Weapons_Firearms_SaigaK",
            "DZ_Weapons_Firearms_Famas",
            "DZ_Gear_Food"
        };
    };
};

class CfgMods
{
    class BDE_UnderSlungLaunchers
    {
        dir = "BDE_UnderSlungLaunchers";
        name = "BDE UnderSlung Launchers";
        author = "Beldum";
        version = "1.0.0";
        type = "mod";
        defines[] = {"BDE_UnderSlungLaunchers"};
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"BDE_UnderSlungLaunchers/Scripts/3_Game"};
            };

            class worldScriptModule
            {
                value = "";
                files[] = {"BDE_UnderSlungLaunchers/Scripts/4_World"};
            };

            class missionScriptModule
            {
                value = "";
                files[] = {"BDE_UnderSlungLaunchers/Scripts/5_Mission"};
            };
        };
    };
};

class CfgSlots
{
    class Slot_BDE_OTS14_LauncherSight
    {
        name = "BDE_OTS14_LauncherSight";
        displayName = "";
        ghostIcon = "";
        show = "false";
    };

    class Slot_BDE_OTS14_Launcher
    {
        name = "BDE_OTS14_Launcher";
        displayName = "Groza launcher";
        ghostIcon = "set:dayz_inventory image:weaponhandguard";
    };

    class Slot_BDE_SideRail
    {
        name = "BDE_SideRail";
        displayName = "Side Rail Sight";
        ghostIcon = "set:dayz_inventory image:weaponoptics";
    };

    class Slot_weaponBipod
    {
        name = "weaponBipod";
        displayName = "Underbarrel Launcher";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_M203_Body
    {
        name = "BDE_M203_Body";
        displayName = "M203 Launcher";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_M203_Barrel
    {
        name = "BDE_M203_Barrel";
        displayName = "M203 Barrel";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_M203_FrontSight
    {
        name = "BDE_M203_FrontSight";
        displayName = "";
        ghostIcon = "";
        show = "false";
    };

    class Slot_BDE_M203_RailAdapter
    {
        name = "BDE_M203_RailAdapter";
        displayName = "M203 Rail Adapter";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_M203_RearSight
    {
        name = "BDE_M203_RearSight";
        displayName = "M203 Rear Sight";
        ghostIcon = "set:dayz_inventory image:weaponoptics";
    };

    class Slot_BDE_GP25_ButtPad
    {
        name = "BDE_GP25_ButtPad";
        displayName = "GP-25 Buttpad";
        ghostIcon = "set:dayz_inventory image:weaponbuttstock";
    };

    class Slot_BDE_M203_ButtPad
    {
        name = "BDE_M203_ButtPad";
        displayName = "M203 Buttpad";
        ghostIcon = "set:dayz_inventory image:weaponbuttstock";
    };

    class Slot_BDE_Six12_ButtPad
    {
        name = "BDE_Six12_ButtPad";
        displayName = "SIX12 Buttpad";
        ghostIcon = "set:dayz_inventory image:weaponbuttstock";
    };

    class Slot_BDE_GP25_ButtStock
    {
        name = "BDE_GP25_ButtStock";
        displayName = "GP-25 Buttstock";
        ghostIcon = "set:dayz_inventory image:weaponbuttstock";
    };

    class Slot_BDE_GP25_Sight
    {
        name = "BDE_GP25_Sight";
        displayName = "";
        ghostIcon = "";
        show = "false";
    };

    class Slot_BDE_Six12
    {
        name = "BDE_Six12";
        displayName = "SIX12 Receiver";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_Six12_Handle
    {
        name = "BDE_Six12_Handle";
        displayName = "SIX12 Handle";
        ghostIcon = "set:dayz_inventory image:weaponpistolgrip";
    };

    class Slot_BDE_Six12_ShortBarrel
    {
        name = "BDE_Six12_ShortBarrel";
        displayName = "SIX12 Short Barrel";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_Six12_LongBarrel
    {
        name = "BDE_Six12_LongBarrel";
        displayName = "SIX12 Long Barrel";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_Six12_Magazine
    {
        name = "BDE_Six12_Magazine";
        displayName = "SIX12 Magazine";
        ghostIcon = "set:dayz_inventory image:magazine";
        show = "true";
    };

    class Slot_BDE_FN40_Body
    {
        name = "BDE_FN40_Body";
        displayName = "FN40 Launcher";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_FN40_Barrel
    {
        name = "BDE_FN40_Barrel";
        displayName = "FN40 Barrel";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_FN40_Handle
    {
        name = "BDE_FN40_Handle";
        displayName = "FN40 Handle";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
    };

    class Slot_BDE_FN40_Sight_Mount
    {
        name = "BDE_FN40_Sight_Mount";
        displayName = "FN40 Sight Mount";
        ghostIcon = "set:dayz_inventory image:weaponoptics";
    };

    class Slot_BDE_FN40_Sight
    {
        name = "BDE_FN40_Sight";
        displayName = "FN40 Sight";
        ghostIcon = "set:dayz_inventory image:weaponmuzzle";
        show = "false";
    };
};

class CfgNonAIVehicles
{
    class ProxyAttachment;

    class ProxyGroza_Launcher_Sight : ProxyAttachment
    {
        scope = 2;
        model = "BDE_UnderSlungLaunchers\Models\Groza_Launcher_Sight.p3d";
        simulation = "ProxyInventory";
        inventorySlot = "BDE_OTS14_LauncherSight";
        autocenter = 0;
        animated = 1;
    };

    class ProxyM203_Barrel : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_M203_Barrel";
        model = "\BDE_UnderSlungLaunchers\Models\M203_Barrel.p3d";
    };

    class ProxyM203_Body : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_M203_Body";
        model = "\BDE_UnderSlungLaunchers\Models\M203_Body.p3d";
    };

    class ProxyM203_FrontSight : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_M203_FrontSight";
        model = "\BDE_UnderSlungLaunchers\Models\M203_FrontSight.p3d";
    };

    class ProxyM203_Rail_Adapter : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_M203_RailAdapter";
        model = "\BDE_UnderSlungLaunchers\Models\M203_Rail_Adapter.p3d";
    };

    class ProxyM203_RearSight : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_M203_RearSight";
        model = "\BDE_UnderSlungLaunchers\Models\M203_RearSight.p3d";
    };

    class ProxyGP25_ButtPad : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_GP25_ButtPad";
        model = "\BDE_UnderSlungLaunchers\Models\GP25_ButtPad.p3d";
    };

    class ProxyM203_ButtPad : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_M203_ButtPad";
        model = "\BDE_UnderSlungLaunchers\Models\M203_ButtPad.p3d";
    };

    class ProxySix12_ButtPad : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_Six12_ButtPad";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_ButtPad.p3d";
    };

    class ProxyGP25_ButtStock : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_GP25_ButtStock";
        model = "\BDE_UnderSlungLaunchers\Models\GP25_ButtStock.p3d";
    };

    class ProxyGP25_Sight : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_GP25_Sight";
        model = "\BDE_UnderSlungLaunchers\Models\GP25_Sight.p3d";
    };

    class ProxySix12_Body : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_Six12";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_Body.p3d";
    };

    class ProxySix12_Handle : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_Six12_Handle";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_Handle.p3d";
    };

    class ProxySix12_ShortBarrel : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_Six12_ShortBarrel";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_ShortBarrel.p3d";
    };

    class ProxySix12_LongBarrel : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_Six12_LongBarrel";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_LongBarrel.p3d";
    };

    class ProxySix12_Magazine : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_Six12_Magazine";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_Magazine.p3d";
    };

    class ProxyFN40_Body : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_FN40_Body";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Body.p3d";
    };

    class ProxyFN40_Barrel : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_FN40_Barrel";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Barrel.p3d";
    };

    class ProxyFN40_Handle : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_FN40_Handle";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Handle.p3d";
    };

    class ProxyFN40_Sight_Mount : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_FN40_Sight_Mount";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Sight_Mount.p3d";
    };

    class ProxyFN40_Sight : ProxyAttachment
    {
        scope = 2;
        simulation = "ProxyInventory";
        inventorySlot = "BDE_FN40_Sight";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Sight.p3d";
    };
};

class Mode_Single;
class Mode_SemiAuto;
class OpticsInfoRifle;
class OpticsInfoShotgun;

class CfgMagazines
{
    class Magazine_Base;
    class Ammo_40mm_Explosive;

    class BDE_Six12_Magazine : Magazine_Base
    {
        scope = 1;
        displayName = "SIX12 6-Round Cylinder";
        descriptionShort = "Six-round 12 gauge revolving cylinder for the SIX12 shotgun.";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_Magazine.p3d";
        inventorySlot[] = {"BDE_Six12_Magazine"};
        weight = 650;
        weightPerQuantityUnit = 35;
        itemSize[] = {2, 2};
        count = 6;
        ammo = "Bullet_12GaugePellets";
        ammoItems[] = {"Ammo_12gaPellets", "Ammo_12gaSlug", "Ammo_12gaRubberSlug", "Ammo_12gaBeanbag"};
        iconCartridge = 4;
        iconType = 0;
        hiddenSelections[] = {"Six12"};
        simpleHiddenSelections[] = {"bullet1", "bullet2", "bullet3", "bullet4", "bullet5", "bullet6"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_Black_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"};

        class AnimationSources
        {
            class six12_cylinder_rotate
            {
                source = "user";
                animPeriod = 0.25;
                initPhase = 0;
            };
            class six12_magazine_slide
            {
                source = "user";
                animPeriod = 0.25;
                initPhase = 0;
            };
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\six12.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_Six12_Magazine_FDE : BDE_Six12_Magazine
    {
        scope = 1;
        displayName = "SIX12 6-Round Cylinder (FDE)";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\six12.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class Ammo_VOG25 : Ammo_40mm_Explosive
    {
        scope = 2;
        displayName = "VOG-25 Grenade";
        descriptionShort = "Caseless 40 mm high-explosive grenade for the GP-25 underbarrel grenade launcher.";
        model = "\BDE_UnderSlungLaunchers\Models\VOG25.p3d";
        ammo = "Bullet_40mm_Explosive";
        count = 1;
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\vog25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class Ammo_VOG25_Smoke_Red : Ammo_VOG25
    {
        displayName = "VOG-25 Smoke Grenade (Red)";
        descriptionShort = "Caseless 40 mm red smoke grenade for the GP-25 underbarrel grenade launcher.";
        ammo = "Bullet_40mm_Smoke_Red";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_RedSmoke.paa"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\vog25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class Ammo_VOG25_Smoke_Green : Ammo_VOG25
    {
        displayName = "VOG-25 Smoke Grenade (Green)";
        descriptionShort = "Caseless 40 mm green smoke grenade for the GP-25 underbarrel grenade launcher.";
        ammo = "Bullet_40mm_Smoke_Green";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_GreenSmoke.paa"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\vog25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class Ammo_VOG25_Smoke_White : Ammo_VOG25
    {
        displayName = "VOG-25 Smoke Grenade (White)";
        descriptionShort = "Caseless 40 mm white smoke grenade for the GP-25 underbarrel grenade launcher.";
        ammo = "Bullet_40mm_Smoke_White";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_WhiteSmoke.paa"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\vog25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class Ammo_VOG25_Smoke_Black : Ammo_VOG25
    {
        displayName = "VOG-25 Smoke Grenade (Black)";
        descriptionShort = "Caseless 40 mm black smoke grenade for the GP-25 underbarrel grenade launcher.";
        ammo = "Bullet_40mm_Smoke_Black";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_BlackSmoke.paa"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\vog25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\VOG25_destruct.rvmat"}}
                    };
                };
            };
        };
    };
};

class CfgWeapons
{
    class M79_Base;
    class Rifle_Base;

    class M4A1_Base;
    class M4A1 : M4A1_Base
    {
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        attachments[] = {"weaponButtstockM4", "WeaponHandguardM4", "weaponWrap", "weaponOptics", "weaponFlashlight", "weaponMuzzleM4", "weaponBayonet", "weaponBipod"};
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_SettingsGroup = "Vanilla";
        BDE_USL_ProjectileSpawnClearance = 0.0;
        BDE_USL_LauncherSlot = "weaponBipod";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "weaponHandguardM4";
        BDE_M203AllowedHandguards[] = {"M4_RISHndgrd"};
        BDE_Six12AllowedHandguards[] = {"M4_RISHndgrd"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBayonet"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};

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

    class SCARH_Base;
    class SCARH : SCARH_Base
    {
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        attachments[] = {"weaponButtstockSCAR", "weaponWrap", "weaponOptics", "suppressorImpro", "Scarh_FrontSight", "weaponFlashlight", "weaponBipod", "BDE_SideRail"};
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_SettingsGroup = "Vanilla";
        BDE_USL_ProjectileSpawnClearance = 0.0;
        BDE_USL_LauncherSlot = "weaponBipod";
        BDE_USL_Types[] = {"BDE_M203", "BDE_Six12", "BDE_FN40"};
        BDE_USL_HandguardSlot = "";
        BDE_M203AllowedHandguards[] = {};
        BDE_Six12AllowedHandguards[] = {};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1;
            dispersion = 0.025;
        };
    };
    class SCARH_Black : SCARH {};

    class AKM_Base;
    class AKM : AKM_Base
    {
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        attachments[] = {"weaponButtstockAK", "WeaponHandguardAK", "weaponWrap", "weaponOpticsAK", "weaponFlashlight", "weaponMuzzleAK", "weaponBayonetAK", "weaponBipod"};
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_SettingsGroup = "Vanilla";
        BDE_USL_ProjectileSpawnClearance = 0.50;
        BDE_USL_LauncherSlot = "weaponBipod";
        BDE_USL_Types[] = {"BDE_GP25", "BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "weaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"AK_RailHndgrd"};
        BDE_Six12AllowedHandguards[] = {"AK_RailHndgrd"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};

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

    class AK101_Base;
    class AK101 : AK101_Base
    {
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        attachments[] = {"weaponButtstockAK", "WeaponHandguardAK", "weaponWrap", "weaponOpticsAK", "weaponFlashlight", "weaponMuzzleAK", "weaponBayonetAK", "weaponBipod"};
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_SettingsGroup = "Vanilla";
        BDE_USL_ProjectileSpawnClearance = 0.50;
        BDE_USL_LauncherSlot = "weaponBipod";
        BDE_USL_Types[] = {"BDE_GP25", "BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "weaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"AK_RailHndgrd"};
        BDE_Six12AllowedHandguards[] = {"AK_RailHndgrd"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};

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

    class AK74_Base;
    class AK74 : AK74_Base
    {
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_Six12CustomReloadAnimation = 1;
        BDE_USL_GP25CustomReloadAnimation = 1;
        attachments[] = {"weaponButtstockAK", "WeaponHandguardAK", "weaponWrap", "weaponOpticsAK", "weaponFlashlight", "weaponMuzzleAK", "weaponBayonetAK", "weaponBipod"};
        modes[] = {"SemiAuto", "FullAuto", "Launcher", "Six12"};
        BDE_USL_Compatible = 1;
        BDE_USL_SettingsGroup = "Vanilla";
        BDE_USL_ProjectileSpawnClearance = 0.50;
        BDE_USL_LauncherSlot = "weaponBipod";
        BDE_USL_Types[] = {"BDE_GP25", "BDE_M203", "BDE_Six12"};
        BDE_USL_HandguardSlot = "weaponHandguardAK";
        BDE_M203AllowedHandguards[] = {"AK_RailHndgrd"};
        BDE_Six12AllowedHandguards[] = {"AK_RailHndgrd"};
        BDE_GP25AllowedHandguards[] = {};
        BDE_USL_BlockedSlots[] = {"weaponBayonetAK"};
        BDE_M203BlockedAttachments[] = {};
        BDE_Six12BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};

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

    class BDE_M203_StandAloneMount_Weapon : M79_Base
    {
        scope = 1;
        displayName = "M203 Standalone Mount";
        descriptionShort = "Standalone chassis for the M203 grenade launcher. Attach an M203 launcher body to use it as a handheld weapon.";
        model = "\BDE_UnderSlungLaunchers\Models\M203_StandAloneMount.p3d";
        BDE_USL_StandaloneSightCameraBackOffset = 0.05;
        weight = 1500;
        itemSize[] = {6, 3};
        WeaponLength = 0.55;
        ObstructionDistance = 0.35;
        WeaponLiftCheckVerticalOffset = -0.1;

        chamberSize = 6;
        chamberedRound = "";
        chamberableFrom[] = {};
        magazines[] = {};
        DisplayMagazine = 0;

        attachments[] = {"BDE_M203_Body", "weaponButtstockM4", "weaponOptics"};

        modes[] = {"Launcher"};
        BDE_USL_Compatible = 1;
        BDE_USL_SettingsGroup = "Vanilla";
        BDE_USL_ProjectileSpawnClearance = 0.20;
        BDE_USL_LauncherSlot = "BDE_M203_Body";
        BDE_USL_Types[] = {"BDE_M203"};
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_BlockedSlots[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };

        class OpticsInfo : OpticsInfoRifle
        {
            memoryPointCamera = "eye";
            discreteDistance[] = {25, 50, 75, 100, 125, 150, 175, 200, 225, 250};
            discreteDistanceInitIndex = 0;
            modelOptics = "-";
            distanceZoomMin = 25;
            distanceZoomMax = 250;
        };

        class InventorySlotsOffsets
        {
            class Shoulder
            {
                position[] = {-0.10, 0, 0.14};
                orientation[] = {0, 0, 0};
            };

            class Melee
            {
                position[] = {-0.10, 0, 0.14};
                orientation[] = {0, 0, 0};
            };
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\m203_frame.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame_damage.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame_damage.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame_destruct.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_UnderSlungLauncher_Base : Rifle_Base
    {
        scope = 0;

        BDE_USL_AimCameraOffset[] = {-0.12, 0.18, -0.43};

        BDE_USL_FallbackShotWear = 1.0;

        BDE_USL_WearDiagnostics = 1;
        BDE_USL_AimGravity = 9.81;
        BDE_USL_AimMaxAngle = 45.0;
        BDE_USL_AimFallbackZeroing = 25.0;

        itemSize[] = {4, 2};
        repairableWithKits[] = {1};
        repairCosts[] = {25};
        PPDOFProperties[] = {1, 0.5, 10, 170, 4, 10};
        WeaponLength = 0.39999999;
        ObstructionDistance = 0.223;
        barrelArmor = 1.875;
        initSpeedMultiplier = 1;
        chamberSize = 1;
        chamberedRound = "";
        chamberableFrom[] =
        {
            "Ammo_40mm_Explosive",
            "Ammo_40mm_ChemGas",
            "Ammo_40mm_Smoke_Red",
            "Ammo_40mm_Smoke_Green",
            "Ammo_40mm_Smoke_White",
            "Ammo_40mm_Smoke_Black",
            "Ammo_40mm_Smoke_AirStrike"
        };
        magazines[] = {};
        DisplayMagazine = 0;
        ejectType = 3;
        recoilModifier[] = {1, 1, 1};
        swayModifier[] = {1, 1, 1};

        class NoiseShoot
        {
            strength = 40;
            type = "shot";
        };

        modes[] = {"Single"};

        class Single : Mode_Single
        {
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
            envShootingDecrease = 0.050000001;
            reloadTime = 1;
            dispersion = 0.025;
        };

        class OpticsInfo : OpticsInfoRifle
        {
            memoryPointCamera = "eye";
            discreteDistance[] = {0};
            discreteDistanceInitIndex = 0;
            modelOptics = "-";
            distanceZoomMin = 0;
            distanceZoomMax = 0;
        };

        class Particles
        {
            class OnFire
            {
                class MuzzleFlash
                {
                    overrideParticle = "weapon_shot_mosin9130_01";
                    ignoreIfSuppressed = 1;
                    illuminateWorld = 0;
                    positionOffset[] = {-0.029999999, 0, 0};
                };
            };
        };

        simpleHiddenSelections[] =
        {
            "bullet"
        };
    };

    class BDE_M203 : BDE_UnderSlungLauncher_Base
    {
        scope = 2;
        displayName = "M203 Grenade Launcher";
        descriptionShort = "Single-shot 40mm underslung grenade launcher for compatible rifles with rail systems. Select the Launcher fire mode to fire. While Launcher mode is selected, hold Charge Firearm Mechanism to reload the launcher or double tap it to unload. The M203 can also be loaded directly by dragging a 40mm round onto it.";
        model = "\BDE_UnderSlungLaunchers\Models\M203_Body.p3d";
        WeaponLiftCheckVerticalOffset = -0.1;

        initSpeedMultiplier = 1.0;
        weight = 750;

        attachments[] = {"BDE_M203_Barrel", "BDE_M203_ButtPad", "BDE_M203_RailAdapter"};
        inventorySlot[] = {"weaponBipod", "BDE_M203_Body"};

        BDE_USL_AimZeroingDistances[] = {0, 50, 100, 150, 200, 250};

        BDE_M203_RailSightFront[] = {-0.221305076, 0.082946869, -0.049917353};
        BDE_M203_RailSightRear1[] = {-0.025853595, 0.085499013, -0.049917353};
        BDE_M203_RailSightRear2[] = {-0.025853597, 0.099917014, -0.049917355};
        BDE_M203_RailSightRear3[] = {-0.025853598, 0.106921014, -0.049917356};
        BDE_M203_RailSightRear4[] = {-0.025853599, 0.115567014, -0.049917357};
        BDE_M203_RailSightRear5[] = {-0.025853600, 0.124038014, -0.049917358};
        BDE_M203_RailSightRear6[] = {-0.025853601, 0.132400015, -0.049917359};
        BDE_M203_RailSightCameraBackOffset = 0.05;
        BDE_USL_CasingEjectOffset[] = {0, 0, 0};

        BDE_USL_AttachedMuzzleStart[] = {-0.11, 0.001463, 0};
        BDE_USL_AttachedMuzzleEnd[] = {-0.40, 0.001463, 0};

        s_recoilControlStabilityX = -0.15;
        s_recoilControlStabilityY = -0.15;
        s_recoilControlMisalignmentX = -0.05;
        s_recoilControlMisalignmentY = -0.1;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\m203.rvmat", "BDE_UnderSlungLaunchers\Data\M203\M203_Receiver_Side_Rail.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\m203.rvmat", "BDE_UnderSlungLaunchers\Data\M203\M203_Receiver_Side_Rail.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\m203.rvmat", "BDE_UnderSlungLaunchers\Data\M203\M203_Receiver_Side_Rail.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\m203_damage.rvmat", "BDE_UnderSlungLaunchers\Data\M203\M203_Receiver_Side_Rail_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\m203_damage.rvmat", "BDE_UnderSlungLaunchers\Data\M203\M203_Receiver_Side_Rail_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_destruct.rvmat", "BDE_UnderSlungLaunchers\Data\M203\M203_Receiver_Side_Rail_destruct.rvmat"}}
                    };
                };
            };
        };

        class InventorySlotsOffsets
        {
            class weaponBipod
            {
                position[] = {0.027, 0.197, 0};
                orientation[] = {0, 0, -90};
            };

            class BDE_M203_Body
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };
    class BDE_GP25 : BDE_UnderSlungLauncher_Base
    {
        scope = 2;
        displayName = "GP-25 Grenade Launcher";
        descriptionShort = "Single-shot 40 mm underslung grenade launcher for compatible AK-pattern rifles. Requires a compatible AK handguard to mount. Select the Launcher fire mode to fire. While Launcher mode is selected, hold Charge Firearm Mechanism to reload the launcher or double tap it to unload.";
        model = "\BDE_UnderSlungLaunchers\Models\GP25_Launcher.p3d";
        WeaponLiftCheckVerticalOffset = -0.1;

        initSpeedMultiplier = 1.0;

        // Preserve Rifle_Base storage slots, including MMG gunwall slots.
        inventorySlot[] +=
        {
            "weaponBipod"
        };
        attachments[] = {"BDE_GP25_ButtPad", "BDE_GP25_ButtStock", "BDE_GP25_Sight"};
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

        chamberableFrom[] =
        {
            "Ammo_VOG25",
            "Ammo_VOG25_Smoke_Red",
            "Ammo_VOG25_Smoke_Green",
            "Ammo_VOG25_Smoke_White",
            "Ammo_VOG25_Smoke_Black",
            "Ammo_40mm_Explosive",
            "Ammo_40mm_ChemGas",
            "Ammo_40mm_Smoke_Red",
            "Ammo_40mm_Smoke_Green",
            "Ammo_40mm_Smoke_White",
            "Ammo_40mm_Smoke_Black",
            "Ammo_40mm_Smoke_AirStrike"
        };

        BDE_USL_AimZeroingDistances[] = {25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400};
        BDE_USL_AimMaxAngle = 21.396938;

        BDE_GP25_VirtualSightCameraPos[] = {-0.266879238, 0.090013905, -0.032630797};
        BDE_GP25_VirtualSightCameraDir[] = {-0.391879238, 0.090013905, -0.032630797};
        BDE_GP25_VirtualSightPivotStart[] = {-0.337900289, 0.079697565, -0.013871579};
        BDE_GP25_VirtualSightPivotEnd[] = {-0.337900289, 0.079697565, -0.033871578};
        BDE_GP25_VirtualSightCameraBackOffset = 0.05;

        BDE_USL_AttachedMuzzleStart[] = {-0.300, 0.025, 0};
        BDE_USL_AttachedMuzzleEnd[] = {-0.375, 0.025, 0};

        s_recoilControlStabilityX = -0.15;
        s_recoilControlStabilityY = -0.15;
        s_recoilControlMisalignmentX = -0.05;
        s_recoilControlMisalignmentY = -0.1;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_destruct.rvmat"}}
                    };
                };
            };
        };

        class InventorySlotsOffsets
        {
            class Shoulder
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };

            class Melee
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };

            class weaponBipod
            {
                position[] = {0.044, 0.21, 0};
                orientation[] = {0, 0, -90};
            };
        };
    };

    class BDE_Six12 : BDE_UnderSlungLauncher_Base
    {
        scope = 2;
        displayName = "SIX12 Shotgun";
        descriptionShort = "Modular six-shot 12 gauge shotgun receiver. Fit the short barrel for underslung use, or remove it and install the receiver in the standalone mount with the handle and long barrel.";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_Body.p3d";
        weight = 1200;
        absorbency = 0;
        repairableWithKits[] = {1};
        repairCosts[] = {25};
        itemSize[] = {4, 2};

        chamberSize = 1;
        chamberedRound = "";
        chamberableFrom[] =
        {
            "Ammo_12gaPellets",
            "Ammo_12gaSlug",
            "Ammo_12gaRubberSlug",
            "Ammo_12gaBeanbag"
        };

        magazines[] = {};
        magazineSwitchTime = 0.2;
        PPDOFProperties[] = {1, 0.5, 10, 140, 4, 10};
        WeaponLength = 0.39;
        ObstructionDistance = 0.22;
        WeaponLiftCheckVerticalOffset = -0.1;
        barrelArmor = 1.68;
        ejectType = 1;
        recoilModifier[] = {1, 1, 1};
        swayModifier[] = {2.5, 2.5, 0.9};
        inventorySlot[] = {"weaponBipod", "BDE_Six12"};
        attachments[] = {"BDE_Six12_Handle", "BDE_Six12_ShortBarrel", "BDE_Six12_Magazine", "BDE_Six12_ButtPad"};
        DisplayMagazine = 0;
        modes[] = {"SemiAuto"};
        hiddenSelections[] = {"Six12"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_Black_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"};
        simpleHiddenSelections[] = {};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 250;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_destruct.rvmat"}}
                    };
                };
            };
        };

        class NoiseShoot
        {
            strength = 100;
            type = "shot";
        };

        class SemiAuto : Mode_SemiAuto
        {
            soundSetShot[] = {};
            reloadTime = 0.35;
            recoil = "recoil_Saiga12";
            recoilProne = "recoil_Saiga12_prone";
            dispersion = 0.01;
            firespreadangle = 1.5;
        };

        class OpticsInfo : OpticsInfoShotgun {};

        BDE_USL_AttachedMuzzleStart[] = {-0.37742267, 0.00796797, 0};
        BDE_USL_AttachedMuzzleEnd[] = {-0.42742267, 0.00796797, 0};

        class InventorySlotsOffsets
        {
            class weaponBipod
            {
                position[] = {0.027, 0.197, 0};
                orientation[] = {0, 0, -90};
            };
            class BDE_Six12
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };
        };
    };

    class BDE_Six12_FDE : BDE_Six12
    {
        scope = 2;
        displayName = "SIX12 Shotgun (FDE)";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 250;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_Six12_StandAloneMount_Weapon : M79_Base
    {
        scope = 1;
        displayName = "SIX12 Standalone Mount";
        descriptionShort = "SIX12 standalone chassis in weapon form. This hidden variant is used while a SIX12 receiver with handle is installed.";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_StandAloneMount.p3d";
        weight = 1000;
        itemSize[] = {8, 3};
        chamberSize = 1;
        chamberedRound = "";
        chamberableFrom[] = {};
        magazines[] = {};
        magazineSwitchTime = 0.2;
        WeaponLength = 0.75;
        ObstructionDistance = 0.51;
        barrelArmor = 1.68;
        ejectType = 1;
        recoilModifier[] = {1, 1, 1};
        swayModifier[] = {2.5, 2.5, 0.9};
        DisplayMagazine = 0;
        attachments[] = {"BDE_Six12", "BDE_Six12_LongBarrel", "weaponOptics"};
        modes[] = {"Six12"};
        simpleHiddenSelections[] = {};
        hiddenSelections[] = {"Six12"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_Black_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"};

        class NoiseShoot
        {
            strength = 100;
            type = "shot";
        };

        class Six12 : Mode_SemiAuto
        {
            displayName = "Six12";
            soundSetShot[] = {};
            reloadTime = 0.35;
            recoil = "recoil_Saiga12";
            recoilProne = "recoil_Saiga12_prone";
            dispersion = 0.01;
            firespreadangle = 1.5;
        };

        class OpticsInfo : OpticsInfoShotgun
        {
            memoryPointCamera = "eye";
        };

        BDE_Six12_MuzzleStart[] = {-0.40423770, 0.04596797, 0};
        BDE_Six12_MuzzleEnd[] = {-0.45423770, 0.04596797, 0};
        BDE_USL_ProjectileSpawnClearance = 0.20;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\six12_02.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_Six12_StandAloneMount_Weapon_FDE : BDE_Six12_StandAloneMount_Weapon
    {
        scope = 1;
        displayName = "SIX12 Standalone Mount (FDE)";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\six12_02.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_FN40 : BDE_M203
    {
        scope = 2;
        displayName = "FN40 Grenade Launcher (Black)";
        descriptionShort = "Modular 40 mm launcher. Requires a barrel and handle; the standalone chassis supplies its own handle. Fits vanilla M4A1 with RIS handguard and SCAR-H.";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Body.p3d";
        attachments[] = {"BDE_FN40_Barrel", "BDE_FN40_Handle"};
        inventorySlot[] = {"weaponBipod", "BDE_FN40_Body"};

        BDE_USL_AimZeroingDistances[] = {0, 50, 100, 150, 200, 250, 300};
        BDE_USL_AttachedMuzzleStart[] = {-0.101600856, -0.011011833, -0.000000096};
        BDE_USL_AttachedMuzzleEnd[] = {-0.355372250, -0.011011833, -0.000000096};
        BDE_USL_CasingEjectOffset[] = {-0.101600856, -0.011011833, -0.000000096};

        class InventorySlotsOffsets
        {
            class weaponBipod
            {
                position[] = {0.037, 0.217, 0};
                orientation[] = {0, 0, -90};
            };
            class BDE_FN40_Body
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };
        };
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_FN40_FDE : BDE_FN40
    {
        displayName = "FN40 Grenade Launcher (FDE)";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_FN40_StandaloneMount_Weapon : M79_Base
    {
        hiddenSelections[] = {"camo", "camo_sight", "camo_grip"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black_co.paa", "BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_co.paa", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black.rvmat"};
        scope = 1;
        displayName = "FN40 Standalone Mount (Black)";
        descriptionShort = "Standalone chassis for the FN40 grenade launcher. Attach an FN40 body without a detachable handle to use it as a handheld weapon.";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_StandaloneMount.p3d";
        BDE_USL_StandaloneSightCameraBackOffset = 0.05;
        weight = 1500;
        itemSize[] = {6, 3};
        WeaponLength = 0.55;
        ObstructionDistance = 0.35;
        WeaponLiftCheckVerticalOffset = -0.1;
        chamberSize = 1;
        chamberedRound = "";
        chamberableFrom[] = {};
        magazines[] = {};
        DisplayMagazine = 0;
        attachments[] = {"BDE_FN40_Body", "BDE_FN40_Sight_Mount", "weaponOptics"};
        modes[] = {"Launcher"};

        BDE_USL_Compatible = 1;
        BDE_USL_SettingsGroup = "Vanilla";
        BDE_USL_ProjectileSpawnClearance = 0.0;
        BDE_USL_LauncherSlot = "BDE_FN40_Body";
        BDE_USL_Types[] = {"BDE_FN40"};
        BDE_USL_M203CustomReloadAnimation = 1;
        BDE_USL_BlockedSlots[] = {};
        BDE_M203BlockedAttachments[] = {};
        BDE_GP25BlockedAttachments[] = {};

        class Launcher : Mode_Single
        {
            displayName = "Launcher";
            reloadTime = 1.0;
            dispersion = 0.025;
        };
        class OpticsInfo : OpticsInfoRifle
        {
            memoryPointCamera = "eye";
            discreteDistance[] = {0};
            discreteDistanceInitIndex = 0;
            modelOptics = "-";
            distanceZoomMin = 0;
            distanceZoomMax = 0;
        };
        class InventorySlotsOffsets
        {
            class Shoulder
            {
                position[] = {-0.10, 0, 0.14};
                orientation[] = {0, 0, 0};
            };
            class Melee
            {
                position[] = {-0.10, 0, 0.14};
                orientation[] = {0, 0, 0};
            };
        };
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black_damage.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black_damage.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black_destruct.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_FN40_StandaloneMount_Weapon_FDE : BDE_FN40_StandaloneMount_Weapon
    {
        hiddenSelections[] = {"camo", "camo_sight", "camo_grip"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde_co.paa", "BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde_co.paa", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"};
        displayName = "FN40 Standalone Mount (FDE)";
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde_damage.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde_damage.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde_destruct.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_OTS14_Launcher : BDE_GP25
    {
        scope = 2;
        displayName = "Groza grenade launcher";
        descriptionShort = "Groza underbarrel grenade launcher. Select Launcher mode on the Groza to fire.";
        model = "BDE_UnderSlungLaunchers\Models\Groza_Launcher.p3d";
        inventorySlot[] =
        {
            "BDE_OTS14_Launcher"
        };
        attachments[] = {};
        hiddenSelections[] = {};
        hiddenSelectionsTextures[] = {};
        BDE_USL_AttachedMuzzleStart[] = {-0.34, 0.044, 0};
        BDE_USL_AttachedMuzzleEnd[] = {-0.447, 0.044, 0};
        BDE_USL_AimZeroingDistances[] = {0, 100, 150, 200, 250};
        BDE_GP25_VirtualSightCameraBackOffset = 0.08;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Groza\groza_attachments.rvmat", "BDE_UnderSlungLaunchers\Data\Groza\groza.rvmat"};
                    healthLevels[] =
                    {
                        {1, {"BDE_UnderSlungLaunchers\Data\Groza\groza_attachments.rvmat", "BDE_UnderSlungLaunchers\Data\Groza\groza.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Groza\groza_attachments.rvmat", "BDE_UnderSlungLaunchers\Data\Groza\groza.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Groza\groza_attachments_damage.rvmat", "BDE_UnderSlungLaunchers\Data\Groza\groza_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Groza\groza_attachments_damage.rvmat", "BDE_UnderSlungLaunchers\Data\Groza\groza_damage.rvmat"}},
                        {0, {"BDE_UnderSlungLaunchers\Data\Groza\groza_attachments_destruct.rvmat", "BDE_UnderSlungLaunchers\Data\Groza\groza_destruct.rvmat"}}
                    };
                };
            };
        };
    };
};

class CfgVehicles
{
    class Inventory_Base;

    class BDE_OTS14_LauncherSight : Inventory_Base
    {
        scope = 1;
        displayName = "Groza launcher sight";
        model = "\BDE_UnderSlungLaunchers\Models\Groza_Launcher_Sight.p3d";
        inventorySlot[] =
        {
            "BDE_OTS14_LauncherSight"
        };
        autocenter = 0;
        weight = 0;
        itemSize[] = {1, 1};
        class AnimationSources
        {
            class groza_sight_fold
            {
                source = "user";
                animPeriod = 0.25;
                initPhase = 1;
            };
        };
    };

    class BDE_Six12_CylinderVisual : Inventory_Base
    {
        scope = 1;
        displayName = "SIX12 Magazine";
        descriptionShort = "Permanent SIX12 cylinder. Ammunition is stored internally by the receiver; this component is visual only and cannot be removed.";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_Magazine.p3d";
        inventorySlot[] = {"BDE_Six12_Magazine"};
        weight = 0;
        itemSize[] = {1, 1};
        hiddenSelections[] = {"Six12"};
        simpleHiddenSelections[] = {"bullet1", "bullet2", "bullet3", "bullet4", "bullet5", "bullet6"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_Black_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"};

        class AnimationSources
        {
            class six12_cylinder_rotate
            {
                source = "user";
                animPeriod = 0.25;
                initPhase = 0;
            };
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\six12.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_Six12_CylinderVisual_FDE : BDE_Six12_CylinderVisual
    {
        scope = 1;
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\six12.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_FDE_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_M203_StandAloneMount : Inventory_Base
    {
        scope = 2;
        displayName = "M203 Standalone Mount";
        descriptionShort = "Standalone chassis for the M203 grenade launcher. Attach an M203 launcher body to convert it into a handheld launcher.";
        model = "\BDE_UnderSlungLaunchers\Models\M203_StandAloneMount.p3d";
        rotationFlags = 17;
        weight = 1500;
        itemSize[] = {6, 3};

        attachments[] = {"BDE_M203_Body", "weaponButtstockM4", "weaponOptics"};

        class InventorySlotsOffsets
        {
            class Shoulder
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };

            class Melee
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };
        };

        s_recoilControlStabilityX = 0.2;
        s_recoilControlStabilityY = 0.2;
        s_recoilControlMisalignmentX = 0.55;
        s_recoilControlMisalignmentY = 0.45;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\m203_frame.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame_damage.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame_damage.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_frame_destruct.rvmat", "BDE_UnderSlungLaunchers\Data\M203\m203_stock_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_GP25_ButtPad : Inventory_Base
    {
        scope = 2;
        displayName = "GP-25 Buttpad";
        descriptionShort = "Rubber buttpad used with a compatible underslung grenade launcher mounted beneath an AK with a plastic buttstock.";
        model = "\BDE_UnderSlungLaunchers\Models\GP25_ButtPad.p3d";
        inventorySlot[] = {"BDE_GP25_ButtPad", "BDE_M203_ButtPad", "BDE_Six12_ButtPad"};
        rotationFlags = 17;
        weight = 100;
        itemSize[] = {1, 2};

        class InventorySlotsOffsets
        {
            class BDE_GP25_ButtPad
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };

            class BDE_M203_ButtPad
            {
                position[] = {0, 0.017, 0};
                orientation[] = {0, 0, 0};
            };

            class BDE_Six12_ButtPad
            {
                position[] = {0, -0.017, 0};
                orientation[] = {0, 0, 0};
            };
        };

        s_recoilControlStabilityX = 0;
        s_recoilControlStabilityY = 0;
        s_recoilControlMisalignmentX = 0;
        s_recoilControlMisalignmentY = 0;
        s_recoilControlKick = 0.4;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"dz\weapons\launchers\gp25\data\gp25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"dz\weapons\launchers\gp25\data\gp25.rvmat"}},
                        {0.7, {"dz\weapons\launchers\gp25\data\gp25.rvmat"}},
                        {0.5, {"dz\weapons\launchers\gp25\data\gp25_damage.rvmat"}},
                        {0.3, {"dz\weapons\launchers\gp25\data\gp25_damage.rvmat"}},
                        {0.0, {"dz\weapons\launchers\gp25\data\gp25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_USL_M203_ButtPad_VanillaAK : BDE_GP25_ButtPad
    {
        scope = 1;
        model = "\BDE_UnderSlungLaunchers\Models\M203_ButtPad_VanillaAK.p3d";

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"dz\weapons\launchers\gp25\data\gp25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"dz\weapons\launchers\gp25\data\gp25.rvmat"}},
                        {0.7, {"dz\weapons\launchers\gp25\data\gp25.rvmat"}},
                        {0.5, {"dz\weapons\launchers\gp25\data\gp25_damage.rvmat"}},
                        {0.3, {"dz\weapons\launchers\gp25\data\gp25_damage.rvmat"}},
                        {0.0, {"dz\weapons\launchers\gp25\data\gp25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_USL_Six12_ButtPad_VanillaAK : BDE_GP25_ButtPad
    {
        scope = 1;
        model = "\BDE_UnderSlungLaunchers\Models\Six12_ButtPad_VanillaAK.p3d";

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"dz\weapons\launchers\gp25\data\gp25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"dz\weapons\launchers\gp25\data\gp25.rvmat"}},
                        {0.7, {"dz\weapons\launchers\gp25\data\gp25.rvmat"}},
                        {0.5, {"dz\weapons\launchers\gp25\data\gp25_damage.rvmat"}},
                        {0.3, {"dz\weapons\launchers\gp25\data\gp25_damage.rvmat"}},
                        {0.0, {"dz\weapons\launchers\gp25\data\gp25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_GP25_ButtStock : Inventory_Base
    {
        scope = 2;
        displayName = "GP-25 Retractable Buttstock";
        descriptionShort = "Retractable buttstock for using the GP-25 as a standalone launcher.";
        model = "\BDE_UnderSlungLaunchers\Models\GP25_ButtStock.p3d";
        inventorySlot[] = {"BDE_GP25_ButtStock"};
        rotationFlags = 17;
        weight = 350;
        itemSize[] = {4, 2};

        class AnimationSources
        {
            class gp25_stock_extend
            {
                source = "user";
                animPeriod = 0.15;
                initPhase = 0.0;
            };
        };

        s_recoilControlStabilityX = 0.4;
        s_recoilControlStabilityY = 0.4;
        s_recoilControlMisalignmentX = 0.05;
        s_recoilControlMisalignmentY = 0.15;
        s_recoilControlKick = 0.6;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 150;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_GP25_Sight : Inventory_Base
    {
        scope = 1;
        displayName = "GP-25 Side Sight";
        descriptionShort = "Integral folding range sight for the GP-25 grenade launcher.";
        model = "\BDE_UnderSlungLaunchers\Models\GP25_Sight.p3d";
        inventorySlot[] = {"BDE_GP25_Sight"};
        rotationFlags = 17;
        weight = 120;
        itemSize[] = {2, 1};

        class AnimationSources
        {
            class gp25_sight_ads
            {
                source = "user";
                animPeriod = 0.001;
                initPhase = 0.0;
            };

            class gp25_sight_zero
            {
                source = "user";
                animPeriod = 0.08;
                initPhase = 0.0;
            };
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class Ammo_40mm_Empty : Inventory_Base
    {
        scope = 2;
        displayName = "Spent 40mm Grenade Casing";
        descriptionShort = "An empty 40mm grenade casing.";
        model = "\DZ\weapons\projectiles\40mm_grenade_shell.p3d";
        rotationFlags = 17;
        weight = 80;
        itemSize[] = {1, 1};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"dz\weapons\ammunition\data\40mm_grenade.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"dz\weapons\ammunition\data\40mm_grenade.rvmat"}},
                        {0.7, {"dz\weapons\ammunition\data\40mm_grenade.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\VanillaDamage\40mm_grenade_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\VanillaDamage\40mm_grenade_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\VanillaDamage\40mm_grenade_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_M203_Barrel : Inventory_Base
    {
        scope = 2;
        displayName = "M203 Barrel";
        descriptionShort = "Removable barrel assembly for the M203 grenade launcher.";
        repairableWithKits[] = {1};
        repairCosts[] = {25};
        model = "\BDE_UnderSlungLaunchers\Models\M203_Barrel.p3d";
        inventorySlot[] = {"BDE_M203_Barrel"};
        rotationFlags = 17;
        weight = 750;
        itemSize[] = {4, 1};

        class AnimationSources
        {
            class m203_tube_open
            {
                source = "user";
                animPeriod = 0.2;
                initPhase = 0.0;
            };
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\M203.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\M203.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\M203.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\M203_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\M203_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\M203_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_M203_Short_Barrel : BDE_M203_Barrel
    {
        scope = 2;
        displayName = "M203 Short Barrel";
        descriptionShort = "Removable barrel assembly for the M203 grenade launcher. It appears to have been shortened with a hacksaw.";
        repairableWithKits[] = {1};
        repairCosts[] = {25};
        model = "\BDE_UnderSlungLaunchers\Models\M203_Short_Barrel.p3d";
        weight = 650;
        itemSize[] = {3, 1};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\M203.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\M203.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\M203.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\M203_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\M203_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\M203_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_M203_ButtStock : Inventory_Base
    {
        scope = 2;
        displayName = "M203 Buttstock";
        descriptionShort = "Dedicated buttstock for the M203 standalone mount.";
        model = "\BDE_UnderSlungLaunchers\Models\M203_ButtStock.p3d";
        inventorySlot[] = {"weaponButtstockM4"};
        rotationFlags = 17;
        weight = 500;
        itemSize[] = {2, 1};

        s_recoilControlStabilityX = 0.4;
        s_recoilControlStabilityY = 0.4;
        s_recoilControlMisalignmentX = 0.05;
        s_recoilControlMisalignmentY = 0.15;
        s_recoilControlKick = 0.6;

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 150;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\m203_stock.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\m203_stock_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\m203_stock_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_stock_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_GP25_Sight_Unfolded : BDE_GP25_Sight
    {
        scope = 1;
        model = "\BDE_UnderSlungLaunchers\Models\GP25_Sight_Unfolded.p3d";

        class AnimationSources
        {
            class gp25_sight_ads
            {
                source = "user";
                animPeriod = 0.001;
                initPhase = 1.0;
            };

            class gp25_sight_zero
            {
                source = "user";
                animPeriod = 0.08;
                initPhase = 0.0;
            };
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\GP25\gp25.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\GP25\gp25_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_M203_FrontSight : Inventory_Base
    {
        scope = 1;
        displayName = "M203 Front Sight";
        descriptionShort = "Front sight for the M203. Automatically fitted when an M203 rail sight adapter is installed.";
        model = "\BDE_UnderSlungLaunchers\Models\M203_FrontSight.p3d";
        inventorySlot[] = {"BDE_M203_FrontSight"};
        rotationFlags = 17;
        weight = 100;
        itemSize[] = {1, 1};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\M203_Sights.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\M203_Sights.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\M203_Sights.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\M203_Sights_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\M203_Sights_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\M203_Sights_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_M203_Rail_Adapter : Inventory_Base
    {
        scope = 2;
        displayName = "M203 Rail Sight Adapter";
        descriptionShort = "Rail adapter for fitting the folding M203 ladder sight to a rifle-mounted M203. Includes an integral automatic front sight.";
        model = "\BDE_UnderSlungLaunchers\Models\M203_Rail_Adapter.p3d";
        inventorySlot[] = {"BDE_M203_RailAdapter"};
        attachments[] = {"BDE_M203_RearSight"};
        rotationFlags = 17;
        weight = 180;
        itemSize[] = {2, 1};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\M203_Rail_Adapter.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\M203_Rail_Adapter.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\M203_Rail_Adapter.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\M203_Rail_Adapter_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\M203_Rail_Adapter_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\M203_Rail_Adapter_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_M203_RearSight : Inventory_Base
    {
        scope = 2;
        attachments[] = {"BDE_M203_FrontSight"};
        displayName = "M203 Rear Sight";
        descriptionShort = "Folding ladder sight with integral front post. Fits M203 and FN40 standalone mounts or the M203 rail adapter.";
        model = "\BDE_UnderSlungLaunchers\Models\M203_RearSight.p3d";
        inventorySlot[] = {"weaponOptics", "BDE_M203_RearSight"};
        rotationFlags = 17;
        weight = 250;
        itemSize[] = {1, 1};
        BDE_USL_SightZeroingDistances[] = {0, 50, 100, 150, 200, 250};

        class AnimationSources
        {
            class m203_sight_fold
            {
                source = "user";
                animPeriod = 0.2;
                initPhase = 1.0;
            };
        };

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\M203\m203_sights.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_sights.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\M203\m203_sights.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\M203\m203_sights_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\M203\m203_sights_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\M203\m203_sights_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_Six12_Part_Base : Inventory_Base
    {
        scope = 0;
        rotationFlags = 17;
        hiddenSelections[] = {"Six12"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_Black_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"};
    };

    class BDE_Six12_Handle : BDE_Six12_Part_Base
    {
        scope = 2;
        displayName = "SIX12 Handle";
        descriptionShort = "SIX12 handle/trigger module. Modular component.";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_Handle.p3d";
        inventorySlot[] = {"BDE_Six12_Handle"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_Black_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"};
        weight = 250;
        itemSize[] = {2, 2};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_Six12_Handle_FDE : BDE_Six12_Handle
    {
        displayName = "SIX12 Handle (FDE)";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_Six12_LongBarrel : BDE_Six12_Part_Base
    {
        scope = 2;
        displayName = "SIX12 Long Barrel";
        descriptionShort = "Long SIX12 barrel module. Modular component.";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_LongBarrel.p3d";
        inventorySlot[] = {"BDE_Six12_LongBarrel"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_Black_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"};
        weight = 800;
        itemSize[] = {4, 1};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_Six12_ShortBarrel : BDE_Six12_Part_Base
    {
        scope = 2;
        displayName = "SIX12 Short Barrel";
        descriptionShort = "Short SIX12 barrel module. Modular component.";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_ShortBarrel.p3d";
        inventorySlot[] = {"BDE_Six12_ShortBarrel"};
        weight = 500;
        itemSize[] = {2, 1};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_Six12_StandAloneMount : Inventory_Base
    {
        scope = 2;
        displayName = "SIX12 Standalone Mount";
        descriptionShort = "Standalone chassis for the SIX12 shotgun. Install a SIX12 receiver with handle to convert it into a handheld weapon.";
        model = "\BDE_UnderSlungLaunchers\Models\Six12_StandAloneMount.p3d";
        rotationFlags = 17;
        weight = 1000;
        itemSize[] = {6, 2};
        attachments[] = {"BDE_Six12", "BDE_Six12_LongBarrel", "weaponOptics"};
        hiddenSelections[] = {"Six12"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_Black_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\six12_02.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_Six12_StandAloneMount_FDE : BDE_Six12_StandAloneMount
    {
        displayName = "SIX12 Standalone Mount (FDE)";
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_CO.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"};

        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\Six12\six12_02.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\Six12\Six12_02_FDE_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_FN40_StandaloneMount : Inventory_Base
    {
        hiddenSelections[] = {"camo", "camo_sight", "camo_grip"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black_co.paa", "BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_co.paa", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black.rvmat"};
        scope = 2;
        displayName = "FN40 Standalone Mount (Black)";
        descriptionShort = "Standalone chassis for the FN40 grenade launcher. Attach an FN40 body without a detachable handle to convert it into a handheld launcher.";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_StandaloneMount.p3d";
        rotationFlags = 17;
        weight = 1500;
        itemSize[] = {6, 3};
        attachments[] = {"BDE_FN40_Body", "BDE_FN40_Sight_Mount", "weaponOptics"};
        class InventorySlotsOffsets
        {
            class Shoulder
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };
            class Melee
            {
                position[] = {0, 0, 0};
                orientation[] = {0, 0, 0};
            };
        };
        s_recoilControlStabilityX = 0.2;
        s_recoilControlStabilityY = 0.2;
        s_recoilControlMisalignmentX = 0.55;
        s_recoilControlMisalignmentY = 0.45;
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black_damage.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black_damage.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_black_destruct.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_black_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_FN40_StandaloneMount_FDE : BDE_FN40_StandaloneMount
    {
        hiddenSelections[] = {"camo", "camo_sight", "camo_grip"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde_co.paa", "BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde_co.paa", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"};
        displayName = "FN40 Standalone Mount (FDE)";
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde_damage.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde_damage.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_holder_fde_destruct.rvmat", "BDE_UnderSlungLaunchers\Data\FN40\pistol_grip_m16a2_fde_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_FN40_Barrel : BDE_M203_Barrel
    {
        scope = 2;
        displayName = "FN40 Barrel (Black)";
        repairableWithKits[] = {1};
        repairCosts[] = {25};
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Barrel.p3d";
        inventorySlot[] = {"BDE_FN40_Barrel"};
        weight = 500;
        itemSize[] = {3, 1};
        rotationFlags = 17;
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_black_destruct.rvmat"}}
                    };
                };
            };
        };
        class AnimationSources
        {
            class m203_tube_open
            {
                source = "user";
                initPhase = 0;
                animPeriod = 0.25;
            };
        };
    };
    class BDE_FN40_Barrel_FDE : BDE_FN40_Barrel
    {
        displayName = "FN40 Barrel (FDE)";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_launcher_fde_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_FN40_Handle : Inventory_Base
    {
        scope = 2;
        displayName = "FN40 Handle (Black)";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Handle.p3d";
        inventorySlot[] = {"BDE_FN40_Handle"};
        weight = 250;
        itemSize[] = {2, 1};
        rotationFlags = 17;
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_black.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_black.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_black.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_black_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_black_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_black_destruct.rvmat"}}
                    };
                };
            };
        };
    };
    class BDE_FN40_Handle_FDE : BDE_FN40_Handle
    {
        displayName = "FN40 Handle (FDE)";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_trigger_mod_fde_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_FN40_Sight_Mount : Inventory_Base
    {
        scope = 2;
        displayName = "FN40 Sight Mount";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Sight_Mount.p3d";
        inventorySlot[] = {"BDE_FN40_Sight_Mount", "BDE_SideRail"};
        attachments[] = {"BDE_FN40_Sight"};
        weight = 150;
        itemSize[] = {2, 1};
        rotationFlags = 17;
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black.rvmat"};
        class InventorySlotsOffsets
        {
            class BDE_FN40_Sight_Mount
            {
                position[] = {0, 0, -0.037};
                orientation[] = {0, 0, 0};
            };
            class BDE_SideRail
            {
                position[] = {0, 0, -0.037};
                orientation[] = {0, 0, 0};
            };
        };
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"bde_underslunglaunchers\data\fn40\fn40gl_sight_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_FN40_Sight : Inventory_Base
    {
        scope = 1;
        displayName = "FN40 Sight (Black)";
        model = "\BDE_UnderSlungLaunchers\Models\FN40_Sight.p3d";
        inventorySlot[] = {"BDE_FN40_Sight"};
        weight = 150;
        itemSize[] = {2, 1};
        BDE_USL_SightZeroingDistances[] = {0, 50, 100, 150, 200, 250, 300};
        rotationFlags = 17;
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_black_destruct.rvmat"}}
                    };
                };
            };
        };
        class AnimationSources
        {
            class fn40_rearsight_fold
            {
                source = "user";
                initPhase = 1;
                animPeriod = 0.20;
            };
            class fn40_frontsight_fold
            {
                source = "user";
                initPhase = 1;
                animPeriod = 0.20;
            };
        };
    };
    class BDE_FN40_Sight_FDE : BDE_FN40_Sight
    {
        displayName = "FN40 Sight (FDE)";
        hiddenSelections[] = {"camo"};
        hiddenSelectionsTextures[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde_co.paa"};
        hiddenSelectionsMaterials[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde.rvmat"};
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 200;
                    RefTexsMats[] = {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde.rvmat"};
                    healthLevels[] =
                    {
                        {1.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde.rvmat"}},
                        {0.7, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde.rvmat"}},
                        {0.5, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde_damage.rvmat"}},
                        {0.3, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde_damage.rvmat"}},
                        {0.0, {"BDE_UnderSlungLaunchers\Data\FN40\fn40gl_sight_fde_destruct.rvmat"}}
                    };
                };
            };
        };
    };

    class BDE_Debug_GrozaSight_Unfolded : Inventory_Base
    {
        scope = 2;
        displayName = "DEBUG Sight B - Groza unfolded";
        model = "\BDE_UnderSlungLaunchers\Models\Groza_Launcher_Sight.p3d";
        weight = 40;
        itemSize[] = {2, 2};

        class AnimationSources
        {
            class groza_sight_fold
            {
                source = "user";
                animPeriod = 0.25;
                initPhase = 0;
            };
        };
    };

    class BDE_Debug_GrozaSight_Static : Inventory_Base
    {
        scope = 2;
        displayName = "DEBUG Sight C - Groza static control";
        model = "\BDE_UnderSlungLaunchers\Models\Groza_Launcher_Sight_Diagnostic.p3d";
        weight = 40;
        itemSize[] = {2, 2};
    };
};

class CfgSoundShaders
{
    class base_Closure_SoundShader;
    class new_closeShotRifle_SoundShader;
    class new_midShotRifle_SoundShader;
    class new_distShotRifle_SoundShader;
    class new_Interior_CloseShotRifle_SoundShader;
    class new_Interior_MidShotRifle_SoundShader;
    class tailDistantRifle_SoundShader;
    class tailTreesRifle_SoundShader;
    class tailForestRifle_SoundShader;
    class tailMeadowsRifle_SoundShader;
    class tailHousesRifle_SoundShader;
    class new_Interior_Close_Tail_Rifle_SoundShader;
    class new_Interior_Mid_Tail_Rifle_SoundShader;
    class base_Slapback_SoundShader;
    class tail_2D_Forest_SoundShader;
    class tail_2D_Houses_SoundShader;
    class tail_2D_Meadows_SoundShader;
    class tail_2D_Trees_SoundShader;

    class BDE_Six12_Mech_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Mech_01", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Mech_02", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Mech_03", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Mech_04", 1}
        };
        volume = 1;
        range = 3000;
        rangeCurve = "closureShotAttenuationCurve";
    };
    class BDE_Six12_CloseShot_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Close_01", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Close_02", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Close_03", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Close_04", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 2000;
        rangeCurve = "closeShotRifleCurve";
    };
    class BDE_Six12_MidShot_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Mid_01", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Mid_02", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Mid_03", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Mid_04", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 2000;
        rangeCurve = "midShotRifleCurve";
    };
    class BDE_Six12_DistShot_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Shot_Dist_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Shot_Dist_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Shot_Dist_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Shot_Dist_04", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 2000;
        rangeCurve = "distShotAttenuationCurve";
    };
    class BDE_Six12_CloseShot_Interior_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Int_Close_01", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Int_Close_02", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Int_Close_03", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Int_Close_04", 1}
        };
        volume = "interior";
        range = 3000;
        rangeCurve = "closeShotInteriorRifleCurve";
    };
    class BDE_Six12_MidShot_Interior_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Int_Mid_01", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Int_Mid_02", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Int_Mid_03", 1},
            {"DZ\sounds\weapons\shotguns\Saiga12\Wpn_Saiga_Shot_Int_Mid_04", 1}
        };
        volume = "interior";
        rangeCurve = "Interior_mid_Shot_and_Tails_Curve";
        range = 1600;
    };
    class BDE_Six12_TailDistant_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_distant_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_distant_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_distant_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_distant_04", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 2000;
        limitation = 1;
        rangeCurve = "tailDistantShotRifleCurve";
    };
    class BDE_Six12_TailTrees_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_04", 1}
        };
        volume = "(trees/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 2000;
        limitation = 1;
        rangeCurve = "tailShotRifleCurve";
    };
    class BDE_Six12_TailForest_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_04", 1}
        };
        volume = "(forest/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 2000;
        limitation = 1;
        rangeCurve = "tailShotRifleCurve";
    };
    class BDE_Six12_TailMeadows_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_04", 1}
        };
        volume = "((meadows + sea)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 2000;
        limitation = 1;
        rangeCurve = "tailShotRifleCurve";
    };
    class BDE_Six12_TailHouses_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_04", 1}
        };
        volume = "(houses/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 2000;
        limitation = 1;
        rangeCurve = "tailShotRifleCurve";
    };
    class BDE_Six12_TailInterior_Close_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Close_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Close_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Close_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Close_04", 1}
        };
        volume = "interior";
        range = 3000;
        rangeCurve = "closeShotInteriorRifleCurve";
    };
    class BDE_Six12_TailInterior_Mid_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Mid_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Mid_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Mid_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Mid_04", 1}
        };
        volume = "interior";
        rangeCurve = "Interior_mid_Shot_and_Tails_Curve";
        range = 1600;
    };
    class BDE_Six12_Slapback_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Slapback_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Slapback_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Slapback_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Slapback_04", 1}
        };
        volume = "(meadows + houses/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 200;
        limitation = 1;
        rangeCurve = "SlapbackAttenuationCurve";
    };
    class BDE_Six12_TailForest_2D_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_2D_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_2D_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_2D_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_2D_04", 1}
        };
        volume = "(forest/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 130;
        limitation = 1;
        rangeCurve = "Tail2DAttenuationCurve";
    };
    class BDE_Six12_TailHouses_2D_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_2D_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_2D_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_2D_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_2D_04", 1}
        };
        volume = "(houses/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 130;
        limitation = 1;
        rangeCurve = "Tail2DAttenuationCurve";
    };
    class BDE_Six12_TailMeadows_2D_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_2D_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_2D_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_2D_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_2D_04", 1}
        };
        volume = "((meadows + sea)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 130;
        limitation = 1;
        rangeCurve = "Tail2DAttenuationCurve";
    };
    class BDE_Six12_TailTrees_2D_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_2D_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_2D_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_2D_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_2D_04", 1}
        };
        volume = "(trees/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 130;
        limitation = 1;
        rangeCurve = "Tail2DAttenuationCurve";
    };
    class BDE_USL_Attached_Mech_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_mech_01", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_mech_02", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_mech_03", 1}
        };
        volume = 1;
        range = 70;
        rangeCurve = "closureShotAttenuationCurve";
    };
    class BDE_USL_Attached_Close_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Close_01", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Close_02", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Close_03", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 3000;
        rangeCurve = "closeShotRifleCurve";
    };
    class BDE_USL_Attached_Mid_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Mid_01", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Mid_02", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Mid_03", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 3000;
        rangeCurve = "midShotRifleCurve";
    };
    class BDE_USL_Attached_Dist_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Dist_01", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Dist_02", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Dist_03", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 500;
        rangeCurve = "distShotAttenuationCurve";
    };
    class BDE_USL_Attached_IntClose_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Int_Close_01", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Int_Close_02", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Int_Close_03", 1}
        };
        volume = "interior";
        range = 3000;
        rangeCurve = "closeShotInteriorRifleCurve";
    };
    class BDE_USL_Attached_IntMid_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Int_Mid_01", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Int_Mid_02", 1},
            {"DZ\sounds\weapons\launchers\M79\Wpn_M79_Shot_Int_Mid_03", 1}
        };
        volume = "interior";
        range = 400;
        rangeCurve = "Interior_mid_Shot_and_Tails_Curve";
    };
    class BDE_USL_Attached_TailDistant_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_distant_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_distant_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_distant_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_distant_04", 1}
        };
        volume = "((meadows + sea + forest + houses + trees)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 500;
        limitation = 1;
        rangeCurve = "distShotAttenuationCurve";
    };
    class BDE_USL_Attached_TailForest_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_04", 1}
        };
        volume = "(forest/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 3000;
        limitation = 1;
        rangeCurve = "tailShotRifleCurve";
    };
    class BDE_USL_Attached_TailHouses_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_04", 1}
        };
        volume = "(houses/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 3000;
        limitation = 1;
        rangeCurve = "tailShotRifleCurve";
    };
    class BDE_USL_Attached_TailMeadows_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_04", 1}
        };
        volume = "((meadows + sea)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 3000;
        limitation = 1;
        rangeCurve = "tailShotRifleCurve";
    };
    class BDE_USL_Attached_TailTrees_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_trees_04", 1}
        };
        volume = "(trees/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 3000;
        limitation = 1;
        rangeCurve = "tailShotRifleCurve";
    };
    class BDE_USL_Attached_TailIntClose_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Close_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Close_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Close_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Close_04", 1}
        };
        volume = "interior";
        range = 3000;
        rangeCurve = "closeShotInteriorRifleCurve";
    };
    class BDE_USL_Attached_TailIntMid_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Mid_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Mid_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Mid_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_interior_Mid_04", 1}
        };
        volume = "interior";
        range = 400;
        rangeCurve = "Interior_mid_Shot_and_Tails_Curve";
    };
    class BDE_USL_Attached_Slapback_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Slapback_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Slapback_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Slapback_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Slapback_04", 1}
        };
        volume = "(meadows + houses/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 200;
        limitation = 1;
        rangeCurve = "SlapbackAttenuationCurve";
    };
    class BDE_USL_Attached_Tail2DForest_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_2D_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_2D_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_2D_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_forest_2D_04", 1}
        };
        volume = "(forest/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 130;
        rangeCurve = "Tail2DAttenuationCurve";
    };
    class BDE_USL_Attached_Tail2DHouses_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_2D_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_2D_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_2D_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_houses_2D_04", 1}
        };
        volume = "(houses/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 130;
        rangeCurve = "Tail2DAttenuationCurve";
    };
    class BDE_USL_Attached_Tail2DMeadows_SoundShader
    {
        samples[] =
        {
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_2D_01", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_2D_02", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_2D_03", 1},
            {"DZ\sounds\weapons\Tails\SG_Tails\Wpn_SG_Tail_meadows_2D_04", 1}
        };
        volume = "((meadows + sea)/(forest + houses + meadows + sea + trees)) * (1-interior)";
        range = 130;
        rangeCurve = "Tail2DAttenuationCurve";
    };
    class BDE_M203_Reload_ChargeOpen_SoundShader
    {
        samples[] = {{"DZ\sounds\weapons\launchers\M79\handling\charge_open", 1}};
        volume = 1.5848932;
        range = 30;
        rangeCurve[] = {{0, 1}, {2, 1}, {10, 0.4}, {20, 0.1}, {30, 0}};
    };

    class BDE_M203_Reload_GrenadeOut_SoundShader
    {
        samples[] = {{"DZ\sounds\weapons\launchers\M79\handling\grenate_out", 1}};
        volume = 1.1220185;
        range = 30;
        rangeCurve[] = {{0, 1}, {2, 1}, {10, 0.4}, {20, 0.1}, {30, 0}};
    };

    class BDE_M203_Reload_GrenadeIn_SoundShader
    {
        samples[] = {{"DZ\sounds\weapons\launchers\M79\handling\grenate_in", 1}};
        volume = 1.1220185;
        range = 30;
        rangeCurve[] = {{0, 1}, {2, 1}, {10, 0.4}, {20, 0.1}, {30, 0}};
    };

    class BDE_M203_Reload_ChargeClose_SoundShader
    {
        samples[] = {{"DZ\sounds\weapons\launchers\M79\handling\charge_close", 1}};
        volume = 1.7782794;
        range = 30;
        rangeCurve[] = {{0, 1}, {2, 1}, {10, 0.4}, {20, 0.1}, {30, 0}};
    };
};

class CfgSoundSets
{
    class BDE_USL_AttachedShot_Exterior_SoundSet
    {
        soundShaders[] = {"BDE_USL_Attached_Mech_SoundShader", "BDE_USL_Attached_Close_SoundShader", "BDE_USL_Attached_Mid_SoundShader", "BDE_USL_Attached_Dist_SoundShader"};
        volumeFactor = 0.8;
        volumeCurve = "RifleShotCurve";
        sound3DProcessingType = "WeaponMediumShot3DProcessingType";
        distanceFilter = "weaponShotDistanceFreqAttenuationFilter";
        occlusionFactor = 0.6;
        obstructionFactor = 0.6;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 4;
    };
    class BDE_USL_AttachedShot_Interior_SoundSet
    {
        soundShaders[] = {"BDE_USL_Attached_IntClose_SoundShader", "BDE_USL_Attached_IntMid_SoundShader"};
        volumeFactor = 0.8;
        volumeCurve = "RifleShot_Interior_Curve";
        sound3DProcessingType = "WeaponMediumShot3DProcessingType";
        distanceFilter = "weaponShotDistanceFreq_INT_AttenuationFilter";
        occlusionFactor = 0.6;
        obstructionFactor = 0.6;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 4;
    };
    class BDE_USL_AttachedTail_Exterior_SoundSet
    {
        soundShaders[] = {"BDE_USL_Attached_TailDistant_SoundShader", "BDE_USL_Attached_TailForest_SoundShader", "BDE_USL_Attached_TailMeadows_SoundShader", "BDE_USL_Attached_TailHouses_SoundShader", "BDE_USL_Attached_TailTrees_SoundShader"};
        volumeFactor = 0.3;
        volumeCurve = "RifleShotCurve";
        frequencyRandomizer = 1;
        frequencyFactor = 1.4;
        startDelay = 0.1;
        sound3DProcessingType = "WeaponMediumShotTail3DProcessingType";
        distanceFilter = "weaponShotTailDistanceFreqAttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 3;
        soundObjectsLimit = 4;
    };
    class BDE_USL_AttachedTail_Interior_SoundSet
    {
        soundShaders[] = {"BDE_USL_Attached_TailIntClose_SoundShader", "BDE_USL_Attached_TailIntMid_SoundShader"};
        volumeFactor = 0.3;
        volumeCurve = "RifleShot_Interior_Curve";
        frequencyRandomizer = 1;
        frequencyFactor = 1.3;
        startDelay = 0.05;
        sound3DProcessingType = "WeaponInteriorShotTail3DProcessingType";
        distanceFilter = "weaponShotDistanceFreq_INT_AttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 4;
    };
    class BDE_USL_AttachedSlapback_SoundSet
    {
        soundShaders[] = {"BDE_USL_Attached_Slapback_SoundShader"};
        volumeFactor = 0.5;
        volumeCurve = "SlapbackAttenuationCurve";
        frequencyRandomizer = 1;
        frequencyFactor = 1.2;
        startDelay = 0.1;
        sound3DProcessingType = "Slapback_3DProcessingType";
        distanceFilter = "Slapback_DistanceFreqAttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundObjectsLimit = 2;
    };
    class BDE_USL_AttachedTail2D_SoundSet
    {
        soundShaders[] = {"BDE_USL_Attached_Tail2DForest_SoundShader", "BDE_USL_Attached_Tail2DHouses_SoundShader", "BDE_USL_Attached_Tail2DMeadows_SoundShader"};
        volumeFactor = 0.3;
        volumeCurve = "Tail2DAttenuationCurve";
        frequencyRandomizer = 1;
        frequencyFactor = 1.4;
        startDelay = 0.1;
        sound3DProcessingType = "Tail_2D_3DProcessingType";
        distanceFilter = "Slapback_DistanceFreqAttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 1;
    };

    class BDE_Six12_Shot_SoundSet
    {
        soundShaders[] = {"BDE_Six12_Mech_SoundShader", "BDE_Six12_CloseShot_SoundShader", "BDE_Six12_MidShot_SoundShader", "BDE_Six12_DistShot_SoundShader"};
        volumeFactor = 0.8;
        volumeCurve = "RifleShotCurve";
        sound3DProcessingType = "WeaponMediumShot3DProcessingType";
        distanceFilter = "weaponShotDistanceFreqAttenuationFilter";
        occlusionFactor = 0.6;
        obstructionFactor = 0.6;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 1;
    };

    class BDE_Six12_Shot_Interior_SoundSet
    {
        soundShaders[] = {"BDE_Six12_CloseShot_Interior_SoundShader", "BDE_Six12_MidShot_Interior_SoundShader"};
        volumeFactor = 0.8;
        volumeCurve = "RifleShot_Interior_Curve";
        sound3DProcessingType = "WeaponMediumShot3DProcessingType";
        distanceFilter = "weaponShotDistanceFreq_INT_AttenuationFilter";
        occlusionFactor = 0.6;
        obstructionFactor = 0.6;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 2;
    };

    class BDE_Six12_Tail_SoundSet
    {
        soundShaders[] = {"BDE_Six12_TailDistant_SoundShader", "BDE_Six12_TailTrees_SoundShader", "BDE_Six12_TailForest_SoundShader", "BDE_Six12_TailMeadows_SoundShader", "BDE_Six12_TailHouses_SoundShader"};
        volumeFactor = 0.8;
        volumeCurve = "RifleShotCurve";
        frequencyRandomizer = 1;
        sound3DProcessingType = "WeaponMediumShotTail3DProcessingType";
        distanceFilter = "weaponShotTailDistanceFreqAttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundObjectsLimit = 2;
    };

    class BDE_Six12_InteriorTail_SoundSet
    {
        soundShaders[] = {"BDE_Six12_TailInterior_Close_SoundShader", "BDE_Six12_TailInterior_Mid_SoundShader"};
        volumeFactor = 0.8;
        volumeCurve = "RifleShot_Interior_Curve";
        frequencyRandomizer = 1;
        sound3DProcessingType = "WeaponInteriorShotTail3DProcessingType";
        distanceFilter = "weaponShotDistanceFreq_INT_AttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 2;
    };

    class BDE_Six12_Slapback_SoundSet
    {
        soundShaders[] = {"BDE_Six12_Slapback_SoundShader"};
        volumeCurve = "SlapbackAttenuationCurve";
        frequencyRandomizer = 1;
        sound3DProcessingType = "Slapback_3DProcessingType";
        distanceFilter = "Slapback_DistanceFreqAttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundObjectsLimit = 2;
        volumeFactor = 0.15;
    };

    class BDE_Six12_Tail_2D_SoundSet
    {
        soundShaders[] = {"BDE_Six12_TailForest_2D_SoundShader", "BDE_Six12_TailHouses_2D_SoundShader", "BDE_Six12_TailMeadows_2D_SoundShader", "BDE_Six12_TailTrees_2D_SoundShader"};
        volumeFactor = 1;
        volumeCurve = "Tail2DAttenuationCurve";
        frequencyRandomizer = 1;
        sound3DProcessingType = "Tail_2D_3DProcessingType";
        distanceFilter = "Slapback_DistanceFreqAttenuationFilter";
        occlusionFactor = 0.35;
        obstructionFactor = 0.35;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 1;
    };

    class BDE_M203_Shot_SoundSet
    {
        soundShaders[] =
        {
            "BDE_M203_Mech_SoundShader",
            "BDE_M203_CloseShot_SoundShader",
            "BDE_M203_MidShot_SoundShader",
            "BDE_M203_DistShot_SoundShader"
        };
        volumeFactor = 0.8;
        volumeCurve = "RifleShotCurve";
        sound3DProcessingType = "WeaponMediumShot3DProcessingType";
        distanceFilter = "weaponShotDistanceFreqAttenuationFilter";
        occlusionFactor = 0.6;
        obstructionFactor = 0.6;
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 2;
        soundObjectsLimit = 4;
    };

    class BDE_M203_Reload_ChargeOpen_SoundSet
    {
        soundShaders[] = {"BDE_M203_Reload_ChargeOpen_SoundShader"};
        sound3DProcessingType = "character3DProcessingType";
        distanceFilter = "BaseCharacter_AttenuationFilter";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 1;
        soundObjectsLimit = 4;
    };

    class BDE_M203_Reload_GrenadeOut_SoundSet
    {
        soundShaders[] = {"BDE_M203_Reload_GrenadeOut_SoundShader"};
        sound3DProcessingType = "character3DProcessingType";
        distanceFilter = "BaseCharacter_AttenuationFilter";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 1;
        soundObjectsLimit = 4;
    };

    class BDE_M203_Reload_GrenadeIn_SoundSet
    {
        soundShaders[] = {"BDE_M203_Reload_GrenadeIn_SoundShader"};
        sound3DProcessingType = "character3DProcessingType";
        distanceFilter = "BaseCharacter_AttenuationFilter";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 1;
        soundObjectsLimit = 4;
    };

    class BDE_M203_Reload_ChargeClose_SoundSet
    {
        soundShaders[] = {"BDE_M203_Reload_ChargeClose_SoundShader"};
        sound3DProcessingType = "character3DProcessingType";
        distanceFilter = "BaseCharacter_AttenuationFilter";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
        soundShadersLimit = 1;
        soundObjectsLimit = 4;
    };
};
