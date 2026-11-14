// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AF210 rf_splitscreen_get_match_ended_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Noarg. Return raw BYTE7B25DC in AL without Boolean normalization or zeroing highEAX. No update/render, score/time test or mutation. Nonzero values other than1
// remain visible to callers.
char rf_splitscreen_get_match_ended_byte()
{
  return unk_7B25DC;
}

