// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEFC0 rf_splitscreen_get_settings_storage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Noarg. Return address7B256C, not a copy/value or owned allocation. Caller can modify shared configuration through returned pointer. No reads, initialization,
// validation or state writes.
int *rf_splitscreen_get_settings_storage()
{
  return (int *)&unk_7B256C;
}

