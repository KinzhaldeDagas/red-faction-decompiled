// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583C60 rf_float4_dot
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Cdecl two float[4] pointers; computes four component products and sequential sum in x87, rounds final sum to float local then returns through ST0. No normalization, scaling, finite or NULL check. Used for quaternion sign and interpolation decisions.
double __cdecl rf_float4_dot(float *a1, float *a2)
{
  return (float)(*a1 * *a2 + a1[1] * a2[1] + a1[2] * a2[2] + a1[3] * a2[3]);
}

