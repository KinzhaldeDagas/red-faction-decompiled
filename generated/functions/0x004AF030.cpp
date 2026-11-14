// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AF030 rf_splitscreen_find_score_rank_or_one
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Cdecl signed score. Index scan0..<signed count7B25E0 across DWORD scores7B2580. Return FIRST index+1 for which input >= table[index] in signed comparison.
// Critically default result index initialized0 and never changed on misses, so EMPTY/nonpositive count or score below EVERY entry returns1, not count+1/error. No sorting,
// unique-score handling, count/capacity validation or writes. Equal score hits first equal-or-lower entry; rank1 cannot by itself prove a winner.
int __cdecl rf_splitscreen_find_score_rank_or_one(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  v2 = 0;
  for ( i = 0; i < unk_7B25E0; ++i )
  {
    if ( a1 >= unk_7B2580[i] )
    {
      v2 = i;
      return v2 + 1;
    }
  }
  return v2 + 1;
}

