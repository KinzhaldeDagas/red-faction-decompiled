// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2640 rf_player_entity_has_armed_timer1216_or1220
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL; resolve own entity UID+20, missing returns AL0. Test exactly two4-byte timestamp objects entity+1216/+1220 via replicator-is-armed40D0F0; any nonzero result returns AL1, otherwise0. Does not compare deadlines to current time, reset timers or test a broader array.
char __cdecl rf_player_entity_has_armed_timer1216_or1220(int a1)
{
  int i; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  v3 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v3 )
    return 0;
  for ( i = 0; i < 2; ++i )
  {
    if ( rf_replicator_is_armed((_DWORD *)(v3 + 4 * i + 1216)) )
      return 1;
  }
  return 0;
}

