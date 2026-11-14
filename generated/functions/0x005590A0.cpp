// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005590A0 rf_vector3_transform_by_matrix_rows
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Thiscall (input vector in ECX, output pointer, matrix9f pointer). Computes out.x=dot(input,matrix[0..2]), out.y=dot(input,matrix[3..5]), out.z=dot(input,matrix[6..8]); computes all three into locals before storing through vector-set helper, allowing input/output aliasing. Returns output pointer. No translation, normalization or matrix mutation.
float *__thiscall rf_vector3_transform_by_matrix_rows(float *this, float *a2, float *a3)
{
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]

  v6 = *this * a3[6] + *(this + 1) * a3[7] + *(this + 2) * a3[8];
  v5 = *this * a3[3] + *(this + 1) * a3[4] + *(this + 2) * a3[5];
  v4 = *this * *a3 + *(this + 1) * a3[1] + *(this + 2) * a3[2];
  rf_vector3_set_components_return_destination(a2, v4, v5, v6);
  return a2;
}

