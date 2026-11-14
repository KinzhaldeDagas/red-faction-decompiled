// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AF080 rf_splitscreen_score_table_maximum_floor_zero
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Noarg. Initialize maximum0; for signed index0..<global count7B25E0, replace only when signed table7B2580[index] > current. Returns max(0,all scanned values),
// therefore0 for empty/nonpositive count or all-negative scores. No count capacity validation, active-bit filtering, player-list scan, sorting or writes; table population is separate
// and not established by this body.
int rf_splitscreen_score_table_maximum_floor_zero()
{
  int v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  v1 = 0;
  for ( i = 0; i < unk_7B25E0; ++i )
  {
    if ( unk_7B2580[i] > v1 )
      v1 = unk_7B2580[i];
  }
  return v1;
}

