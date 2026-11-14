// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1D60 rf_record16_should_swap_descending
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Cdecl(leftRecord,rightRecord,low BYTE mode),12-byte caller cleanup. Mode0 returns ordered right.X>left.X. Nonzero mode: returns true on ordered right.X>left.X with delta>epsilon,else on right.Y>left.Y with delta>epsilon,else on right.Z>left.Z with delta>epsilon,else returns ordered right.X>left.X even when X delta<=epsilon. Epsilon is stored double0.003000000026077032(near float0.003 promoted). Differences use x87 FSUB directly before compare,no intervening float store. Effective finite predicate is right.X>left.X OR right.Y-left.Y>epsilon OR right.Z-left.Z>epsilon(with each corresponding strict greater gate),so X epsilon does NOT suppress small positive X differences. No
// requirement earlier axes equal/near; can prefer opposite directions for left(1,0,0),right(0,1,0). Not a valid strict-weak/lexicographic comparator. Raw TEST AH,41h/JNZ rejects unordered for each tested comparison; unrelated finite axes may still trigger. Ignores fourth DWORD; no writes or bounds validation.
bool __cdecl rf_record16_should_swap_descending(float *a1, float *a2, char a3)
{
  if ( !a3 )
    return *a2 > (double)*a1;
  if ( *a2 > (double)*a1 && *a2 - *a1 > 0.003000000026077032 )
    return 1;
  if ( a2[1] > (double)a1[1] && a2[1] - a1[1] > 0.003000000026077032 )
    return 1;
  return a2[2] > (double)a1[2] && a2[2] - a1[2] > 0.003000000026077032 || *a2 > (double)*a1;
}

