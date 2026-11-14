// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D9ED0 rf_renderer_draw_oriented_world_billboard_aspect
// UNREALRED VERIFIED [renderer-overlays-20261028]: Arguments worldcenter,orientationmatrix,size,packedstate. Camera-facing test uses matrix thirdrow and center via0x5818E0; rejectsfalse. Queries pendingbitmapdimensions if signedhandle>=0,width0 rejects,height0 unguarded; aspect expandsX for width>height orY forheight>width,using size as other halfextent. Builds corners center +/- matrixrow0*halfX +/- matrixrow1*halfY,transforms worldpoints via0x5817B0,assigns fullUV,reversed pointerorder and submits mask1,no depthoverride. Calls sin/cos0 but values do not affect cornerformula. Does not normalize matrix rows or validate size/textureheight; returns submission result.
char __cdecl rf_renderer_draw_oriented_world_billboard_aspect(float *lhs, float *vector, float a3, int a4)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float v17; // [esp+0h] [ebp-1F4h]
  float v18; // [esp+0h] [ebp-1F4h]
  float *scalar; // [esp+8h] [ebp-1ECh]
  float *scalara; // [esp+8h] [ebp-1ECh]
  float scalarb; // [esp+8h] [ebp-1ECh]
  float *scalarc; // [esp+8h] [ebp-1ECh]
  float scalard; // [esp+8h] [ebp-1ECh]
  float *scalare; // [esp+8h] [ebp-1ECh]
  float v25[3]; // [esp+Ch] [ebp-1E8h] BYREF
  float v26[3]; // [esp+18h] [ebp-1DCh] BYREF
  float v27[3]; // [esp+24h] [ebp-1D0h] BYREF
  float v28[3]; // [esp+30h] [ebp-1C4h] BYREF
  float v29[3]; // [esp+3Ch] [ebp-1B8h] BYREF
  float v30[3]; // [esp+48h] [ebp-1ACh] BYREF
  float v31[3]; // [esp+54h] [ebp-1A0h] BYREF
  float v32[3]; // [esp+60h] [ebp-194h] BYREF
  float v33[3]; // [esp+6Ch] [ebp-188h] BYREF
  float v34[3]; // [esp+78h] [ebp-17Ch] BYREF
  float v35[3]; // [esp+84h] [ebp-170h] BYREF
  float v36[3]; // [esp+90h] [ebp-164h] BYREF
  float v37[3]; // [esp+9Ch] [ebp-158h] BYREF
  float v38[3]; // [esp+A8h] [ebp-14Ch] BYREF
  float v39[3]; // [esp+B4h] [ebp-140h] BYREF
  float copy_result[3]; // [esp+C0h] [ebp-134h] BYREF
  float v41[3]; // [esp+CCh] [ebp-128h] BYREF
  float scaled_result[3]; // [esp+D8h] [ebp-11Ch] BYREF
  float sum_result[3]; // [esp+E4h] [ebp-110h] BYREF
  float v44[3]; // [esp+F0h] [ebp-104h] BYREF
  int v45; // [esp+FCh] [ebp-F8h] BYREF
  int v46[2]; // [esp+100h] [ebp-F4h] BYREF
  float v47; // [esp+108h] [ebp-ECh]
  float v48; // [esp+10Ch] [ebp-E8h]
  int v49[6]; // [esp+110h] [ebp-E4h] BYREF
  float destination[3]; // [esp+128h] [ebp-CCh] BYREF
  char v51[28]; // [esp+134h] [ebp-C0h] BYREF
  float v52; // [esp+150h] [ebp-A4h]
  float v53; // [esp+154h] [ebp-A0h]
  _BYTE v54[28]; // [esp+164h] [ebp-90h] BYREF
  float v55; // [esp+180h] [ebp-74h]
  float v56; // [esp+184h] [ebp-70h]
  _BYTE v57[28]; // [esp+194h] [ebp-60h] BYREF
  float v58; // [esp+1B0h] [ebp-44h]
  float v59; // [esp+1B4h] [ebp-40h]
  _BYTE v60[28]; // [esp+1C4h] [ebp-30h] BYREF
  float v61; // [esp+1E0h] [ebp-14h]
  float v62; // [esp+1E4h] [ebp-10h]

  if ( !rf_renderer_plane_faces_camera_backend_wrapper((int)(vector + 6), lhs) )
    return 0;
  rf_vector_construct_no_unwind(v51, 0x30u, 4, rf_vector_prefix_construct_noop);
  v49[0] = (int)v60;
  v49[1] = (int)v57;
  v49[2] = (int)v54;
  v49[3] = (int)v51;
  *(float *)&v49[5] = 0.0;
  *(float *)&v49[4] = rf_sin_float(0.0);
  *(float *)&v46[1] = rf_cos_float(0.0);
  if ( (int)dword_187CCE8 <= -1 )
  {
    v48 = a3;
    v47 = a3;
  }
  else
  {
    rf_bitmap_get_resolved_dimensions(dword_187CCE8, &v45, v46);
    if ( !v45 )
      return 0;
    if ( v45 >= v46[0] )
    {
      v48 = a3;
      if ( v45 <= v46[0] )
        v47 = a3;
      else
        v47 = (double)v45 * a3 / (double)v46[0];
    }
    else
    {
      v47 = a3;
      v48 = (double)v46[0] * a3 / (double)v45;
    }
  }
  rf_vector3_default_construct_noop(destination);
  scalar = rf_vector_multiply_scalar(vector + 3, scaled_result, v48);
  v17 = -v47;
  v5 = rf_vector_multiply_scalar(vector, v44, v17);
  v6 = rf_vector_add(lhs, sum_result, v5);
  v7 = rf_vector_add(v6, v41, scalar);
  rf_vector_copy(destination, copy_result, v7);
  rf_renderer_transform_world_point_backend_wrapper((int)v51, destination);
  v52 = 1.0;
  v53 = 0.0;
  scalara = rf_vector_multiply_scalar(vector + 3, v37, v48);
  v8 = rf_vector_multiply_scalar(vector, v39, v47);
  v9 = rf_vector_add(lhs, v38, v8);
  v10 = rf_vector_add(v9, v36, scalara);
  rf_vector_copy(destination, v35, v10);
  rf_renderer_transform_world_point_backend_wrapper((int)v54, destination);
  v55 = 0.0;
  v56 = 0.0;
  scalarb = -v48;
  scalarc = rf_vector_multiply_scalar(vector + 3, v32, scalarb);
  v11 = rf_vector_multiply_scalar(vector, v34, v47);
  v12 = rf_vector_add(lhs, v33, v11);
  v13 = rf_vector_add(v12, v31, scalarc);
  rf_vector_copy(destination, v30, v13);
  rf_renderer_transform_world_point_backend_wrapper((int)v57, destination);
  v58 = 0.0;
  v59 = 1.0;
  scalard = -v48;
  scalare = rf_vector_multiply_scalar(vector + 3, v27, scalard);
  v18 = -v47;
  v14 = rf_vector_multiply_scalar(vector, v29, v18);
  v15 = rf_vector_add(lhs, v28, v14);
  v16 = rf_vector_add(v15, v26, scalare);
  rf_vector_copy(destination, v25, v16);
  rf_renderer_transform_world_point_backend_wrapper((int)v60, destination);
  v61 = 1.0;
  v62 = 1.0;
  return rf_renderer_submit_immediate_polygon(4, (int)v49, 1, a4, 0, 0.0);
}

