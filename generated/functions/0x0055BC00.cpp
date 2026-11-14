// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055BC00 rf_random_orientation_matrix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Samples RF random unit direction into local vector5596A0 then builds orientation55C050 from that forward. Roll is determined by fixed reference-basis rule, not sampled independently; not a uniform sample over all3D orientations. No additional orthonormal repair or matrix default constructor here; returns builder result.
float *__thiscall rf_random_orientation_matrix(float *this)
{
  float v3[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v3);
  rf_random_unit_vector(v3);
  return rf_orientation_matrix_from_direction(this, (int)v3);
}

