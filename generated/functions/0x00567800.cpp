// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567800 rf_round_float_to_step_truncating
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(value,step). Returns float(truncToInt32((value+0.5*step)/step)*step) throughST0. Positive-value nearest-step convention,not symmetric rounding for negatives because division result truncates toward0;ties biased by adding half-step. No zero/negative-step,nonfinite or integer-overflow guard.
double __cdecl rf_round_float_to_step_truncating(float value, float step)
{
  return (float)((double)(int)((step * 0.5 + value) / step) * step);
}

