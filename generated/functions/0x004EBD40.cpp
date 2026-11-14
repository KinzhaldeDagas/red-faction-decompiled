// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EBD40 rf_fpgun_get_action_animation_duration
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Returns x87 duration. Reject unequal local-global, signed action slot outside0..11, missing own entity, zero model52, selected weapon EXACT-1, missing named first-person action entry(selector0), or zero entry handle16 ->FLDZ. Otherwise pass model52 and handle from weapon+756+28*entry+16 to564FE0 and return ST0 unchanged with no F32 spill. Restored callee floating return signature removes uninitialized-result pseudocode artifact. No independent NULL guard if both player/globalNULL or general selected index/handle bounds validation. Returns total clip duration, not remaining active time.
double __cdecl rf_fpgun_get_action_animation_duration(_DWORD *a1, unsigned int a2)
{
  int named_animation_entry; // [esp+0h] [ebp-14h]
  char *v4; // [esp+4h] [ebp-10h]
  unsigned int selected_weapon_and_resolve_mesh; // [esp+Ch] [ebp-8h]

  if ( a1 != (_DWORD *)rf_local_fpgun_player )
    return 0.0;
  if ( a2 >= 0xC )
    return 0.0;
  if ( !rf_entity_resolve_handle(a1[5]) )
    return 0.0;
  selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(a1);
  if ( !a1[13] )
    return 0.0;
  if ( selected_weapon_and_resolve_mesh == -1 )
    return 0.0;
  v4 = (char *)&rf_weapon_records + 1360 * selected_weapon_and_resolve_mesh;
  named_animation_entry = rf_weapon_find_named_animation_entry(
                            selected_weapon_and_resolve_mesh,
                            (char *)rf_fpgun_action_names[a2],
                            0);
  if ( named_animation_entry < 0 )
    return 0.0;
  if ( *(_DWORD *)&v4[28 * named_animation_entry + 772] )
    return rf_model_animation_duration_seconds((unsigned int *)a1[13], *(_DWORD *)&v4[28 * named_animation_entry + 772]);
  return 0.0;
}

