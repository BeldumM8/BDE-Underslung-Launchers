class BDE_Six12_StandAloneMountSwapLambda : TurnItemIntoItemLambda
{
    void BDE_Six12_StandAloneMountSwapLambda(EntityAI old_item, string new_item_type, PlayerBase player)
    {
    }

    override void OnSuccess(EntityAI new_item)
    {
        super.OnSuccess(new_item);

        BDE_Six12_StandAloneMount itemMount = BDE_Six12_StandAloneMount.Cast(new_item);
        if (itemMount)
        {
            itemMount.BDE_Six12_PostSwapRefresh();
            return;
        }

        BDE_Six12_StandAloneMount_Weapon weaponMount = BDE_Six12_StandAloneMount_Weapon.Cast(new_item);
        if (weaponMount)
            weaponMount.BDE_Six12_PostSwapRefresh();
    }
}

class BDE_Six12_StandAloneMount extends Inventory_Base
{
    protected bool m_BDE_Six12_SwapInProgress;

    override void EEInit()
    {
        super.EEInit();
        BDE_Six12_RequestVariantRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_Six12_RequestVariantRefresh();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
        BDE_Six12_RequestVariantRefresh();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        BDE_Six12_RequestVariantRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_Six12_RequestVariantRefresh();
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!attachment)
            return false;

        string slotName = InventorySlots.GetSlotName(slotId);

        if (slotName == "BDE_Six12" && attachment.IsKindOf("BDE_Six12"))
        {
            BDE_Six12 body = BDE_Six12.Cast(attachment);
            if (!body || body.BDE_Six12_HasShortBarrel())
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        if (slotName == "BDE_Six12_LongBarrel" && attachment.IsKindOf("BDE_Six12_LongBarrel"))
        {
            if (!FindAttachmentBySlotName("BDE_Six12"))
                return false;
        }

        return super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (!m_BDE_Six12_SwapInProgress && attachment && FindAttachmentBySlotName("BDE_Six12") == attachment)
        {
            if (FindAttachmentBySlotName("BDE_Six12_LongBarrel"))
                return false;
        }

        return super.CanReleaseAttachment(attachment);
    }

    BDE_Six12 BDE_Six12_GetBody()
    {
        return BDE_Six12.Cast(FindAttachmentBySlotName("BDE_Six12"));
    }

    bool BDE_Six12_ShouldBeWeaponVariant()
    {
        BDE_Six12 body = BDE_Six12_GetBody();
        return body && body.BDE_Six12_HasHandle() && FindAttachmentBySlotName("BDE_Six12_LongBarrel");
    }

    override void OnDebugSpawn()
    {
        if (!GetGame().IsServer())
            return;

        string bodyType = "BDE_Six12";
        if (GetType() == "BDE_Six12_StandAloneMount_FDE")
            bodyType = "BDE_Six12_FDE";

        BDE_Six12 body = BDE_Six12.Cast(FindAttachmentBySlotName("BDE_Six12"));
        if (!body)
            body = BDE_Six12.Cast(GetInventory().CreateAttachment(bodyType));

        if (body)
        {
            string handleType = "BDE_Six12_Handle";
            if (bodyType == "BDE_Six12_FDE")
                handleType = "BDE_Six12_Handle_FDE";
            if (!body.FindAttachmentBySlotName("BDE_Six12_Handle"))
                body.GetInventory().CreateAttachment(handleType);
            body.OnDebugSpawn();
        }

        if (!FindAttachmentBySlotName("BDE_Six12_LongBarrel"))
        {
            string barrelType = "BDE_Six12_LongBarrel";
            GetInventory().CreateAttachment(barrelType);
        }
        if (!FindAttachmentBySlotName("weaponOptics"))
            GetInventory().CreateAttachment("ReflexOptic");

        BDE_Six12_RequestVariantRefresh();
    }

    void BDE_Six12_PostSwapRefresh()
    {
        m_BDE_Six12_SwapInProgress = false;
        BDE_Six12_RequestVariantRefresh();
    }

    void BDE_Six12_RequestVariantRefresh()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || m_BDE_Six12_SwapInProgress)
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_RefreshVariant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_RefreshVariant, 150, false);
    }

    protected void BDE_Six12_RefreshVariant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || m_BDE_Six12_SwapInProgress || !BDE_Six12_ShouldBeWeaponVariant())
            return;

        InventoryLocation stableLocation = new InventoryLocation();
        if (!GetInventory().GetCurrentInventoryLocation(stableLocation))
            return;

        string targetType = "BDE_Six12_StandAloneMount_Weapon";
        if (GetType() == "BDE_Six12_StandAloneMount_FDE")
            targetType = "BDE_Six12_StandAloneMount_Weapon_FDE";

        m_BDE_Six12_SwapInProgress = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_Six12_StandAloneMountSwapLambda lambda = new BDE_Six12_StandAloneMountSwapLambda(this, targetType, owner);
        lambda.SetTransferParams(true, true, true);
        if (!GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda))
            m_BDE_Six12_SwapInProgress = false;
    }
}

class BDE_Six12_StandAloneMount_FDE extends BDE_Six12_StandAloneMount
{
}

class BDE_Six12_StandAloneMount_Weapon extends M79_Base
{
    protected bool m_BDE_Six12_SwapInProgress;

    override void EEInit()
    {
        super.EEInit();
        BDE_Six12_QueueHostChamberClear();
        BDE_Six12_RequestVariantRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_Six12_QueueHostChamberClear();
        BDE_Six12_RequestVariantRefresh();
    }

    override bool CanChamberBullet(int muzzleIndex, Magazine mag)
    {
        return false;
    }

    override void EEAmmoChanged()
    {
        super.EEAmmoChanged();
        BDE_Six12_QueueHostChamberClear();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
        BDE_Six12_RequestVariantRefresh();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);
        BDE_Six12_RequestVariantRefresh();
    }

    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);
        BDE_Six12_RequestVariantRefresh();
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!attachment)
            return false;

        string slotName = InventorySlots.GetSlotName(slotId);

        if (slotName == "BDE_Six12" && attachment.IsKindOf("BDE_Six12"))
        {
            BDE_Six12 body = BDE_Six12.Cast(attachment);
            if (!body || body.BDE_Six12_HasShortBarrel())
                return false;

            return super.CanReceiveAttachment(attachment, slotId);
        }

        if (slotName == "BDE_Six12_LongBarrel" && attachment.IsKindOf("BDE_Six12_LongBarrel"))
        {
            if (!FindAttachmentBySlotName("BDE_Six12"))
                return false;
        }

        return super.CanReceiveAttachment(attachment, slotId);
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (!m_BDE_Six12_SwapInProgress && attachment && FindAttachmentBySlotName("BDE_Six12") == attachment)
        {
            if (FindAttachmentBySlotName("BDE_Six12_LongBarrel"))
                return false;
        }

        return super.CanReleaseAttachment(attachment);
    }

    BDE_Six12 BDE_Six12_GetBody()
    {
        return BDE_Six12.Cast(FindAttachmentBySlotName("BDE_Six12"));
    }

    bool BDE_Six12_ShouldBeWeaponVariant()
    {
        BDE_Six12 body = BDE_Six12_GetBody();
        return body && body.BDE_Six12_HasHandle() && FindAttachmentBySlotName("BDE_Six12_LongBarrel");
    }

    bool BDE_Six12_CanFireAssembly()
    {
        BDE_Six12 body = BDE_Six12_GetBody();
        if (!body || !body.BDE_Six12_HasHandle())
            return false;

        if (body.BDE_Six12_HasShortBarrel())
            return false;

        if (!FindAttachmentBySlotName("BDE_Six12_LongBarrel"))
            return false;

        return body.BDE_Six12_HasLoadedMagazine();
    }

    void BDE_Six12_PostSwapRefresh()
    {
        m_BDE_Six12_SwapInProgress = false;
        BDE_Six12_QueueHostChamberClear();
        BDE_Six12_RequestVariantRefresh();
    }

    void BDE_Six12_RequestVariantRefresh()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || m_BDE_Six12_SwapInProgress)
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_RefreshVariant);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_RefreshVariant, 150, false);
    }

    protected void BDE_Six12_RefreshVariant()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || m_BDE_Six12_SwapInProgress || BDE_Six12_ShouldBeWeaponVariant())
            return;

        InventoryLocation stableLocation = new InventoryLocation();
        if (!GetInventory().GetCurrentInventoryLocation(stableLocation))
            return;

        string targetType = "BDE_Six12_StandAloneMount";
        if (GetType() == "BDE_Six12_StandAloneMount_Weapon_FDE")
            targetType = "BDE_Six12_StandAloneMount_FDE";

        m_BDE_Six12_SwapInProgress = true;
        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        BDE_Six12_StandAloneMountSwapLambda lambda = new BDE_Six12_StandAloneMountSwapLambda(this, targetType, owner);
        lambda.SetTransferParams(true, true, true);
        if (!GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda))
            m_BDE_Six12_SwapInProgress = false;
    }

    bool BDE_Six12_GetMuzzlePointsWS(out vector muzzleStart, out vector muzzleEnd)
    {
        array<float> startValues = new array<float>;
        array<float> endValues = new array<float>;
        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " BDE_Six12_MuzzleStart", startValues);
        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " BDE_Six12_MuzzleEnd", endValues);

        if (startValues.Count() < 3 || endValues.Count() < 3)
            return false;

        vector localStart = Vector(startValues[0], startValues[1], startValues[2]);
        vector localEnd = Vector(endValues[0], endValues[1], endValues[2]);

        vector longBarrelProxyTransform[4];
        if (BDE_Six12_ProxyGeometry.GetSlotProxyTransform(this, "BDE_Six12_LongBarrel", longBarrelProxyTransform))
        {
            muzzleStart = ModelToWorld(localStart.Multiply4(longBarrelProxyTransform));
            muzzleEnd = ModelToWorld(localEnd.Multiply4(longBarrelProxyTransform));
            return true;
        }

        vector fallbackLongBarrelProxyOrigin = "0.115 0 0";
        muzzleStart = ModelToWorld(localStart + fallbackLongBarrelProxyOrigin);
        muzzleEnd = ModelToWorld(localEnd + fallbackLongBarrelProxyOrigin);
        return true;
    }

    protected void BDE_Six12_QueueHostChamberClear()
    {
        if (!GetGame().IsServer() && GetGame().IsMultiplayer())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_Six12_ClearHostChamber);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_ClearHostChamber, 1, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_Six12_ClearHostChamber, 250, false);
    }

    protected void BDE_Six12_ClearHostChamber()
    {
        if (!GetGame().IsServer() && GetGame().IsMultiplayer())
            return;

        bool changed = false;
        for (int muzzleIndex = 0; muzzleIndex < GetMuzzleCount(); muzzleIndex++)
        {
            if (IsChamberEmpty(muzzleIndex))
                continue;

            float damage;
            string ammoType;
            if (PopCartridgeFromChamber(muzzleIndex, damage, ammoType))
                changed = true;
        }

        if (changed)
        {
            RandomizeFSMState();
            Synchronize();
            SetSynchDirty();
        }
    }
}

class BDE_Six12_StandAloneMount_Weapon_FDE extends BDE_Six12_StandAloneMount_Weapon
{
}
