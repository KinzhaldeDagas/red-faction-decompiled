// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DBA90 rf_renderer_beam_camera_facing_edge_pair
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments outputplus,outputminus,direction,worldcenter,fullwidth. Computes normalizedcameraPosition0x18CD5E8-center,normalizes cross(direction,viewvector),then writes center +/- normalizedside*(width/2). Direction itself need not be normalized for nondegeneratecross. No explicit parallel/zero-length guard; normalization helper determines degenerate behavior. Returns vector-copy result for secondoutput.
float *__cdecl rf_renderer_beam_camera_facing_edge_pair(float *a1, float *a2, float *a3, float *rhs, float a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float v12; // [esp+4h] [ebp-A4h]
  float scalar; // [esp+8h] [ebp-A0h]
  float v14[3]; // [esp+Ch] [ebp-9Ch] BYREF
  float v15[3]; // [esp+18h] [ebp-90h] BYREF
  float v16[3]; // [esp+24h] [ebp-84h] BYREF
  float v17[3]; // [esp+30h] [ebp-78h] BYREF
  float sum_result[3]; // [esp+3Ch] [ebp-6Ch] BYREF
  float scaled_result[3]; // [esp+48h] [ebp-60h] BYREF
  float v20[3]; // [esp+54h] [ebp-54h] BYREF
  float v21[3]; // [esp+60h] [ebp-48h] BYREF
  float copy_result[3]; // [esp+6Ch] [ebp-3Ch] BYREF
  float out_vector[3]; // [esp+78h] [ebp-30h] BYREF
  float vector[3]; // [esp+84h] [ebp-24h] BYREF
  float destination[3]; // [esp+90h] [ebp-18h] BYREF
  float lhs[3]; // [esp+9Ch] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_copy_return_destination(lhs, rhs);
  v5 = rf_vector_subtract(&flt_18CD5E8, out_vector, rhs);
  rf_vector_copy(destination, copy_result, v5);
  rf_vector_normalize(destination);
  v6 = rf_vector_cross(a3, v21, destination);
  rf_vector_copy(vector, v20, v6);
  rf_vector_normalize(vector);
  scalar = a5 / 2.0;
  v7 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  v8 = rf_vector_add(lhs, sum_result, v7);
  rf_vector_copy(a1, v17, v8);
  v12 = -a5 / 2.0;
  v9 = rf_vector_multiply_scalar(vector, v16, v12);
  v10 = rf_vector_add(lhs, v15, v9);
  return rf_vector_copy(a2, v14, v10);
}

