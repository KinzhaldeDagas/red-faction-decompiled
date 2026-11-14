// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005597C0 rf_random_unit_vector_in_cone
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX output plus direction XYZ passed BY VALUE as3float stack words and minimumDot float, RET16; corrected old int triple. Builds55C050 orientation from local by-value direction, samples559730 local cone then rotates output in place. General basis preserves RAW forward and nonunit up, so output need not be unit for nonunit direction. Near-vertical basis snaps forward; no minimumDot clamp here or final normalization.
float *__thiscall rf_random_unit_vector_in_cone(float *this, float a2, float a3, float a4, float a5)
{
  float v7[9]; // [esp+8h] [ebp-24h] BYREF

  rf_matrix3_construct((char *)v7);
  rf_orientation_matrix_from_direction(v7, (int)&a2);
  rf_random_unit_vector_in_local_cone(this, a5);
  return rf_vector_rotate_by_matrix3(this, v7);
}

