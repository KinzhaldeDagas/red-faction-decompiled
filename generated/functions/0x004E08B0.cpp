// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E08B0 rf_player_entity_mode1_or3_without_use_attachments
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Reject monitor predicate AL==1, missing own entity, attached-use vehicle AL==1, carried body AL==1 or attached-use turret AL==1. Return AL1 only if DWORD at *(entity+2136)+4 is EXACT1 or3. No separate death predicate, playerNULL or movement-record NULL check. Source-level meaning beyond these class IDs is not assigned.
bool __cdecl rf_player_entity_mode1_or3_without_use_attachments(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( rf_player_view_target_is_monitor(a1) )
    return 0;
  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v2 )
    return 0;
  if ( rf_entity_has_attached_use_vehicle(v2) )
    return 0;
  if ( rf_entity_is_carrying_body(v2) )
    return 0;
  if ( rf_entity_has_attached_use_turret(v2) )
    return 0;
  return *(_DWORD *)(*(_DWORD *)(v2 + 2136) + 4) == 1 || *(_DWORD *)(*(_DWORD *)(v2 + 2136) + 4) == 3;
}

