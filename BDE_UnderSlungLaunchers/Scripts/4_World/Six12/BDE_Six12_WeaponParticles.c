modded class WeaponParticlesOnFire
{
    override void OnActivate(ItemBase weapon, int muzzle_index, string ammoType, ItemBase muzzle_owner, ItemBase suppressor, string config_to_search)
    {
        if (weapon && weapon.IsKindOf("BDE_Six12"))
            return;

        super.OnActivate(weapon, muzzle_index, ammoType, muzzle_owner, suppressor, config_to_search);
    }
}
