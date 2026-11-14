// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057EBF0 rf_renderer_world_aabb_screen_bounds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Cdecl worldAABB min3f,max3f,outputMinX,outputMinY,outputMaxX,outputMaxY. Builds8 corners,transforms to local48-byte vertices,AND/ORs returned outcodes. Common nonzero AND returnsfalse without touching outputs. Faces use corner indices(3,2,1,0),(4,5,6,7),(7,6,2,3),(0,1,5,4),(1,2,6,5),(4,7,3,0). Calls57E7C0 for each4-vertex face;first positive screen count initializes all four outputs from first XY,then reduces bounds over every returned pair. Returns true iff any face produced positive count;otherwise outputs unchanged. Does not clamp bounds to viewport rectangle itself;inherits projection/clipper behavior and early-cleanup limitations.16-pair scratch constructed with stride8/no-op vector constructor,so this loop does
// not actually initialize/write12-byte vectors. No output alias/capacity or min<=max checks.
bool __cdecl rf_renderer_world_aabb_screen_bounds(float *a1, float *a2, float *a3, float *a4, float *a5, float *a6)
{
  float v7; // [esp+Ch] [ebp-300h]
  float v8; // [esp+10h] [ebp-2FCh]
  float v9; // [esp+14h] [ebp-2F8h]
  float v10; // [esp+18h] [ebp-2F4h]
  int j; // [esp+1Ch] [ebp-2F0h]
  int k; // [esp+1Ch] [ebp-2F0h]
  int v13; // [esp+20h] [ebp-2ECh]
  float v14; // [esp+24h] [ebp-2E8h] BYREF
  _QWORD v15[16]; // [esp+28h] [ebp-2E4h]
  _DWORD v16[4]; // [esp+A8h] [ebp-264h] BYREF
  char v17; // [esp+BBh] [ebp-251h]
  char v18[384]; // [esp+BCh] [ebp-250h] BYREF
  float v19[3]; // [esp+23Ch] [ebp-D0h] BYREF
  float v20[3]; // [esp+248h] [ebp-C4h] BYREF
  float v21[3]; // [esp+254h] [ebp-B8h] BYREF
  float v22[3]; // [esp+260h] [ebp-ACh] BYREF
  float v23[3]; // [esp+26Ch] [ebp-A0h] BYREF
  float v24[3]; // [esp+278h] [ebp-94h] BYREF
  float v25[3]; // [esp+284h] [ebp-88h] BYREF
  float v26[3]; // [esp+290h] [ebp-7Ch] BYREF
  _DWORD v27[25]; // [esp+29Ch] [ebp-70h] BYREF
  char v28; // [esp+302h] [ebp-Ah]
  char v29; // [esp+303h] [ebp-9h]
  int i; // [esp+304h] [ebp-8h]
  char v31; // [esp+30Bh] [ebp-1h]

  rf_vector_construct_no_unwind((char *)v19, 0xCu, 8, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind(v18, 0x30u, 8, rf_vector_prefix_construct_noop);
  rf_vector3_set_components_thiscall(v19, *a1, a1[1], a1[2]);
  rf_vector3_set_components_thiscall(v20, *a2, a1[1], a1[2]);
  rf_vector3_set_components_thiscall(v21, *a2, a2[1], a1[2]);
  rf_vector3_set_components_thiscall(v22, *a1, a2[1], a1[2]);
  rf_vector3_set_components_thiscall(v23, *a1, a1[1], a2[2]);
  rf_vector3_set_components_thiscall(v24, *a2, a1[1], a2[2]);
  rf_vector3_set_components_thiscall(v25, *a2, a2[1], a2[2]);
  rf_vector3_set_components_thiscall(v26, *a1, a2[1], a2[2]);
  v31 = -1;
  v29 = 0;
  for ( i = 0; i < 8; ++i )
  {
    v17 = rf_renderer_transform_world_point_backend_wrapper((int)&v18[48 * i], &v19[3 * i]);
    v31 &= v17;
    v29 |= v17;
  }
  if ( v31 )
    return 0;
  v27[0] = 3;
  v27[1] = 2;
  v27[2] = 1;
  v27[3] = 0;
  v27[4] = 4;
  v27[5] = 5;
  v27[6] = 6;
  v27[7] = 7;
  v27[8] = 7;
  v27[9] = 6;
  v27[10] = 2;
  v27[11] = 3;
  v27[12] = 0;
  v27[13] = 1;
  v27[14] = 5;
  v27[15] = 4;
  v27[16] = 1;
  v27[17] = 2;
  v27[18] = 6;
  v27[19] = 5;
  v27[20] = 4;
  v27[21] = 7;
  v27[22] = 3;
  v27[23] = 0;
  v28 = 1;
  for ( i = 0; i < 6; ++i )
  {
    rf_vector_construct_no_unwind((char *)&v14, 8u, 16, rf_vector3_default_construct_noop);
    for ( j = 0; j < 4; ++j )
      v16[j] = &v18[48 * v27[4 * i + j]];
    v13 = rf_renderer_clip_polygon_to_screen_xy(4, (int)v16, (int)&v14);
    if ( v13 > 0 )
    {
      if ( v28 )
      {
        v28 = 0;
        *a5 = v14;
        *a6 = *(float *)v15;
        *a3 = v14;
        *a4 = *(float *)v15;
      }
      for ( k = 0; k < v13; ++k )
      {
        if ( *a3 >= (double)*(&v14 + 2 * k) )
          v10 = *(&v14 + 2 * k);
        else
          v10 = *a3;
        *a3 = v10;
        if ( *a5 <= (double)*(&v14 + 2 * k) )
          v9 = *(&v14 + 2 * k);
        else
          v9 = *a5;
        *a5 = v9;
        if ( *a4 >= (double)*(float *)&v15[k] )
          v8 = *(float *)&v15[k];
        else
          v8 = *a4;
        *a4 = v8;
        if ( *a6 <= (double)*(float *)&v15[k] )
          v7 = *(float *)&v15[k];
        else
          v7 = *a6;
        *a6 = v7;
      }
    }
  }
  return v28 == 0;
}

