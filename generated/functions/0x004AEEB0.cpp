// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEEB0 rf_splitscreen_set_configured_player_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Recovered4AEEB0..4AEEBD, lastRET4AEEBC. Cdecl signed count DWORD; store raw to configured count662C6C and RET. No clamp to1/2, player creation, viewport
// update, local-entry count synchronization or runtime guard. Negative/excessive values stored unchanged. No semantic return value.
void __cdecl rf_splitscreen_set_configured_player_count(int count)
{
  rf_splitscreen_local_player_count = count;
}

