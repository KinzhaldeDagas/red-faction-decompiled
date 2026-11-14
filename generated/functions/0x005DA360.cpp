// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DA360 rf_renderer_draw_camera_facing_beam_quad
// UNREALRED VERIFIED [renderer-overlays-20261028]: Arguments two worldendpoints,fullwidth,packedstate. Normalizes direction(endpoint1-endpoint2),computes midpoint,normalizes cameraPosition-midpoint,crosses direction with viewvector,and normalizes resulting sideaxis. Builds four worldcorners endpoint +/- sideaxis*(width/2),transforms to48-byte clipvertices,sets fullUV and submits4vertices attributemask1 without depthoverride. Returns1 regardless polygon submission result. No explicit coincident-endpoint,parallel-view or zero-width guard; normalization helper determines degenerate behavior. Leaves pendingtexture/color unchanged.
char __cdecl rf_renderer_draw_camera_facing_beam_quad(float *lhs, float *rhs, float a3, int a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float scalar; // [esp+10h] [ebp-170h]
  float v11[3]; // [esp+14h] [ebp-16Ch] BYREF
  float v12[3]; // [esp+20h] [ebp-160h] BYREF
  float v13[3]; // [esp+2Ch] [ebp-154h] BYREF
  float v14[3]; // [esp+38h] [ebp-148h] BYREF
  float sum_result[3]; // [esp+44h] [ebp-13Ch] BYREF
  float vector[3]; // [esp+50h] [ebp-130h] BYREF
  float out_vector[3]; // [esp+5Ch] [ebp-124h] BYREF
  float v18[3]; // [esp+68h] [ebp-118h] BYREF
  float v19[3]; // [esp+74h] [ebp-10Ch] BYREF
  float v20[3]; // [esp+80h] [ebp-100h] BYREF
  _BYTE v21[28]; // [esp+8Ch] [ebp-F4h] BYREF
  float v22; // [esp+A8h] [ebp-D8h]
  float v23; // [esp+ACh] [ebp-D4h]
  float v24[3]; // [esp+BCh] [ebp-C4h] BYREF
  _BYTE v25[28]; // [esp+C8h] [ebp-B8h] BYREF
  float v26; // [esp+E4h] [ebp-9Ch]
  float v27; // [esp+E8h] [ebp-98h]
  float v28[3]; // [esp+F8h] [ebp-88h] BYREF
  _BYTE v29[28]; // [esp+104h] [ebp-7Ch] BYREF
  float v30; // [esp+120h] [ebp-60h]
  float v31; // [esp+124h] [ebp-5Ch]
  _BYTE v32[28]; // [esp+134h] [ebp-4Ch] BYREF
  float v33; // [esp+150h] [ebp-30h]
  float v34; // [esp+154h] [ebp-2Ch]
  float scaled_result[3]; // [esp+164h] [ebp-1Ch] BYREF
  int v36[4]; // [esp+170h] [ebp-10h] BYREF

  rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_normalize(out_vector);
  v4 = rf_vector_add(lhs, sum_result, rhs);
  rf_vector_multiply_scalar(v4, scaled_result, 0.5);
  rf_vector_subtract(&flt_18CD5E8, v18, scaled_result);
  rf_vector_normalize(v18);
  rf_vector_cross(out_vector, vector, v18);
  rf_vector_normalize(vector);
  rf_vector_prefix_construct_noop(v25);
  scalar = a3 * 0.5;
  v5 = rf_vector_multiply_scalar(vector, v14, scalar);
  rf_vector_add(lhs, v19, v5);
  rf_renderer_transform_world_point_backend_wrapper((int)v25, v19);
  rf_vector_prefix_construct_noop(v32);
  v6 = rf_vector_multiply_scalar(vector, v13, scalar);
  rf_vector_subtract(lhs, v28, v6);
  rf_renderer_transform_world_point_backend_wrapper((int)v32, v28);
  rf_vector_prefix_construct_noop(v21);
  v7 = rf_vector_multiply_scalar(vector, v12, scalar);
  rf_vector_add(rhs, v20, v7);
  rf_renderer_transform_world_point_backend_wrapper((int)v21, v20);
  rf_vector_prefix_construct_noop(v29);
  v8 = rf_vector_multiply_scalar(vector, v11, scalar);
  rf_vector_subtract(rhs, v24, v8);
  rf_renderer_transform_world_point_backend_wrapper((int)v29, v24);
  v36[0] = (int)v25;
  v36[1] = (int)v21;
  v36[2] = (int)v29;
  v36[3] = (int)v32;
  v26 = 0.0;
  v27 = 0.0;
  v22 = 0.0;
  v23 = 1.0;
  v30 = 1.0;
  v31 = 1.0;
  v33 = 1.0;
  v34 = 0.0;
  rf_renderer_submit_immediate_polygon(4, (int)v36, 1, a4, 0, 0.0);
  return 1;
}

