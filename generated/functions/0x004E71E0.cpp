// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E71E0 rf_fpgun_request_holster_action
// UNREALRED VERIFIED [fpgun-action-dispatch]: Requests holster from the weapon-selection path.
char __cdecl rf_fpgun_request_holster_action(int a1)
{
  int v1; // eax
  unsigned int selected_weapon_and_resolve_mesh; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  LOBYTE(v1) = a1;
  if ( a1 == rf_local_fpgun_player )
  {
    rf_player_reset_alt_zoom_state(a1);
    sub_4E71A0(a1);
    *(_BYTE *)(a1 + 4016) = 0;
    rf_fpgun_dispatch_semantic_action(a1, 7u);
    selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
    if ( rf_weapon_selected_mode_is_continuous_exact_selector(selected_weapon_and_resolve_mesh, 0)
      || rf_weapon_selected_mode_is_continuous_exact_selector(selected_weapon_and_resolve_mesh, 1) )
    {
      rf_entity_stop_weapon_firing(*(_DWORD *)(a1 + 20), selected_weapon_and_resolve_mesh);
    }
    v1 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    v4 = v1;
    if ( v1 )
    {
      LOBYTE(v1) = rf_weapon_is_riot_stick(selected_weapon_and_resolve_mesh);
      if ( (unsigned __int8)v1 == 1 )
        LOBYTE(v1) = rf_replicator_arm_milliseconds((int *)(v4 + 4972), 0);
    }
  }
  return v1;
}

