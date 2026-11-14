// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419560 rf_math_ceil_float_core
// UNREALRED VERIFIED [hud-ammo-general] Converts one float to its ceiling by calling the CRT ceil routine and returning the result as a float.
double __cdecl rf_math_ceil_float_core(float a1)
{
  return (float)ceil(a1);
}

