modded class CleanWeapon
{
    override void Init()
    {
        super.Init();
        InsertIngredient(1, "BDE_M203_Barrel", DayZPlayerConstants.CMD_ACTIONFB_CLEANING_WEAPON, true);
        InsertIngredient(1, "BDE_M203_Short_Barrel", DayZPlayerConstants.CMD_ACTIONFB_CLEANING_WEAPON, true);
        InsertIngredient(1, "BDE_FN40_Barrel", DayZPlayerConstants.CMD_ACTIONFB_CLEANING_WEAPON, true);
    }
}
