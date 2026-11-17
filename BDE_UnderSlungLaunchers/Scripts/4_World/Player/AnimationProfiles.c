modded class ModItemRegisterCallbacks
{
    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);

        pType.AddItemInHandsProfileIK("BDE_M203", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Standalone_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_FN40", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Standalone_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_M203_Barrel", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Barrel_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_M203_Short_Barrel", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Barrel_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_FN40_Barrel", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Barrel_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_M203_RearSight", "dz/anims/workspaces/player/player_main/props/player_main_1h_lighter.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_RearSight_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_FN40_Sight_Mount", "dz/anims/workspaces/player/player_main/props/player_main_1h_lighter.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_RearSight_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_M203_ButtStock", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/attachments/support/buttstock_m4_oe.anm");
        pType.AddItemInHandsProfileIK("BDE_FN40_Handle", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/attachments/support/buttstock_m4_oe.anm");
        pType.AddItemInHandsProfileIK("BDE_GP25_ButtPad", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_GP25_ButtPad_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_GP25_ButtStock", "dz/anims/workspaces/player/player_main/props/player_main_1h_lighter.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_GP25_ButtStock_IK.anm");
        pType.AddItemInHandsProfileIK("Ammo_40mm_Empty", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/ammunition/40mm_Grenade.anm");

        pType.AddItemInHandsProfileIK("BDE_M203_Rail_Adapter", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Rail_Adapter_IK.anm");

        pType.AddItemInHandsProfileIK("BDE_Six12_StandAloneMount", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_Six12_StandAloneMount_Item_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_Six12", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Standalone_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_Six12_Handle", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_Six12_Handle_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_Six12_LongBarrel", "dz/anims/workspaces/player/player_main/props/player_main_1h_lighter.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_Six12_LongBarrel_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_Six12_ShortBarrel", "dz/anims/workspaces/player/player_main/props/player_main_1h_lighter.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_Six12_ShortBarrel_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_Six12_Magazine", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_Six12_Magazine_IK.anm");
    }

    override void RegisterPistol(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterPistol(pType, pBehavior);

        pType.AddItemInHandsProfileIK("BDE_GP25", "BDE_UnderSlungLaunchers/Animations/GP25/player_main_gp25.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_GP25_Standalone_IK.anm", "dz/anims/anm/player/reloads/Flaregun/w_Flaregun_states.anm");
        pType.AddItemInHandsProfileIK("BDE_M203_StandAloneMount", "BDE_UnderSlungLaunchers/Animations/Player/player_main_m203_standalone_item.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Standalone_Item_IK.anm", "dz/anims/anm/player/reloads/Flaregun/w_Flaregun_states.anm");
        pType.AddItemInHandsProfileIK("BDE_FN40_StandaloneMount", "BDE_UnderSlungLaunchers/Animations/Player/player_main_m203_standalone_item.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_M203_Standalone_Item_IK.anm", "dz/anims/anm/player/reloads/Flaregun/w_Flaregun_states.anm");
    }

    override void RegisterFireArms(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterFireArms(pType, pBehavior);

        pType.AddItemInHandsProfileIK("BDE_M203_StandAloneMount_Weapon", "BDE_UnderSlungLaunchers/Animations/Player/player_main_m203_standalone_ak74u.asi", pBehavior, "dz/anims/anm/player/ik/weapons/aks74u.anm", "dz/anims/anm/player/reloads/AK74U/w_AKS74U_states.anm");
        pType.AddItemInHandsProfileIK("BDE_FN40_StandaloneMount_Weapon", "BDE_UnderSlungLaunchers/Animations/Player/player_main_m203_standalone_ak74u.asi", pBehavior, "dz/anims/anm/player/ik/weapons/aks74u.anm", "dz/anims/anm/player/reloads/AK74U/w_AKS74U_states.anm");
        pType.AddItemInHandsProfileIK("BDE_Six12_StandAloneMount_Weapon", "BDE_UnderSlungLaunchers/Animations/Six12/player_main_six12_standalone.asi", pBehavior, "dz/anims/anm/player/ik/weapons/famas.anm", "dz/anims/anm/player/reloads/famas/w_famas_states.anm");
        pType.AddItemInHandsProfileIK("M4A1", "BDE_UnderSlungLaunchers/Animations/Player/player_main_m4a1_bde_usl.asi", pBehavior, "dz/anims/anm/player/ik/weapons/m4a1_ik.anm", "dz/anims/anm/player/reloads/M4A1/w_M4A1_states.anm");
        pType.AddItemInHandsProfileIK("SCARH", "BDE_UnderSlungLaunchers/Animations/Player/player_main_scarh_bde_usl.asi", pBehavior, "dz/anims/anm/player/ik/weapons/scar_ik.anm", "dz/anims/anm/player/reloads/scar/w_scar_states.anm");
        pType.AddItemInHandsProfileIK("SCARH_Black", "BDE_UnderSlungLaunchers/Animations/Player/player_main_scarh_bde_usl.asi", pBehavior, "dz/anims/anm/player/ik/weapons/scar_ik.anm", "dz/anims/anm/player/reloads/scar/w_scar_states.anm");
        pType.AddItemInHandsProfileIK("AKM", "BDE_UnderSlungLaunchers/Animations/Player/player_main_akm_bde_usl.asi", pBehavior, "dz/anims/anm/player/ik/weapons/akm.anm", "dz/anims/anm/player/reloads/AKM/w_akm_states.anm");
        pType.AddItemInHandsProfileIK("AK74", "BDE_UnderSlungLaunchers/Animations/Player/player_main_ak101_bde_usl.asi", pBehavior, "dz/anims/anm/player/ik/weapons/ak101.anm", "dz/anims/anm/player/reloads/AK101/w_AK101_states.anm");
        pType.AddItemInHandsProfileIK("AK101", "BDE_UnderSlungLaunchers/Animations/Player/player_main_ak101_bde_usl.asi", pBehavior, "dz/anims/anm/player/ik/weapons/ak101.anm", "dz/anims/anm/player/reloads/AK101/w_AK101_states.anm");
    }
}
