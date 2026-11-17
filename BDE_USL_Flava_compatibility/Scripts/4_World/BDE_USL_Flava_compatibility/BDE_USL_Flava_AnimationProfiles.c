modded class ModItemRegisterCallbacks
{
    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);

        pType.AddItemInHandsProfileIK("BDE_USL_GP25_ButtPad_FlavaAK", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_GP25_ButtPad_IK.anm");
        pType.AddItemInHandsProfileIK("BDE_USL_GP25_ButtPad_FlavaShortAK", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "BDE_UnderSlungLaunchers/Animations/IK/BDE_GP25_ButtPad_IK.anm");
    }

    override void RegisterFireArms(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterFireArms(pType, pBehavior);

        pType.AddItemInHandsProfileIK("TF_M4A1", "BDE_USL_Flava_compatibility/Animations/Player/player_main_m4a1_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/m4a1_ik.anm", "dz/anims/anm/player/reloads/M4A1/w_M4A1_states.anm");
        pType.AddItemInHandsProfileIK("TF_M4A1_CQBR", "BDE_USL_Flava_compatibility/Animations/Player/player_main_m4a1_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/m4a1_ik.anm", "dz/anims/anm/player/reloads/M4A1/w_M4A1_states.anm");
        pType.AddItemInHandsProfileIK("TF_ADAR2_15", "BDE_USL_Flava_compatibility/Animations/Player/player_main_m4a1_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/m4a1_ik.anm", "dz/anims/anm/player/reloads/M4A1/w_M4A1_states.anm");
        pType.AddItemInHandsProfileIK("TF_MK47_CQBR", "BDE_USL_Flava_compatibility/Animations/Player/player_main_m4a1_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/m4a1_ik.anm", "dz/anims/anm/player/reloads/M4A1/w_M4A1_states.anm");
        pType.AddItemInHandsProfileIK("TF_MK47", "BDE_USL_Flava_compatibility/Animations/Player/player_main_m4a1_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/m4a1_ik.anm", "dz/anims/anm/player/reloads/M4A1/w_M4A1_states.anm");
        pType.AddItemInHandsProfileIK("TF_SR25", "BDE_USL_Flava_compatibility/Animations/Player/player_main_m4a1_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/m4a1_ik.anm", "dz/anims/anm/player/reloads/M4A1/w_M4A1_states.anm");

        pType.AddItemInHandsProfileIK("TF_AK101", "BDE_USL_Flava_compatibility/Animations/Player/player_main_ak101_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/ak101.anm", "dz/anims/anm/player/reloads/AK101/w_AK101_states.anm");
        pType.AddItemInHandsProfileIK("TF_AK102", "BDE_USL_Flava_compatibility/Animations/Player/player_main_ak101_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/ak101.anm", "dz/anims/anm/player/reloads/AK101/w_AK101_states.anm");
        pType.AddItemInHandsProfileIK("TF_AK105", "BDE_USL_Flava_compatibility/Animations/Player/player_main_ak101_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/ak101.anm", "dz/anims/anm/player/reloads/AK101/w_AK101_states.anm");
        pType.AddItemInHandsProfileIK("TF_AK74M", "BDE_USL_Flava_compatibility/Animations/Player/player_main_ak101_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/ak101.anm", "dz/anims/anm/player/reloads/AK101/w_AK101_states.anm");
        pType.AddItemInHandsProfileIK("TF_AN94M", "BDE_USL_Flava_compatibility/Animations/Player/player_main_ak101_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/ak101.anm", "dz/anims/anm/player/reloads/AK101/w_AK101_states.anm");

        pType.AddItemInHandsProfileIK("TF_AK103", "BDE_USL_Flava_compatibility/Animations/Player/player_main_akm_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/akm.anm", "dz/anims/anm/player/reloads/AKM/w_akm_states.anm");
        pType.AddItemInHandsProfileIK("TF_AK104", "BDE_USL_Flava_compatibility/Animations/Player/player_main_akm_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/akm.anm", "dz/anims/anm/player/reloads/AKM/w_akm_states.anm");
        pType.AddItemInHandsProfileIK("TF_AKM", "BDE_USL_Flava_compatibility/Animations/Player/player_main_akm_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/akm.anm", "dz/anims/anm/player/reloads/AKM/w_akm_states.anm");
        pType.AddItemInHandsProfileIK("TF_VPO136", "BDE_USL_Flava_compatibility/Animations/Player/player_main_akm_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/akm.anm", "dz/anims/anm/player/reloads/AKM/w_akm_states.anm");
        pType.AddItemInHandsProfileIK("TF_AKMN", "BDE_USL_Flava_compatibility/Animations/Player/player_main_akm_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/akm.anm", "dz/anims/anm/player/reloads/AKM/w_akm_states.anm");

        pType.AddItemInHandsProfileIK("TF_MAR10", "BDE_USL_Flava_compatibility/Animations/Player/player_main_svd_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/svd.anm", "dz/anims/anm/player/reloads/SVD/w_SVD_states.anm");
        pType.AddItemInHandsProfileIK("TF_PKM", "BDE_USL_Flava_compatibility/Animations/Player/player_main_svd_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/svd.anm", "dz/anims/anm/player/reloads/SVD/w_SVD_states.anm");
        pType.AddItemInHandsProfileIK("TF_PKP", "BDE_USL_Flava_compatibility/Animations/Player/player_main_svd_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/svd.anm", "dz/anims/anm/player/reloads/SVD/w_SVD_states.anm");

        pType.AddItemInHandsProfileIK("TF_SCAR_L_FDE", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_L_Black", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_L_CQC_FDE", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_L_CQC_Black", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_H_FDE", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_H_Black", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_H_CQC_FDE", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_H_CQC_Black", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_20_FDE", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_20_Black", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SCAR_20_Shd", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SVCh308", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");
        pType.AddItemInHandsProfileIK("TF_SVCh", "BDE_USL_Flava_compatibility/Animations/Player/player_main_fnfal_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm", "dz/anims/anm/player/reloads/FNFal/w_FNFal_states.anm");

        pType.AddItemInHandsProfileIK("TF_M16A4", "BDE_USL_Flava_compatibility/Animations/Player/player_main_m16a2_bde_usl_flava.asi", pBehavior, "dz/anims/anm/player/ik/weapons/M16A2_ik.anm", "dz/anims/anm/player/reloads/m16a2/w_m16a2_states.anm");
    }
}
