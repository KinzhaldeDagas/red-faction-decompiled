// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490A50 rf_lag_compensation_snapshot_count_reset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments. Sets global snapshot countDWORD754150=0 only. Does not clear32 records,free embedded storage or restore entity fields. Existing record contents persist for
// reuse.
void rf_lag_compensation_snapshot_count_reset()
{
  unk_754150 = 0;
}

