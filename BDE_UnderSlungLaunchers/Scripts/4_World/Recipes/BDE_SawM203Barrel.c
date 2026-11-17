class BDE_SawM203Barrel extends RecipeBase
{
    override void Init()
    {
        m_Name = "Shorten M203 barrel";
        m_IsInstaRecipe = false;
        m_AnimationLength = 2;

        m_MinDamageIngredient[0] = -1;
        m_MaxDamageIngredient[0] = 3;
        m_MinQuantityIngredient[0] = -1;
        m_MaxQuantityIngredient[0] = -1;

        m_MinDamageIngredient[1] = -1;
        m_MaxDamageIngredient[1] = 3;
        m_MinQuantityIngredient[1] = -1;
        m_MaxQuantityIngredient[1] = -1;

        InsertIngredient(0, "BDE_M203_Barrel");

        m_IngredientAddHealth[0] = 0;
        m_IngredientSetHealth[0] = -1;
        m_IngredientAddQuantity[0] = 0;
        m_IngredientDestroy[0] = false;

        InsertIngredient(1, "Hacksaw", DayZPlayerConstants.CMD_ACTIONFB_SPLITTING_FIREWOOD, true);

        m_IngredientAddHealth[1] = -10;
        m_IngredientSetHealth[1] = -1;
        m_IngredientAddQuantity[1] = 0;
        m_IngredientDestroy[1] = false;
    }

    override bool CanDo(ItemBase ingredients[], PlayerBase player)
    {
        return ingredients[0] && ingredients[0].GetType() == "BDE_M203_Barrel" && !Weapon_Base.Cast(ingredients[0].GetHierarchyParent());
    }

    override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
    {
        MiscGameplayFunctions.TurnItemIntoItemEx(player, new TurnItemIntoItemLambda(ingredients[0], "BDE_M203_Short_Barrel", player));
    }
};
