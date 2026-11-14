// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005594A0 rf_matrix3_inverse_rotate_vector
// UNREALRED VERIFIED [trigger-geometry-20261020] Exact row contract revalidated: output0=dot(input,row0), output1=dot(input,row1), output2=dot(input,row2). World Y-up/Z-up conversion applies to the rows and world positions; local trigger size scalars remain paired with their original row indices.
float *__thiscall rf_matrix3_inverse_rotate_vector(float *this, float *a2)
{
  float v3; // [esp+4h] [ebp-Ch]
  float v4; // [esp+8h] [ebp-8h]
  float v5; // [esp+Ch] [ebp-4h]

  v3 = *this;
  v5 = *(this + 1);
  v4 = *(this + 2);
  *this = v3 * *a2 + v5 * a2[1] + v4 * a2[2];
  *(this + 1) = v3 * a2[3] + v5 * a2[4] + v4 * a2[5];
  *(this + 2) = v3 * a2[6] + v5 * a2[7] + v4 * a2[8];
  return a2;
}

