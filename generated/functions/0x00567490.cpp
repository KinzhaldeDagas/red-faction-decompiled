// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567490 rf_tsc_delta_to_seconds_calibrated
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl signed32 TSC delta. Returns float-rounded (double(delta)/double(DWORD1806908))/4 throughST0. Existing clock initializer calibrates1806908 as signed low32TSC difference across two250ms sleeps divided2; helper therefore applies its quarter-second calibration. No ready,zero-calibration,overflow,sign or TSC serialization guard.
double __cdecl rf_tsc_delta_to_seconds_calibrated(int a1)
{
  return (float)((double)a1 / (double)unk_1806908 / 4.0);
}

