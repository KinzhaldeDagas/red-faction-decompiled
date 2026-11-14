// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D300 rf_frame_clock_restore_saved_duration_limits
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Calls56D250 with backup floats18092FC/1809300,which sorts them into current min/max. Does not test whether backup was saved,clear it or maintain nesting; before first save BSS values can restore both bounds0. No clock sampling or delta recalculation.
void __cdecl rf_frame_clock_restore_saved_duration_limits()
{
  rf_frame_clock_set_duration_limits_sorted(flt_18092FC, flt_1809300);
}

