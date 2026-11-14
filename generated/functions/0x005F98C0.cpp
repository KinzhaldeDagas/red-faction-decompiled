// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F98C0 rf_noise_gradient2_normalize_unchecked
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl mutable float[2]. Computes float lengthSq=x*x+y*y,sqrt via rf_sqrt_float,float-rounded length,divides both components by length,returns pointer. No zero/finite check or fallback;zero vector produces division by zero/NaNs. Used by random noise table initializer.
float *__cdecl rf_noise_gradient2_normalize_unchecked(float *a1)
{
  float v2; // [esp+4h] [ebp-8h]
  float v3; // [esp+8h] [ebp-4h]

  v2 = *a1 * *a1 + a1[1] * a1[1];
  v3 = rf_sqrt_float(v2);
  *a1 = *a1 / v3;
  a1[1] = a1[1] / v3;
  return a1;
}

