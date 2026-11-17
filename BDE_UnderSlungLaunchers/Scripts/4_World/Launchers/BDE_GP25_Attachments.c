class BDE_USL_ButtPadSwapLambda : TurnItemIntoItemLambda
{
    protected float m_BDE_USL_Health01;
    protected bool m_BDE_USL_WasRuined;

    void BDE_USL_ButtPadSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player)
    {
        m_BDE_USL_Health01 = old_item.GetHealth01("", "Health");
        m_BDE_USL_WasRuined = old_item.IsRuined();

        if (!m_BDE_USL_WasRuined && m_BDE_USL_Health01 <= 0.0)
            m_BDE_USL_Health01 = 1.0;
    }

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

        if (!new_item)
            return;

        if (m_BDE_USL_WasRuined)
        {
            new_item.SetHealth01("", "Health", 0.0);
            return;
        }

        new_item.SetHealth01("", "Health", Math.Clamp(m_BDE_USL_Health01, 0.0, 1.0));
    }
}

class BDE_GP25_ButtPad extends Inventory_Base
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;

        if (!parent.IsKindOf("BDE_GP25") && !parent.IsKindOf("BDE_M203") && !parent.IsKindOf("BDE_Six12"))
            return false;

        return super.CanPutAsAttachment(parent);
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);

        BDE_GP25 gp25 = BDE_GP25.Cast(parent);
        if (gp25)
        {
            gp25.BDE_GP25_RequestVariantRefresh();
            return;
        }

        BDE_M203 m203 = BDE_M203.Cast(parent);
        if (m203)
        {
            m203.BDE_M203_RequestButtPadRefresh();
            return;
        }

        BDE_Six12 six12 = BDE_Six12.Cast(parent);
        if (six12)
            six12.BDE_Six12_RequestButtPadRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);

        BDE_GP25 gp25 = BDE_GP25.Cast(parent);
        if (gp25)
        {
            gp25.BDE_GP25_RequestVariantRefresh();
        }
        else
        {
            BDE_M203 m203 = BDE_M203.Cast(parent);
            if (m203)
                m203.BDE_M203_RequestButtPadRefresh();
            else
            {
                BDE_Six12 six12 = BDE_Six12.Cast(parent);
                if (six12)
                    six12.BDE_Six12_RequestButtPadRefresh();
            }
        }

        BDE_USL_QueueVanillaAKPadNormalize();
    }

    protected void BDE_USL_QueueVanillaAKPadNormalize()
    {
        if (!GetGame().IsServer())
            return;

        string padType = GetType();
        if (padType != "BDE_USL_M203_ButtPad_VanillaAK" && padType != "BDE_USL_Six12_ButtPad_VanillaAK")
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_NormalizeVanillaAKPad);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_NormalizeVanillaAKPad, 50, false);
    }

    protected void BDE_USL_NormalizeVanillaAKPad()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        EntityAI parent = GetHierarchyParent();
        if (parent && (parent.IsKindOf("BDE_GP25") || parent.IsKindOf("BDE_M203") || parent.IsKindOf("BDE_Six12")))
            return;

        string padType = GetType();
        if (padType != "BDE_USL_M203_ButtPad_VanillaAK" && padType != "BDE_USL_Six12_ButtPad_VanillaAK")
            return;

        InventoryLocation padLocation = new InventoryLocation();
        if (!GetInventory().GetCurrentInventoryLocation(padLocation) || !padLocation.IsValid() || padLocation.GetType() == InventoryLocationType.UNKNOWN)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_NormalizeVanillaAKPad);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_NormalizeVanillaAKPad, 100, false);
            return;
        }

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_USL_ButtPadSwapLambda lambda = new BDE_USL_ButtPadSwapLambda(this, "BDE_GP25_ButtPad", owner);
        lambda.SetTransferParams(true, true, false);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }
}

class BDE_GP25_ButtStock extends Inventory_Base
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        BDE_GP25 launcher = BDE_GP25.Cast(parent);

        if (!launcher || Weapon_Base.Cast(launcher.GetHierarchyParent()))
            return false;

        return super.CanPutAsAttachment(parent);
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_GP25_QueueStockRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_GP25_QueueStockRefresh();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_GP25_QueueStockRefresh();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_GP25_QueueStockRefresh();
    }

    override void OnWasDetached(EntityAI parent, int slot_id)
    {
        super.OnWasDetached(parent, slot_id);
        BDE_GP25_QueueStockRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_GP25_QueueStockRefresh();
    }

    void BDE_GP25_QueueStockRefresh()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_ApplyStockState);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_ApplyStockState, 1, false);
    }

    protected void BDE_GP25_ApplyStockState()
    {
        float phase = 0.0;
        BDE_GP25 launcher = BDE_GP25.Cast(GetHierarchyParent());

        if (launcher)
        {
            PlayerBase owner = PlayerBase.Cast(launcher.GetHierarchyRootPlayer());

            if (owner && owner.GetEntityInHands() == launcher)
                phase = 1.0;
        }

        SetAnimationPhase("gp25_stock_extend", phase);
    }
}

class BDE_GP25_Sight extends Inventory_Base
{
    protected float m_BDE_GP25_ZeroTarget = -1.0;

    void BDE_GP25_SetZeroTarget(float phase, bool force = false)
    {
        phase = Math.Clamp(phase, 0.0, 1.0);

        if (!force && m_BDE_GP25_ZeroTarget >= 0.0 && Math.AbsFloat(m_BDE_GP25_ZeroTarget - phase) < 0.0001)
            return;

        m_BDE_GP25_ZeroTarget = phase;
        SetAnimationPhase("gp25_sight_zero", phase);
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent || !parent.IsKindOf("BDE_GP25"))
            return false;

        return super.CanPutAsAttachment(parent);
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        BDE_GP25 launcher = BDE_GP25.Cast(parent);
        if (launcher && launcher.BDE_GP25_IsSightSwapInProgress())
            return true;

        return false;
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_GP25_QueueFixedSightState();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_GP25_QueueFixedSightState();
    }

    override void OnWasAttached(EntityAI parent, int slot_id)
    {
        super.OnWasAttached(parent, slot_id);
        BDE_GP25_QueueFixedSightState();
    }

    protected void BDE_GP25_QueueFixedSightState()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_GP25_ApplyFixedSightState);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_GP25_ApplyFixedSightState, 1, false);
    }

    protected void BDE_GP25_ApplyFixedSightState()
    {
        float foldPhase = 0.0;
        if (IsKindOf("BDE_GP25_Sight_Unfolded"))
            foldPhase = 1.0;

        SetAnimationPhase("gp25_sight_ads", foldPhase);

        BDE_GP25 launcher = BDE_GP25.Cast(GetHierarchyParent());
        if (launcher)
            launcher.BDE_GP25_UpdateSightZeroVisual();
    }
}
