// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401EF0 rf_ai_has_unholstered_mode3_peer_on_same_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): One required AI block; owner pointer at DWORD+0. Walks complete entity list68211C to681E90 via next+652,
// excludes owner by POINTER equality, not by handle. Requires peer DWORD+504==0, dead predicate!=EXACT AL1, humanoid predicate any-nonzero, inactive predicate!=EXACT1, owner-holster
// predicate!=EXACT1, peer numeric primary mode DWORD+1312==3, and peer raw target DWORD+1376==input AI raw target+704. First qualifying peer returns canonical AL1; no peer AL0. No
// input-owner mode3 requirement, target resolution, target!=-1 requirement, distance/geometry query, multiplayer/authority or peer friendliness-match-to-source test. Consequently raw
// shared target-1 may qualify. No state writes; upper EAX bits are not independently boolean-canonicalized.
char __cdecl rf_ai_has_unholstered_mode3_peer_on_same_target(_DWORD *a1)
{
  int i; // [esp+0h] [ebp-8h]
  char v3; // [esp+7h] [ebp-1h]

  v3 = 0;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( i != *a1
      && !*(_DWORD *)(i + 504)
      && !rf_entity_is_dead(i)
      && rf_entity_has_humanoid_flag(i)
      && !rf_object_has_respawn_inactive_flag(i)
      && !rf_entity_weapon_is_holstered_for_actions(i)
      && *(_DWORD *)(i + 1312) == 3
      && *(_DWORD *)(i + 1376) == a1[176] )
    {
      return 1;
    }
  }
  return v3;
}

