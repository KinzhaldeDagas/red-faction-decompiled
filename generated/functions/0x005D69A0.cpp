// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D69A0 rf_renderer_draw_face_debug_texture_channel
// UNREALRED VERIFIED [renderer-polygons-20261028]: Arguments context,room,count,facepointerarray; room unused. Packedstate(1,1,2,0,4,0). Per face builds48 local48-byte transformed vertices from circular cornerlist+64. If global0xA420A0 nonzero,sets pending texture to face bitmap+48 and copies base cornerUV+4/+8 into vertexUV+28/+32. Otherwise requires signed face lightmapindex+54>=0,resolves through context+192 and nested bitmap handle,and copies lightmap cornerUV+12/+16. Submits polygon attributemask1; no vertexcount<=48,context lookup or texture validation in body. Leaves renderer state/textures changed; return loop artifact.
int *__cdecl rf_renderer_draw_face_debug_texture_channel(int a1, int a2, int a3, int a4)
{
  int *result; // eax
  int v5; // eax
  int v6; // [esp+4h] [ebp-9DCh]
  int v7; // [esp+8h] [ebp-9D8h]
  int v8; // [esp+Ch] [ebp-9D4h]
  int v9[48]; // [esp+10h] [ebp-9D0h] BYREF
  char v10[2308]; // [esp+D0h] [ebp-910h] BYREF
  int v11; // [esp+9D4h] [ebp-Ch]
  int v12; // [esp+9D8h] [ebp-8h] BYREF
  int i; // [esp+9DCh] [ebp-4h]

  result = rf_render_state_pack(&v12, 1, 1, 2, 0, 4, 0);
  for ( i = 0; i < a3; ++i )
  {
    v11 = *(_DWORD *)(a4 + 4 * i);
    rf_vector_construct_no_unwind(v10, 0x30u, 48, rf_vector_prefix_construct_noop);
    v8 = 0;
    v7 = *(_DWORD *)(v11 + 64);
    if ( dword_A420A0 )
    {
      rf_renderer_set_pending_texture_handles(*(_DWORD *)(v11 + 48), -1);
    }
    else
    {
      if ( *(__int16 *)(v11 + 54) < 0 )
        goto LABEL_2;
      v5 = sub_552200((_DWORD *)(a1 + 192), *(__int16 *)(v11 + 54));
      rf_renderer_set_pending_texture_handles(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v5 + 12) + 16), -1);
    }
    while ( v7 )
    {
      v9[v8] = (int)&v10[48 * v8];
      rf_renderer_transform_world_point_to_clip_vertex((int)&v10[48 * v8], *(float **)v7);
      if ( dword_A420A0 )
      {
        *(float *)&v10[48 * v8 + 28] = *(float *)(v7 + 4);
        *(float *)&v10[48 * v8 + 32] = *(float *)(v7 + 8);
      }
      else
      {
        *(float *)&v10[48 * v8 + 28] = *(float *)(v7 + 12);
        *(float *)&v10[48 * v8 + 32] = *(float *)(v7 + 16);
      }
      if ( *(_DWORD *)(v7 + 20) == *(_DWORD *)(v11 + 64) )
        v6 = 0;
      else
        v6 = *(_DWORD *)(v7 + 20);
      v7 = v6;
      ++v8;
    }
    rf_renderer_submit_immediate_polygon(v8, (int)v9, 1, v12, 0, 0.0);
LABEL_2:
    result = (int *)(i + 1);
  }
  return result;
}

