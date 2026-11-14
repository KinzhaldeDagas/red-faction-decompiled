// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00431DF0 rf_ai_switch_to_default_primary_after_launcher_exhaustion
// UNREALRED VERIFIED [ai-ammo-decode]: Grants and selects the archetype Default Primary and resets active weapon actions; it does not refill the exhausted launcher.
// UNREALRED VERIFIED [reload-exhaustion-caller-20260923]: This helper itself has no multiplayer or split-screen condition. It grants definition Default Primary (+0x88) with quantity -1, then unconditionally selects that same identity after the grant returns; any selector side effect inside a new grant is overwritten by 0x431E28. The reload owner calls it directly in every admitted runtime mode. Only the separate failed-fire caller at 0x4325E3 chooses between this helper and 0x4014F0. Earlier standalone-only descriptions generalized the fire caller too broadly.
// UNREALRED VERIFIED [default-grant-no-clip-20260924]: The internal grant at 0x431E0C passes quantity -1, including defaults without a positive active clip. For a newly owned no-clip default, a valid ammo pool is decremented and clamped to 0/active maximum; an invalid ammo index causes no ammo writes. An already-owned default remains untouched. In every case this caller still selects the authored default at 0x431E28. This is the direct inventory grant contract, not the ordinary weapon-pickup caller and its companion-record behavior.
void __cdecl rf_ai_switch_to_default_primary_after_launcher_exhaustion(int *a1)
{
  int i; // [esp+0h] [ebp-4h]

  rf_entity_inventory_grant_weapon(a1, *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 136), -1);
  a1[1] = *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 136);
  if ( rf_entity_body_action_is_active(*a1, 2u) || rf_entity_body_action_is_active(*a1, 3u) )
    rf_model_handle_reset_actions_adapter(*(_DWORD *)(*a1 + 128));
  rf_replicator_arm_milliseconds(a1 + 297, 500);
  rf_replicator_arm_milliseconds(a1 + 134, 500);
  for ( i = 0; i < 2; ++i )
    rf_replicator_reset(&a1[i + 136]);
  rf_entity_restore_action_tables_and_apply_weapon_overrides(*a1, *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 136));
}

