// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EBC30 rf_fpgun_action_is_active
// UNREALRED VERIFIED [fpgun-action-dispatch]: Resolves a semantic action and tests for nonzero VMesh remaining time.
bool __cdecl rf_fpgun_action_is_active(_DWORD *a1, unsigned int a2)
{
  int named_animation_entry; // [esp+0h] [ebp-10h]
  signed int selected_weapon_and_resolve_mesh; // [esp+8h] [ebp-8h]

  if ( a1 != (_DWORD *)rf_local_fpgun_player )
    return 0;
  if ( a2 >= 0xC )
    return 0;
  if ( !rf_entity_resolve_handle(a1[5]) )
    return 0;
  selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(a1);
  if ( selected_weapon_and_resolve_mesh < 0 )
    return 0;
  named_animation_entry = rf_weapon_find_named_animation_entry(
                            selected_weapon_and_resolve_mesh,
                            (char *)rf_fpgun_action_names[a2],
                            0);
  if ( named_animation_entry < 0 )
    return 0;
  if ( !*((_DWORD *)&unk_9122F4 + 340 * selected_weapon_and_resolve_mesh + 7 * named_animation_entry + 4) )
    return 0;
  if ( a1[13] )
    return rf_vfx_get_remaining_time(
             (const void *)a1[13],
             *((_DWORD *)&unk_9122F4 + 340 * selected_weapon_and_resolve_mesh + 7 * named_animation_entry + 4)) != 0.0;
  return 0;
}

