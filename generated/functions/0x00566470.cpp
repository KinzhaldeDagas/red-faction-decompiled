// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566470 rf_model_handle_build_lod_vertex_rgb_packets
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Supports tag1 or2(first embedded character LOD container);other tagsreturn0. Caller supplies unbounded output buffer. Per mesh reserves16byte header:total byteSize0 and LOD payload pointers4/8/12;writes one pointer per LOD without checking3-slot limit. Payload bytes per LOD=sum(3*batchWORD40). Transforms mesh LOD-table center by caller orientation/translation, radius unchanged, builds active light list, pushes instance transform and syncs receiver lights. Per batch uses material textureID16 and first float from pointer188; while current factor<1 scans same-texture materials for larger factor, may stop once>=1. Converts factor*255 to raw byte WITHOUT clamp. Per count entry, source position/normal
// addresses=arrays4/8 +36*i; computes nonworld RGB using gain3.2 in multiplayer else2.0, then replaces EACH channel with UNSIGNED MAX(channel,materialByte) via566E80, not multiplication. Invalidates active light list and pops transform per mesh;returns1. No buffer capacity, material-array/key-pointer, LOD-count or scale checks.
int __cdecl rf_model_handle_build_lod_vertex_rgb_packets(_DWORD *a1, int a2, float *a3, float *a4, _DWORD *a5)
{
  int mesh_count; // eax
  float *lod_table_translation; // eax
  unsigned __int8 v8; // al
  unsigned __int8 v9; // al
  unsigned __int8 v10; // al
  float lod_table_radius; // [esp+0h] [ebp-9Ch]
  float v12; // [esp+Ch] [ebp-90h]
  float copy_result[3]; // [esp+20h] [ebp-7Ch] BYREF
  char v14[12]; // [esp+2Ch] [ebp-70h] BYREF
  int ii; // [esp+38h] [ebp-64h]
  int v16; // [esp+3Ch] [ebp-60h]
  int n; // [esp+40h] [ebp-5Ch]
  int v18; // [esp+44h] [ebp-58h]
  float v19; // [esp+48h] [ebp-54h]
  int v20; // [esp+4Ch] [ebp-50h]
  int v21; // [esp+50h] [ebp-4Ch]
  unsigned __int8 v22; // [esp+57h] [ebp-45h]
  int m; // [esp+58h] [ebp-44h]
  int v24; // [esp+5Ch] [ebp-40h]
  int v25; // [esp+60h] [ebp-3Ch]
  int k; // [esp+64h] [ebp-38h]
  int v27; // [esp+68h] [ebp-34h]
  int v28; // [esp+6Ch] [ebp-30h]
  float destination[3]; // [esp+70h] [ebp-2Ch] BYREF
  _DWORD *v30; // [esp+7Ch] [ebp-20h]
  _DWORD *v31; // [esp+80h] [ebp-1Ch]
  _DWORD *v32; // [esp+84h] [ebp-18h]
  _DWORD *v33; // [esp+88h] [ebp-14h]
  int i; // [esp+8Ch] [ebp-10h]
  _DWORD *v35; // [esp+90h] [ebp-Ch]
  _DWORD *v36; // [esp+94h] [ebp-8h]
  int j; // [esp+98h] [ebp-4h]

  v35 = a1;
  if ( *a1 == 1 )
  {
    v36 = (_DWORD *)v35[1];
  }
  else
  {
    if ( *a1 != 2 )
      return 0;
    v36 = rf_vector3_default_construct_noop((void *)(v35[2] + 6592));
  }
  for ( i = 0; ; ++i )
  {
    mesh_count = rf_v3c_asset_get_mesh_count(v36);
    if ( i >= mesh_count )
      break;
    v32 = (_DWORD *)(v36[19] + 144 * i);
    v31 = (_DWORD *)v32[35];
    v30 = a5;
    v33 = a5 + 1;
    a5 += 4;
    *v30 = 16;
    for ( j = 0; j < *v31; ++j )
    {
      v33[j] = a5;
      v28 = 0;
      v27 = v31[j + 1];
      for ( k = 0; k < *(unsigned __int16 *)(v27 + 12); ++k )
        v28 += 3 * *(unsigned __int16 *)(*(_DWORD *)(v27 + 8) + 56 * k + 40);
      a5 = (_DWORD *)((char *)a5 + v28);
      *v30 += v28;
    }
    rf_vector3_set_components_return_destination(destination, 0.0, 0.0, 0.0);
    lod_table_translation = rf_model_mesh144_get_lod_table_translation(v32, (float *)v14);
    rf_vector_copy(destination, copy_result, lod_table_translation);
    rf_vector_rotate_by_matrix3(destination, a4);
    rf_vector_accumulate(destination, a3);
    lod_table_radius = rf_mesh144_get_lod_table_radius(v32);
    rf_light_build_active_list_for_sphere_query(a2, destination, lod_table_radius, 0, 1);
    rf_renderer_push_instance_transform_dispatch((int)a3, (int)a4);
    rf_light_sync_active_receiver_space_if_enabled();
    for ( j = 0; j < *v31; ++j )
    {
      v24 = v31[j + 1];
      v25 = v33[j];
      for ( m = 0; m < *(unsigned __int16 *)(v24 + 12); ++m )
      {
        v20 = *(_DWORD *)(v24 + 8) + 56 * m;
        v21 = *(unsigned __int8 *)(v24 + *(_DWORD *)(v20 + 32) + 24);
        v18 = *(_DWORD *)(v32[34] + 200 * v21 + 16);
        v19 = **(float **)(v32[34] + 200 * v21 + 188);
        for ( n = 0; n < v32[33] && v19 < 1.0; ++n )
        {
          v16 = v32[34] + 200 * n;
          if ( *(_DWORD *)(v16 + 16) == v18 && **(float **)(v16 + 188) > (double)v19 )
            v19 = **(float **)(v16 + 188);
        }
        v22 = (int)(v19 * 255.0);
        for ( ii = 0; ii < *(unsigned __int16 *)(v20 + 40); ++ii )
        {
          if ( rf_multiplayer_runtime_mode )
            v12 = 3.2;
          else
            v12 = 2.0;
          rf_renderer_compute_nonworld_diffuse_rgb8(
            (_BYTE *)v25,
            (_BYTE *)(v25 + 1),
            (_BYTE *)(v25 + 2),
            1,
            (float *)(*(_DWORD *)(v20 + 4) + 36 * ii),
            (float *)(*(_DWORD *)(v20 + 8) + 36 * ii),
            v12);
          v8 = rf_byte_maximum_unsigned(*(_BYTE *)v25, v22);
          *(_BYTE *)v25 = v8;
          v9 = rf_byte_maximum_unsigned(*(_BYTE *)(v25 + 1), v22);
          *(_BYTE *)(v25 + 1) = v9;
          v10 = rf_byte_maximum_unsigned(*(_BYTE *)(v25 + 2), v22);
          *(_BYTE *)(v25 + 2) = v10;
          v25 += 3;
        }
      }
    }
    rf_light_invalidate_active_world_list();
    rf_renderer_pop_instance_transform_dispatch();
  }
  return 1;
}

