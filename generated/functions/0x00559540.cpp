// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559540 rf_vector_rotate_by_matrix3
// UNREALRED VERIFIED [trigger-geometry-20261020] Inverse partner to5594A0: row coefficients are accumulated into world components. Combined with56BE90 this proves that local trigger size order is independent of the world coordinate-axis conversion.
float *__thiscall rf_vector_rotate_by_matrix3(float *this, float *a2)
{
  float v3; // [esp+4h] [ebp-Ch]
  float v4; // [esp+8h] [ebp-8h]
  float v5; // [esp+Ch] [ebp-4h]

  v3 = *this;
  v5 = *(this + 1);
  v4 = *(this + 2);
  *this = v3 * *a2 + v5 * a2[3] + v4 * a2[6];
  *(this + 1) = v3 * a2[1] + v5 * a2[4] + v4 * a2[7];
  *(this + 2) = v3 * a2[2] + v5 * a2[5] + v4 * a2[8];
  return a2;
}

