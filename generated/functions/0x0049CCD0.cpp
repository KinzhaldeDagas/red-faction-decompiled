// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049CCD0 rf_multiplayer_compare_player_scores_descending
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores): Cdecl
// comparator of pointers to player pointers (qsort callback observed at49EA2A). Dereference each player, its DWORD+44 stats pointer, then SIGN-EXTEND score WORD+2. Return -1 when
// left score greater, +1 when smaller, 0 equal. Signed descending order, no subtraction/overflow trick, secondary key or stable tie ordering. No NULL/player/stats guards; comparator
// reads score again on <= branch.
int __cdecl rf_multiplayer_compare_player_scores_descending(const void *a1, const void *a2)
{
  if ( *(__int16 *)(*(_DWORD *)(*(_DWORD *)a1 + 44) + 2) <= *(__int16 *)(*(_DWORD *)(*(_DWORD *)a2 + 44) + 2) )
    return *(__int16 *)(*(_DWORD *)(*(_DWORD *)a1 + 44) + 2) < *(__int16 *)(*(_DWORD *)(*(_DWORD *)a2 + 44) + 2);
  else
    return -1;
}

