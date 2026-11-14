// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402540 rf_ai_player_candidate_has_other_mode3_tracker
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Cdecl(candidate common/entity record,source record to exclude). Candidate player-association predicate ANY
// nonzero AL is required; otherwise returnsAL0 before list scan. Walk entity list68211C to681E90 via next+652, excludes BOTH candidate and second input by POINTER equality. A peer
// qualifies when inactive predicate!=EXACT AL1, raw peer target DWORD+1376==candidate full handle DWORD+44, and peer primary mode DWORD+1312==3; first match returnsAL1, noneAL0.
// Input polarity is candidate FIRST and owner/exclusion SECOND, as used by402160. Does not require humanoid, live/not-dead, unholstered, same friendliness, valid/resolved target,
// distance or geometry admission; no state mutation. No own second-input dereference and no independent candidate null guard beyond delegated association predicate.
char __cdecl rf_ai_player_candidate_has_other_mode3_tracker(int a1, int a2)
{
  int i; // [esp+0h] [ebp-4h]

  if ( !rf_object_is_player_associated(a1) )
    return 0;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( i != a2
      && i != a1
      && !rf_object_has_respawn_inactive_flag(i)
      && *(_DWORD *)(i + 1376) == *(_DWORD *)(a1 + 44)
      && *(_DWORD *)(i + 1312) == 3 )
    {
      return 1;
    }
  }
  return 0;
}

