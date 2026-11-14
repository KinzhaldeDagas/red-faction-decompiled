// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E190 rf_affine48_interpolate_matrix_inputs_staged
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): cdecl(output,A,B,fraction). Converts first9floats of A/B to quaternions582420, calls RF quaternion interpolation583D20, converts result to affine with translation0, then sets translation=(1-fraction)*A.translation+fraction*B.translation using ORIGINAL fraction. Quaternion helper wraps its LOCAL fraction into[0,1], so out-of-range fractions produce wrapped rotation but extrapolated translation; it also has near-identical chosen-B and zero-W quirks, no final normalization. Entire48byte result staged before copy, permitting output==A/B. No input orthogonalization or fraction clamp here.
float *__cdecl rf_affine48_interpolate_matrix_inputs_staged(float *a1, const float *a2, const float *a3, float a4)
{
  float v5[12]; // [esp+Ch] [ebp-60h] BYREF
  float v6[4]; // [esp+3Ch] [ebp-30h] BYREF
  float v7[4]; // [esp+4Ch] [ebp-20h] BYREF
  float v8[4]; // [esp+5Ch] [ebp-10h] BYREF

  rf_affine3x4_default_construct_noop(v5);
  rf_quaternion_from_matrix3x3(v6, (float *)a2);
  rf_quaternion_from_matrix3x3(v7, (float *)a3);
  rf_float4_construct_zero_zero_zero_one(v8);
  rf_quaternion_interpolate(v8, v6, (int)v7, a4);
  rf_quaternion_to_affine3x4_zero_translation(v8, v5);
  v5[9] = (1.0 - a4) * a2[9] + a3[9] * a4;
  v5[10] = (1.0 - a4) * a2[10] + a3[10] * a4;
  v5[11] = (1.0 - a4) * a2[11] + a3[11] * a4;
  qmemcpy(a1, v5, 0x30u);
  return a1;
}

