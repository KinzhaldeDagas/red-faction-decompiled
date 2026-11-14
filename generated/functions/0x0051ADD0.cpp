// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051ADD0 rf_geomod_component_extract
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall source solid plus component label, RET4 returns new888-byte solid. Clears DWORD28 scratch mapping on ALL source vertices120. Collect unique authored-room pointers face68 for faces whose label44 matches, then choose FIRST room having strictly smallest SIGNED DWORD32; no null-room guard. For each matching face cache next before mutation and copy to output with source mapping and flag0. For nonnegative signed lightmap WORD54, allocate/register fresh124-byte descriptor in output, copying plane108..123, DWORD/float fields12,16,20,24,28,44,48,52..75,76..91,92,96,100 and BYTE9/10; set output face lightmap to new descriptor WORD0 and original face WORD54=-1. Other descriptor fields retain constructor
// values. Negative lightmap becomes output-1. If original face room68 equals selected room, remove face decal polygons via525460, unlink solid membership and destroy original. Otherwise reverse-clone source face, attach clone to selected room, and call runtime room/portal assignment for BOTH original and clone using original room and selected room. Finalize output bounds; erase/release source vertices with empty incidence32 without incrementing erased index; finalize source bounds. When global52A9E0 returns exactly BYTE1, call receiver-ignored no-op51D690 with extracted bounds72/84. Temporary room-array storage released. Allocation/copy failures unchecked; no rollback, model substitution, centering or render-tree build here.
float *__thiscall rf_geomod_component_extract(char *this, int a2)
{
  int first_dword; // eax
  int v3; // eax
  int v4; // eax
  float *v6; // [esp+4h] [ebp-80h]
  float *v7; // [esp+8h] [ebp-7Ch]
  float *v9; // [esp+10h] [ebp-74h]
  float v10[3]; // [esp+14h] [ebp-70h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-64h] BYREF
  void *v12; // [esp+2Ch] [ebp-58h]
  float *v13; // [esp+30h] [ebp-54h]
  void *v14; // [esp+34h] [ebp-50h]
  float *v15; // [esp+38h] [ebp-4Ch]
  int v16; // [esp+3Ch] [ebp-48h]
  int v17; // [esp+40h] [ebp-44h]
  _DWORD *v18; // [esp+44h] [ebp-40h]
  float *v19; // [esp+48h] [ebp-3Ch]
  int v20; // [esp+4Ch] [ebp-38h]
  int v21; // [esp+50h] [ebp-34h]
  _DWORD *link; // [esp+54h] [ebp-30h]
  int v23; // [esp+58h] [ebp-2Ch]
  _DWORD *j; // [esp+5Ch] [ebp-28h]
  void *v25[3]; // [esp+60h] [ebp-24h] BYREF
  int i; // [esp+6Ch] [ebp-18h]
  float *v27; // [esp+70h] [ebp-14h]
  float *v28; // [esp+74h] [ebp-10h]
  int v29; // [esp+80h] [ebp-4h]

  v14 = operator new(0x378u);
  v29 = 0;
  if ( v14 )
    v7 = (float *)rf_solid888_construct((void **)v14);
  else
    v7 = nullptr;
  v15 = v7;
  v29 = -1;
  v28 = v7;
  for ( i = 0; i < rf_receiver_get_first_dword(this + 120); ++i )
  {
    v23 = *(_DWORD *)sub_552200((_DWORD *)this + 30, i);
    *(_DWORD *)(v23 + 28) = 0;
  }
  rf_dword_array_construct_capacity(v25, 0);
  v29 = 1;
  for ( j = (_DWORD *)rf_receiver_get_first_dword(this + 112); j; j = (_DWORD *)rf_solid_face_next_link((int)j) )
  {
    if ( j[11] == a2 )
      rf_pointer_array_append_unique(v25, j[17]);
  }
  v27 = nullptr;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(v25);
    if ( i >= first_dword )
      break;
    if ( v27 )
    {
      v3 = sub_552200(v25, i);
      if ( *(_DWORD *)(*(_DWORD *)v3 + 32) >= *((_DWORD *)v27 + 8) )
        continue;
    }
    v27 = *(float **)sub_552200(v25, i);
  }
  rf_pointer_array_release_storage(v25);
  for ( j = (_DWORD *)rf_receiver_get_first_dword(this + 112); j; j = link )
  {
    link = (_DWORD *)rf_solid_face_next_link((int)j);
    if ( j[11] == a2 )
    {
      v21 = rf_geomod_face_copy_to_output(j, v28, (int)this, 0);
      if ( *((__int16 *)j + 27) < 0 )
      {
        *(_WORD *)(v21 + 54) = -1;
      }
      else
      {
        v20 = *(_DWORD *)sub_552200((_DWORD *)this + 48, *((__int16 *)j + 27));
        v12 = operator new(0x7Cu);
        LOBYTE(v29) = 2;
        if ( v12 )
          v6 = (float *)rf_lightmap_descriptor124_construct_register(v12, (int)v28);
        else
          v6 = nullptr;
        v13 = v6;
        LOBYTE(v29) = 1;
        v19 = v6;
        rf_plane_copy(v6 + 27, (float *)(v20 + 108));
        v19[23] = *(float *)(v20 + 92);
        *((_BYTE *)v19 + 10) = *(_BYTE *)(v20 + 10);
        v19[7] = *(float *)(v20 + 28);
        v19[3] = *(float *)(v20 + 12);
        *((_BYTE *)v19 + 9) = *(_BYTE *)(v20 + 9);
        v19[24] = *(float *)(v20 + 96);
        rf_vector2_copy_return_source(v19 + 21, (float *)(v20 + 84));
        rf_vector2_copy_return_source(v19 + 19, (float *)(v20 + 76));
        v19[25] = *(float *)(v20 + 100);
        v19[6] = *(float *)(v20 + 24);
        v19[11] = *(float *)(v20 + 44);
        v19[12] = *(float *)(v20 + 48);
        v19[4] = *(float *)(v20 + 16);
        v19[5] = *(float *)(v20 + 20);
        rf_vector_copy(v19 + 13, copy_result, (const float *)(v20 + 52));
        rf_vector_copy(v19 + 16, v10, (const float *)(v20 + 64));
        *(_WORD *)(v21 + 54) = *(_WORD *)v19;
        *((_WORD *)j + 27) = -1;
      }
      if ( (float *)j[17] == v27 )
      {
        rf_geomod_face_decal_polygons_remove((int)j);
        rf_solid_face_list_remove((int *)this + 28, (int)j);
        rf_geomod_face_destroy(j);
      }
      else
      {
        v18 = rf_geomod_face_clone_reversed(j, (int)this);
        rf_geomod_room_face_attach(v27, (int)v18);
        rf_world_assign_face_runtime_room_portal(this, (int)j, j[17], (int)v27);
        rf_world_assign_face_runtime_room_portal(this, (int)v18, j[17], (int)v27);
      }
    }
  }
  rf_solid_finalize_bounds(v28);
  v17 = 0;
  while ( 1 )
  {
    v4 = rf_receiver_get_first_dword(this + 120);
    if ( v17 >= v4 )
      break;
    v16 = *(_DWORD *)sub_552200((_DWORD *)this + 30, v17);
    if ( rf_receiver_get_first_dword((void *)(v16 + 32)) )
    {
      ++v17;
    }
    else
    {
      rf_pointer_array_erase_index_unchecked((_DWORD *)this + 30, v17);
      rf_geomod_vertex_destroy_and_release_to_pool(v16);
    }
  }
  rf_solid_finalize_bounds((float *)this);
  if ( rf_renderer_world_lighting_enabled() )
    rf_solid_bounds_notification_noop_51d690((int)(v28 + 18), (int)(v28 + 21));
  v9 = v28;
  v29 = -1;
  rf_pointer_array_destroy_backing_storage(v25);
  return v9;
}

