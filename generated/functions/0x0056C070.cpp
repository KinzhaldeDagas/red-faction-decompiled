// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056C070 rf_ray_oriented_box_hit_point
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(ray6,boxCenter,basis9,fullDimensions,outPoint),returnsAL byte. World ray consists of startXYZ then directionXYZ. Transforms direction using row dots5590A0,and start-center using same row dots5594A0; local bounds=-0.5*dimensions and+0.5*dimensions. Calls56C200 forward-ray candidate-plane query,which has no t<=1 or ray-length test. Then UNCONDITIONALLY rotates outPoint back with559540 and adds center,even when local query returned0 and output was untouched/partial. Failure can therefore read and transform incoming/stale output. Both transforms require orthonormal row basis for geometric inverse. Shared scratch180927C/1809270/1809264 and flags1809288 without lock; dimensions not validated.
unsigned __int8 __cdecl rf_ray_oriented_box_hit_point(
        float *lhs,
        float *rhs,
        float *a3,
        float *vector,
        float *out_point)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float v9[3]; // [esp+8h] [ebp-64h] BYREF
  float v10[3]; // [esp+14h] [ebp-58h] BYREF
  float v11[3]; // [esp+20h] [ebp-4Ch] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-40h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-34h] BYREF
  float out_vector[3]; // [esp+44h] [ebp-28h] BYREF
  float direction[3]; // [esp+50h] [ebp-1Ch] BYREF
  unsigned __int8 v16; // [esp+5Fh] [ebp-Dh]
  int v17; // [esp+68h] [ebp-4h]

  if ( (dword_1809288 & 1) == 0 )
  {
    dword_1809288 |= 1u;
    rf_vector3_default_construct_noop(&flt_180927C);
    v17 = -1;
  }
  rf_vector3_transform_by_matrix_rows(lhs + 3, direction, a3);
  v5 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(&flt_180927C, copy_result, v5);
  rf_matrix3_inverse_rotate_vector(&flt_180927C, a3);
  if ( (dword_1809288 & 2) == 0 )
  {
    dword_1809288 |= 2u;
    v17 = 1;
    rf_vector3_default_construct_noop(&flt_1809270);
    v17 = -1;
  }
  if ( (dword_1809288 & 4) == 0 )
  {
    dword_1809288 |= 4u;
    v17 = 2;
    rf_vector3_default_construct_noop(&flt_1809264);
    v17 = -1;
  }
  v6 = rf_vector_multiply_scalar(vector, scaled_result, -0.5);
  rf_vector_copy(&flt_1809270, v11, v6);
  v7 = rf_vector_multiply_scalar(vector, v10, 0.5);
  rf_vector_copy(&flt_1809264, v9, v7);
  v16 = rf_ray_aabb_hit_point_candidate_planes(&flt_1809270, &flt_1809264, &flt_180927C, direction, out_point);
  rf_vector_rotate_by_matrix3(out_point, a3);
  rf_vector_accumulate(out_point, rhs);
  return v16;
}

