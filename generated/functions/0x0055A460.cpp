// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A460 rf_vector_inverse_translate_rotate_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): cdecl(pointXYZ,translationXYZ,orientationMatrix). Replaces point with point-translation, then inverse-rotates in place via the matrix inverse-rotation helper. Returns point destination. Assumes supplied matrix suitable for transpose/inverse rotation, performs no true matrix inversion or validation.
float *__cdecl rf_vector_inverse_translate_rotate_in_place(float *lhs, float *rhs, float *a3)
{
  float *v3; // eax
  float copy_result[3]; // [esp+0h] [ebp-18h] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-Ch] BYREF

  v3 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(lhs, copy_result, v3);
  return rf_matrix3_inverse_rotate_vector(lhs, a3);
}

