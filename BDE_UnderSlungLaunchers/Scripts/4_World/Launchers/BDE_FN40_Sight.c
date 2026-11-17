class BDE_FN40_Sight extends Inventory_Base
{
    protected bool m_FN40_Open;
    protected bool m_FN40_Initialized;

    override void EEInit()
    {
        super.EEInit();
        SetAnimationPhaseNow("fn40_rearsight_fold", 1.0);
        SetAnimationPhaseNow("fn40_frontsight_fold", 1.0);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_FN40_RefreshFold, 150, true);
    }

    void ~BDE_FN40_Sight()
    {
        if (GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_FN40_RefreshFold);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_FN40_FinishFold);
        }
    }

    bool BDE_FN40_ShouldOpen()
    {
        EntityAI sightMount = GetHierarchyParent();
        if (!sightMount || !sightMount.IsKindOf("BDE_FN40_Sight_Mount"))
            return false;
        EntityAI mount = sightMount.GetHierarchyParent();
        Weapon_Base host = Weapon_Base.Cast(mount);
        if (!host)
            return false;
        PlayerBase player = PlayerBase.Cast(host.GetHierarchyRootPlayer());
        if (!player || player.GetEntityInHands() != host)
            return false;
        if (host.IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
            return true;
        BDE_UnderSlungLauncher_Base launcher = host.BDE_USL_GetLauncher();
        return launcher && host.BDE_USL_IsLauncherModeSelected();
    }

    void BDE_FN40_RefreshFold()
    {
        if (IsSetForDeletion())
            return;
        bool open = BDE_FN40_ShouldOpen();
        if (m_FN40_Initialized && m_FN40_Open == open)
            return;
        m_FN40_Initialized = true;
        m_FN40_Open = open;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_FN40_FinishFold);
        if (open)
            SetAnimationPhase("fn40_frontsight_fold", 0.0);
        else
            SetAnimationPhase("fn40_rearsight_fold", 1.0);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_FN40_FinishFold, 250, false);
    }

    void BDE_FN40_FinishFold()
    {
        if (IsSetForDeletion())
            return;
        if (m_FN40_Open != BDE_FN40_ShouldOpen())
        {
            BDE_FN40_RefreshFold();
            return;
        }
        if (m_FN40_Open)
            SetAnimationPhase("fn40_rearsight_fold", 0.0);
        else
            SetAnimationPhase("fn40_frontsight_fold", 1.0);
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        return parent && parent.IsKindOf("BDE_FN40_Sight_Mount") && super.CanPutAsAttachment(parent);
    }
    override bool CanDetachAttachment(EntityAI parent) { return false; }
    override bool CanPutInCargo(EntityAI parent) { return false; }
    override bool CanPutIntoHands(EntityAI parent) { return false; }
}
class BDE_FN40_Sight_FDE extends BDE_FN40_Sight {}
