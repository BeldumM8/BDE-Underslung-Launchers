#ifdef S_GUNPLAY
modded class PPERequester_CameraADS
{
    void BDE_USL_ResetLauncherPiP()
    {
        GetGame().ResetPPMask();
        SetTargetValueFloatDefault(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSDISTORT);
        SetTargetValueFloatDefault(PostProcessEffectType.Glow, PPEGlow.PARAM_MAXCHROMABBERATION);
        SetTargetValueFloatDefault(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSCENTERX);
        SetTargetValueFloatDefault(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSCENTERY);
    }
}
#endif
