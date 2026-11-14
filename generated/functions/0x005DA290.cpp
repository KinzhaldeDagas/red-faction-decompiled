// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DA290 rf_renderer_draw_world_billboard_aspect
// UNREALRED VERIFIED [renderer-overlays-20261028]: Arguments worldcenter,angle,size,packedstate. Constructs one48-byte clipvertex,transforms worldcenter through0x5817B0,projects via0x5818B0,and requires flags+25 bit1. Then delegates0x5D9790 camera billboard with bitmapaspect handling. Otherwise returns0. Size is passed unchanged as halfextent; current pendingtexture/color used.
char __cdecl rf_renderer_draw_world_billboard_aspect(float *a1, float a2, float a3, int a4)
{
  int v5[6]; // [esp+Ch] [ebp-34h] BYREF
  char v6; // [esp+25h] [ebp-1Bh]
  char v7; // [esp+3Fh] [ebp-1h]

  rf_vector_prefix_construct_noop(v5);
  v7 = rf_renderer_transform_world_point_backend_wrapper((int)v5, a1);
  rf_renderer_project_clip_vertex_backend_wrapper((int)v5);
  if ( (v6 & 1) != 0 )
    return rf_renderer_draw_rotated_billboard_camera_aspect((int)v5, a2, a3, a4);
  else
    return 0;
}

