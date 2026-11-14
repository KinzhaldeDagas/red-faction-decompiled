// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056BE90 rf_segment_intersects_oriented_box
// UNREALRED VERIFIED [trigger-geometry-20261020] Transforms BOTH finite segment endpoints into trigger row coordinates by subtracting center and dotting against matrix rows via5594A0. Builds local min/max as full dimensions times-0.5/+0.5, then calls56C450. Dimensions belong to the matrix rows and must not be permuted as world-space vectors after converting the orientation. UnrealRed previously swapped local Y/Z at import; corrected scalar order affects1682 of2120 retail box triggers.
bool __cdecl rf_segment_intersects_oriented_box(float *rhs, float *a2, float *vector, float *lhs, float *a5, float *a6)
{
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float v11[3]; // [esp+8h] [ebp-70h] BYREF
  float v12[3]; // [esp+14h] [ebp-64h] BYREF
  float v13[3]; // [esp+20h] [ebp-58h] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-4Ch] BYREF
  float v15[3]; // [esp+38h] [ebp-40h] BYREF
  float v16[3]; // [esp+44h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+50h] [ebp-28h] BYREF
  float out_vector[3]; // [esp+5Ch] [ebp-1Ch] BYREF
  bool v19; // [esp+6Bh] [ebp-Dh]
  int v20; // [esp+74h] [ebp-4h]

  if ( (dword_1809260 & 1) == 0 )
  {
    dword_1809260 |= 1u;
    rf_vector3_default_construct_noop(&flt_1809254);
    v20 = -1;
  }
  if ( (dword_1809260 & 2) == 0 )
  {
    dword_1809260 |= 2u;
    rf_vector3_default_construct_noop(&flt_1809248);
    v20 = -1;
  }
  v6 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(&flt_1809254, copy_result, v6);
  rf_matrix3_inverse_rotate_vector(&flt_1809254, a2);
  v7 = rf_vector_subtract(a5, v16, rhs);
  rf_vector_copy(&flt_1809248, v15, v7);
  rf_matrix3_inverse_rotate_vector(&flt_1809248, a2);
  if ( (dword_1809260 & 4) == 0 )
  {
    dword_1809260 |= 4u;
    v20 = 2;
    rf_vector3_default_construct_noop(&flt_180923C);
    v20 = -1;
  }
  if ( (dword_1809260 & 8) == 0 )
  {
    dword_1809260 |= 8u;
    v20 = 3;
    rf_vector3_default_construct_noop(&flt_1809230);
    v20 = -1;
  }
  v8 = rf_vector_multiply_scalar(vector, scaled_result, -0.5);
  rf_vector_copy(&flt_180923C, v13, v8);
  v9 = rf_vector_multiply_scalar(vector, v12, 0.5);
  rf_vector_copy(&flt_1809230, v11, v9);
  v19 = rf_segment_intersects_aabb(&flt_180923C, &flt_1809230, &flt_1809254, &flt_1809248, a6);
  rf_vector_rotate_by_matrix3(a6, a2);
  rf_vector_accumulate(a6, rhs);
  return v19;
}

