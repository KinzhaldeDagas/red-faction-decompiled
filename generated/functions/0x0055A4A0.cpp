// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A4A0 rf_vector_rotate_translate_in_place
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments mutable3-floatpoint,translation,matrix3. Computes matrix-rotatedpoint through rf_matrix3_rotate_vector then adds translation and copies into originalpoint. No matrix normalization or scaling validation. Return follows vector-copy helper.
float *__cdecl rf_vector_rotate_translate_in_place(float *destination, float *rhs, float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float copy_result[3]; // [esp+0h] [ebp-24h] BYREF
  float sum_result[3]; // [esp+Ch] [ebp-18h] BYREF
  float v8[3]; // [esp+18h] [ebp-Ch] BYREF

  v3 = rf_matrix3_rotate_vector(destination, v8, a3);
  v4 = rf_vector_add(v3, sum_result, rhs);
  return rf_vector_copy(destination, copy_result, v4);
}

