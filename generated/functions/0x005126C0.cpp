// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005126C0 rf_projected_shadow_emit_vertices
// UNREALRED VERIFIED [general-gap-20260830]: Emits projected-shadow vertices with white RGB, converts normalized alpha through 255.0, and submits the final clipped vertex packet with texture-UV, RGB, and alpha attributes.
_DWORD *__cdecl rf_projected_shadow_emit_vertices(int a1, int a2, int a3)
{
  _DWORD *result; // eax
  int v4; // [esp+14h] [ebp-32Ch]
  int v5; // [esp+18h] [ebp-328h]
  _DWORD *v6; // [esp+1Ch] [ebp-324h]
  char v7; // [esp+27h] [ebp-319h]
  char v8[772]; // [esp+28h] [ebp-318h] BYREF
  int i; // [esp+32Ch] [ebp-14h]
  int v10; // [esp+330h] [ebp-10h]
  int j; // [esp+334h] [ebp-Ch]
  float v12; // [esp+338h] [ebp-8h]
  char v13; // [esp+33Ch] [ebp-4h] BYREF
  char v14; // [esp+33Dh] [ebp-3h]

  v10 = a1;
  rf_vector_construct_no_unwind(v8, 0x30u, 16, rf_vector_prefix_construct_noop);
  v6 = unk_18CD108;
  for ( i = 0; i < a1; ++i )
  {
    rf_renderer_transform_world_point_backend_wrapper((int)&v8[48 * i], (float *)(a2 + 12 * i));
    v8[48 * i + 44] = -1;
    v8[48 * i + 45] = -1;
    v8[48 * i + 46] = -1;
    v8[48 * i + 47] = (int)(*(float *)(a3 + 12 * i + 8) * 255.0);
    *(float *)&v8[48 * i + 28] = *(float *)(a3 + 12 * i);
    *(float *)&v8[48 * i + 32] = *(float *)(a3 + 12 * i + 4);
  }
  v13 = 0;
  v14 = -1;
  for ( j = 0; ; ++j )
  {
    result = (_DWORD *)j;
    if ( j >= a1 )
      break;
    unk_18CD108[j] = &v8[48 * j];
    v5 = unk_18CD108[j];
    v14 &= *(_BYTE *)(v5 + 24);
    v13 |= *(_BYTE *)(v5 + 24);
  }
  v7 = 0;
  if ( !v14 )
  {
    if ( v13 )
    {
      rf_clip_vertex48_pool_reset();
      result = (_DWORD *)rf_clip_polygon_outcode_planes_48((int)unk_18CD108, (int)unk_18CD040, &a1, &v13, 13);
      v6 = result;
      if ( !a1 || v14 )
        return result;
      v7 = 1;
    }
    v12 = 0.0;
    for ( j = 0; j < a1; ++j )
    {
      v4 = v6[j];
      if ( (*(_BYTE *)(v4 + 25) & 1) == 0 )
        rf_renderer_project_clip_vertex_backend_wrapper(v4);
      if ( v12 < (double)*(unsigned __int8 *)(v4 + 47) )
        v12 = (float)*(unsigned __int8 *)(v4 + 47);
      *(float *)(v4 + 20) = *(float *)(v4 + 20) * 1.019999980926514;
      result = (_DWORD *)(*(_BYTE *)(v4 + 25) & 2);
      if ( (*(_BYTE *)(v4 + 25) & 2) != 0 )
        return result;
    }
    for ( j = unk_928424; ; ++j )
    {
      result = (_DWORD *)j;
      if ( j >= dword_663AD8 )
        break;
      rf_renderer_draw_preprojected_polygon_backend_wrapper(a1, (int)v6, 13, unk_928554);
    }
    if ( v7 )
    {
      for ( j = 0; ; ++j )
      {
        result = (_DWORD *)j;
        if ( j >= a1 )
          break;
        if ( (*(_BYTE *)(v6[j] + 25) & 4) != 0 )
          rf_clip_vertex48_pool_release(v6[j]);
      }
    }
  }
  return result;
}

