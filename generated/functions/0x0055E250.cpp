// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E250 rf_affine48_interpolate_quaternion_inputs_staged
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): cdecl(output,quatA,quatB,translationA,translationB,fraction). RF quaternion interpolation into local, quaternion-to-affine into LOCAL48bytes, then translation linear interpolation using original fraction, final48byte copy to output. Thus translation extrapolates while quaternion helper wraps fraction. Local staging keeps original translation inputs intact until all three read, including output aliasing translation storage. No final orthonormal repair, pointer checks or local clamp.
float *__cdecl rf_affine48_interpolate_quaternion_inputs_staged(
        float *a1,
        const float *a2,
        const float *a3,
        const float *a4,
        const float *a5,
        float a6)
{
  float v7[12]; // [esp+Ch] [ebp-40h] BYREF
  float v8[4]; // [esp+3Ch] [ebp-10h] BYREF

  rf_affine3x4_default_construct_noop(v7);
  rf_float4_construct_zero_zero_zero_one(v8);
  rf_quaternion_interpolate(v8, (float *)a2, (int)a3, a6);
  rf_quaternion_to_affine3x4_zero_translation(v8, v7);
  v7[9] = (1.0 - a6) * *a4 + *a5 * a6;
  v7[10] = (1.0 - a6) * a4[1] + a5[1] * a6;
  v7[11] = (1.0 - a6) * a4[2] + a5[2] * a6;
  qmemcpy(a1, v7, 0x30u);
  return a1;
}

