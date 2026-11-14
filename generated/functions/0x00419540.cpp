// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419540 rf_math_ceil_float
// UNREALRED VERIFIED [hud-ammo-general] Thin float wrapper that forwards to rf_math_ceil_float_core and returns its ceiling result. The prior imported-symbol-derived log name was not faithful to the called implementation.
double __cdecl rf_math_ceil_float(float a1)
{
  return rf_math_ceil_float_core(a1);
}

