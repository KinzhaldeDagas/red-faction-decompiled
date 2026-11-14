// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E300 rf_affine48_interpolate_quaternion_inputs_direct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): Same6cdecl args as55E250 but converts interpolated quaternion DIRECTLY into output affine BEFORE reading translation pointers, zeroing output translation. Then writes translation components sequentially from original fraction. If translation input aliases output+36, prior zeroing changes source values; differs from staged variant. Rotation interpolation wraps fraction while translation uses unwrapped fraction; no final normalization.
float *__cdecl rf_affine48_interpolate_quaternion_inputs_direct(
        float *a1,
        const float *a2,
        const float *a3,
        const float *a4,
        const float *a5,
        float a6)
{
  float v7[4]; // [esp+4h] [ebp-10h] BYREF

  rf_float4_construct_zero_zero_zero_one(v7);
  rf_quaternion_interpolate(v7, (float *)a2, (int)a3, a6);
  rf_quaternion_to_affine3x4_zero_translation(v7, a1);
  a1[9] = (1.0 - a6) * *a4 + *a5 * a6;
  a1[10] = (1.0 - a6) * a4[1] + a5[1] * a6;
  a1[11] = (1.0 - a6) * a4[2] + a5[2] * a6;
  return a1;
}

