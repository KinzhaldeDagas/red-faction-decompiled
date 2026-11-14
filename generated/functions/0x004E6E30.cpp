// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6E30 rf_fpgun_request_fire_action
// UNREALRED VERIFIED [fpgun-action-dispatch]: Requests alt_fire when admitted and available; otherwise requests fire.
char __cdecl rf_fpgun_request_fire_action(_DWORD *a1, char a2)
{
  int v2; // eax
  unsigned int v4; // [esp+0h] [ebp-10h]
  unsigned int selected_weapon_and_resolve_mesh; // [esp+4h] [ebp-Ch]
  int v6; // [esp+Ch] [ebp-4h]

  LOBYTE(v2) = (_BYTE)a1;
  if ( a1 == (_DWORD *)rf_local_fpgun_player )
  {
    if ( a1 )
    {
      v2 = rf_entity_resolve_handle(a1[5]);
      v6 = v2;
      if ( v2 )
      {
        selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(a1);
        v4 = a2 == 1;
        if ( !rf_weapon_has_loaded_fpgun_action_animation(selected_weapon_and_resolve_mesh, 1u) )
          v4 = 0;
        if ( !rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(v6 + 44), selected_weapon_and_resolve_mesh) )
          rf_fpgun_dispatch_semantic_action((int)a1, v4);
        sub_4EBD20((int)a1);
        rf_replicator_arm_milliseconds((int *)(v6 + 4972), 50);
        LOBYTE(v2) = rf_weapon_is_riot_stick(selected_weapon_and_resolve_mesh);
        if ( (unsigned __int8)v2 == 1 )
          LOBYTE(v2) = (unsigned __int8)rf_replicator_reset((_DWORD *)(v6 + 4972));
      }
    }
  }
  return v2;
}

