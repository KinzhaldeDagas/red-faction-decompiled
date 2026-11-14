// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0210 rf_beam_edge_pair_facing_supplied_viewpoint
// UNREALRED VERIFIED [renderer-lighting-20261028]: Sixarguments viewpoint,outputplus,outputminus,direction,worldcenter,fullwidth. Normalizes viewpoint-center,then side=normalized cross(direction,viewvector). Writes center +/- side*(width/2). Equivalent to0x5DBA90 except viewpoint explicitly supplied instead of globalcamera. No explicit coincidentviewpoint or paralleldirection guard; normalizationhelper handles degeneracy. Return vector-copy result for secondoutput.
float *__cdecl rf_beam_edge_pair_facing_supplied_viewpoint(
        float *lhs,
        float *a2,
        float *a3,
        float *a4,
        float *rhs,
        float a6)
{
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float v13; // [esp+4h] [ebp-A4h]
  float scalar; // [esp+8h] [ebp-A0h]
  float v15[3]; // [esp+Ch] [ebp-9Ch] BYREF
  float v16[3]; // [esp+18h] [ebp-90h] BYREF
  float v17[3]; // [esp+24h] [ebp-84h] BYREF
  float v18[3]; // [esp+30h] [ebp-78h] BYREF
  float sum_result[3]; // [esp+3Ch] [ebp-6Ch] BYREF
  float scaled_result[3]; // [esp+48h] [ebp-60h] BYREF
  float v21[3]; // [esp+54h] [ebp-54h] BYREF
  float v22[3]; // [esp+60h] [ebp-48h] BYREF
  float copy_result[3]; // [esp+6Ch] [ebp-3Ch] BYREF
  float out_vector[3]; // [esp+78h] [ebp-30h] BYREF
  float vector[3]; // [esp+84h] [ebp-24h] BYREF
  float destination[3]; // [esp+90h] [ebp-18h] BYREF
  float v27[3]; // [esp+9Ch] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_copy_return_destination(v27, rhs);
  v6 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(destination, copy_result, v6);
  rf_vector_normalize(destination);
  v7 = rf_vector_cross(a4, v22, destination);
  rf_vector_copy(vector, v21, v7);
  rf_vector_normalize(vector);
  scalar = a6 / 2.0;
  v8 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  v9 = rf_vector_add(v27, sum_result, v8);
  rf_vector_copy(a2, v18, v9);
  v13 = -a6 / 2.0;
  v10 = rf_vector_multiply_scalar(vector, v17, v13);
  v11 = rf_vector_add(v27, v16, v10);
  return rf_vector_copy(a3, v15, v11);
}

