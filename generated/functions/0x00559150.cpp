// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559150 rf_matrix3_rotate_vector
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX input vector, stack(output,matrix), RET8. Output=(x*m0+y*m3+z*m6,x*m1+y*m4+z*m7,x*m2+y*m5+z*m8), i.e. input row vector times row-major3x3. Stages all outputs before stores, permitting output=input; no translation, projection, normalization or matrix validation. Returns output.
float *__thiscall rf_matrix3_rotate_vector(float *this, float *a2, float *a3)
{
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]

  v6 = *this * a3[2] + *(this + 1) * a3[5] + *(this + 2) * a3[8];
  v5 = *this * a3[1] + *(this + 1) * a3[4] + *(this + 2) * a3[7];
  v4 = *this * *a3 + *(this + 1) * a3[3] + *(this + 2) * a3[6];
  rf_vector3_set_components_return_destination(a2, v4, v5, v6);
  return a2;
}

