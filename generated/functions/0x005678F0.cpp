// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005678F0 rf_sqrt_abs_branch_x87
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(float). If ordered value>=0 passes value to rf_sqrt_float;else passes -value. Floating result remains LIVE inST0 through epilogue despite old inferred void. No clamp/error flag;negative zero takes nonnegative branch and preserves its sign into sqrt,unlike bitwise fabs. NaN still reaches sqrt via negated branch.
double __cdecl rf_sqrt_abs_branch_x87(float value)
{
  float v2; // [esp+0h] [ebp-4h]

  if ( value >= 0.0 )
    return rf_sqrt_float(value);
  v2 = -value;
  return rf_sqrt_float(v2);
}

