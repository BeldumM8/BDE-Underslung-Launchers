modded class ItemActionsWidget
{
    override protected void SetWeaponModeAndZeroing(string itemWidget, string upWidget, string downWidget, bool enabled)
    {
        Widget widget = m_Root.FindAnyWidget(itemWidget);

        if (enabled && m_Player)
        {
            TextWidget modeWidget;
            TextWidget zeroingWidget;
            Class.CastTo(modeWidget, widget.FindAnyWidget(upWidget));
            Class.CastTo(zeroingWidget, widget.FindAnyWidget(downWidget));

            Weapon_Base host = Weapon_Base.Cast(m_Player.GetEntityInHands());
            string zeroing = string.Empty;

            if (host)
            {
                BDE_UnderSlungLauncher_Base launcher = host.BDE_USL_GetLauncher();

                if (launcher && host.BDE_USL_IsLauncherModeSelected())
                    zeroing = string.Format("%1 m", launcher.BDE_USL_GetCurrentAimZeroing());
                else
                    zeroing = string.Format("%1 m", host.GetCurrentZeroing(host.GetCurrentMuzzle()));
            }

            modeWidget.SetText(m_Player.GetWeaponManager().GetCurrentModeName());
            zeroingWidget.SetText(zeroing);
            widget.Show(true);
        }
        else
        {
            widget.Show(false);
        }
    }
}
