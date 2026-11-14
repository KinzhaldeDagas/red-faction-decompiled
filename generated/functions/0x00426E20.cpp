// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00426E20 rf_entity_ai_update_admit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl entity pointer, canonical AL0/1; no writes in this wrapper. First runtime BYTE==EXACT1 AND authority BYTE==0 rejects; runtime other
// bytes bypass this authority test. Player-flag predicate EXACT AL1 rejects. Local-player-or-related predicate ANY nonzero then requires4390E0 ANY nonzero; this extra admits only
// authored-jeep with unchecked second relation resolving COMMON, not ordinary direct player ownership. Dead predicate EXACT AL1 rejects. After all these, entity DWORD+2068 HIGHBIT
// set immediately returns1, bypassing room/common-flags gate. Otherwise cached room firstDWORD must be nonNULL and common flags DWORD+124 mask00800000 must be CLEAR. Room is not
// queried and liquid/type/deadline/visibility/owner pending-delete not checked here. No own pointer guard before delegates or general server-only admission for runtime bytes other
// than1.
bool __cdecl rf_entity_ai_update_admit(_DWORD *a1)
{
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    return 0;
  if ( rf_object_has_player_flag((int)a1) )
    return 0;
  if ( rf_entity_matches_local_player_or_related_handle((int)a1)
    && !rf_entity_jeep_second_relation_resolves_object((int)a1) )
  {
    return 0;
  }
  if ( rf_entity_is_dead((int)a1) )
    return 0;
  if ( (int)a1[517] < 0 )
    return 1;
  if ( rf_receiver_get_first_dword(a1) )
    return ((unsigned int)&unk_800000 & a1[31]) == 0;
  return 0;
}

