// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004013A0 sub_4013A0
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Initial no-primary helper writesAI+4=literal3 BEFORE calling403AB0(3,-1), then438DE0 holdingrefresh. This DOES grant3 ifnotalreadyowned and prevents recursion because primary isalready3. Distinct from4014F0 later no-player-record branch which merely selects3 withoutgrant.
void __cdecl sub_4013A0(int *a1)
{
  a1[1] = 3;
  rf_entity_inventory_grant_weapon((int)a1, 3, -1);
  rf_entity_restore_action_tables_and_apply_weapon_overrides(*a1, a1[1]);
}

