// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E8860 rf_fpgun_has_reload_fire_or_riotstick_state2
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Unequal global local-fpgun pointer returnsAL0; no independent NULL guard if both pointersNULL. First action8 reload NONZERO returns1; then action0 fire EXACT1 or action1 alt_fire EXACT1 returns1. Otherwise get selected weapon through0440 (may resolve/cache mesh), resolve own entity; found AND riot-stick predicate EXACT1 AND current-or-pending fpgun state2 predicate EXACT1 yields1, else0. Not a pure visibility/weapon-validity test, no draw/holster check, and selected-weapon helper has side effects.
bool __cdecl rf_fpgun_has_reload_fire_or_riotstick_state2(_DWORD *a1)
{
  unsigned int selected_weapon_and_resolve_mesh; // [esp+4h] [ebp-4h]

  if ( a1 != (_DWORD *)rf_local_fpgun_player )
    return 0;
  if ( rf_fpgun_action_is_active((int)a1, 8u) )
    return 1;
  if ( rf_fpgun_action_is_active((int)a1, 0) )
    return 1;
  if ( rf_fpgun_action_is_active((int)a1, 1u) )
    return 1;
  selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(a1);
  return rf_entity_resolve_handle(a1[5])
      && rf_weapon_is_riot_stick(selected_weapon_and_resolve_mesh)
      && rf_fpgun_state_is_resident((int)a1, 2);
}

