// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DB680 rf_renderer_draw_textured_polyline_ribbon
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments record,packedstate. RecordDWORD0 pointcount,positions at+4 stride12,bitmap+196,width+200. Zeroes four48-byte clipvertices; transforms firstpoint into two coincidentpreviousedges. Direction initiallyzero. For points1..count-1 uses normalized(current-next) as tangent except last reuses previousdirection; count2 therefore retains zerodirection. Computes camera-facingedgepair through0x5DBA90 and transforms newedges. Sets fullUV and allcolorbytes255; pendingtexture=recordbitmap,-1. Draws triangles(prevminus,newminus,newplus) and(prevminus,newplus,prevplus),attributemask1; copies newvertices into previous via0x5DF960. Returns1 even if nosegments or submissions fail. No pointcountcapacity guard; fixedrecord layout places bitmap immediately after16positions. Initialsegment begins collapsed at firstpoint; no joinmiter or endcap handling.
char __cdecl rf_renderer_draw_textured_polyline_ribbon(int a1, int a2)
{
  float *v2; // eax
  float v4[3]; // [esp+4h] [ebp-188h] BYREF
  float v5[3]; // [esp+10h] [ebp-17Ch] BYREF
  float v6[3]; // [esp+1Ch] [ebp-170h] BYREF
  float out_vector[3]; // [esp+28h] [ebp-164h] BYREF
  float v8[3]; // [esp+34h] [ebp-158h] BYREF
  float v9[3]; // [esp+40h] [ebp-14Ch] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-140h] BYREF
  float lhs[3]; // [esp+58h] [ebp-134h] BYREF
  int v12[3]; // [esp+64h] [ebp-128h] BYREF
  float v13; // [esp+70h] [ebp-11Ch]
  int v14[4]; // [esp+74h] [ebp-118h] BYREF
  float *v15; // [esp+84h] [ebp-108h]
  float v16[12]; // [esp+88h] [ebp-104h] BYREF
  float source[3]; // [esp+B8h] [ebp-D4h] BYREF
  float v18[12]; // [esp+C4h] [ebp-C8h] BYREF
  float destination[3]; // [esp+F4h] [ebp-98h] BYREF
  float v20[12]; // [esp+100h] [ebp-8Ch] BYREF
  float v21[12]; // [esp+130h] [ebp-5Ch] BYREF
  int v22[3]; // [esp+160h] [ebp-2Ch] BYREF
  float v23[3]; // [esp+16Ch] [ebp-20h] BYREF
  int v24; // [esp+178h] [ebp-14h]
  int i; // [esp+17Ch] [ebp-10h]
  int v26[3]; // [esp+180h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v26);
  rf_vector3_default_construct_noop(v22);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v23);
  rf_vector3_default_construct_noop(source);
  rf_vector_prefix_construct_noop(v20);
  rf_vector_prefix_construct_noop(v18);
  rf_vector_prefix_construct_noop(v16);
  rf_vector_prefix_construct_noop(v21);
  memset(v20, 0, sizeof(v20));
  memset(v18, 0, sizeof(v18));
  memset(v16, 0, sizeof(v16));
  memset(v21, 0, sizeof(v21));
  v24 = *(_DWORD *)a1 - 1;
  rf_vector_copy(destination, copy_result, (const float *)(a1 + 4));
  rf_renderer_transform_world_point_backend_wrapper((int)v20, destination);
  rf_renderer_transform_world_point_backend_wrapper((int)v18, destination);
  rf_vector3_zero_return_destination(source);
  for ( i = 1; i <= v24; ++i )
  {
    v13 = *(float *)(a1 + 200);
    rf_vector3_default_construct_noop(lhs);
    rf_vector_copy(lhs, v9, (const float *)(a1 + 12 * i + 4));
    if ( i == v24 )
    {
      rf_vector_copy(v23, v8, source);
    }
    else
    {
      v2 = rf_vector_subtract(lhs, out_vector, (const float *)(a1 + 12 * (i + 1) + 4));
      rf_vector_copy(v23, v6, v2);
      rf_vector_normalize(v23);
    }
    v15 = v23;
    rf_vector_copy(source, v5, v23);
    rf_renderer_beam_camera_facing_edge_pair((float *)v26, (float *)v22, (int)v15, (int)lhs, v13);
    rf_renderer_transform_world_point_backend_wrapper((int)v16, (float *)v26);
    rf_renderer_transform_world_point_backend_wrapper((int)v21, (float *)v22);
    v14[0] = (int)v18;
    v14[1] = (int)v21;
    v14[2] = (int)v16;
    v14[3] = (int)v20;
    v18[7] = 1.0;
    v18[8] = 0.0;
    v21[7] = 1.0;
    v21[8] = 1.0;
    v16[7] = 0.0;
    v16[8] = 1.0;
    v20[7] = 0.0;
    v20[8] = 0.0;
    v20[11] = NAN;
    v16[11] = NAN;
    v21[11] = NAN;
    v18[11] = NAN;
    v12[0] = (int)v18;
    v12[1] = (int)v16;
    v12[2] = (int)v20;
    rf_renderer_set_pending_texture_handles(*(_DWORD *)(a1 + 196), -1);
    rf_renderer_submit_immediate_polygon(3, (int)v14, 1, a2, 0, 0.0);
    rf_renderer_submit_immediate_polygon(3, (int)v12, 1, a2, 0, 0.0);
    rf_vector_copy(destination, v4, lhs);
    rf_clip_vertex48_copy_return_destination((int)v20, (int)v16);
    rf_clip_vertex48_copy_return_destination((int)v18, (int)v21);
  }
  return 1;
}

