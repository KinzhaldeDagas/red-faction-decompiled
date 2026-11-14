// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DDB70 rf_d3d8_submit_immediate_polygon
// UNREALRED VERIFIED [reflection-binding-20260903]: D3D8 immediate-polygon submission backend. It stages vertex pointers, optionally clips against the 48-plane/outcode path, performs vertex preparation, and forwards the surviving polygon plus vertex flags and packed state to 0x005D3FF0.
char __cdecl rf_d3d8_submit_immediate_polygon(int a1, int a2, unsigned __int8 a3, unsigned int a4, char a5, float a6)
{
  int v7; // [esp+4h] [ebp-18h]
  int v8; // [esp+8h] [ebp-14h]
  void **v9; // [esp+Ch] [ebp-10h]
  char v10; // [esp+12h] [ebp-Ah]
  char v11; // [esp+13h] [ebp-9h]
  int i; // [esp+14h] [ebp-8h]
  int j; // [esp+14h] [ebp-8h]
  int k; // [esp+14h] [ebp-8h]
  char v15; // [esp+18h] [ebp-4h] BYREF
  char v16; // [esp+19h] [ebp-3h]

  v10 = 1;
  v15 = 0;
  v16 = -1;
  v9 = (void **)unk_18CD040;
  for ( i = 0; i < a1; ++i )
  {
    unk_18CD040[i] = *(_DWORD *)(a2 + 4 * i);
    v8 = unk_18CD040[i];
    v16 &= *(_BYTE *)(v8 + 24);
    v15 |= *(_BYTE *)(v8 + 24);
  }
  if ( v16 )
    return 0;
  v11 = 0;
  if ( !byte_663F06
    || !v15
    || (v11 = 1, v9 = (void **)rf_clip_polygon_outcode_planes_48(unk_18CD040, unk_18CD108, &a1, &v15, a3), a1) && !v16 )
  {
    for ( j = 0; j < a1; ++j )
    {
      v7 = (int)v9[j];
      if ( (*(_BYTE *)(v7 + 25) & 1) == 0 )
        rf_renderer_project_clip_vertex_cached(v7);
      if ( (*(_BYTE *)(v7 + 25) & 2) != 0 )
      {
        v10 = 0;
        goto LABEL_21;
      }
      if ( a5 )
      {
        *(float *)(v7 + 8) = a6;
        *(float *)(v7 + 20) = 1.0 / a6;
      }
    }
    rf_d3d8_draw_immediate_polygon(a1, (const void *const *)v9, a3, a4);
  }
LABEL_21:
  if ( v11 )
  {
    for ( k = 0; k < a1; ++k )
    {
      if ( (*((_BYTE *)v9[k] + 25) & 4) != 0 )
        rf_clip_vertex48_pool_release((int)v9[k]);
    }
  }
  return v10;
}

