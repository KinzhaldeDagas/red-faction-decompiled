// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEFF0 rf_splitscreen_initialize_settings_defaults
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Noarg. Store DWORD7B256C=2, DWORD7B2570=2, signed score-limit7B2574=15, minutes7B2578=15, BYTE7B257C=1, in that order. Does not memset remainder, set
// configured-local-player count662C6C, start timer, reset active match/end flags, load resources or validate previous config.
void rf_splitscreen_initialize_settings_defaults()
{
  unk_7B256C = 2;
  unk_7B2570 = 2;
  dword_7B2574 = 15;
  unk_7B2578 = 15;
  unk_7B257C = 1;
}

