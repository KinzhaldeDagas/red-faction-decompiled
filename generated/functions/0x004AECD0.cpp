// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AECD0 rf_splitscreen_stop_all_announcer_voices
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Noarg. For exactly11 rows662C80 stride12, if handleDWORD+4 != -1 call gamesound_stop_voice_handle. Does NOT set stopped handles-1, clear played bytes, change
// event IDs, stop unrelated voices or test backend success. Returns integer11 from final loop increment; repeated calls revisit same stored handles, whose delegates generation-check
// them.
int rf_splitscreen_stop_all_announcer_voices()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 11; ++i )
  {
    if ( dword_662C84[3 * i] != -1 )
      rf_gamesound_stop_voice_handle(dword_662C84[3 * i]);
    result = i + 1;
  }
  return result;
}

