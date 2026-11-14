// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00572CD0 rf_renderer_fill_rectangle_clipped
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Builds inclusive endpoint x+w-1 for positive width or x+w+1 otherwise, likewise height; normalizes endpoints and clips to inclusive relative bounds. Thus zero extent is not rejected and yields a small nonempty range. Constructs four preprojected vertices at origin+left/top and origin+right/bottom+1 with reciprocal depth1, unbinds both texture handles, and submits untextured quad with caller mode. Rejection paths return incidental coordinate values; successful path returns draw-wrapper EAX.
int __cdecl rf_renderer_fill_rectangle_clipped(int a1, int a2, int a3, int a4, int a5)
{
  int result; // eax
  int v6; // [esp+28h] [ebp-E0h]
  int v7; // [esp+2Ch] [ebp-DCh]
  int v8; // [esp+30h] [ebp-D8h]
  int v9; // [esp+34h] [ebp-D4h]
  char v10[12]; // [esp+38h] [ebp-D0h] BYREF
  float v11; // [esp+44h] [ebp-C4h]
  float v12; // [esp+48h] [ebp-C0h]
  float v13; // [esp+4Ch] [ebp-BCh]
  char v14; // [esp+68h] [ebp-A0h] BYREF
  float v15; // [esp+74h] [ebp-94h]
  float v16; // [esp+78h] [ebp-90h]
  float v17; // [esp+7Ch] [ebp-8Ch]
  char v18; // [esp+98h] [ebp-70h] BYREF
  float v19; // [esp+A4h] [ebp-64h]
  float v20; // [esp+A8h] [ebp-60h]
  float v21; // [esp+ACh] [ebp-5Ch]
  char v22; // [esp+C8h] [ebp-40h] BYREF
  float v23; // [esp+D4h] [ebp-34h]
  float v24; // [esp+D8h] [ebp-30h]
  float v25; // [esp+DCh] [ebp-2Ch]
  _DWORD v26[4]; // [esp+F8h] [ebp-10h] BYREF

  v6 = a1;
  v7 = a2;
  if ( a3 <= 0 )
    v8 = a1 + a3 + 1;
  else
    v8 = a1 + a3 - 1;
  if ( a4 <= 0 )
    v9 = a2 + a4 + 1;
  else
    v9 = a2 + a4 - 1;
  if ( v8 < a1 )
  {
    v6 = v8;
    v8 = a1;
  }
  if ( v9 < a2 )
  {
    v7 = v9;
    v9 = a2;
  }
  result = v6;
  if ( v6 <= dword_187CCD8 && v8 >= dword_187CCD4 && v7 <= dword_187CCE0 )
  {
    result = v9;
    if ( v9 >= dword_187CCDC )
    {
      if ( v6 < dword_187CCD4 )
        v6 = dword_187CCD4;
      if ( v7 < dword_187CCDC )
        v7 = dword_187CCDC;
      if ( v8 > dword_187CCD8 )
        v8 = dword_187CCD8;
      if ( v9 > dword_187CCE0 )
        v9 = dword_187CCE0;
      rf_vector_construct_no_unwind(v10, 0x30u, 4, rf_vector_prefix_construct_noop);
      v26[0] = v10;
      v11 = (float)(unk_187CCBC + v6);
      v12 = (float)(unk_187CCC0 + v7);
      v13 = 1.0;
      v26[1] = &v14;
      v15 = (float)(v8 + unk_187CCBC + 1);
      v16 = v12;
      v17 = 1.0;
      v26[2] = &v18;
      v19 = v15;
      v20 = (float)(v9 + unk_187CCC0 + 1);
      v21 = 1.0;
      v26[3] = &v22;
      v23 = v11;
      v24 = v20;
      v25 = 1.0;
      rf_renderer_set_pending_texture_handles(-1, -1);
      return rf_renderer_draw_preprojected_polygon_backend_wrapper(4, (int)v26, 0, a5);
    }
  }
  return result;
}

