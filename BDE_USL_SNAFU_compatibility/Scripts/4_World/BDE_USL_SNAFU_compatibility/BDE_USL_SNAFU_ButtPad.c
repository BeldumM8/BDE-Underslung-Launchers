class BDE_USL_SNAFU_ButtPadSupport
{
    static bool IsSupportedHost(Weapon_Base host)
    {
        if (!host)
            return false;

        return host.IsKindOf("SNAFU_AK19_Base") || host.IsKindOf("SNAFU_AK12A_Base") || host.IsKindOf("SNAFU_AK308_Base");
    }

    static bool HostSupports(EntityAI launcher)
    {
        if (!launcher)
            return false;

        Weapon_Base host = Weapon_Base.Cast(launcher.GetHierarchyParent());
        if (!IsSupportedHost(host))
            return false;

        EntityAI buttstock = host.FindAttachmentBySlotName("weaponButtstockAK");
        if (!buttstock)
            return false;

        return buttstock.IsKindOf("AK_PlasticBttstck");
    }

    static void SwapPad(EntityAI buttPad, string targetType)
    {
        if (!buttPad || buttPad.GetType() == targetType)
            return;

        PlayerBase owner = PlayerBase.Cast(buttPad.GetHierarchyRootPlayer());
        BDE_USL_ButtPadSwapLambda lambda = new BDE_USL_ButtPadSwapLambda(buttPad, targetType, owner);
        lambda.SetTransferParams(true, true, false);
        buttPad.GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }
}

modded class BDE_M203
{
    override protected bool BDE_M203_HostSupportsButtPad()
    {
        if (super.BDE_M203_HostSupportsButtPad())
            return true;

        return BDE_USL_SNAFU_ButtPadSupport.HostSupports(this);
    }

    override protected void BDE_M203_RefreshButtPad()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!BDE_USL_SNAFU_ButtPadSupport.IsSupportedHost(host))
        {
            super.BDE_M203_RefreshButtPad();
            return;
        }

        EntityAI buttPad = FindAttachmentBySlotName("BDE_M203_ButtPad");
        if (!buttPad || !BDE_M203_HostSupportsButtPad())
            return;

        BDE_USL_SNAFU_ButtPadSupport.SwapPad(buttPad, "BDE_USL_SNAFU_M203_ButtPad");
    }
}

modded class BDE_GP25
{
    override protected bool BDE_GP25_HostSupportsButtPad()
    {
        if (super.BDE_GP25_HostSupportsButtPad())
            return true;

        return BDE_USL_SNAFU_ButtPadSupport.HostSupports(this);
    }

    override protected void BDE_GP25_RefreshButtPad()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!BDE_USL_SNAFU_ButtPadSupport.IsSupportedHost(host))
        {
            super.BDE_GP25_RefreshButtPad();
            return;
        }

        EntityAI buttPad = FindAttachmentBySlotName("BDE_GP25_ButtPad");
        if (!buttPad || !BDE_GP25_HostSupportsButtPad())
            return;

        BDE_USL_SNAFU_ButtPadSupport.SwapPad(buttPad, "BDE_USL_SNAFU_GP25_ButtPad");
    }
}

modded class BDE_Six12
{
    override protected bool BDE_Six12_HostSupportsButtPad()
    {
        if (super.BDE_Six12_HostSupportsButtPad())
            return true;

        return BDE_USL_SNAFU_ButtPadSupport.HostSupports(this);
    }

    override protected void BDE_Six12_RefreshButtPad()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        if (!BDE_USL_SNAFU_ButtPadSupport.IsSupportedHost(host))
        {
            super.BDE_Six12_RefreshButtPad();
            return;
        }

        EntityAI buttPad = FindAttachmentBySlotName("BDE_Six12_ButtPad");
        if (!buttPad || !BDE_Six12_HostSupportsButtPad())
            return;

        BDE_USL_SNAFU_ButtPadSupport.SwapPad(buttPad, "BDE_USL_SNAFU_Six12_ButtPad");
    }
}

modded class BDE_GP25_ButtPad
{
    override protected void BDE_USL_QueueVanillaAKPadNormalize()
    {
        string padType = GetType();
        if (padType != "BDE_USL_SNAFU_GP25_ButtPad" && padType != "BDE_USL_SNAFU_M203_ButtPad" && padType != "BDE_USL_SNAFU_Six12_ButtPad")
        {
            super.BDE_USL_QueueVanillaAKPadNormalize();
            return;
        }

        if (!GetGame().IsServer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_SNAFU_NormalizeButtPad);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_SNAFU_NormalizeButtPad, 50, false);
    }

    protected void BDE_USL_SNAFU_NormalizeButtPad()
    {
        if (!GetGame().IsServer() || IsSetForDeletion())
            return;

        EntityAI parent = GetHierarchyParent();
        if (parent && (parent.IsKindOf("BDE_GP25") || parent.IsKindOf("BDE_M203") || parent.IsKindOf("BDE_Six12")))
            return;

        string padType = GetType();
        if (padType != "BDE_USL_SNAFU_GP25_ButtPad" && padType != "BDE_USL_SNAFU_M203_ButtPad" && padType != "BDE_USL_SNAFU_Six12_ButtPad")
            return;

        InventoryLocation location = new InventoryLocation();
        if (!GetInventory().GetCurrentInventoryLocation(location) || !location.IsValid() || location.GetType() == InventoryLocationType.UNKNOWN)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_SNAFU_NormalizeButtPad);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_SNAFU_NormalizeButtPad, 100, false);
            return;
        }

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_USL_ButtPadSwapLambda lambda = new BDE_USL_ButtPadSwapLambda(this, "BDE_GP25_ButtPad", owner);
        lambda.SetTransferParams(true, true, false);
        GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
    }
}
