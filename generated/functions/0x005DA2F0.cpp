// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DA2F0 rf_renderer_draw_world_billboard_rectangle
// UNREALRED VERIFIED [renderer-overlays-20261028]: Arguments worldcenter,angle,fullwidth,fullheight,packedstate. Constructs one48-byte clipvertex,transforms and projects through0x5817B0/0x5818B0. Requires projectedflagbit1 then delegates0x5D9BA0; otherwise returns0. No textureaspect lookup here; current pendingtexture/color used.
char __cdecl rf_renderer_draw_world_billboard_rectangle(float *a1, float a2, float a3, float a4, int a5)
{
  int v6[6]; // [esp+10h] [ebp-34h] BYREF
  char v7; // [esp+29h] [ebp-1Bh]
  char v8; // [esp+43h] [ebp-1h]

  rf_vector_prefix_construct_noop(v6);
  v8 = rf_renderer_transform_world_point_backend_wrapper((int)v6, a1);
  rf_renderer_project_clip_vertex_backend_wrapper((int)v6);
  if ( (v7 & 1) != 0 )
    return rf_renderer_draw_rotated_billboard_camera_rectangle((int)v6, a2, a3, a4, a5);
  else
    return 0;
}

