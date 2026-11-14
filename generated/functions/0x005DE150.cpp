// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DE150 rf_renderer_draw_face_green_translucent_overlay
// UNREALRED VERIFIED [renderer-lighting-20261028]: Lazily packsstate(0,0,0,3,1,0). Walks circularfacecornerlist+64,transforms worldpositions directly through backend1020x582180,sets pervertexRGBA=(63,255,0,63),fills local48-pointerarray. Submits polygon via rf_d3d8_submit_immediate_polygon,attributemask12,no depthoverride; returns submissionresult. No vertexcount<=48 guard,texture reset or currentcolor restoration.
char __cdecl rf_renderer_draw_face_green_translucent_overlay(int a1)
{
  int v2; // [esp+8h] [ebp-9D8h]
  _OWORD v3[144]; // [esp+Ch] [ebp-9D4h] BYREF
  int v4[48]; // [esp+90Ch] [ebp-D4h] BYREF
  int v5; // [esp+9CCh] [ebp-14h]
  int i; // [esp+9D0h] [ebp-10h]
  int v7; // [esp+9DCh] [ebp-4h]

  if ( (dword_1E01530 & 1) == 0 )
  {
    dword_1E01530 |= 1u;
    rf_render_state_pack(&unk_1E0152C, 0, 0, 0, 3, 1, 0);
    v7 = -1;
  }
  rf_vector_construct_no_unwind((char *)v3, 0x30u, 48, rf_vector_prefix_construct_noop);
  v5 = 0;
  for ( i = *(_DWORD *)(a1 + 64); i; i = v2 )
  {
    rf_renderer_transform_world_point_to_clip_vertex((int)&v3[3 * v5], *(float **)i);
    BYTE12(v3[3 * v5 + 2]) = 63;
    BYTE13(v3[3 * v5 + 2]) = -1;
    BYTE14(v3[3 * v5 + 2]) = 0;
    HIBYTE(v3[3 * v5 + 2]) = 63;
    v4[v5] = (int)&v3[3 * v5];
    ++v5;
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a1 + 64) )
      v2 = 0;
    else
      v2 = *(_DWORD *)(i + 20);
  }
  return rf_d3d8_submit_immediate_polygon(v5, (int)v4, 0xCu, unk_1E0152C, 0, 0.0);
}

