// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EBE30 rf_fpgun_get_state_animation_duration
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Recovered original229-byte application function4EBE30..4EBF15: complete prologue/branches/RET, adjacent alignment boundaries, original PE bytes and no overlapping function. Local-global equality, signed state0..2, resolved own entity, nonzero model52, selected weapon!=EXACT-1 required. Find name from verified state table(idle,run,loop_fire), selector EXACT1 chooses3-entry array+672. Missing entry or zero entry handle+16 ->x87+0; otherwise564FE0(model52,handle) and forward ST0 unchanged. No independent NULL guard or general weapon bounds check. No incoming code references currently identified; this does not imply observed runtime use. Distinct from12-slot action durationBD40 and from remaining-time helper.
double __cdecl rf_fpgun_get_state_animation_duration(int player, int state)
{
  int named_animation_entry; // [esp+0h] [ebp-14h]
  char *v4; // [esp+4h] [ebp-10h]
  unsigned int selected_weapon_and_resolve_mesh; // [esp+Ch] [ebp-8h]

  if ( player != rf_local_fpgun_player )
    return 0.0;
  if ( (unsigned int)state > 2 )
    return 0.0;
  if ( !rf_entity_resolve_handle(*(_DWORD *)(player + 20)) )
    return 0.0;
  if ( !*(_DWORD *)(player + 52) )
    return 0.0;
  selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)player);
  if ( selected_weapon_and_resolve_mesh == -1 )
    return 0.0;
  v4 = (char *)&rf_weapon_records + 1360 * selected_weapon_and_resolve_mesh;
  named_animation_entry = rf_weapon_find_named_animation_entry(
                            selected_weapon_and_resolve_mesh,
                            (char *)rf_fpgun_state_names[state],
                            1);
  if ( named_animation_entry < 0 )
    return 0.0;
  if ( *(_DWORD *)&v4[28 * named_animation_entry + 688] )
    return rf_model_animation_duration_seconds(
             (unsigned int *)*(_DWORD *)(player + 52),
             *(_DWORD *)&v4[28 * named_animation_entry + 688]);
  return 0.0;
}

