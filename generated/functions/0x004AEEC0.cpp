// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEEC0 rf_splitscreen_get_configured_player_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Recovered4AEEC0..4AEECA, lastRET4AEEC9. Cdecl noargs; return raw DWORD configured count662C6C in EAX. No validation/normalization or state mutation; not
// current allocated local-player entry count87C638.
int __cdecl rf_splitscreen_get_configured_player_count()
{
  return rf_splitscreen_local_player_count;
}

