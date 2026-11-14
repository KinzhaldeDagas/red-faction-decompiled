// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005381B0 rf_solid_rebuild_lightmaps_blend_seams_and_borders
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Thiscall solid,shadowMode,optionalBegin(count),optionalPerDescriptor(). Invalidates active light list;for each current lightmap descriptor in array+192,sets ENTIRE flags byte8=07,updates lighting/upload54D990(mode),then per-descriptor callback. Selects descriptors with byte9 nonzero into temporary28-byte records:descriptor pointer0,face list+4,processed-neighbor-ID list+16;allocation has array cookie/count. Collects associated faces by descriptor index equality Face54,from solid+112 if roomIndex104==-1,otherwise owner room array144 entry face list+40. Calls5385B0 seam matcher. For each selected descriptor,copies border top row<-row1,bottom<-height-2,then left col<-col1,right<-width-2 for all rows
// (corners follow this order). No small-dimension checks. Sets entire flags8=08,updates54D990 again with mode0 to upload blended/border RAM. Destroys28-byte array via vector deleting adapter flags3. Return pointer incidental/former allocation address,not success/count. No NULL descriptor/allocation guards or transactional cleanup;callbacks can observe partial rebuild.
char *__thiscall rf_solid_rebuild_lightmaps_blend_seams_and_borders(
        char *this,
        int a2,
        void (__cdecl *a3)(int),
        void (*a4)(void))
{
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  char *result; // eax
  char *v8; // [esp+8h] [ebp-60h]
  char *v10; // [esp+18h] [ebp-50h]
  int kk; // [esp+24h] [ebp-44h]
  int jj; // [esp+28h] [ebp-40h]
  int v13; // [esp+2Ch] [ebp-3Ch]
  int m; // [esp+30h] [ebp-38h]
  int n; // [esp+34h] [ebp-34h]
  char *v16; // [esp+3Ch] [ebp-2Ch]
  _DWORD *v17; // [esp+40h] [ebp-28h]
  int v18; // [esp+48h] [ebp-20h]
  int v19; // [esp+4Ch] [ebp-1Ch]
  int v20; // [esp+4Ch] [ebp-1Ch]
  int first_dword; // [esp+54h] [ebp-14h]
  int i; // [esp+58h] [ebp-10h]
  int j; // [esp+58h] [ebp-10h]
  int k; // [esp+58h] [ebp-10h]
  int ii; // [esp+58h] [ebp-10h]

  rf_light_invalidate_active_world_list();
  first_dword = rf_receiver_get_first_dword(this + 192);
  if ( a3 )
    a3(first_dword);
  for ( i = 0; i < first_dword; ++i )
  {
    v18 = *(_DWORD *)sub_552200((_DWORD *)this + 48, i);
    *(_BYTE *)(v18 + 8) = 7;
    rf_lightmap_update_lighting_and_upload_rgb555(v18, (int)this, a2);
    if ( a4 )
      a4();
  }
  v19 = 0;
  for ( j = 0; j < first_dword; ++j )
  {
    if ( *(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)this + 48, j) + 9) )
      ++v19;
  }
  v4 = (28 * (unsigned __int64)(unsigned int)v19) >> 32 != 0 ? -1 : 28 * v19;
  v10 = (char *)operator new(__CFADD__(v4, 4) ? -1 : v4 + 4);
  if ( v10 )
  {
    *(_DWORD *)v10 = v19;
    `eh vector constructor iterator'(
      v10 + 4,
      0x1Cu,
      v19,
      (void (__thiscall *)(void *))rf_dual_array28_construct_members,
      (void (__thiscall *)(void *))rf_dual_array28_destroy_members);
    v8 = v10 + 4;
  }
  else
  {
    v8 = nullptr;
  }
  v20 = 0;
  for ( k = 0; k < first_dword; ++k )
  {
    v5 = sub_552200((_DWORD *)this + 48, k);
    v17 = *(_DWORD **)v5;
    if ( *(_BYTE *)(*(_DWORD *)v5 + 9) )
    {
      v16 = &v8[28 * v20++];
      *(_DWORD *)v16 = v17;
      if ( v17[26] == -1 )
      {
        for ( m = rf_receiver_get_first_dword(this + 112); m; m = rf_solid_face_next_link(m) )
        {
          if ( *(__int16 *)(m + 54) == *v17 )
            rf_pointer_array_append_dword((_DWORD *)v16 + 1, m);
        }
      }
      else
      {
        v6 = sub_552200((_DWORD *)this + 36, v17[26]);
        for ( n = rf_receiver_get_first_dword((void *)(*(_DWORD *)v6 + 40)); n; n = rf_face_next_room_link(n) )
        {
          if ( *(__int16 *)(n + 54) == *v17 )
            rf_pointer_array_append_dword((_DWORD *)v16 + 1, n);
        }
      }
    }
  }
  rf_lightmap_blend_matching_record_seams((int)v8, v20);
  for ( ii = 0; ii < v20; ++ii )
  {
    v13 = *(_DWORD *)&v8[28 * ii];
    for ( jj = 0; jj < *(_DWORD *)(v13 + 24); ++jj )
    {
      rf_lightmap_tile_copy_rgb24_texel_unchecked((_DWORD *)v13, jj, 0, jj, 1);
      rf_lightmap_tile_copy_rgb24_texel_unchecked(
        (_DWORD *)v13,
        jj,
        *(_DWORD *)(v13 + 28) - 1,
        jj,
        *(_DWORD *)(v13 + 28) - 2);
    }
    for ( kk = 0; kk < *(_DWORD *)(v13 + 28); ++kk )
    {
      rf_lightmap_tile_copy_rgb24_texel_unchecked((_DWORD *)v13, 0, kk, 1, kk);
      rf_lightmap_tile_copy_rgb24_texel_unchecked(
        (_DWORD *)v13,
        *(_DWORD *)(v13 + 24) - 1,
        kk,
        *(_DWORD *)(v13 + 24) - 2,
        kk);
    }
    *(_BYTE *)(v13 + 8) = 8;
    rf_lightmap_update_lighting_and_upload_rgb555(v13, (int)this, 0);
  }
  result = v8;
  if ( v8 )
    return rf_dual_array28_vector_deleting_destructor(v8, 3);
  return result;
}

