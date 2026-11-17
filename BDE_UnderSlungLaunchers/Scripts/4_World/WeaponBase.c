modded class Weapon_Base
{
    protected ref array<int> m_BDE_USL_LockedSlots;

    override bool CanChamberBullet(int muzzleIndex, Magazine mag)
    {
        if (mag && mag.IsKindOf("Ammo_VOG25") && !IsKindOf("BDE_GP25"))
            return false;

        return super.CanChamberBullet(muzzleIndex, mag);
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (!super.CanReleaseAttachment(attachment))
            return false;

        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();
        BDE_Six12 six12 = BDE_USL_GetSix12();
        EntityAI underbarrel = BDE_USL_GetUnderbarrelEntity();

        if (attachment && underbarrel)
        {
            string handguardSlot;
            GetGame().ConfigGetText("CfgWeapons " + GetType() + " BDE_USL_HandguardSlot", handguardSlot);

            if (handguardSlot != "" && FindAttachmentBySlotName(handguardSlot) == attachment)
                return false;
        }

        if (attachment && FindAttachmentBySlotName("weaponButtstockAK") == attachment)
        {
            if (launcher && (launcher.FindAttachmentBySlotName("BDE_GP25_ButtPad") || launcher.FindAttachmentBySlotName("BDE_M203_ButtPad")))
                return false;

            if (six12 && six12.FindAttachmentBySlotName("BDE_Six12_ButtPad"))
                return false;
        }

        return true;
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();

        if (!GetGame().IsServer() || !BDE_USL_IsCompatibleHost())
            return;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_PostStoreLoadRefresh, 100, false);
    }

    void BDE_USL_PostStoreLoadRefresh()
    {
        if (!GetGame().IsServer() || IsSetForDeletion() || !BDE_USL_IsCompatibleHost())
            return;

        EntityAI underbarrel = BDE_USL_GetUnderbarrelEntity();

        if (underbarrel && !BDE_USL_IsLauncherTypeAllowed(underbarrel))
        {
            GetInventory().DropEntity(InventoryMode.SERVER, this, underbarrel);
            BDE_USL_UnlockConfiguredBlockedSlots();
            BDE_USL_ForceNormalMode();
            BDE_USL_RefreshLauncherModeState();
            return;
        }

        if (underbarrel)
        {
            BDE_USL_LockConfiguredBlockedSlots();

            BDE_GP25 gp25 = BDE_GP25.Cast(underbarrel);
            if (gp25)
                gp25.BDE_GP25_RequestVariantRefresh();
        }
        else
        {
            BDE_USL_UnlockConfiguredBlockedSlots();
            BDE_USL_ForceNormalMode();
        }

        BDE_USL_RefreshLauncherModeState();
    }

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);

        if (!BDE_USL_IsCompatibleHost())
            return;

        BDE_UnderSlungLauncher_Base attachedLauncher = BDE_UnderSlungLauncher_Base.Cast(item);

        if (attachedLauncher)
        {
            string configuredSlot = BDE_USL_GetConfiguredLauncherSlotName();

            if (slot_name != configuredSlot || !BDE_USL_IsLauncherTypeAllowed(attachedLauncher))
            {
                BDE_USL_UnlockConfiguredBlockedSlots();
                BDE_USL_ForceNormalMode();

                if (GetGame().IsServer())
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerRejectMisSlottedLauncher, 1, false, attachedLauncher);

                return;
            }

            BDE_USL_LockConfiguredBlockedSlots();
            BDE_USL_RefreshLauncherModeState();
        }

        BDE_Six12 attachedSix12 = BDE_Six12.Cast(item);
        if (attachedSix12)
        {
            string six12Slot = BDE_USL_GetConfiguredLauncherSlotName();
            if (slot_name != six12Slot || !BDE_USL_IsLauncherTypeAllowed(attachedSix12))
            {
                BDE_USL_UnlockConfiguredBlockedSlots();
                BDE_USL_ForceNormalMode();
                if (GetGame().IsServer())
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_ServerRejectMisSlottedLauncher, 1, false, attachedSix12);
                return;
            }

            BDE_USL_LockConfiguredBlockedSlots();
            BDE_USL_RefreshLauncherModeState();
        }

        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();
        BDE_GP25 gp25 = BDE_GP25.Cast(launcher);

        if (gp25)
        {
            if (slot_name == "weaponButtstockAK")
                gp25.BDE_GP25_NotifyHostButtstockChanged();
            else
                gp25.BDE_GP25_RequestVariantRefresh();
        }

        BDE_M203 m203 = BDE_M203.Cast(launcher);

        if (m203 && slot_name == "weaponButtstockAK")
            m203.BDE_M203_NotifyHostButtstockChanged();

        BDE_Six12 six12 = BDE_USL_GetSix12();
        if (six12 && slot_name == "weaponButtstockAK")
            six12.BDE_Six12_NotifyHostButtstockChanged();
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (!BDE_USL_IsCompatibleHost())
            return;

        if (BDE_UnderSlungLauncher_Base.Cast(item) || BDE_Six12.Cast(item))
        {
            BDE_USL_UnlockConfiguredBlockedSlots();
            BDE_USL_ForceNormalMode();
            BDE_USL_RefreshLauncherModeState();
        }

        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();
        BDE_GP25 gp25 = BDE_GP25.Cast(launcher);

        if (gp25)
        {
            if (slot_name == "weaponButtstockAK")
                gp25.BDE_GP25_NotifyHostButtstockChanged();
            else
                gp25.BDE_GP25_RequestVariantRefresh();
        }

        BDE_M203 m203 = BDE_M203.Cast(launcher);

        if (m203 && slot_name == "weaponButtstockAK")
            m203.BDE_M203_NotifyHostButtstockChanged();

        BDE_Six12 six12 = BDE_USL_GetSix12();
        if (six12 && slot_name == "weaponButtstockAK")
            six12.BDE_Six12_NotifyHostButtstockChanged();
    }

    protected void BDE_USL_ServerRejectMisSlottedLauncher(EntityAI launcher)
    {
        if (!GetGame().IsServer() || !launcher || launcher.GetHierarchyParent() != this)
            return;

        int configuredSlotId = BDE_USL_GetConfiguredLauncherSlotId();

        if (configuredSlotId != InventorySlots.INVALID && GetInventory().FindAttachment(configuredSlotId) == launcher && BDE_USL_IsLauncherTypeAllowed(launcher))
            return;

        GetInventory().DropEntity(InventoryMode.SERVER, this, launcher);
    }

    BDE_Six12 BDE_USL_GetSix12InteractionTarget()
    {
        BDE_Six12_StandAloneMount_Weapon standalone = BDE_Six12_StandAloneMount_Weapon.Cast(this);
        if (standalone)
            return standalone.BDE_Six12_GetBody();

        return BDE_USL_GetSix12();
    }

    bool BDE_USL_CanDirectLoadSix12Ammo(Magazine source, bool reservationCheck = true)
    {
        BDE_Six12 six12 = BDE_USL_GetSix12InteractionTarget();
        return six12 && six12.BDE_Six12_CanDirectLoadAmmo(source, reservationCheck);
    }

    bool BDE_USL_CanDirectLoadAttachedRound(Magazine source, bool reservationCheck = true)
    {
        if (!source)
            return false;

        PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

        if (!player || player.GetItemInHands() != this)
            return false;

        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();

        if (!launcher)
            return false;

        return launcher.BDE_USL_CanDirectLoadRound(source, reservationCheck);
    }

    override bool CanBeCombined(EntityAI other_item, bool reservation_check = true, bool stack_max_limit = false)
    {
        Magazine source = Magazine.Cast(other_item);
        if (source && BDE_USL_CanDirectLoadSix12Ammo(source, reservation_check))
            return true;

        if (source && BDE_USL_CanDirectLoadAttachedRound(source, reservation_check))
            return true;

        return super.CanBeCombined(other_item, reservation_check, stack_max_limit);
    }

    override void CombineItems(ItemBase other_item, bool use_stack_max = true)
    {
        Magazine source = Magazine.Cast(other_item);
        if (source && BDE_USL_CanDirectLoadSix12Ammo(source, false))
        {
            BDE_Six12 six12AmmoTarget = BDE_USL_GetSix12InteractionTarget();
            if (six12AmmoTarget)
                six12AmmoTarget.BDE_Six12_RequestSpecificAmmo(source);
            return;
        }

        if (source && BDE_USL_CanDirectLoadAttachedRound(source, false))
        {
            BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();

            if (launcher && launcher.BDE_USL_ShouldUseAttachedCustomAnimation())
            {
                PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());

                if (GetGame().IsClient() && player && GetGame().GetPlayer() == player)
                    player.BDE_USL_ClientBeginSpecificReload(launcher, source);
                else if (GetGame().IsServer())
                    launcher.BDE_USL_ServerRequestOwnerSpecificReload(source);

                return;
            }

            if (launcher && GetGame().IsServer())
                launcher.BDE_USL_ServerLoadSpecificRound(source);

            return;
        }

        super.CombineItems(other_item, use_stack_max);
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (!attachment)
            return false;

        BDE_UnderSlungLauncher_Base incomingLauncher = BDE_UnderSlungLauncher_Base.Cast(attachment);
        BDE_Six12 incomingSix12 = BDE_Six12.Cast(attachment);

        if (incomingSix12 && IsKindOf("BDE_Six12_StandAloneMount_Weapon") && InventorySlots.GetSlotName(slotId) == "BDE_Six12")
            return super.CanReceiveAttachment(attachment, slotId);

        if (incomingLauncher || incomingSix12)
        {
            if (!BDE_USL_IsCompatibleHost())
                return false;
            if (!BDE_USL_IsLauncherSlot(slotId))
                return false;
            if (!super.CanReceiveAttachment(attachment, slotId))
                return false;

            if (incomingLauncher)
                return BDE_USL_CanAttachLauncher(incomingLauncher, slotId);

            return BDE_USL_CanAttachSix12(incomingSix12, slotId);
        }

        if (!super.CanReceiveAttachment(attachment, slotId))
            return false;

        EntityAI currentUnderbarrel = BDE_USL_GetUnderbarrelEntity();
        if (currentUnderbarrel && !BDE_USL_CanAttachWithLauncher(currentUnderbarrel, attachment, slotId))
            return false;

        return true;
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (!super.CanDisplayAttachmentSlot(slot_id))
            return false;

        return BDE_USL_ShouldDisplayAttachmentSlot(slot_id);
    }

    bool BDE_USL_ShouldDisplayAttachmentSlot(int slotId)
    {
        EntityAI underbarrel = BDE_USL_GetUnderbarrelEntity();

        if (underbarrel && BDE_USL_IsBlockedSlot(slotId))
            return false;

        return true;
    }

    BDE_UnderSlungLauncher_Base BDE_USL_GetLauncher()
    {
        if (IsKindOf("BDE_GP25") && !Weapon_Base.Cast(GetHierarchyParent()))
            return BDE_UnderSlungLauncher_Base.Cast(this);

        int attachmentCount = GetInventory().AttachmentCount();

        for (int i = 0; i < attachmentCount; i++)
        {
            BDE_UnderSlungLauncher_Base launcher = BDE_UnderSlungLauncher_Base.Cast(GetInventory().GetAttachmentFromIndex(i));

            if (launcher)
                return launcher;
        }

        return null;
    }

    BDE_Six12 BDE_USL_GetSix12()
    {
        int attachmentCount = GetInventory().AttachmentCount();
        for (int i = 0; i < attachmentCount; i++)
        {
            BDE_Six12 six12 = BDE_Six12.Cast(GetInventory().GetAttachmentFromIndex(i));
            if (six12)
                return six12;
        }
        return null;
    }

    EntityAI BDE_USL_GetUnderbarrelEntity()
    {
        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();
        if (launcher)
            return launcher;
        return BDE_USL_GetSix12();
    }

    bool BDE_USL_IsSix12Operational(BDE_Six12 six12)
    {
        if (!six12 || six12.IsSetForDeletion() || six12.IsRuined())
            return false;

        if (IsKindOf("BDE_Six12_StandAloneMount_Weapon"))
        {
            BDE_Six12_StandAloneMount_Weapon mount = BDE_Six12_StandAloneMount_Weapon.Cast(this);
            return mount && mount.BDE_Six12_GetBody() == six12 && six12.BDE_Six12_HasHandle() && !six12.BDE_Six12_HasShortBarrel() && FindAttachmentBySlotName("BDE_Six12_LongBarrel") != null;
        }

        if (!BDE_USL_IsLauncherTypeAllowed(six12))
            return false;
        return six12.BDE_Six12_HasShortBarrel();
    }

    bool BDE_USL_IsAnyLauncherOperational()
    {
        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();
        if (launcher)
            return BDE_USL_IsLauncherOperational(launcher);

        return BDE_USL_IsSix12Operational(BDE_USL_GetSix12());
    }

    bool BDE_USL_IsLauncherOperational(BDE_UnderSlungLauncher_Base launcher)
    {
        if (!launcher || launcher.IsSetForDeletion())
            return false;

        if (!BDE_USL_IsLauncherTypeAllowed(launcher))
            return false;

        BDE_M203 m203 = BDE_M203.Cast(launcher);

        if (m203)
        {
            if (IsKindOf("BDE_M203_StandAloneMount_Weapon") || IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
                return true;

            return m203.BDE_M203_HasBarrel();
        }

        if (launcher.IsRuined())
            return false;

        return true;
    }

    protected int BDE_USL_GetNamedModeIndex(string modeName)
    {
        if (modeName == "")
            return -1;
        if (!BDE_USL_IsCompatibleHost() && !IsKindOf("BDE_Six12_StandAloneMount_Weapon"))
            return -1;

        array<string> configuredModes = new array<string>;
        GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " modes", configuredModes);

        for (int i = 0; i < configuredModes.Count(); i++)
        {
            if (configuredModes[i] == modeName)
                return i;
        }

        return -1;
    }

    int BDE_USL_GetLauncherModeIndex()
    {
        return BDE_USL_GetNamedModeIndex("Launcher");
    }

    int BDE_USL_GetSix12ModeIndex()
    {
        return BDE_USL_GetNamedModeIndex("Six12");
    }

    override void OnFireModeChange(int fireMode)
    {
        super.OnFireModeChange(fireMode);

        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();
        BDE_GP25 gp25 = BDE_GP25.Cast(launcher);

        if (gp25)
            gp25.BDE_GP25_UpdateSightVisual(false);

        BDE_M203 m203 = BDE_M203.Cast(launcher);

        if (m203)
            m203.BDE_M203_QueueRailSightFoldRefresh();
    }

    bool BDE_USL_IsLauncherModeSelected()
    {
        if (BDE_USL_GetSix12())
            return false;

        int launcherModeIndex = BDE_USL_GetLauncherModeIndex();
        if (launcherModeIndex < 0 || !BDE_USL_IsLauncherOperational(BDE_USL_GetLauncher()))
            return false;

        return GetCurrentMode(GetCurrentMuzzle()) == launcherModeIndex;
    }

    bool BDE_USL_IsSix12ModeSelected()
    {
        int six12ModeIndex = BDE_USL_GetSix12ModeIndex();

        if (six12ModeIndex < 0)
            return false;

        return GetCurrentMode(GetCurrentMuzzle()) == six12ModeIndex;
    }

    bool BDE_USL_IsGrozaLauncherADSBlocked()
    {
        if (GetAttachedOptics())
            return false;

        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();
        return BDE_USL_IsLauncherModeSelected() && launcher && launcher.IsKindOf("BDE_OTS14_Launcher") && FindAttachmentBySlotName("BDE_OTS14_Sight") != null;
    }

    bool BDE_USL_ShouldUseLauncherAimView()
    {
        if (!BDE_USL_IsLauncherModeSelected())
            return false;

        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();

        if (!BDE_USL_IsLauncherOperational(launcher))
            return false;

        if (launcher != this && launcher.GetHierarchyParent() != this)
            return false;

        if (launcher.IsKindOf("BDE_OTS14_Launcher"))
        {
            if (GetAttachedOptics())
                return false;

            return !BDE_USL_IsGrozaLauncherADSBlocked() && launcher.BDE_USL_GetCurrentAimZeroing() > 0;
        }

        if (IsKindOf("BDE_M203_StandAloneMount_Weapon") || IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
        {
            return BDE_USL_IsStandaloneM203IronSightActive();
        }
        else
        {
            if (BDE_USL_GetSideRailSight())
                return true;

            BDE_M203 attachedM203 = BDE_M203.Cast(launcher);

            if (attachedM203)
                return attachedM203.BDE_M203_HasRailSightSystem();
        }

        return true;
    }

    protected bool BDE_USL_IsFiniteVector(vector value)
    {
        if (value[0] != value[0] || value[1] != value[1] || value[2] != value[2])
            return false;

        if (Math.AbsFloat(value[0]) > 1000000.0 || Math.AbsFloat(value[1]) > 1000000.0 || Math.AbsFloat(value[2]) > 1000000.0)
            return false;

        return true;
    }

    protected float BDE_USL_GetLauncherAimMuzzleVelocity(BDE_UnderSlungLauncher_Base launcher)
    {
        if (!launcher)
            return 76.0;

        int muzzleIndex = launcher.GetCurrentMuzzle();
        float cartridgeDamage = 0.0;
        string ammoType = "";

        if (muzzleIndex >= 0 && muzzleIndex < launcher.GetMuzzleCount())
            launcher.GetCartridgeInfo(muzzleIndex, cartridgeDamage, ammoType);

        float initialSpeed = 0.0;

        if (ammoType != "")
            initialSpeed = GetGame().ConfigGetFloat("CfgAmmo " + ammoType + " initSpeed");

        if (initialSpeed <= 0.0)
            initialSpeed = GetGame().ConfigGetFloat("CfgAmmo Bullet_40mm_Explosive initSpeed");

        if (initialSpeed <= 0.0)
            initialSpeed = 76.0;

        float multiplier = GetGame().ConfigGetFloat("CfgWeapons " + launcher.GetType() + " initSpeedMultiplier");

        if (multiplier <= 0.0)
            multiplier = 1.0;

        return initialSpeed * multiplier;
    }

    protected float BDE_USL_CalculateLauncherAimAngle(BDE_UnderSlungLauncher_Base launcher)
    {
        if (!launcher)
            return 0.0;

        float zeroingDistance = launcher.BDE_USL_GetCurrentAimZeroing();
        float muzzleVelocity = BDE_USL_GetLauncherAimMuzzleVelocity(launcher);
        float gravity = launcher.BDE_USL_GetAimGravity();
        float maxAngle = launcher.BDE_USL_GetAimMaxAngle();
        float velocitySquared = muzzleVelocity * muzzleVelocity;

        if (zeroingDistance <= 0.0 || velocitySquared <= 0.0 || gravity <= 0.0)
            return 0.0;

        float ballisticRatio = (gravity * zeroingDistance) / velocitySquared;

        if (ballisticRatio >= 1.0)
            return maxAngle;

        ballisticRatio = Math.Clamp(ballisticRatio, 0.0, 1.0);
        float angleDegrees = 0.5 * Math.Asin(ballisticRatio) * Math.RAD2DEG;
        return Math.Clamp(angleDegrees, 0.0, maxAngle);
    }

    EntityAI BDE_USL_GetSideRailSight()
    {
        EntityAI mount = FindAttachmentBySlotName("BDE_SideRail");
        if (mount && mount.IsKindOf("BDE_FN40_Sight_Mount") && mount.FindAttachmentBySlotName("BDE_FN40_Sight"))
            return mount;
        return null;
    }

    EntityAI BDE_USL_GetFN40SightMount()
    {
        EntityAI mount = BDE_USL_GetSideRailSight();
        if (!mount && IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
            mount = FindAttachmentBySlotName("BDE_FN40_Sight_Mount");
        if (mount && mount.FindAttachmentBySlotName("BDE_FN40_Sight"))
            return mount;
        return null;
    }

    bool BDE_USL_GetFN40SightCameraWS(out vector eyeWS, out vector targetWS, out vector upWS)
    {
        EntityAI mount = BDE_USL_GetFN40SightMount();
        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();
        if (!mount || !launcher)
            return false;
        float distance = launcher.BDE_USL_GetCurrentAimZeroing();
        string pointName = "fn40_front1";
        if (distance >= 275) pointName = "fn40_front7";
        else if (distance >= 225) pointName = "fn40_front6";
        else if (distance >= 175) pointName = "fn40_front5";
        else if (distance >= 125) pointName = "fn40_front4";
        else if (distance >= 75) pointName = "fn40_front3";
        else if (distance >= 25) pointName = "fn40_front2";

        if (!MemoryPointExists("bde_fn40_eye") || !MemoryPointExists("bde_" + pointName))
            return false;
        vector sightTM[4];
        GetRenderTransform(sightTM);
        eyeWS = GetMemoryPointPos("bde_fn40_eye").Multiply4(sightTM);
        targetWS = GetMemoryPointPos("bde_" + pointName).Multiply4(sightTM);
        upWS = GetMemoryPointPos("bde_fn40_up").Multiply4(sightTM) - eyeWS;
        vector direction = targetWS - eyeWS;
        if (direction.LengthSq() < 0.000001) return false;
        direction.Normalize();
        eyeWS = eyeWS - direction * 0.060;
        upWS = upWS - direction * vector.Dot(upWS, direction);
        if (upWS.LengthSq() < 0.000001) return false;
        upWS.Normalize();
        return true;
    }

    bool BDE_USL_HasFN40DedicatedSight()
    {
        if (!IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
            return false;
        EntityAI mount = FindAttachmentBySlotName("BDE_FN40_Sight_Mount");
        return mount && mount.FindAttachmentBySlotName("BDE_FN40_Sight");
    }

    bool BDE_USL_IsStandaloneM203IronSightActive()
    {
        if (!IsKindOf("BDE_M203_StandAloneMount_Weapon") && !IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
            return false;
        if (BDE_USL_HasFN40DedicatedSight())
            return true;
        EntityAI opticEntity = FindAttachmentBySlotName("weaponOptics");
        return opticEntity && opticEntity.IsKindOf("BDE_M203_RearSight") && opticEntity.FindAttachmentBySlotName("BDE_M203_FrontSight");
    }

    protected string BDE_USL_GetStandaloneM203RearSightPoint(BDE_UnderSlungLauncher_Base launcher)
    {
        if (BDE_USL_HasFN40DedicatedSight())
            return "fn40_rear_sight1";
        EntityAI opticEntity = FindAttachmentBySlotName("weaponOptics");

        if (!opticEntity)
            return "rear_sight1";

        float zeroing = launcher.BDE_USL_GetCurrentAimZeroing();

        if (zeroing >= 225.0)
            return "rear_sight6";
        if (zeroing >= 175.0)
            return "rear_sight5";
        if (zeroing >= 125.0)
            return "rear_sight4";
        if (zeroing >= 75.0)
            return "rear_sight3";
        if (zeroing >= 25.0)
            return "rear_sight2";
        return "rear_sight1";
    }

    protected bool BDE_USL_GetStandaloneM203IronSightCameraPoint(BDE_UnderSlungLauncher_Base launcher, out vector cameraPosition, out vector cameraDirection)
    {
        cameraPosition = vector.Zero;
        cameraDirection = vector.Zero;

        if (!launcher || !BDE_USL_IsStandaloneM203IronSightActive())
            return false;

        string rearPointName = BDE_USL_GetStandaloneM203RearSightPoint(launcher);
        vector rearPoint = GetMemoryPointPos(rearPointName);
        string frontPointName = "front_sight";
        if (BDE_USL_HasFN40DedicatedSight())
            frontPointName = "fn40_front_sight";

        vector frontPoint = GetMemoryPointPos(frontPointName);
        vector sightDirection = frontPoint - rearPoint;

        if (sightDirection.LengthSq() < 0.000001)
            return false;

        sightDirection.Normalize();

        float cameraBackOffset = GetGame().ConfigGetFloat("CfgWeapons " + GetType() + " BDE_USL_StandaloneSightCameraBackOffset");
        if (cameraBackOffset <= 0.0)
            cameraBackOffset = 0.05;

        cameraPosition = rearPoint - (sightDirection * cameraBackOffset);
        cameraDirection = sightDirection;
        return BDE_USL_IsFiniteVector(cameraPosition) && BDE_USL_IsFiniteVector(cameraDirection);
    }

    bool BDE_USL_GetLauncherAimCameraPoint(out vector cameraPosition, out vector cameraDirection)
    {
        cameraPosition = vector.Zero;
        cameraDirection = vector.Zero;

        BDE_UnderSlungLauncher_Base launcher = BDE_USL_GetLauncher();

        if (!BDE_USL_IsLauncherOperational(launcher))
            return false;

        if (launcher != this && launcher.GetHierarchyParent() != this)
            return false;

        vector fnEyeWS;
        vector fnTargetWS;
        vector fnUpWS;
        if (BDE_USL_GetFN40SightCameraWS(fnEyeWS, fnTargetWS, fnUpWS))
        {
            cameraPosition = WorldToModel(fnEyeWS);
            cameraDirection = WorldToModel(fnTargetWS) - cameraPosition;
            cameraDirection.Normalize();
            return true;
        }

        if (BDE_USL_IsStandaloneM203IronSightActive())
        {
            if (BDE_USL_GetStandaloneM203IronSightCameraPoint(launcher, cameraPosition, cameraDirection))
                return true;
        }

        BDE_M203 m203 = BDE_M203.Cast(launcher);

        if (m203)
        {
            if (m203.BDE_M203_GetRailSightCameraPoint(cameraPosition, cameraDirection))
                return BDE_USL_IsFiniteVector(cameraPosition) && BDE_USL_IsFiniteVector(cameraDirection);

            return false;
        }

        BDE_GP25 gp25 = BDE_GP25.Cast(launcher);
        if (gp25 && gp25.BDE_GP25_GetVirtualSightCameraPoint(cameraPosition, cameraDirection))
            return BDE_USL_IsFiniteVector(cameraPosition) && BDE_USL_IsFiniteVector(cameraDirection);

        vector boreDirection;
        vector launcherUp;
        if (!launcher.BDE_USL_GetAttachedAimCameraGeometryEx(cameraPosition, boreDirection, launcherUp))
            return false;

        if (boreDirection.LengthSq() < 0.0001)
            return false;
        boreDirection.Normalize();

        launcherUp = launcherUp - (boreDirection * vector.Dot(launcherUp, boreDirection));
        if (launcherUp.LengthSq() < 0.0001)
            launcherUp = vector.Up;
        launcherUp.Normalize();

        float ballisticAngle = BDE_USL_CalculateLauncherAimAngle(launcher);
        float ballisticRadians = ballisticAngle * Math.DEG2RAD;
        vector physicalSightDirection = (boreDirection * Math.Cos(ballisticRadians)) - (launcherUp * Math.Sin(ballisticRadians));

        if (physicalSightDirection.LengthSq() < 0.0001)
            return false;

        physicalSightDirection.Normalize();
        cameraDirection = physicalSightDirection;
        return BDE_USL_IsFiniteVector(cameraPosition) && BDE_USL_IsFiniteVector(cameraDirection);
    }

    void BDE_USL_ForceNormalMode()
    {
        int muzzleIndex = GetCurrentMuzzle();
        if (muzzleIndex < 0 || muzzleIndex >= GetMuzzleCount())
            return;

        int currentMode = GetCurrentMode(muzzleIndex);
        int launcherModeIndex = BDE_USL_GetLauncherModeIndex();
        int six12ModeIndex = BDE_USL_GetSix12ModeIndex();

        if (currentMode != launcherModeIndex && currentMode != six12ModeIndex)
            return;

        if (currentMode == six12ModeIndex)
            Print("[BDE SIX12 MODE] ForceNormalMode host=" + this + " six12=" + BDE_USL_GetSix12());

        SetCurrentMode(muzzleIndex, 0);
        OnFireModeChange(0);
    }

    void BDE_USL_RefreshLauncherModeState()
    {
        if (!BDE_USL_IsCompatibleHost())
            return;

        int muzzleIndex = GetCurrentMuzzle();
        if (muzzleIndex < 0 || muzzleIndex >= GetMuzzleCount())
            return;

        int currentMode = GetCurrentMode(muzzleIndex);
        int launcherModeIndex = BDE_USL_GetLauncherModeIndex();
        int six12ModeIndex = BDE_USL_GetSix12ModeIndex();
        BDE_Six12 installedSix12 = BDE_USL_GetSix12();
        bool six12Available = installedSix12 && !installedSix12.IsSetForDeletion();
        bool launcherAvailable = !installedSix12 && BDE_USL_IsLauncherOperational(BDE_USL_GetLauncher());

        if ((currentMode == launcherModeIndex && !launcherAvailable) || (currentMode == six12ModeIndex && !six12Available))
        {
            if (currentMode == six12ModeIndex)
            {
                bool six12HasShortBarrel = installedSix12 && installedSix12.BDE_Six12_HasShortBarrel();
                Print("[BDE SIX12 MODE] RefreshLauncherModeState forcing normal host=" + this + " six12=" + installedSix12 + " operational=" + six12Available + " shortBarrel=" + six12HasShortBarrel);
            }

            SetCurrentMode(muzzleIndex, 0);
            OnFireModeChange(0);
        }
    }

    override void SetNextWeaponMode(int muzzleIndex)
    {
        int launcherModeIndex = BDE_USL_GetLauncherModeIndex();
        int six12ModeIndex = BDE_USL_GetSix12ModeIndex();

        if (launcherModeIndex < 0 && six12ModeIndex < 0)
        {
            super.SetNextWeaponMode(muzzleIndex);
            return;
        }

        int modeCount = GetMuzzleModeCount(muzzleIndex);
        if (modeCount <= 1)
        {
            super.SetNextWeaponMode(muzzleIndex);
            return;
        }

        int originalMode = GetCurrentMode(muzzleIndex);
        BDE_Six12 installedSix12 = BDE_USL_GetSix12();
        bool six12Available = installedSix12 && !installedSix12.IsSetForDeletion();
        bool launcherAvailable = !installedSix12 && BDE_USL_IsLauncherOperational(BDE_USL_GetLauncher());

        for (int step = 1; step <= modeCount; step++)
        {
            int nextMode = (originalMode + step) % modeCount;

            if (nextMode == launcherModeIndex && !launcherAvailable)
                continue;
            if (nextMode == six12ModeIndex && !six12Available)
                continue;

            SetCurrentMode(muzzleIndex, nextMode);
            OnFireModeChange(nextMode);
            return;
        }

        SetCurrentMode(muzzleIndex, originalMode);
    }

    bool BDE_USL_CanAttachLauncher(BDE_UnderSlungLauncher_Base launcher, int slotId)
    {
        if (!launcher)
            return false;

        if (!BDE_USL_IsCompatibleHost())
            return false;

        if (!BDE_USL_IsLauncherSlot(slotId))
            return false;

        if (!BDE_USL_IsLauncherTypeAllowed(launcher))
            return false;

        BDE_GP25 gp25Launcher = BDE_GP25.Cast(launcher);

        if (gp25Launcher && gp25Launcher.BDE_GP25_HasStandaloneButtStock())
            return false;

        if (!BDE_USL_HasValidHandguard(launcher))
            return false;

        if (BDE_USL_HasOccupiedBlockedSlot())
            return false;

        if (BDE_USL_HasBlockedAttachment(launcher))
            return false;

        BDE_M203 incomingM203 = BDE_M203.Cast(launcher);
        if (incomingM203 && incomingM203.BDE_M203_GetRailAdapter() && BDE_USL_GetSideRailSight())
            return false;

        return true;
    }

    bool BDE_USL_CanAttachLauncherToConfiguredSlot(BDE_UnderSlungLauncher_Base launcher)
    {
        int slotId = BDE_USL_GetConfiguredLauncherSlotId();

        if (slotId == InventorySlots.INVALID)
            return false;

        return BDE_USL_CanAttachLauncher(launcher, slotId);
    }

    bool BDE_USL_CanAttachSix12(BDE_Six12 six12, int slotId)
    {
        if (!six12 || !BDE_USL_IsCompatibleHost() || !BDE_USL_IsLauncherSlot(slotId))
            return false;
        if (!BDE_USL_IsLauncherTypeAllowed(six12))
            return false;
        if (!BDE_USL_HasValidHandguard(six12))
            return false;
        if (BDE_USL_HasOccupiedBlockedSlot())
            return false;
        if (BDE_USL_HasBlockedAttachment(six12))
            return false;
        return true;
    }

    bool BDE_USL_CanAttachSix12ToConfiguredSlot(BDE_Six12 six12)
    {
        int slotId = BDE_USL_GetConfiguredLauncherSlotId();
        if (slotId == InventorySlots.INVALID)
            return false;
        return BDE_USL_CanAttachSix12(six12, slotId);
    }

    string BDE_USL_GetConfiguredLauncherSlotName()
    {
        string launcherSlot;
        GetGame().ConfigGetText("CfgWeapons " + GetType() + " BDE_USL_LauncherSlot", launcherSlot);
        return launcherSlot;
    }

    int BDE_USL_GetConfiguredLauncherSlotId()
    {
        string launcherSlot = BDE_USL_GetConfiguredLauncherSlotName();

        if (launcherSlot == "")
            return InventorySlots.INVALID;

        return InventorySlots.GetSlotIdFromString(launcherSlot);
    }

    bool BDE_USL_CanAttachWithLauncher(EntityAI launcher, EntityAI attachment, int slotId)
    {
        if (BDE_USL_IsBlockedSlot(slotId))
            return false;

        if (BDE_USL_IsBlockedAttachment(launcher, attachment))
            return false;

        BDE_M203 m203 = BDE_M203.Cast(launcher);
        if (m203 && m203.BDE_M203_GetRailAdapter() && attachment.IsKindOf("BDE_FN40_Sight_Mount"))
            return false;

        return true;
    }

    bool BDE_USL_IsCompatibleHost()
    {
        if (IsKindOf("BDE_GP25") && !Weapon_Base.Cast(GetHierarchyParent()))
            return true;

        return GetGame().ConfigGetInt("CfgWeapons " + GetType() + " BDE_USL_Compatible") == 1;
    }

    bool BDE_USL_IsLauncherSlot(int slotId)
    {
        int launcherSlotId = BDE_USL_GetConfiguredLauncherSlotId();

        if (launcherSlotId == InventorySlots.INVALID)
            return false;

        return slotId == launcherSlotId;
    }

    bool BDE_USL_IsLauncherTypeAllowed(EntityAI launcher)
    {
        if (!launcher)
            return false;

        if (launcher == this && IsKindOf("BDE_GP25"))
            return BDE_USL_SettingsManager.IsLauncherEnabled(GetType(), launcher);

        bool launcherIsFN40 = launcher.IsKindOf("BDE_FN40");
        if (launcherIsFN40)
        {
            string fn40Host = GetType();
            if (fn40Host != "M4A1" && fn40Host != "SCARH" && fn40Host != "SCARH_Black" && !IsKindOf("BDE_FN40_StandaloneMount_Weapon"))
                return false;
        }

        if (!BDE_USL_SettingsManager.IsLauncherEnabled(GetType(), launcher))
            return false;

        array<string> launcherTypes = new array<string>;

        GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_USL_Types", launcherTypes);

        foreach (string launcherType : launcherTypes)
        {
            if (launcherIsFN40 && launcherType != "BDE_FN40")
                continue;
            if (launcher.IsKindOf(launcherType))
                return true;
        }

        return false;
    }

    bool BDE_USL_HasValidHandguard(EntityAI launcher)
    {
        string handguardSlot;

        GetGame().ConfigGetText("CfgWeapons " + GetType() + " BDE_USL_HandguardSlot", handguardSlot);

        if (handguardSlot == "")
            return true;

        EntityAI handguard = FindAttachmentBySlotName(handguardSlot);

        if (!handguard)
            return false;

        array<string> allowedHandguards = new array<string>;

        if (launcher.IsKindOf("BDE_M203"))
        {
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_M203AllowedHandguards", allowedHandguards);
        }
        else if (launcher.IsKindOf("BDE_GP25"))
        {
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_GP25AllowedHandguards", allowedHandguards);
        }
        else if (launcher.IsKindOf("BDE_Six12"))
        {
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_Six12AllowedHandguards", allowedHandguards);
        }

        if (allowedHandguards.Count() == 0)
            return true;

        foreach (string allowedHandguard : allowedHandguards)
        {
            if (handguard.IsKindOf(allowedHandguard))
                return true;
        }

        return false;
    }

    float BDE_USL_GetProjectileSpawnClearance()
    {
        string path = "CfgWeapons " + GetType() + " BDE_USL_ProjectileSpawnClearance";

        if (!GetGame().ConfigIsExisting(path))
            return 0.0;

        return GetGame().ConfigGetFloat(path);
    }

    void BDE_USL_LockConfiguredBlockedSlots()
    {
        array<string> blockedSlots = new array<string>;
        GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_USL_BlockedSlots", blockedSlots);

        if (!m_BDE_USL_LockedSlots)
            m_BDE_USL_LockedSlots = new array<int>;

        string launcherSlot = BDE_USL_GetConfiguredLauncherSlotName();

        foreach (string blockedSlot : blockedSlots)
        {
            if (blockedSlot == "" || blockedSlot == launcherSlot)
                continue;

            int blockedSlotId = InventorySlots.GetSlotIdFromString(blockedSlot);

            if (blockedSlotId == InventorySlots.INVALID)
                continue;

            if (GetInventory().GetSlotLock(blockedSlotId))
                continue;

            GetInventory().SetSlotLock(blockedSlotId, true);

            if (m_BDE_USL_LockedSlots.Find(blockedSlotId) == -1)
                m_BDE_USL_LockedSlots.Insert(blockedSlotId);
        }
    }

    void BDE_USL_UnlockConfiguredBlockedSlots()
    {
        if (!m_BDE_USL_LockedSlots)
            return;

        foreach (int blockedSlotId : m_BDE_USL_LockedSlots)
        {
            if (blockedSlotId != InventorySlots.INVALID)
                GetInventory().SetSlotLock(blockedSlotId, false);
        }

        m_BDE_USL_LockedSlots.Clear();
    }

    bool BDE_USL_IsBlockedSlot(int slotId)
    {
        string slotName = InventorySlots.GetSlotName(slotId);

        array<string> blockedSlots = new array<string>;

        GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_USL_BlockedSlots", blockedSlots);

        return blockedSlots.Find(slotName) != -1;
    }

    bool BDE_USL_HasOccupiedBlockedSlot()
    {
        array<string> blockedSlots = new array<string>;

        GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_USL_BlockedSlots", blockedSlots);

        foreach (string slotName : blockedSlots)
        {
            if (FindAttachmentBySlotName(slotName))
                return true;
        }

        return false;
    }

    bool BDE_USL_HasBlockedAttachment(EntityAI launcher)
    {
        int attachmentCount = GetInventory().AttachmentCount();

        for (int i = 0; i < attachmentCount; i++)
        {
            EntityAI attachment = GetInventory().GetAttachmentFromIndex(i);

            if (attachment && BDE_USL_IsBlockedAttachment(launcher, attachment))
                return true;
        }

        return false;
    }

    bool BDE_USL_IsBlockedAttachment(EntityAI launcher, EntityAI attachment)
    {
        if (!launcher || !attachment)
            return false;

        array<string> blockedAttachments = new array<string>;

        if (launcher.IsKindOf("BDE_M203"))
        {
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_M203BlockedAttachments", blockedAttachments);
        }
        else if (launcher.IsKindOf("BDE_GP25"))
        {
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_GP25BlockedAttachments", blockedAttachments);
        }
        else if (launcher.IsKindOf("BDE_Six12"))
        {
            GetGame().ConfigGetTextArray("CfgWeapons " + GetType() + " BDE_Six12BlockedAttachments", blockedAttachments);
        }

        foreach (string blockedAttachment : blockedAttachments)
        {
            if (attachment.IsKindOf(blockedAttachment))
                return true;
        }

        return false;
    }
}
