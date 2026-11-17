modded class WeaponManager
{
    override bool CanFire(Weapon_Base wpn)
    {
        if (wpn && wpn.IsKindOf("BDE_M203"))
            return false;

        if (wpn && wpn.IsKindOf("BDE_GP25") && !Weapon_Base.Cast(wpn.GetHierarchyParent()) && wpn.GetType() != "BDE_GP25")
            return false;

        BDE_Six12_StandAloneMount_Weapon six12Mount = BDE_Six12_StandAloneMount_Weapon.Cast(wpn);
        if (six12Mount)
        {
            BDE_Six12 standaloneBody = six12Mount.BDE_Six12_GetBody();
            if (wpn.IsRuined() || !standaloneBody || standaloneBody.IsRuined() || !standaloneBody.BDE_Six12_HasHandle() || standaloneBody.BDE_Six12_HasShortBarrel())
                return false;
            if (!six12Mount.FindAttachmentBySlotName("BDE_Six12_LongBarrel"))
                return false;
            if (standaloneBody.BDE_Six12_IsFireCycleLocked())
                return false;

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
            if (!m_player || !m_player.BDE_USL_NinjinsCanFire())
                return false;
#endif

            return true;
        }

        if (wpn && wpn.BDE_USL_IsSix12ModeSelected())
        {
            BDE_Six12 six12 = wpn.BDE_USL_GetSix12();
            if (!six12 || !wpn.BDE_USL_IsSix12Operational(six12) || six12.BDE_Six12_IsFireCycleLocked())
                return false;

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
            if (!m_player || !m_player.BDE_USL_NinjinsCanFire())
                return false;
#endif

            return true;
        }

        if (wpn && wpn.BDE_USL_IsLauncherModeSelected())
        {
            BDE_UnderSlungLauncher_Base launcher = wpn.BDE_USL_GetLauncher();
            if (!wpn.BDE_USL_IsLauncherOperational(launcher) || launcher.BDE_USL_IsManipulationActive())
                return false;

#ifdef Ninjins_PvP_PvE_Upgraded_Zones
            if (!m_player || !m_player.BDE_USL_NinjinsCanFire())
                return false;
#endif

            return true;
        }

        return super.CanFire(wpn);
    }

    override void Fire(Weapon_Base wpn)
    {
        BDE_Six12_StandAloneMount_Weapon six12Mount = BDE_Six12_StandAloneMount_Weapon.Cast(wpn);
        if (six12Mount)
        {
            if (!m_player || m_player.GetItemInHands() != wpn)
                return;

            BDE_Six12 standaloneBody = six12Mount.BDE_Six12_GetBody();
            if (standaloneBody && GetGame().IsClient())
                standaloneBody.BDE_Six12_ClientFireAttachedFromHost(wpn, m_player);
            return;
        }

        if (wpn && wpn.BDE_USL_IsSix12ModeSelected())
        {
            if (!m_player || m_player.GetItemInHands() != wpn)
                return;

            BDE_Six12 six12 = wpn.BDE_USL_GetSix12();
            if (six12 && GetGame().IsClient())
                six12.BDE_Six12_ClientFireAttachedFromHost(wpn, m_player);
            return;
        }

        if (wpn && wpn.BDE_USL_IsLauncherModeSelected())
        {
            if (!m_player || m_player.GetItemInHands() != wpn)
                return;

            BDE_UnderSlungLauncher_Base launcher = wpn.BDE_USL_GetLauncher();
            if (!launcher || launcher.BDE_USL_IsManipulationActive())
                return;

            if (GetGame().IsClient())
                launcher.BDE_USL_ClientFireAttachedFromHost(wpn, m_player);

            return;
        }

        super.Fire(wpn);
    }

    override bool CanLoadBullet(Weapon_Base wpn, Magazine mag, bool reservationCheck = true)
    {
        if (wpn && wpn.IsKindOf("BDE_M203"))
            return false;

        if (wpn && wpn.IsKindOf("BDE_GP25") && !Weapon_Base.Cast(wpn.GetHierarchyParent()) && wpn.GetType() != "BDE_GP25")
            return false;

        BDE_GP25 handheldGP25 = BDE_GP25.Cast(wpn);

        if (handheldGP25 && handheldGP25.GetType() == "BDE_GP25" && mag && !Weapon_Base.Cast(handheldGP25.GetHierarchyParent()) && handheldGP25.BDE_USL_CanDirectLoadRound(mag, reservationCheck))
            return true;

        if (wpn && mag && !mag.GetHierarchyRootPlayer() && wpn.BDE_USL_CanDirectLoadAttachedRound(mag, reservationCheck))
            return true;

        return super.CanLoadBullet(wpn, mag, reservationCheck);
    }

    override Magazine GetPreparedMagazine()
    {
        BDE_GP25 handheldGP25 = BDE_GP25.Cast(m_WeaponInHand);

        if (handheldGP25 && !Weapon_Base.Cast(handheldGP25.GetHierarchyParent()))
        {
            Magazine fallbackRound;

            for (int i = 0; i < m_SuitableMagazines.Count(); i++)
            {
                Magazine candidate = m_SuitableMagazines[i];

                if (!candidate || candidate.IsRuined() || (candidate.GetHierarchyParent() && candidate.GetHierarchyParent().IsWeapon()))
                    continue;

                if (candidate.GetHierarchyParent() && !candidate.GetHierarchyParent().GetInventory().AreChildrenAccessible())
                    continue;

                if (candidate.GetAmmoCount() <= 0 || !handheldGP25.BDE_USL_IsRoundAllowed(candidate))
                    continue;

                if (candidate.IsKindOf("Ammo_VOG25"))
                    return candidate;

                if (!fallbackRound)
                    fallbackRound = candidate;
            }

            if (fallbackRound)
                return fallbackRound;
        }

        return super.GetPreparedMagazine();
    }

    override bool LoadBullet(Magazine mag, ActionBase control_action = NULL)
    {
        Weapon_Base wpn;

        if (m_player)
            wpn = Weapon_Base.Cast(m_player.GetItemInHands());

        if (wpn && wpn.IsKindOf("BDE_GP25") && !Weapon_Base.Cast(wpn.GetHierarchyParent()) && wpn.GetType() != "BDE_GP25")
            return false;

        BDE_GP25 handheldGP25 = BDE_GP25.Cast(wpn);

        if (handheldGP25 && handheldGP25.GetType() == "BDE_GP25" && mag && !Weapon_Base.Cast(handheldGP25.GetHierarchyParent()) && handheldGP25.BDE_USL_CanDirectLoadRound(mag, false))
        {
            if (GetGame().IsClient() && m_player)
                return m_player.BDE_USL_ClientBeginSpecificReload(handheldGP25, mag);

            if (GetGame().IsServer())
                return handheldGP25.BDE_USL_ServerRequestOwnerSpecificReload(mag);

            return true;
        }

        if (wpn && mag && !mag.GetHierarchyRootPlayer() && wpn.BDE_USL_CanDirectLoadAttachedRound(mag, false))
        {
            BDE_UnderSlungLauncher_Base launcher = wpn.BDE_USL_GetLauncher();

            if (!launcher)
                return false;

            if (launcher.BDE_USL_ShouldUseAttachedCustomAnimation())
            {
                if (GetGame().IsClient() && m_player)
                    m_player.BDE_USL_ClientBeginSpecificReload(launcher, mag);
                else if (GetGame().IsServer())
                    launcher.BDE_USL_ServerRequestOwnerSpecificReload(mag);

                return true;
            }

            if (GetGame().IsClient())
            {
                launcher.BDE_USL_ClientRequestLoadSpecificRound(mag);
                return true;
            }

            if (GetGame().IsServer())
                return launcher.BDE_USL_ServerLoadSpecificRound(mag);

            return true;
        }

        return super.LoadBullet(mag, control_action);
    }

    override bool CanLoadMultipleBullet(Weapon_Base wpn, Magazine mag, bool reservationCheck = true)
    {
        if (wpn && (wpn.IsKindOf("BDE_M203") || (wpn.GetType() == "BDE_GP25" && !Weapon_Base.Cast(wpn.GetHierarchyParent()))))
            return false;

        return super.CanLoadMultipleBullet(wpn, mag, reservationCheck);
    }

    override bool CanEjectBullet(Weapon_Base wpn, bool reservationCheck = true)
    {
        if (wpn && (wpn.IsKindOf("BDE_M203") || (wpn.GetType() == "BDE_GP25" && !Weapon_Base.Cast(wpn.GetHierarchyParent()))))
            return false;

        return super.CanEjectBullet(wpn, reservationCheck);
    }

    override bool EjectBulletVerified(ActionBase control_action = NULL)
    {
        Weapon_Base wpn;

        if (m_player)
            wpn = Weapon_Base.Cast(m_player.GetItemInHands());

        if (wpn && (wpn.IsKindOf("BDE_M203") || (wpn.GetType() == "BDE_GP25" && !Weapon_Base.Cast(wpn.GetHierarchyParent()))))
            return false;

        return super.EjectBulletVerified(control_action);
    }
}
