// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D6570 rf_renderer_draw_face_debug_colors_and_edges
// UNREALRED VERIFIED [renderer-polygons-20261028]: Arguments context,room,count,facepointerarray; context unused. Builds packedstate(0,0,0,0,4,0),sets pendingtextures-1/-1 and globalcolor white. Global0xA42090 selects local state plus vertexalpha255,otherwise state0x187CC4C plus alpha63. Per face builds48 local48-byte vertices from circular cornerlist+64; transforms original worldpositions via0x582180. When debugmode and face+68 owner exists,derives RGB bytes as43*(ownerDWORD+32 masks),falling back48/48/48 if summed derived bytes<=16; elsewhite. Submits polygon attributemask12. Sets currentcolor black when room==global0xA42080 elsewhite,then draws closed edges via0x57E710. No vertexcount<=48 check or state/color restoration. Returns loop artifact,not draw success.
int *__cdecl rf_renderer_draw_face_debug_colors_and_edges(int a1, int a2, int a3, int a4)
{
  int *result; // eax
  int v5; // [esp+4h] [ebp-9F8h]
  int v6; // [esp+8h] [ebp-9F4h]
  unsigned __int8 v7; // [esp+10h] [ebp-9ECh]
  unsigned __int8 v8; // [esp+14h] [ebp-9E8h]
  unsigned __int8 v9; // [esp+18h] [ebp-9E4h]
  int v10; // [esp+1Ch] [ebp-9E0h]
  int v11; // [esp+20h] [ebp-9DCh]
  int v12[48]; // [esp+24h] [ebp-9D8h] BYREF
  _OWORD v13[144]; // [esp+E4h] [ebp-918h] BYREF
  int v14; // [esp+9E4h] [ebp-18h]
  int *j; // [esp+9E8h] [ebp-14h]
  int *v16; // [esp+9ECh] [ebp-10h]
  int v17; // [esp+9F0h] [ebp-Ch] BYREF
  int i; // [esp+9F4h] [ebp-8h]
  char v19; // [esp+9FBh] [ebp-1h]

  rf_render_state_pack(&v17, 0, 0, 0, 0, 4, 0);
  rf_renderer_set_pending_texture_handles(-1, -1);
  LOBYTE(result) = rf_render_color_set_rgba8(255, 255, 255, 255);
  if ( dword_A42090 )
  {
    result = &v17;
    v16 = &v17;
    v19 = -1;
  }
  else
  {
    v16 = (int *)&unk_187CC4C;
    v19 = 63;
  }
  for ( i = 0; i < a3; ++i )
  {
    v14 = *(_DWORD *)(a4 + 4 * i);
    rf_vector_construct_no_unwind((char *)v13, 0x30u, 48, rf_vector_prefix_construct_noop);
    v11 = 0;
    v10 = *(_DWORD *)(v14 + 64);
    while ( v10 )
    {
      v12[v11] = (int)&v13[3 * v11];
      rf_renderer_transform_world_point_to_clip_vertex((int)&v13[3 * v11], *(float **)v10);
      if ( dword_A42090 && *(_DWORD *)(v14 + 68) )
      {
        v7 = 43 * (*(_BYTE *)(*(_DWORD *)(v14 + 68) + 32) & 0x49);
        v8 = 43 * ((*(_BYTE *)(*(_DWORD *)(v14 + 68) + 32) & 0x12) + (*(_DWORD *)(*(_DWORD *)(v14 + 68) + 32) & 0x80));
        v9 = 43 * (*(_BYTE *)(*(_DWORD *)(v14 + 68) + 32) & 0x24);
        if ( v9 + v8 + v7 <= 16 )
        {
          v7 = 48;
          v8 = 48;
          v9 = 48;
        }
      }
      else
      {
        v7 = -1;
        v8 = -1;
        v9 = -1;
      }
      BYTE12(v13[3 * v11 + 2]) = v7;
      BYTE13(v13[3 * v11 + 2]) = v8;
      BYTE14(v13[3 * v11 + 2]) = v9;
      HIBYTE(v13[3 * v11 + 2]) = v19;
      if ( *(_DWORD *)(v10 + 20) == *(_DWORD *)(v14 + 64) )
        v6 = 0;
      else
        v6 = *(_DWORD *)(v10 + 20);
      v10 = v6;
      ++v11;
    }
    rf_renderer_submit_immediate_polygon(v11, (int)v12, 12, *v16, 0, 0.0);
    if ( a2 == unk_A42080 )
      rf_render_color_set_rgba8(0, 0, 0, 255);
    else
      rf_render_color_set_rgba8(255, 255, 255, 255);
    for ( j = nullptr; ; j = (int *)((char *)j + 1) )
    {
      result = j;
      if ( (int)j >= v11 )
        break;
      if ( j )
        v5 = (int)j - 1;
      else
        v5 = v11 - 1;
      rf_renderer_draw_projected_line_backend_wrapper((int)&v13[3 * (int)j], (int)&v13[3 * v5], *v16);
    }
  }
  return result;
}

