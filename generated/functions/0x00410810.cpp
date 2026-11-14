// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00410810 rf_vector_cross
// UNREALRED VERIFIED [projected-shadow-cone-20260903]: Computes the exact three-component cross product. The projected-shadow builder uses global up cross the entity orientation row to complete its orthonormal lateral basis.
float *__thiscall rf_vector_cross(float *this, float *a2, float *a3)
{
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]

  v6 = *this * a3[1] - *(this + 1) * *a3;
  v5 = *(this + 2) * *a3 - *this * a3[2];
  v4 = *(this + 1) * a3[2] - *(this + 2) * a3[1];
  rf_vector3_set_components_return_destination(a2, v4, v5, v6);
  return a2;
}

