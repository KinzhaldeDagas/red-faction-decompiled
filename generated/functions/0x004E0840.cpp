// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E0840 rf_player_has_live_entity_outside_monitor_and_turret
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Reject monitor predicate AL==1, then resolve own entity UID+20; reject missing, attached-use-turret AL==1, or any nonzero dead predicate. Otherwise AL1. No playerNULL guard before UID access; does not reject attached vehicles or carried bodies.
bool __cdecl rf_player_has_live_entity_outside_monitor_and_turret(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( rf_player_view_target_is_monitor(a1) )
    return 0;
  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v2 )
    return 0;
  if ( rf_entity_has_attached_use_turret(v2) )
    return 0;
  return !rf_entity_is_dead(v2);
}

