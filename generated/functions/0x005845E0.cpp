// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005845E0 rf_quaternion_relative_unit_log
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered cdecl(out,A,B):conjugates A tolocal,normalizes that float quaternion with583030,computes normalizedConjugate(A)*B using Hamilton product5829C0,takes unit-log583140,assigns to output,returns output. No exponential or control weight;not a full non-unit inverse because normalization rather than divide-by-norm-squared. No zero/finite guard;output temp permits exact alias.
float *__cdecl rf_quaternion_relative_unit_log(float *a1, const float *a2, const float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float v6[4]; // [esp+0h] [ebp-40h] BYREF
  float v7[4]; // [esp+10h] [ebp-30h] BYREF
  float v8[4]; // [esp+20h] [ebp-20h] BYREF
  float v9[4]; // [esp+30h] [ebp-10h] BYREF

  rf_quaternion_conjugate_to_destination((float *)a2, v8);
  rf_quaternion_normalized_to_destination_unchecked(v8, v9);
  v3 = rf_quaternion_hamilton_product_to_destination(v9, v7, (float *)a3);
  v4 = rf_quaternion_unit_log_to_destination(v3, v6);
  rf_float4_copy_return_destination(v8, v4);
  rf_float4_assign_components_return_this(a1, v8);
  return a1;
}

