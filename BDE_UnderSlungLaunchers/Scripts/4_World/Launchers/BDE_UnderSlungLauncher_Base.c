class BDE_UnderSlungLauncher_Base extends RifleSingleShotManual_Base
{
    protected int m_BDE_USL_LastDryFireTime;
    protected int m_BDE_USL_LastRemoteSmokeShot = -1;
    protected bool m_BDE_USL_ManipulationActive;
    protected int m_BDE_USL_ServerManipulationAction;
    protected Magazine m_BDE_USL_PendingReloadSource;
    protected PlayerBase m_BDE_USL_PendingManipulationPlayer;
    protected bool m_BDE_USL_ServerEjectHandled;

    protected string m_BDE_USL_LoadedMagazineSourceType;

    protected bool m_BDE_USL_HasReservedGroundRound;
    protected string m_BDE_USL_ReservedGroundMagazineType;
    protected string m_BDE_USL_ReservedGroundAmmoType;
    protected float m_BDE_USL_ReservedGroundAmmoDamage;

    void BDE_UnderSlungLauncher_Base()
    {
    }

    override void EEInit()
    {
        super.EEInit();

        BDE_USL_QueueChamberVisualRefresh();
    }

    override void EEOnAfterLoad()
    {
        super.EEOnAfterLoad();

        BDE_USL_QueueChamberVisualRefresh();
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        BDE_USL_ShotWear.LogClient(this);

        BDE_USL_QueueChamberVisualRefresh();
    }

    bool BDE_USL_UsesStaticChamberProxy()
    {
        if (IsKindOf("BDE_M203") || IsKindOf("BDE_GP25"))
            return true;

        return Weapon_Base.Cast(GetHierarchyParent()) != null;
    }

    protected void BDE_USL_ApplyStaticChamberProxy(bool visible)
    {
        TStringArray selectionNames = new TStringArray;
        ConfigGetTextArray("simpleHiddenSelections", selectionNames);

        int bulletSelection = selectionNames.Find("bullet");

        if (bulletSelection < 0)
            return;

        SetSimpleHiddenSelectionState(bulletSelection, visible);
    }

    string BDE_USL_GetLoadedMagazineSourceType()
    {
        return m_BDE_USL_LoadedMagazineSourceType;
    }

    void BDE_USL_SetLoadedMagazineSourceType(string typeName)
    {
        m_BDE_USL_LoadedMagazineSourceType = typeName;
    }

    void BDE_USL_SyncChamberVisual()
    {
        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex)
            return;

        bool showRound = IsChamberFull(muzzleIndex) && !IsChamberFiredOut(muzzleIndex);

        if (BDE_USL_UsesStaticChamberProxy())
        {
            BDE_USL_ApplyStaticChamberProxy(showRound);
            return;
        }

        if (showRound)
            ShowBullet(muzzleIndex);
        else
            HideBullet(muzzleIndex);
    }

    void BDE_USL_QueueChamberVisualRefresh()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_SyncChamberVisual);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_SyncChamberVisual, 1, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_SyncChamberVisual, 50, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_SyncChamberVisual, 250, false);
    }

    override void ShowBullet(int muzzleIndex)
    {
        if (BDE_USL_UsesStaticChamberProxy())
        {
            BDE_USL_SyncChamberVisual();
            return;
        }

        super.ShowBullet(muzzleIndex);
    }

    override void HideBullet(int muzzleIndex)
    {
        if (BDE_USL_UsesStaticChamberProxy())
        {
            BDE_USL_ApplyStaticChamberProxy(false);
            return;
        }

        super.HideBullet(muzzleIndex);
    }

    override void SyncSelectionState(bool has_bullet, bool has_mag)
    {
        if (!BDE_USL_UsesStaticChamberProxy())
        {
            super.SyncSelectionState(has_bullet, has_mag);
            return;
        }

        BDE_USL_SyncChamberVisual();
    }

    override void ForceSyncSelectionState()
    {
        if (!BDE_USL_UsesStaticChamberProxy())
        {
            super.ForceSyncSelectionState();
            return;
        }

        BDE_USL_SyncChamberVisual();
    }

    override void OnFire(int muzzle_index)
    {
        super.OnFire(muzzle_index);

        if (GetGame().IsServer())
            BDE_USL_SetLoadedMagazineSourceType("");

        BDE_USL_QueueChamberVisualRefresh();
    }

    protected bool BDE_USL_FireWatchdogRetryPreserveState(int muzzleIndex, vector projectilePosition, vector shotDirection, vector inheritedVelocity)
    {
        float healthBefore = GetHealth("", "Health");
        bool jamBefore = IsJammed();
        bool fired = Fire(muzzleIndex, projectilePosition, shotDirection, inheritedVelocity);

        if (GetGame().IsServer())
        {
            float healthAfter = GetHealth("", "Health");
            if (healthBefore > 0.0 && healthAfter < healthBefore)
                SetHealth("", "Health", healthBefore);

            if (IsJammed() != jamBefore)
                SetJammed(jamBefore);
        }

        return fired;
    }

    bool BDE_USL_WatchdogRetryPhysicalShot(string ammoType, vector projectilePosition, vector shotDirection, vector inheritedVelocity)
    {
        if (!GetGame().IsServer() || ammoType == "" || GetMuzzleCount() <= 0)
            return false;

        int muzzleIndex = 0;
        float existingDamage = 0.0;
        string existingType = "";

        if (!IsChamberEmpty(muzzleIndex))
        {
            if (!IsChamberFiredOut(muzzleIndex))
            {
                GetCartridgeInfo(muzzleIndex, existingDamage, existingType);
                if (existingType != ammoType)
                    return false;

                return BDE_USL_FireWatchdogRetryPreserveState(muzzleIndex, projectilePosition, shotDirection, inheritedVelocity);
            }

            if (!PopCartridgeFromChamber(muzzleIndex, existingDamage, existingType))
                return false;
        }

        if (!PushCartridgeToChamber(muzzleIndex, existingDamage, ammoType))
            return false;

        bool fired = BDE_USL_FireWatchdogRetryPreserveState(muzzleIndex, projectilePosition, shotDirection, inheritedVelocity);
        if (fired)
        {
            RandomizeFSMState();
            BDE_USL_QueueChamberVisualRefresh();
        }

        return fired;
    }

    void BDE_USL_WatchdogRetryPhysicalShotDispatch(string ammoType, vector projectilePosition, vector shotDirection, vector inheritedVelocity, int shotId, vector impactPosition)
    {
        bool fired = BDE_USL_WatchdogRetryPhysicalShot(ammoType, projectilePosition, shotDirection, inheritedVelocity);
        GetGame().BDE_USL_Report40mmPhysicalRetry(shotId, this, ammoType, fired, impactPosition);
    }

    void BDE_USL_WatchdogRetryCleanup(string ammoType)
    {
        if (!GetGame().IsServer() || GetMuzzleCount() <= 0 || IsChamberEmpty(0) || IsChamberFiredOut(0))
            return;

        float cleanupDamage;
        string cleanupType;
        GetCartridgeInfo(0, cleanupDamage, cleanupType);
        if (cleanupType != ammoType)
            return;

        PopCartridgeFromChamber(0, cleanupDamage, cleanupType);
        RandomizeFSMState();
        BDE_USL_QueueChamberVisualRefresh();
    }

    override void EEFired(int muzzleType, int mode, string ammoType)
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host)
            return;

        super.EEFired(muzzleType, mode, ammoType);
    }

    override bool CanPutAsAttachment(EntityAI parent)
    {
        if (!parent)
            return false;

        if (!super.CanPutAsAttachment(parent))
            return false;

        Weapon_Base host = Weapon_Base.Cast(parent);

        if (!host)
            return true;

        return host.BDE_USL_CanAttachLauncherToConfiguredSlot(this);
    }

    bool BDE_USL_GetProxyMuzzlePositions(out vector startPosition, out vector endPosition)
    {
        vector transform[4];
        BDE_USL_GetAdjustedAttachmentTransform(transform);

        vector startOffset = BDE_USL_GetProxyMuzzleStartOffset();
        vector endOffset = BDE_USL_GetProxyMuzzleEndOffset();

        startPosition = startOffset.Multiply4(transform);
        endPosition = endOffset.Multiply4(transform);

        return true;
    }

    vector BDE_USL_GetProxyMuzzleStartOffset()
    {
        array<float> values = new array<float>;

        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " BDE_USL_AttachedMuzzleStart", values);

        if (values.Count() < 3)
            return "0 0 0";

        return Vector(values[0], values[1], values[2]);
    }

    vector BDE_USL_GetProxyMuzzleEndOffset()
    {
        array<float> values = new array<float>;

        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " BDE_USL_AttachedMuzzleEnd", values);

        if (values.Count() < 3)
            return "0 0 0";

        return Vector(values[0], values[1], values[2]);
    }

    vector BDE_USL_GetAimCameraOffset()
    {
        vector offset = "-0.12 0.18 -0.43";
        array<float> values = new array<float>;
        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " BDE_USL_AimCameraOffset", values);

        if (values.Count() >= 3)
            offset = Vector(values[0], values[1], values[2]);

        return offset;
    }

    float BDE_USL_GetAimGravity()
    {
        float gravity = GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " BDE_USL_AimGravity");

        if (gravity <= 0.0)
            return 9.81;

        return gravity;
    }

    float BDE_USL_GetAimMaxAngle()
    {
        float maxAngle = GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " BDE_USL_AimMaxAngle");

        if (maxAngle <= 0.0)
            return 45.0;

        return Math.Clamp(maxAngle, 1.0, 45.0);
    }

    float BDE_USL_GetAimFallbackZeroing()
    {
        float fallbackZeroing = GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " BDE_USL_AimFallbackZeroing");

        if (fallbackZeroing <= 0.0)
            return 25.0;

        return fallbackZeroing;
    }

    protected int m_BDE_USL_AimZeroingIndex = -1;

    protected bool BDE_USL_IsStandaloneM203Host()
    {
        EntityAI parent = GetHierarchyParent();
        return parent && parent.IsKindOf("BDE_M203_StandAloneMount_Weapon");
    }

    protected EntityAI BDE_USL_GetActiveAimSight()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!host)
            return null;

        EntityAI fn40Mount = host.BDE_USL_GetFN40SightMount();

        if (fn40Mount)
        {
            EntityAI fn40Sight = fn40Mount.FindAttachmentBySlotName("BDE_FN40_Sight");

            if (fn40Sight)
                return fn40Sight;
        }

        if (host.IsKindOf("BDE_M203_StandAloneMount_Weapon") || host.IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
        {
            EntityAI standaloneSight = host.FindAttachmentBySlotName("weaponOptics");

            if (standaloneSight && standaloneSight.IsKindOf("BDE_M203_RearSight") && standaloneSight.FindAttachmentBySlotName("BDE_M203_FrontSight"))
                return standaloneSight;
        }

        BDE_M203 m203 = BDE_M203.Cast(this);

        if (m203 && m203.BDE_M203_HasRailSightSystem())
            return m203.BDE_M203_GetRailRearSight();

        return null;
    }

    protected bool BDE_USL_GetSightZeroingDistances(EntityAI sight, out TFloatArray distances)
    {
        distances = new TFloatArray;

        if (!sight)
            return false;

        GetGame().ConfigGetFloatArray("CfgVehicles " + sight.GetType() + " BDE_USL_SightZeroingDistances", distances);
        return distances.Count() > 0;
    }

    protected void BDE_USL_GetAimZeroingDistances(out TFloatArray distances)
    {
        if (BDE_USL_GetSightZeroingDistances(BDE_USL_GetActiveAimSight(), distances))
            return;

        distances = new TFloatArray;

        if (BDE_USL_IsStandaloneM203Host())
        {
            Weapon_Base standaloneHost = Weapon_Base.Cast(GetHierarchyParent());
            EntityAI opticEntity;

            if (standaloneHost)
                opticEntity = standaloneHost.FindAttachmentBySlotName("weaponOptics");

            if (!opticEntity)
            {
                distances.Insert(0.0);
                return;
            }
        }

        GetGame().ConfigGetFloatArray("CfgWeapons " + GetType() + " BDE_USL_AimZeroingDistances", distances);

        if (distances.Count() == 0)
            distances.Insert(BDE_USL_GetAimFallbackZeroing());
    }

    protected int BDE_USL_FindDefaultAimZeroingIndex(TFloatArray distances)
    {
        if (!distances || distances.Count() == 0)
            return 0;

        if (BDE_USL_IsStandaloneM203Host())
            return 0;

        float fallback = BDE_USL_GetAimFallbackZeroing();
        int bestIndex = 0;
        float bestDifference = Math.AbsFloat(distances[0] - fallback);

        for (int index = 1; index < distances.Count(); index++)
        {
            float difference = Math.AbsFloat(distances[index] - fallback);

            if (difference < bestDifference)
            {
                bestDifference = difference;
                bestIndex = index;
            }
        }

        return bestIndex;
    }

    protected void BDE_USL_EnsureAimZeroingIndex(TFloatArray distances)
    {
        if (!distances || distances.Count() == 0)
        {
            m_BDE_USL_AimZeroingIndex = 0;
            return;
        }

        if (m_BDE_USL_AimZeroingIndex < 0)
            m_BDE_USL_AimZeroingIndex = BDE_USL_FindDefaultAimZeroingIndex(distances);

        m_BDE_USL_AimZeroingIndex = Math.Clamp(m_BDE_USL_AimZeroingIndex, 0, distances.Count() - 1);
    }

    float BDE_USL_GetCurrentAimZeroing()
    {
        TFloatArray distances;
        BDE_USL_GetAimZeroingDistances(distances);
        BDE_USL_EnsureAimZeroingIndex(distances);
        return distances[m_BDE_USL_AimZeroingIndex];
    }

    bool BDE_USL_StepAimZeroingUp()
    {
        TFloatArray distances;
        BDE_USL_GetAimZeroingDistances(distances);
        BDE_USL_EnsureAimZeroingIndex(distances);

        if (m_BDE_USL_AimZeroingIndex >= distances.Count() - 1)
            return false;

        m_BDE_USL_AimZeroingIndex++;
        return true;
    }

    bool BDE_USL_StepAimZeroingDown()
    {
        TFloatArray distances;
        BDE_USL_GetAimZeroingDistances(distances);
        BDE_USL_EnsureAimZeroingIndex(distances);

        if (m_BDE_USL_AimZeroingIndex <= 0)
            return false;

        m_BDE_USL_AimZeroingIndex--;
        return true;
    }

    protected bool BDE_USL_CalculateAttachedAimCameraGeometry(out vector cameraPosition, out vector launchDirection, out vector launcherUp)
    {
        cameraPosition = vector.Zero;
        launchDirection = vector.Zero;
        launcherUp = vector.Up;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        bool standaloneGP25 = !host && IsKindOf("BDE_GP25");

        if (!host && !standaloneGP25)
            return false;

        vector slotTransform[4];
        slotTransform[0] = "1 0 0";
        slotTransform[1] = "0 1 0";
        slotTransform[2] = "0 0 1";
        slotTransform[3] = vector.Zero;

        vector slotPosition;
        vector slotOrientation;
        string slotName;

        if (host && BDE_USL_GetCurrentInventorySlotOffset(slotPosition, slotOrientation, slotName))
        {
            vector slotRotation[3];
            Math3D.YawPitchRollMatrix(slotOrientation, slotRotation);
            slotTransform[0] = slotRotation[0];
            slotTransform[1] = slotRotation[1];
            slotTransform[2] = slotRotation[2];
            slotTransform[3] = slotPosition;
        }

        vector muzzleStart = BDE_USL_GetProxyMuzzleStartOffset().Multiply4(slotTransform);
        vector muzzleEnd = BDE_USL_GetProxyMuzzleEndOffset().Multiply4(slotTransform);
        launchDirection = muzzleEnd - muzzleStart;

        float directionLength = launchDirection.Length();
        if (directionLength <= 0.001)
            return false;

        launchDirection = launchDirection * (1.0 / directionLength);

        launcherUp = slotTransform[1];
        float upLength = launcherUp.Length();
        if (upLength > 0.001)
            launcherUp = launcherUp * (1.0 / upLength);
        else
            launcherUp = vector.Up;

        vector cameraBasis[4];
        Math3D.DirectionAndUpMatrix(launchDirection, launcherUp, cameraBasis);
        vector offset = BDE_USL_GetAimCameraOffset();

        cameraPosition = muzzleStart;
        cameraPosition = cameraPosition + (cameraBasis[0] * offset[0]);
        cameraPosition = cameraPosition + (cameraBasis[1] * offset[1]);
        cameraPosition = cameraPosition + (cameraBasis[2] * offset[2]);

        return cameraPosition[0] == cameraPosition[0] && cameraPosition[1] == cameraPosition[1] && cameraPosition[2] == cameraPosition[2];
    }

    bool BDE_USL_GetAttachedAimCameraGeometry(out vector cameraPosition, out vector launchDirection)
    {
        vector launcherUp;
        return BDE_USL_CalculateAttachedAimCameraGeometry(cameraPosition, launchDirection, launcherUp);
    }

    bool BDE_USL_GetAttachedAimCameraGeometryEx(out vector cameraPosition, out vector launchDirection, out vector launcherUp)
    {
        return BDE_USL_CalculateAttachedAimCameraGeometry(cameraPosition, launchDirection, launcherUp);
    }

    bool BDE_USL_GetCurrentInventorySlotOffset(out vector slotPosition, out vector slotOrientation, out string slotName)
    {
        slotPosition = vector.Zero;
        slotOrientation = vector.Zero;
        slotName = "";

        int slotId;

        if (!GetInventory().GetCurrentAttachmentSlotInfo(slotId, slotName))
            return false;

        if (slotName == "")
            return false;

        string configPath = "CfgWeapons " + GetType() + " InventorySlotsOffsets " + slotName;

        array<float> positionValues = new array<float>;
        array<float> orientationValues = new array<float>;

        GetGame().ConfigGetFloatArray(configPath + " position", positionValues);
        GetGame().ConfigGetFloatArray(configPath + " orientation", orientationValues);

        if (positionValues.Count() >= 3)
            slotPosition = Vector(positionValues[0], positionValues[1], positionValues[2]);

        if (orientationValues.Count() >= 3)
            slotOrientation = Vector(orientationValues[0], orientationValues[1], orientationValues[2]);

        return true;
    }

    bool BDE_USL_GetAdjustedAttachmentTransform(out vector adjustedTransform[4])
    {
        // Use the rendered attachment frame without the legacy slot correction.
        GetRenderTransform(adjustedTransform);
        return true;
    }

    vector BDE_USL_LocalToWorld(vector localPosition)
    {
        vector transform[4];
        GetRenderTransform(transform);

        return localPosition.Multiply4(transform);
    }

    override bool ShootsExplosiveAmmo()
    {
        return true;
    }

    override RecoilBase SpawnRecoilObject()
    {
        return new M79Recoil(this);
    }

    override void OnDebugSpawn()
    {
        string debugAmmo = "Ammo_40mm_Explosive";

        if (IsKindOf("BDE_GP25"))
            debugAmmo = "Ammo_VOG25";

        SpawnAmmo(debugAmmo, SAMF_DEFAULT);

        if (IsKindOf("BDE_GP25") && !BDE_USL_HasLiveRound() && GetMuzzleCount() > 0)
        {
            if (!IsChamberEmpty(0))
            {
                float oldDamage;
                string oldAmmoType;
                PopCartridgeFromChamber(0, oldDamage, oldAmmoType);
            }

            if (PushCartridgeToChamber(0, 0.0, "Bullet_40mm_Explosive"))
            {
                RandomizeFSMState();
                BDE_USL_SyncChamberVisual();
                Synchronize();
                SetSynchDirty();
            }
        }

        EntityAI entity;
        if (Class.CastTo(entity, this))
        {
            entity.SpawnEntityOnGroundPos(debugAmmo, entity.GetPosition());
            entity.SpawnEntityOnGroundPos(debugAmmo, entity.GetPosition());
            entity.SpawnEntityOnGroundPos(debugAmmo, entity.GetPosition());
        }
    }

    bool BDE_USL_IsChamberAmmoAllowed(int muzzleIndex)
    {
        if (!IsKindOf("BDE_GP25"))
            return true;

        string magazineType = m_BDE_USL_LoadedMagazineSourceType;

        if (magazineType == "")
            magazineType = GetChamberedCartridgeMagazineTypeName(muzzleIndex);

        if (magazineType != "")
            return BDE_USL_SettingsManager.IsVOG25MagazineTypeAllowed(magazineType);

        float ammoDamage = 0.0;
        string ammoType = "";

        if (!GetCartridgeInfo(muzzleIndex, ammoDamage, ammoType))
            return false;

        return BDE_USL_SettingsManager.IsVOG25AmmoTypeAllowed(ammoType);
    }

    bool BDE_USL_HasLiveRound()
    {
        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex)
            return false;

        return IsChamberFull(muzzleIndex) && !IsChamberFiredOut(muzzleIndex);
    }

    string BDE_USL_GetHUDShortName()
    {
        if (IsKindOf("BDE_GP25"))
            return "GP25";

        return "M203";
    }

    string BDE_USL_GetHUDAmmoLabel()
    {
        if (!BDE_USL_HasLiveRound())
            return "";

        int muzzleIndex = 0;
        string magazineType = GetChamberedCartridgeMagazineTypeName(muzzleIndex);

        switch (magazineType)
        {
            case "Ammo_40mm_Explosive":
            case "Ammo_VOG25":
                return "(HE)";
            case "Ammo_40mm_ChemGas":
                return "(POX)";
            case "Ammo_40mm_Smoke_Red":
            case "Ammo_40mm_Smoke_Green":
            case "Ammo_40mm_Smoke_White":
            case "Ammo_40mm_Smoke_Black":
            case "Ammo_VOG25_Smoke_Red":
            case "Ammo_VOG25_Smoke_Green":
            case "Ammo_VOG25_Smoke_White":
            case "Ammo_VOG25_Smoke_Black":
                return "(SMK)";
            case "Ammo_40mm_Smoke_AirStrike":
                return "(STK)";
        }

        float ammoDamage;
        string ammoType;

        if (!GetCartridgeInfo(muzzleIndex, ammoDamage, ammoType))
            return "";

        switch (ammoType)
        {
            case "Bullet_40mm_Explosive":
            case "Bullet_VOG25":
                return "(HE)";
            case "Bullet_40mm_ChemGas":
                return "(POX)";
            case "Bullet_40mm_Smoke_Red":
            case "Bullet_40mm_Smoke_Green":
            case "Bullet_40mm_Smoke_White":
            case "Bullet_40mm_Smoke_Black":
                return "(SMK)";
        }

        return "";
    }

    protected string BDE_USL_GetMagazineTypeForAmmo(string ammoType)
    {
        switch (ammoType)
        {
            case "Bullet_40mm_Explosive":
                return "Ammo_40mm_Explosive";
            case "Bullet_VOG25":
                return "Ammo_VOG25";
            case "Bullet_40mm_ChemGas":
                return "Ammo_40mm_ChemGas";
            case "Bullet_40mm_Smoke_Red":
                return "Ammo_40mm_Smoke_Red";
            case "Bullet_40mm_Smoke_Green":
                return "Ammo_40mm_Smoke_Green";
            case "Bullet_40mm_Smoke_White":
                return "Ammo_40mm_Smoke_White";
            case "Bullet_40mm_Smoke_Black":
                return "Ammo_40mm_Smoke_Black";
        }

        return "";
    }

    bool BDE_USL_IsRoundAllowed(Magazine source)
    {
        if (!source || !source.IsKindOf("Ammo_40mm_Base"))
            return false;

        return !source.IsKindOf("Ammo_VOG25");
    }

    bool BDE_USL_CanDirectLoadRound(Magazine source, bool reservationCheck = true)
    {
        if (!BDE_USL_IsRoundAllowed(source))
            return false;

        if (IsRuined() || source.IsRuined() || source.IsSetForDeletion() || source.GetAmmoCount() <= 0)
            return false;

        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex)
            return false;

        if (!IsChamberEmpty(muzzleIndex) && !IsChamberFiredOut(muzzleIndex))
            return false;

        PlayerBase launcherPlayer = PlayerBase.Cast(GetHierarchyRootPlayer());
        PlayerBase sourcePlayer = PlayerBase.Cast(source.GetHierarchyRootPlayer());

        if (!launcherPlayer)
            return false;

        if (sourcePlayer && sourcePlayer != launcherPlayer)
            return false;

        if (!sourcePlayer && vector.Distance(source.GetPosition(), launcherPlayer.GetPosition()) > 3.0)
            return false;

        if (reservationCheck && GetInventory().HasInventoryReservation(this, null))
            return false;

        if (reservationCheck && source.GetInventory().HasInventoryReservation(source, null))
            return false;

        if (IsChamberFiredOut(muzzleIndex))
            return true;

        if (IsKindOf("BDE_GP25") && source.IsKindOf("Ammo_VOG25"))
            return true;

        if (IsKindOf("BDE_GP25") && GetType() != "BDE_GP25")
            return true;

        return CanChamberBullet(muzzleIndex, source);
    }

    protected void BDE_USL_ClearGroundRoundReservation()
    {
        m_BDE_USL_HasReservedGroundRound = false;
        m_BDE_USL_ReservedGroundMagazineType = "";
        m_BDE_USL_ReservedGroundAmmoType = "";
        m_BDE_USL_ReservedGroundAmmoDamage = 0.0;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(BDE_USL_ServerExpireGroundRoundReservation);
    }

    protected bool BDE_USL_ServerRefundGroundRoundReservation()
    {
        if (!GetGame().IsServer() || !m_BDE_USL_HasReservedGroundRound || m_BDE_USL_ReservedGroundMagazineType == "")
            return false;

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
        vector refundPosition = GetPosition();

        if (player)
            refundPosition = player.GetPosition() + "0 0.15 0";

        int spawnFlags = ECE_CREATEPHYSICS | ECE_KEEPHEIGHT | ECE_NOSURFACEALIGN | ECE_DYNAMIC_PERSISTENCY;
        Magazine refund = Magazine.Cast(GetGame().CreateObjectEx(m_BDE_USL_ReservedGroundMagazineType, refundPosition, spawnFlags));

        if (!refund)
            return false;

        refund.ServerSetAmmoCount(0);
        refund.SetHealth("", "", (1.0 - m_BDE_USL_ReservedGroundAmmoDamage) * refund.GetMaxHealth());

        if (!refund.ServerStoreCartridge(m_BDE_USL_ReservedGroundAmmoDamage, m_BDE_USL_ReservedGroundAmmoType))
        {
            refund.ServerSetAmmoCount(1);
        }

        refund.SetSynchDirty();
        BDE_USL_ClearGroundRoundReservation();
        return true;
    }

    protected void BDE_USL_ServerExpireGroundRoundReservation()
    {
        if (!GetGame().IsServer() || !m_BDE_USL_HasReservedGroundRound)
            return;

        BDE_USL_ServerRefundGroundRoundReservation();
    }

    void BDE_USL_ClientReserveGroundRound(Magazine source)
    {
        if (!GetGame().IsClient() || !source)
            return;

        Param1<EntityAI> reserveData = new Param1<EntityAI>(source);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_RESERVE_GROUND_ROUND, reserveData, true);
    }

    protected bool BDE_USL_ServerReserveGroundRound(PlayerIdentity sender, Magazine source)
    {
        if (!GetGame().IsServer() || !source || m_BDE_USL_HasReservedGroundRound || m_BDE_USL_ManipulationActive)
            return false;

        PlayerBase player;

        if (!BDE_USL_ValidateSpecificLoadOwner(sender, player))
            return false;

        InventoryLocation sourceLocation = new InventoryLocation();

        if (!source.GetInventory().GetCurrentInventoryLocation(sourceLocation) || sourceLocation.GetType() != InventoryLocationType.GROUND)
            return false;

        if (vector.Distance(source.GetPosition(), player.GetPosition()) > 3.0 || !BDE_USL_CanDirectLoadRound(source, false))
            return false;

        string sourceMagazineType = source.GetType();
        float ammoDamage;
        string ammoType;
        bool isVOG = source.IsKindOf("Ammo_VOG25");

        if (isVOG)
        {
            if (source.GetAmmoCount() <= 0)
                return false;

            ammoDamage = 0.0;
            GetGame().ConfigGetText("CfgMagazines " + source.GetType() + " ammo", ammoType);

            if (ammoType == "")
                return false;

            source.ServerSetAmmoCount(source.GetAmmoCount() - 1);
        }
        else if (!source.ServerAcquireCartridge(ammoDamage, ammoType))
        {
            return false;
        }

        m_BDE_USL_HasReservedGroundRound = true;
        m_BDE_USL_ReservedGroundMagazineType = sourceMagazineType;
        m_BDE_USL_ReservedGroundAmmoType = ammoType;
        m_BDE_USL_ReservedGroundAmmoDamage = ammoDamage;

        if (source.GetAmmoCount() <= 0)
            source.DeleteSafe();
        else
            source.SetSynchDirty();

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerExpireGroundRoundReservation, BDE_USL_GROUND_ROUND_RESERVATION_TIMEOUT_MS, false);
        return true;
    }

    protected bool BDE_USL_ServerLoadReservedGroundRound()
    {
        if (!GetGame().IsServer() || !m_BDE_USL_HasReservedGroundRound || m_BDE_USL_ReservedGroundAmmoType == "")
            return false;

        BDE_M203 m203 = BDE_M203.Cast(this);

        if (m203 && !m203.BDE_M203_HasUsableBarrel())
            return false;

        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex || BDE_USL_HasLiveRound())
            return false;

        bool hadFiredOut = IsChamberFiredOut(muzzleIndex);
        float spentDamage;
        string spentType;

        if (hadFiredOut && !PopCartridgeFromChamber(muzzleIndex, spentDamage, spentType))
            return false;

        if (!PushCartridgeToChamber(muzzleIndex, m_BDE_USL_ReservedGroundAmmoDamage, m_BDE_USL_ReservedGroundAmmoType))
        {
            if (hadFiredOut)
                PushCartridgeToChamber(muzzleIndex, spentDamage, spentType);

            return false;
        }

        string sourceType = m_BDE_USL_ReservedGroundMagazineType;
        BDE_USL_ClearGroundRoundReservation();
        BDE_USL_SetLoadedMagazineSourceType(sourceType);

        if (IsKindOf("BDE_GP25") && !Weapon_Base.Cast(GetHierarchyParent()))
            RandomizeFSMState();

        BDE_USL_SyncChamberVisual();
        Synchronize();
        SetSynchDirty();
        return true;
    }

    bool BDE_USL_ServerLoadSpecificRound(Magazine source)
    {
        if (!GetGame().IsServer() || !BDE_USL_CanDirectLoadRound(source, false))
            return false;

        string loadedMagazineSourceType = source.GetType();
        float ammoDamage;
        string ammoType;
        bool manuallyAcquiredVOG = false;
        bool isVOG = source.IsKindOf("Ammo_VOG25");

        if (isVOG)
        {
            if (source.GetAmmoCount() <= 0)
                return false;

            ammoDamage = 0.0;
            GetGame().ConfigGetText("CfgMagazines " + source.GetType() + " ammo", ammoType);

            if (ammoType == "")
                return false;

            source.ServerSetAmmoCount(source.GetAmmoCount() - 1);
            manuallyAcquiredVOG = true;
        }
        else if (!source.ServerAcquireCartridge(ammoDamage, ammoType))
        {
            return false;
        }

        int muzzleIndex = 0;
        bool hadFiredOut = IsChamberFiredOut(muzzleIndex);
        float spentDamage;
        string spentType;

        if (hadFiredOut && !PopCartridgeFromChamber(muzzleIndex, spentDamage, spentType))
        {
            if (manuallyAcquiredVOG)
                source.ServerSetAmmoCount(source.GetAmmoCount() + 1);
            else
                source.ServerStoreCartridge(ammoDamage, ammoType);

            return false;
        }

        if (!PushCartridgeToChamber(muzzleIndex, ammoDamage, ammoType))
        {
            if (hadFiredOut)
                PushCartridgeToChamber(muzzleIndex, spentDamage, spentType);

            if (manuallyAcquiredVOG)
                source.ServerSetAmmoCount(source.GetAmmoCount() + 1);
            else
                source.ServerStoreCartridge(ammoDamage, ammoType);

            return false;
        }

        if (source.GetAmmoCount() <= 0)
            source.DeleteSafe();
        else
            source.SetSynchDirty();

        BDE_USL_SetLoadedMagazineSourceType(loadedMagazineSourceType);

        if (IsKindOf("BDE_GP25") && !Weapon_Base.Cast(GetHierarchyParent()))
            RandomizeFSMState();

        BDE_USL_SyncChamberVisual();
        Synchronize();
        SetSynchDirty();

        return true;
    }

    protected Magazine BDE_USL_FindInventoryRound(PlayerBase player)
    {
        if (!player)
            return null;

        array<EntityAI> items = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            Magazine source = Magazine.Cast(item);

            if (!BDE_USL_IsRoundAllowed(source))
                continue;

            if (source.IsRuined() || source.IsSetForDeletion() || source.GetAmmoCount() <= 0)
                continue;

            return source;
        }

        return null;
    }

    Magazine BDE_USL_FindInventoryRoundForManipulation(PlayerBase player)
    {
        return BDE_USL_FindInventoryRound(player);
    }

    bool BDE_USL_ShouldUseAttachedCustomAnimation()
    {
        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!host)
            return false;

        string configKey = "";

        if (IsKindOf("BDE_GP25"))
            configKey = "BDE_USL_GP25CustomReloadAnimation";
        else if (IsKindOf("BDE_M203"))
            configKey = "BDE_USL_M203CustomReloadAnimation";
        else
            return false;

        string path = "CfgWeapons " + host.GetType() + " " + configKey;

        if (!GetGame().ConfigIsExisting(path))
            return false;

        return GetGame().ConfigGetInt(path) == 1;
    }

    bool BDE_USL_ShouldUseCustomManipulationAnimation()
    {
        if (IsKindOf("BDE_GP25") && !Weapon_Base.Cast(GetHierarchyParent()))
            return GetType() == "BDE_GP25";

        return BDE_USL_ShouldUseAttachedCustomAnimation();
    }

    bool BDE_USL_ShouldUseAttachedM203Animation()
    {
        return IsKindOf("BDE_M203") && BDE_USL_ShouldUseAttachedCustomAnimation();
    }

    bool BDE_USL_IsManipulationActive()
    {
        return m_BDE_USL_ManipulationActive;
    }

    void BDE_USL_SetManipulationActive(bool active)
    {
        m_BDE_USL_ManipulationActive = active;
    }

    bool BDE_USL_ServerUnload(PlayerBase player)
    {
        if (!GetGame().IsServer() || !player)
            return false;

        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex || IsChamberEmpty(muzzleIndex))
            return false;

        bool firedOut = IsChamberFiredOut(muzzleIndex);
        string magazineType = m_BDE_USL_LoadedMagazineSourceType;

        if (magazineType == "")
            magazineType = GetChamberedCartridgeMagazineTypeName(muzzleIndex);
        float ammoDamage;
        string ammoType;

        if (!PopCartridgeFromChamber(muzzleIndex, ammoDamage, ammoType))
            return false;

        if (!firedOut)
        {
            if (magazineType == "")
                magazineType = BDE_USL_GetMagazineTypeForAmmo(ammoType);

            if (magazineType == "" || !DayZPlayerUtils.HandleStoreCartridge(player, this, muzzleIndex, ammoDamage, ammoType, magazineType))
            {
                PushCartridgeToChamber(muzzleIndex, ammoDamage, ammoType);
                return false;
            }
        }

        BDE_USL_SetLoadedMagazineSourceType("");

        if (GetType() == "BDE_GP25" && !Weapon_Base.Cast(GetHierarchyParent()))
            RandomizeFSMState();

        BDE_USL_SyncChamberVisual();
        Synchronize();
        SetSynchDirty();
        return true;
    }

    bool BDE_USL_ServerReload(PlayerBase player)
    {
        if (!GetGame().IsServer() || !player)
            return false;

        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex)
            return false;

        if (BDE_USL_HasLiveRound())
            return false;

        Magazine source = BDE_USL_FindInventoryRound(player);

        if (!source)
            return false;

        if (IsChamberFiredOut(muzzleIndex))
        {
            float spentDamage;
            string spentType;

            if (!PopCartridgeFromChamber(muzzleIndex, spentDamage, spentType))
                return false;
        }

        return BDE_USL_ServerLoadSpecificRound(source);
    }

    void BDE_USL_ClientPlayDryFire(PlayerBase player)
    {
        if (!GetGame().IsClient())
            return;

        if (!player || GetGame().GetPlayer() != player)
            return;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (!host || player.GetItemInHands() != host)
            return;

        int now = GetGame().GetTime();

        if (m_BDE_USL_LastDryFireTime > 0 && now - m_BDE_USL_LastDryFireTime < 150)
            return;

        m_BDE_USL_LastDryFireTime = now;
        HumanCommandWeapons weaponCommand = player.GetCommandModifier_Weapons();

        if (!weaponCommand)
            return;

        if (weaponCommand.GetRunningAction() != -1 && !weaponCommand.IsActionFinished())
            return;

        DryFire(GetCurrentMuzzle());

        int dryFireActionType = GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY);
        weaponCommand.StartAction(WeaponActions.FIRE, dryFireActionType);
    }

    protected void BDE_USL_PlayEnvironmentSound(string soundSet, vector position)
    {
        EffectSound sound = SEffectManager.PlaySoundEnviroment(soundSet, position);

        if (sound)
            sound.SetAutodestroy(true);
    }

    void BDE_USL_PlayAttachedFireFX(vector muzzlePosition, vector shotDirection)
    {
        if (GetGame().IsDedicatedServer())
            return;

        BDE_USL_PlayEnvironmentSound("BDE_USL_AttachedShot_Exterior_SoundSet", muzzlePosition);
        BDE_USL_PlayEnvironmentSound("BDE_USL_AttachedShot_Interior_SoundSet", muzzlePosition);
        BDE_USL_PlayEnvironmentSound("BDE_USL_AttachedTail_Exterior_SoundSet", muzzlePosition);
        BDE_USL_PlayEnvironmentSound("BDE_USL_AttachedTail_Interior_SoundSet", muzzlePosition);
        BDE_USL_PlayEnvironmentSound("BDE_USL_AttachedSlapback_SoundSet", muzzlePosition);
        BDE_USL_PlayEnvironmentSound("BDE_USL_AttachedTail2D_SoundSet", muzzlePosition);

        int muzzleParticleId = ParticleList.GetParticleIDByName("weapon_shot_mosin9130_01");

        if (muzzleParticleId <= 0)
            muzzleParticleId = ParticleList.GUN_IZH18;

        Particle muzzleParticle = ParticleManager.GetInstance().PlayInWorld(muzzleParticleId, muzzlePosition);

        if (muzzleParticle)
        {
            vector particleOrientation = shotDirection.VectorToAngles();
            particleOrientation[0] = particleOrientation[0] + 90.0;
            muzzleParticle.SetOrientation(particleOrientation);
        }
    }

    protected bool BDE_USL_IsSmokeRound(string ammoType)
    {
        return ammoType == "Bullet_40mm_Smoke_Red" || ammoType == "Bullet_40mm_Smoke_Green" || ammoType == "Bullet_40mm_Smoke_White" || ammoType == "Bullet_40mm_Smoke_Black";
    }

    protected void BDE_USL_ReplayRemoteSmoke(int muzzleIndex, string ammoType, vector projectilePosition, vector shotDirection, vector inheritedVelocity, int shotId)
    {
        // Direct Fire bypasses the normal remote weapon event. SmokeSimulation
        // is local to the native projectile, so spectators need that event too.
        if (!GetGame().IsClient() || GetGame().IsServer() || !BDE_USL_IsSmokeRound(ammoType))
            return;

        PlayerBase owner = PlayerBase.Cast(GetHierarchyRootPlayer());
        if (!owner || owner == GetGame().GetPlayer() || shotId == m_BDE_USL_LastRemoteSmokeShot)
            return;

        if (muzzleIndex < 0 || muzzleIndex >= GetMuzzleCount())
            return;

        m_BDE_USL_LastRemoteSmokeShot = shotId;
        bool wasEmpty = IsChamberEmpty(muzzleIndex);
        bool wasSpent = IsChamberFiredOut(muzzleIndex);
        float savedDamage;
        string savedAmmo;

        if (!wasEmpty && !PopCartridgeFromChamber(muzzleIndex, savedDamage, savedAmmo))
            return;

        bool fired = false;
        if (PushCartridgeToChamber(muzzleIndex, 0.0, ammoType))
            fired = Fire(muzzleIndex, projectilePosition, shotDirection, inheritedVelocity);

        // A successful Fire leaves the spent case. Preserve that state when the
        // server's spent-case update arrived first; otherwise restore the snapshot.
        if (!wasSpent || !fired)
        {
            float discardDamage;
            string discardAmmo;
            if (!IsChamberEmpty(muzzleIndex))
                PopCartridgeFromChamber(muzzleIndex, discardDamage, discardAmmo);

            if (!wasEmpty && !wasSpent)
                PushCartridgeToChamber(muzzleIndex, savedDamage, savedAmmo);
        }

        BDE_USL_QueueChamberVisualRefresh();
        Print("[BDE USL Smoke] remote replay shot=" + shotId.ToString() + " ammo=" + ammoType + " fired=" + fired.ToString());
    }

    protected void BDE_USL_ServerBroadcastAttachedFireFX(PlayerIdentity shooter, vector muzzlePosition, vector shotDirection, int shotId, int muzzleIndex, string ammoType, vector projectilePosition, vector inheritedVelocity)
    {
        if (!GetGame().IsServer())
            return;

        string shooterId = "";
        if (shooter)
            shooterId = shooter.GetId();

        Param4<vector, vector, string, int> fxData = new Param4<vector, vector, string, int>(muzzlePosition, shotDirection, shooterId, shotId);
        Param4<int, string, vector, vector> projectileData = new Param4<int, string, vector, vector>(muzzleIndex, ammoType, projectilePosition, inheritedVelocity);
        ScriptRPC rpc = new ScriptRPC;
        rpc.Write(fxData);
        rpc.Write(projectileData);
        rpc.Send(this, BDE_USL_RPC.BDE_USL_RPC_FIRE_FX, true, NULL);

        if (BDE_USL_IsSmokeRound(ammoType))
            Print("[BDE USL Smoke] server confirmed shot=" + shotId.ToString() + " ammo=" + ammoType);
    }

    bool BDE_USL_CanFireAttachedFromHost(Weapon_Base host)
    {
        if (IsRuined())
            return false;

        return true;
    }

    bool BDE_USL_ClientFireAttachedFromHost(Weapon_Base host, PlayerBase player)
    {
        if (!GetGame().IsClient() || !host || !player)
            return false;

        if (GetGame().GetPlayer() != player || player.GetItemInHands() != host)
            return false;

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
        if (!player.BDE_USL_NinjinsCanFire())
            return false;
#endif

        if (host.BDE_USL_GetLauncher() != this || !host.BDE_USL_IsLauncherModeSelected())
            return false;

        if (!BDE_USL_CanFireAttachedFromHost(host))
        {
            BDE_USL_ClientPlayDryFire(player);
            return false;
        }

        if (m_BDE_USL_ManipulationActive)
            return false;

        int muzzleIndex = GetCurrentMuzzle();

        if (muzzleIndex < 0 || muzzleIndex >= GetMuzzleCount())
            return false;

        if (IsChamberEmpty(muzzleIndex) || IsChamberFiredOut(muzzleIndex) || !CanFire(muzzleIndex) || !BDE_USL_IsChamberAmmoAllowed(muzzleIndex))
        {
            BDE_USL_ClientPlayDryFire(player);
            return false;
        }

        vector muzzleStart;
        vector muzzleEnd;

        if (!BDE_USL_GetProxyMuzzlePositions(muzzleStart, muzzleEnd))
        {
            return false;
        }

        vector shotDirection = muzzleEnd - muzzleStart;
        float directionLength = shotDirection.Length();

        if (directionLength <= 0.001)
        {
            return false;
        }

        shotDirection = shotDirection * (1.0 / directionLength);
        vector muzzlePosition = muzzleEnd;
        float projectileClearance = host.BDE_USL_GetProjectileSpawnClearance();
        vector projectilePosition = muzzlePosition + (shotDirection * projectileClearance);
        vector inheritedVelocity = GetVelocity(player);

        float chamberDamage = 0.0;
        string chamberAmmoType = "";
        GetCartridgeInfo(muzzleIndex, chamberDamage, chamberAmmoType);

        int shotId = GetGame().GetTime();
        float launchSpeed = GetGame().ConfigGetFloat("CfgAmmo " + chamberAmmoType + " initSpeed") * GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " initSpeedMultiplier");
        GetGame().BDE_USL_RegisterTerminal40mmShot(this, chamberAmmoType, projectilePosition, shotDirection, inheritedVelocity, launchSpeed, shotId);
        GetGame().BDE_USL_RegisterClient40mmFireSource(this, chamberAmmoType, muzzlePosition, shotDirection, shotId);

        BDE_USL_ClientRequestAttachedFire(muzzleIndex, muzzlePosition, shotDirection, inheritedVelocity, shotId);

        bool clientFired = Fire(muzzleIndex, projectilePosition, shotDirection, inheritedVelocity);
        GetGame().BDE_USL_MarkTerminal40mmFireResult(shotId, this, chamberAmmoType, clientFired);

        if (clientFired)
        {
            OnFire(muzzleIndex);

            if (host == this)
                RandomizeFSMState();

            DayZPlayerImplement playerImplement = player;

            if (playerImplement)
                playerImplement.GetAimingModel().SetRecoil(this);
        }
        else
        {
            GetGame().BDE_USL_CancelClient40mmFireSource(shotId);
            GetGame().BDE_USL_CancelTerminal40mmShot(shotId, this, chamberAmmoType);
        }

        return clientFired;
    }

    void BDE_USL_ClientRequestAttachedFire(int muzzleIndex, vector firePosition, vector shotDirection, vector inheritedVelocity, int shotId)
    {
        if (!GetGame().IsClient())
            return;

        Param5<int, vector, vector, vector, int> data = new Param5<int, vector, vector, vector, int>(muzzleIndex, firePosition, shotDirection, inheritedVelocity, shotId);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_FIRE_ATTACHED, data, true);
    }

    protected bool BDE_USL_ValidateAttachedFireOwner(PlayerIdentity sender, out PlayerBase player, out Weapon_Base host)
    {
        player = PlayerBase.Cast(GetHierarchyRootPlayer());
        host = Weapon_Base.Cast(GetHierarchyParent());

        // A handheld GP25 is its own host, as on the client fire path.
        if (!host && player && GetType() == "BDE_GP25" && player.GetItemInHands() == this)
            host = this;

        if (!sender || !player || !host)
            return false;

        PlayerIdentity identity = player.GetIdentity();

        if (!identity || identity.GetId() != sender.GetId())
            return false;

        return player.GetItemInHands() == host && host.BDE_USL_IsLauncherModeSelected() && host.BDE_USL_GetLauncher() == this;
    }

    protected void BDE_USL_ServerFireAttached(PlayerIdentity sender, int muzzleIndex, vector muzzlePosition, vector shotDirection, vector clientInheritedVelocity, int shotId)
    {
        if (!GetGame().IsServer())
            return;

        PlayerBase player;
        Weapon_Base host;

        if (!BDE_USL_ValidateAttachedFireOwner(sender, player, host))
            return;

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
        if (!player.BDE_USL_NinjinsCanFire())
            return;
#endif

        if (!BDE_USL_CanFireAttachedFromHost(host))
            return;

        if (m_BDE_USL_ManipulationActive)
            return;

        if (muzzleIndex < 0 || muzzleIndex >= GetMuzzleCount())
            return;

        if (IsChamberEmpty(muzzleIndex) || IsChamberFiredOut(muzzleIndex) || !CanFire(muzzleIndex) || !BDE_USL_IsChamberAmmoAllowed(muzzleIndex))
            return;

        if (vector.Distance(muzzlePosition, player.GetPosition()) > 3.0)
        {
            return;
        }

        float directionLength = shotDirection.Length();

        if (directionLength <= 0.001)
            return;

        shotDirection = shotDirection * (1.0 / directionLength);
        float projectileClearance = host.BDE_USL_GetProjectileSpawnClearance();
        vector projectilePosition = muzzlePosition + (shotDirection * projectileClearance);

        vector serverInheritedVelocity = GetVelocity(player);
        vector inheritedVelocity = serverInheritedVelocity;
        float inheritedVelocityDelta = vector.Distance(clientInheritedVelocity, serverInheritedVelocity);

        if (inheritedVelocityDelta <= 5.0)
            inheritedVelocity = clientInheritedVelocity;

        float chamberDamage = 0.0;
        string chamberAmmoType = "";
        GetCartridgeInfo(muzzleIndex, chamberDamage, chamberAmmoType);

        float launchSpeed = GetGame().ConfigGetFloat("CfgAmmo " + chamberAmmoType + " initSpeed") * GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " initSpeedMultiplier");
        GetGame().BDE_USL_RegisterTerminal40mmShot(this, chamberAmmoType, projectilePosition, shotDirection, inheritedVelocity, launchSpeed, shotId);

        float healthBeforeShot = GetHealth("", "Health");
        bool serverFired = Fire(muzzleIndex, projectilePosition, shotDirection, inheritedVelocity);
        BDE_USL_ShotWear.Apply(this, serverFired, healthBeforeShot, shotId);
        GetGame().BDE_USL_MarkTerminal40mmFireResult(shotId, this, chamberAmmoType, serverFired);

        if (!serverFired)
            GetGame().BDE_USL_CancelTerminal40mmShot(shotId, this, chamberAmmoType);

        if (serverFired)
        {
            OnFire(muzzleIndex);

            if (host == this)
                RandomizeFSMState();

            Synchronize();
            SetSynchDirty();

            BDE_USL_ServerBroadcastAttachedFireFX(sender, muzzlePosition, shotDirection, shotId, muzzleIndex, chamberAmmoType, projectilePosition, inheritedVelocity);
        }
    }

    void BDE_USL_ClientRequestLoadSpecificRound(Magazine source)
    {
        if (!GetGame().IsClient() || !source)
            return;

        Param1<EntityAI> data = new Param1<EntityAI>(source);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_LOAD_SPECIFIC, data, true);
    }

    protected bool BDE_USL_ValidateSpecificLoadOwner(PlayerIdentity sender, out PlayerBase player)
    {
        player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (!sender || !player)
            return false;

        PlayerIdentity identity = player.GetIdentity();

        if (!identity || identity.GetId() != sender.GetId())
            return false;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host)
            return player.GetItemInHands() == host && host.BDE_USL_GetLauncher() == this;

        return IsKindOf("BDE_GP25") && player.GetItemInHands() == this;
    }

    protected void BDE_USL_ApplyEjectedRoundDropPhysics(ItemBase looseRound)
    {
        if (!GetGame().IsServer() || !looseRound || looseRound.IsSetForDeletion())
            return;

        if (looseRound.GetHierarchyParent())
            return;

        // Activate after deferred inventory initialization, which can reset the body.
        looseRound.CreateDynamicPhysics(PhxInteractionLayers.DYNAMICITEM_NOCHAR);
        looseRound.ThrowPhysically(null, Vector(0.0, -BDE_USL_M203_EJECT_DROP_FORCE, 0.0), false);

        if (dBodyIsSet(looseRound))
        {
            dBodyDynamic(looseRound, true);
            dBodyEnableGravity(looseRound, true);
            dBodyActive(looseRound, ActiveState.ACTIVE);
        }
    }

    protected bool BDE_USL_ServerSpawnEjectedRound(string typeName, vector position, vector boreDirection, bool firedOut, float ammoDamage = 0.0, string ammoType = "")
    {
        if (!GetGame().IsServer() || typeName == "")
            return false;

        int spawnFlags = ECE_CREATEPHYSICS | ECE_KEEPHEIGHT | ECE_NOSURFACEALIGN | ECE_DYNAMIC_PERSISTENCY;
        Object looseObject = GetGame().CreateObjectEx(typeName, position, spawnFlags);
        ItemBase looseRound = ItemBase.Cast(looseObject);

        if (!looseRound)
        {
            if (looseObject)
                GetGame().ObjectDelete(looseObject);

            return false;
        }

        if (boreDirection.LengthSq() > 0.000001)
        {
            boreDirection.Normalize();
            vector upReference = vector.Up;

            if (Math.AbsFloat(vector.Dot(boreDirection, upReference)) > 0.98)
                upReference = "0 0 1";

            vector boreBasis[4];
            Math3D.DirectionAndUpMatrix(boreDirection, upReference, boreBasis);

            vector roundTransform[4];
            roundTransform[0] = boreBasis[0];
            roundTransform[1] = boreBasis[2];
            roundTransform[2] = boreBasis[1] * -1.0;
            roundTransform[3] = position;
            looseRound.SetTransform(roundTransform);
        }
        else
        {
            looseRound.SetPosition(position);
        }

        if (!firedOut)
        {
            Magazine looseMagazine = Magazine.Cast(looseRound);

            if (!looseMagazine)
            {
                GetGame().ObjectDelete(looseRound);
                return false;
            }

            looseMagazine.ServerSetAmmoCount(0);
            looseMagazine.SetHealth("", "", (1.0 - ammoDamage) * looseMagazine.GetMaxHealth());

            if (!looseMagazine.ServerStoreCartridge(ammoDamage, ammoType))
            {
                GetGame().ObjectDelete(looseRound);
                return false;
            }
        }

        if (dBodyIsSet(looseRound))
        {
            dBodySetInteractionLayer(looseRound, PhxInteractionLayers.DYNAMICITEM_NOCHAR);
            dBodyDynamic(looseRound, true);
            dBodyActive(looseRound, ActiveState.ACTIVE);
        }

        PlayerBase ejectedSourcePlayer = PlayerBase.Cast(GetHierarchyRootPlayer());
        Ammo_40mm_Base looseLiveRound = Ammo_40mm_Base.Cast(looseRound);

        if (looseLiveRound)
            looseLiveRound.BDE_USL_MarkEjectedForPhysicsSleep(ejectedSourcePlayer);
        else
        {
            Ammo_40mm_Empty looseEmptyCase = Ammo_40mm_Empty.Cast(looseRound);

            if (looseEmptyCase)
                looseEmptyCase.BDE_USL_MarkEjectedForPhysicsSleep(ejectedSourcePlayer);
        }

        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(BDE_USL_ApplyEjectedRoundDropPhysics, BDE_USL_M203_EJECT_PHYSICS_DELAY_MS, false, looseRound);
        looseRound.SetSynchDirty();
        return true;
    }

    void BDE_USL_ClientRequestManipulationEject(int actionType, vector ejectPosition, vector ejectDirection)
    {
        if (!GetGame().IsClient())
            return;

        Param3<int, vector, vector> data = new Param3<int, vector, vector>(actionType, ejectPosition, ejectDirection);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_MANIPULATION_EJECT, data, true);
    }

    protected void BDE_USL_ServerHandleManipulationEject(PlayerIdentity sender, int actionType, vector ejectPosition, vector ejectDirection)
    {
        if (!GetGame().IsServer() || !m_BDE_USL_ManipulationActive || m_BDE_USL_ServerEjectHandled)
            return;

        if (actionType != m_BDE_USL_ServerManipulationAction)
            return;

        PlayerBase player;

        if (!BDE_USL_ValidateManipulationOwner(sender, player))
            return;

        if (player != m_BDE_USL_PendingManipulationPlayer)
            return;

        if (vector.Distance(ejectPosition, player.GetPosition()) > 3.0)
            return;

        if (ejectDirection.LengthSq() < 0.000001)
            return;

        ejectDirection.Normalize();

        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex || IsChamberEmpty(muzzleIndex))
            return;

        bool firedOut = IsChamberFiredOut(muzzleIndex);
        bool isGP25 = IsKindOf("BDE_GP25");

        if (actionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD)
        {
            if (!firedOut || isGP25)
                return;
        }

        string magazineType = m_BDE_USL_LoadedMagazineSourceType;

        if (magazineType == "")
            magazineType = GetChamberedCartridgeMagazineTypeName(muzzleIndex);

        float ammoDamage;
        string ammoType;

        if (!PopCartridgeFromChamber(muzzleIndex, ammoDamage, ammoType))
            return;

        m_BDE_USL_ServerEjectHandled = true;

        string looseType = "";

        if (!firedOut)
        {
            looseType = magazineType;

            if (looseType == "")
                looseType = BDE_USL_GetMagazineTypeForAmmo(ammoType);
        }
        else if (!isGP25)
        {
            looseType = "Ammo_40mm_Empty";
        }

        if (looseType != "")
            BDE_USL_ServerSpawnEjectedRound(looseType, ejectPosition, ejectDirection, firedOut, ammoDamage, ammoType);

        BDE_USL_SetLoadedMagazineSourceType("");

        if (GetType() == "BDE_GP25" && !Weapon_Base.Cast(GetHierarchyParent()))
            RandomizeFSMState();

        BDE_USL_SyncChamberVisual();
        Synchronize();
        SetSynchDirty();
    }

    protected void BDE_USL_ServerClearGP25FiredOutAtUnloadFrame()
    {
        if (!GetGame().IsServer() || !m_BDE_USL_ManipulationActive || !IsKindOf("BDE_GP25"))
            return;

        if (m_BDE_USL_ServerManipulationAction != BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
            return;

        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex || IsChamberEmpty(muzzleIndex) || !IsChamberFiredOut(muzzleIndex))
            return;

        float spentDamage;
        string spentType;

        if (!PopCartridgeFromChamber(muzzleIndex, spentDamage, spentType))
            return;

        m_BDE_USL_ServerEjectHandled = true;
        BDE_USL_SetLoadedMagazineSourceType("");

        if (GetType() == "BDE_GP25" && !Weapon_Base.Cast(GetHierarchyParent()))
            RandomizeFSMState();

        BDE_USL_SyncChamberVisual();
        Synchronize();
        SetSynchDirty();
    }

    protected void BDE_USL_ServerSetM203TubeOpen(bool open)
    {
        if (!GetGame().IsServer() || !m_BDE_USL_ManipulationActive)
            return;

        BDE_M203 m203 = BDE_M203.Cast(this);

        if (m203)
            m203.BDE_M203_SetTubeOpen(open);
    }

    protected void BDE_USL_ServerCompleteTimedReload()
    {
        if (!GetGame().IsServer() || !m_BDE_USL_ManipulationActive)
            return;

        if (m_BDE_USL_ServerManipulationAction != BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD)
            return;

        BDE_M203 m203 = BDE_M203.Cast(this);

        if (m203)
            m203.BDE_M203_SetTubeOpen(false);

        PlayerBase player = m_BDE_USL_PendingManipulationPlayer;

        if (!player)
            return;

        if (m_BDE_USL_HasReservedGroundRound)
        {
            BDE_USL_ServerLoadReservedGroundRound();
            return;
        }

        Magazine source = m_BDE_USL_PendingReloadSource;

        if (!source || source.IsSetForDeletion() || source.GetAmmoCount() <= 0)
            return;

        if (!BDE_USL_CanDirectLoadRound(source, false))
            return;

        BDE_USL_ServerLoadSpecificRound(source);
    }

    protected void BDE_USL_ServerFinishTimedManipulation()
    {
        if (!GetGame().IsServer())
            return;

        BDE_M203 m203 = BDE_M203.Cast(this);

        if (m203)
            m203.BDE_M203_SetTubeOpen(false);

        if (m_BDE_USL_HasReservedGroundRound)
            BDE_USL_ServerRefundGroundRoundReservation();

        m_BDE_USL_ManipulationActive = false;
        m_BDE_USL_ServerManipulationAction = BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_NONE;
        m_BDE_USL_PendingReloadSource = null;
        m_BDE_USL_PendingManipulationPlayer = null;
        m_BDE_USL_ServerEjectHandled = false;
    }

    protected bool BDE_USL_ServerStartTimedManipulation(PlayerIdentity sender, PlayerBase player, int actionType, Magazine requestedSource)
    {
        if (!GetGame().IsServer() || !player || !BDE_USL_ShouldUseCustomManipulationAnimation())
            return false;

        if (m_BDE_USL_ManipulationActive)
            return false;

        int muzzleIndex = 0;

        if (GetMuzzleCount() <= muzzleIndex)
            return false;

        bool isGP25 = IsKindOf("BDE_GP25");
        Magazine source = null;
        bool playGrenadeOut = false;
        string ammoVisualType = "";

        if (actionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD)
        {
            if (BDE_USL_HasLiveRound())
                return false;

            if (m_BDE_USL_HasReservedGroundRound)
            {
                ammoVisualType = m_BDE_USL_ReservedGroundMagazineType;
            }
            else
            {
                source = requestedSource;

                if (!source || !BDE_USL_CanDirectLoadRound(source, false))
                    return false;

                ammoVisualType = source.GetType();
            }

            playGrenadeOut = !isGP25 && IsChamberFiredOut(muzzleIndex);
        }
        else if (actionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
        {
            if (IsChamberEmpty(muzzleIndex))
                return false;

            if (isGP25)
                playGrenadeOut = !IsChamberFiredOut(muzzleIndex);
            else
                playGrenadeOut = true;
        }
        else
        {
            return false;
        }

        m_BDE_USL_ManipulationActive = true;
        m_BDE_USL_ServerManipulationAction = actionType;
        m_BDE_USL_PendingReloadSource = source;
        m_BDE_USL_PendingManipulationPlayer = player;
        m_BDE_USL_ServerEjectHandled = false;

        Param3<int, bool, string> sequenceData = new Param3<int, bool, string>(actionType, playGrenadeOut, ammoVisualType);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_MANIPULATION_SEQUENCE, sequenceData, true, NULL);

        if (isGP25)
        {
            if (actionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD)
            {
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerCompleteTimedReload, BDE_USL_GP25_RELOAD_GRENADE_IN_MS, false);
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerFinishTimedManipulation, BDE_USL_GP25_RELOAD_TOTAL_MS, false);
            }
            else
            {
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerClearGP25FiredOutAtUnloadFrame, BDE_USL_GP25_UNLOAD_GRENADE_OUT_MS, false);
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerFinishTimedManipulation, BDE_USL_GP25_UNLOAD_TOTAL_MS, false);
            }

            return true;
        }

        if (actionType == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerSetM203TubeOpen, BDE_USL_M203_RELOAD_TUBE_OPEN_MS, false, true);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerCompleteTimedReload, BDE_USL_M203_RELOAD_INSERT_CLOSE_MS, false);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerFinishTimedManipulation, BDE_USL_M203_RELOAD_TOTAL_MS, false);
        }
        else
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerSetM203TubeOpen, BDE_USL_M203_UNLOAD_TUBE_OPEN_MS, false, true);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerSetM203TubeOpen, BDE_USL_M203_UNLOAD_TUBE_CLOSE_MS, false, false);
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerFinishTimedManipulation, BDE_USL_M203_UNLOAD_TOTAL_MS, false);
        }

        return true;
    }

    bool BDE_USL_ServerRequestOwnerSpecificReload(Magazine source)
    {
        if (!GetGame().IsServer() || !source || !BDE_USL_ShouldUseCustomManipulationAnimation())
            return false;

        if (m_BDE_USL_ManipulationActive || !BDE_USL_CanDirectLoadRound(source, false))
            return false;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());
        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (!player)
            return false;

        if (host)
        {
            if (player.GetItemInHands() != host || host.BDE_USL_GetLauncher() != this)
                return false;
        }
        else if (GetType() != "BDE_GP25" || player.GetItemInHands() != this)
        {
            return false;
        }

        Param1<EntityAI> beginData = new Param1<EntityAI>(source);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_BEGIN_SPECIFIC_RELOAD, beginData, true, NULL);
        return true;
    }

    void BDE_USL_ClientRequestManipulation(int actionType, Magazine source = null)
    {
        if (!GetGame().IsClient())
            return;

        Param2<int, EntityAI> data = new Param2<int, EntityAI>(actionType, source);
        GetGame().RPCSingleParam(this, BDE_USL_RPC.BDE_USL_RPC_MANIPULATE, data, true);
    }

    protected bool BDE_USL_ValidateManipulationOwner(PlayerIdentity sender, out PlayerBase player)
    {
        player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (!sender || !player)
            return false;

        PlayerIdentity identity = player.GetIdentity();

        if (!identity || identity.GetId() != sender.GetId())
            return false;

        Weapon_Base host = Weapon_Base.Cast(GetHierarchyParent());

        if (host)
            return player.GetItemInHands() == host && host.BDE_USL_GetLauncher() == this;

        if (IsKindOf("BDE_M203"))
            return player.GetItemInHands() == this;

        return GetType() == "BDE_GP25" && player.GetItemInHands() == this;
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_BEGIN_SPECIFIC_RELOAD)
        {
            Param1<EntityAI> beginData = new Param1<EntityAI>(null);

            if (!ctx.Read(beginData) || GetGame().IsDedicatedServer())
                return;

            PlayerBase beginOwner = PlayerBase.Cast(GetHierarchyRootPlayer());
            PlayerBase beginLocalPlayer = PlayerBase.Cast(GetGame().GetPlayer());
            Magazine beginSource = Magazine.Cast(beginData.param1);

            if (beginOwner && beginOwner == beginLocalPlayer && beginSource)
                beginOwner.BDE_USL_ClientBeginSpecificReload(this, beginSource);

            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_LOAD_SPECIFIC)
        {
            Param1<EntityAI> loadData = new Param1<EntityAI>(null);

            if (!ctx.Read(loadData) || !GetGame().IsServer())
                return;

            PlayerBase loadPlayer;
            Magazine loadSource = Magazine.Cast(loadData.param1);

            if (!loadSource || !BDE_USL_ValidateSpecificLoadOwner(sender, loadPlayer))
                return;

            string sourceType = loadSource.GetType();
            bool loaded = BDE_USL_ServerLoadSpecificRound(loadSource);
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_RESERVE_GROUND_ROUND)
        {
            Param1<EntityAI> reserveData = new Param1<EntityAI>(null);

            if (!ctx.Read(reserveData) || !GetGame().IsServer())
                return;

            BDE_USL_ServerReserveGroundRound(sender, Magazine.Cast(reserveData.param1));
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_FIRE_ATTACHED)
        {
            Param5<int, vector, vector, vector, int> fireData = new Param5<int, vector, vector, vector, int>(0, vector.Zero, vector.Zero, vector.Zero, -1);

            if (!ctx.Read(fireData))
                return;

            BDE_USL_ServerFireAttached(sender, fireData.param1, fireData.param2, fireData.param3, fireData.param4, fireData.param5);
            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_FIRE_FX)
        {
            Param4<vector, vector, string, int> fxData = new Param4<vector, vector, string, int>(vector.Zero, vector.Zero, "", -1);

            if (!ctx.Read(fxData) || GetGame().IsDedicatedServer())
                return;

            Param4<int, string, vector, vector> projectileData = new Param4<int, string, vector, vector>(0, "", vector.Zero, vector.Zero);
            if (!ctx.Read(projectileData))
                return;

            BDE_USL_ReplayRemoteSmoke(projectileData.param1, projectileData.param2, projectileData.param3, fxData.param2, projectileData.param4, fxData.param4);
            BDE_USL_PlayAttachedFireFX(fxData.param1, fxData.param2);

            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_MANIPULATION_SEQUENCE)
        {
            Param3<int, bool, string> sequenceData = new Param3<int, bool, string>(BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_NONE, false, "");

            if (!ctx.Read(sequenceData) || GetGame().IsDedicatedServer())
                return;

            BDE_M203 m203 = BDE_M203.Cast(this);
            BDE_GP25 gp25 = BDE_GP25.Cast(this);
            PlayerBase sequenceOwner = PlayerBase.Cast(GetHierarchyRootPlayer());
            PlayerBase sequenceLocalPlayer = PlayerBase.Cast(GetGame().GetPlayer());

            if (!sequenceOwner || sequenceOwner != sequenceLocalPlayer)
            {
                if (m203)
                {
                    if (sequenceData.param1 == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
                        m203.BDE_M203_StartUnloadTubeSequence(sequenceData.param2);
                    else if (sequenceData.param1 == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD)
                        m203.BDE_M203_StartReloadTubeSequence(sequenceData.param2, sequenceData.param3);
                }
                else if (gp25)
                {
                    if (sequenceData.param1 == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD)
                        gp25.BDE_GP25_StartUnloadSequence(sequenceData.param2);
                    else if (sequenceData.param1 == BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD)
                        gp25.BDE_GP25_StartReloadSequence(sequenceData.param3);
                }
            }

            return;
        }

        if (rpc_type == BDE_USL_RPC.BDE_USL_RPC_MANIPULATION_EJECT)
        {
            Param3<int, vector, vector> ejectData = new Param3<int, vector, vector>(BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_NONE, vector.Zero, vector.Zero);

            if (!ctx.Read(ejectData) || !GetGame().IsServer())
                return;

            BDE_USL_ServerHandleManipulationEject(sender, ejectData.param1, ejectData.param2, ejectData.param3);
            return;
        }

        if (rpc_type != BDE_USL_RPC.BDE_USL_RPC_MANIPULATE)
            return;

        Param2<int, EntityAI> data = new Param2<int, EntityAI>(BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_NONE, null);

        if (!ctx.Read(data) || !GetGame().IsServer())
            return;

        PlayerBase player;

        if (!BDE_USL_ValidateManipulationOwner(sender, player))
            return;

        if (BDE_USL_ShouldUseCustomManipulationAnimation())
        {
            BDE_USL_ServerStartTimedManipulation(sender, player, data.param1, Magazine.Cast(data.param2));
            return;
        }

        switch (data.param1)
        {
            case BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_UNLOAD:
                BDE_USL_ServerUnload(player);
                break;
            case BDE_USL_ManipulationAction.BDE_USL_MANIPULATION_RELOAD:
                BDE_USL_ServerReload(player);
                break;
        }
    }
}
