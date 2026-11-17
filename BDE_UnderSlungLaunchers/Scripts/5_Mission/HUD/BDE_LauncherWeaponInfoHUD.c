modded class ItemActionsWidget
{
    protected BDE_Six12 BDE_USL_GetActiveSix12(Weapon_Base host)
    {
        if (!host)
            return null;

        BDE_Six12 six12 = host.BDE_USL_GetSix12();
        if (!six12)
            return null;

        if (!host.BDE_USL_IsSix12ModeSelected())
            return null;

        return six12;
    }

    override protected int GetItemHealth()
    {
        Weapon_Base host = Weapon_Base.Cast(m_EntityInHands);

        BDE_Six12 six12 = BDE_USL_GetActiveSix12(host);
        if (six12)
            return six12.GetHealthLevel();

        if (host && host.BDE_USL_IsLauncherModeSelected())
        {
            BDE_UnderSlungLauncher_Base launcher = host.BDE_USL_GetLauncher();

            if (launcher && launcher.GetHierarchyParent() == host)
                return launcher.GetHealthLevel();
        }

        return super.GetItemHealth();
    }

    override protected string GetItemDesc(EntityAI entity)
    {
        Weapon_Base host = Weapon_Base.Cast(entity);

        BDE_Six12 six12 = BDE_USL_GetActiveSix12(host);
        if (six12)
            return six12.BDE_Six12_GetHUDShortName();

        if (host && host.BDE_USL_IsLauncherModeSelected())
        {
            BDE_UnderSlungLauncher_Base launcher = host.BDE_USL_GetLauncher();

            if (launcher && launcher.GetHierarchyParent() == host)
                return launcher.BDE_USL_GetHUDShortName();
        }

        return super.GetItemDesc(entity);
    }

    override protected void SetWeaponQuantity(int chamber, int mag, string itemWidget, string quantityPBWidget, string quantityTextWidget, bool enabled)
    {
        super.SetWeaponQuantity(chamber, mag, itemWidget, quantityPBWidget, quantityTextWidget, enabled);

        if (!enabled)
            return;

        Weapon_Base host = Weapon_Base.Cast(m_EntityInHands);
        if (!host)
            return;

        Widget itemRoot = m_Root.FindAnyWidget(itemWidget);
        if (!itemRoot)
            return;

        TextWidget quantityText = TextWidget.Cast(itemRoot.FindAnyWidget(quantityTextWidget));
        if (!quantityText)
            return;

        BDE_Six12 six12 = BDE_USL_GetActiveSix12(host);
        if (six12)
        {
            quantityText.SetText(six12.BDE_Six12_GetAmmoCount().ToString());
            quantityText.Show(true);
            quantityText.GetParent().Show(true);
            return;
        }

        if (!host.BDE_USL_IsLauncherModeSelected())
            return;

        BDE_UnderSlungLauncher_Base launcher = host.BDE_USL_GetLauncher();
        if (!launcher || launcher.GetHierarchyParent() != host)
            return;

        string launcherQuantity = "x";
        if (launcher.BDE_USL_HasLiveRound())
            launcherQuantity = "1";

        string ammoLabel = launcher.BDE_USL_GetHUDAmmoLabel();
        if (launcher.BDE_USL_HasLiveRound() && ammoLabel != "")
            launcherQuantity = launcherQuantity + " " + ammoLabel;

        quantityText.SetText(launcherQuantity);
        quantityText.Show(true);
        quantityText.GetParent().Show(true);
    }
}
