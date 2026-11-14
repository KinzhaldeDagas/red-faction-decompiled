// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBA90 rf_player_weapon_action_context_is_available
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player; missing resolved entity returnsfalse. Rejects attached-vehicle predicate AL EXACT1; attached-turret ANY nonzero; monitor predicate EXACT1; carrying-body predicate EXACT1; custom-action-busy EXACT1; weapon-holstered-for-actions EXACT1. Otherwise true. No own health, ammo, selected weapon, player NULL or model check; these predicates define this context only.
bool __cdecl rf_player_weapon_action_context_is_available(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v2 )
    return 0;
  if ( rf_entity_has_attached_use_vehicle(v2) )
    return 0;
  if ( rf_entity_has_attached_use_turret(v2) )
    return 0;
  if ( rf_player_view_target_is_monitor(a1) )
    return 0;
  if ( rf_entity_is_carrying_body(v2) )
    return 0;
  if ( rf_fpgun_custom_action_busy(a1) )
    return 0;
  return !rf_entity_weapon_is_holstered_for_actions(v2);
}

