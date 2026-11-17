class BDE_Six12_Magazine : MagazineStorage
{
    int BDE_Six12_GetAmmoMax()
    {
        return GetAmmoMax();
    }

    int BDE_Six12_GetAmmoCount()
    {
        return GetAmmoCount();
    }

    bool BDE_Six12_ConsumeRound(bool serverSide, out float ammoDamage, out string projectileType)
    {
        ammoDamage = 0.0;
        projectileType = "";

        if (GetAmmoCount() <= 0)
            return false;

        bool result;
        if (serverSide)
            result = ServerAcquireCartridge(ammoDamage, projectileType);
        else
            result = LocalAcquireCartridge(ammoDamage, projectileType);

        if (result)
        {
            SetSynchDirty();
            BDE_Six12_UpdateVisuals();
        }

        return result;
    }

    bool BDE_Six12_RestoreRound(bool serverSide, float ammoDamage, string projectileType)
    {
        if (GetAmmoCount() >= GetAmmoMax() || projectileType == "")
            return false;

        bool result;
        if (serverSide)
            result = ServerStoreCartridge(ammoDamage, projectileType);
        else
            result = LocalStoreCartridge(ammoDamage, projectileType);

        if (result)
        {
            SetSynchDirty();
            BDE_Six12_UpdateVisuals();
        }

        return result;
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        return parent && parent.IsKindOf("BDE_Six12");
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        BDE_Six12 six12 = BDE_Six12.Cast(parent);
        if (six12)
        {
            return six12.BDE_Six12_IsReceiverSwapInProgress();
        }

        return super.CanDetachAttachment(parent);
    }

    override bool CanSwapEntities(EntityAI otherItem, InventoryLocation otherDestination, InventoryLocation destination)
    {
        BDE_Six12 six12 = BDE_Six12.Cast(GetHierarchyParent());
        if (six12)
            return six12.BDE_Six12_IsReceiverSwapInProgress();

        return super.CanSwapEntities(otherItem, otherDestination, destination);
    }

    protected float BDE_Six12_NormalizeRotationPhase(float phase)
    {
        while (phase < 0.0)
            phase = phase + 1.0;
        while (phase >= 1.0)
            phase = phase - 1.0;
        return phase;
    }

    int BDE_Six12_GetFirstLoadedBulletIndex()
    {
        int ammoCount = Math.Clamp(GetAmmoCount(), 0, 6);
        if (ammoCount <= 0)
            return 1;
        return 7 - ammoCount;
    }

    int BDE_Six12_GetNextEmptyBulletIndex()
    {
        int ammoCount = Math.Clamp(GetAmmoCount(), 0, 6);
        if (ammoCount >= 6)
            return -1;
        return 6 - ammoCount;
    }

    float BDE_Six12_GetTopPhaseForBullet(int bulletIndex)
    {
        if (bulletIndex < 1 || bulletIndex > 6)
            return 0.0;

        return (bulletIndex - 1) / 6.0;
    }

    float BDE_Six12_GetBottomPhaseForBullet(int bulletIndex)
    {
        if (bulletIndex < 1 || bulletIndex > 6)
            return 0.0;

        float authoredPhase = (bulletIndex - 1) / 6.0;
        return BDE_Six12_NormalizeRotationPhase(authoredPhase - 0.5);
    }

    float BDE_Six12_GetFirstLoadedTopPhase()
    {
        return BDE_Six12_GetTopPhaseForBullet(BDE_Six12_GetFirstLoadedBulletIndex());
    }

    float BDE_Six12_GetNextEmptyBottomPhase()
    {
        int bulletIndex = BDE_Six12_GetNextEmptyBulletIndex();
        if (bulletIndex < 1)
            return BDE_Six12_GetFirstLoadedTopPhase();
        return BDE_Six12_GetBottomPhaseForBullet(bulletIndex);
    }

    void BDE_Six12_SetVisualPose(float slidePhase, float rotationPhase)
    {
        SetAnimationPhase("six12_magazine_slide", Math.Clamp(slidePhase, 0.0, 1.0));
        SetAnimationPhase("six12_cylinder_rotate", BDE_Six12_NormalizeRotationPhase(rotationPhase));
    }

    void BDE_Six12_UpdateBulletSelections()
    {
        int ammoCount = Math.Clamp(GetAmmoCount(), 0, 6);
        int firstLoadedIndex = 7 - ammoCount;

        for (int i = 0; i < 6; i++)
        {
            int bulletIndex = i + 1;
            bool showBullet = ammoCount > 0 && bulletIndex >= firstLoadedIndex;
            SetSimpleHiddenSelectionState(i, showBullet);
        }
    }

    void BDE_Six12_UpdateVisuals()
    {
        BDE_Six12_UpdateBulletSelections();

        BDE_Six12 six12 = BDE_Six12.Cast(GetHierarchyParent());
        if (six12 && six12.BDE_Six12_IsReloadActive())
            return;

        BDE_Six12_SetVisualPose(0.0, BDE_Six12_GetFirstLoadedTopPhase());
    }

    override void EEInit()
    {
        super.EEInit();
        BDE_Six12_UpdateVisuals();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();
        BDE_Six12_UpdateVisuals();
    }

    override void EEAmmoChanged()
    {
        super.EEAmmoChanged();
        BDE_Six12_UpdateVisuals();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_Six12_UpdateVisuals();
    }
}

class BDE_Six12_Magazine_FDE : BDE_Six12_Magazine
{
}

class BDE_Six12_CylinderVisual : Inventory_Base
{
    override bool CanPutAsAttachment(EntityAI parent)
    {
        return parent && parent.IsKindOf("BDE_Six12");
    }

    override bool CanDetachAttachment(EntityAI parent)
    {
        BDE_Six12 six12 = BDE_Six12.Cast(parent);
        if (six12)
            return six12.BDE_Six12_IsReceiverSwapInProgress();

        return super.CanDetachAttachment(parent);
    }
}

class BDE_Six12_CylinderVisual_FDE : BDE_Six12_CylinderVisual
{
}
