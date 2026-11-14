// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553290 rf_solid_flip_selected_triangle_diagonal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Reads the first two selected faces from array216 without checking count or triangle/shared-edge validity. Requires identical room68 or invokes fatal diagnostic g_edit.cpp:350. Finds two shared vertices through incident-face membership and the opposite corners; creates two replacement triangles connecting the opposite vertices. Copies four corner UVs except second triangle opposite-A corner takes its fourth UV from opposite-B (original instruction quirk), then generated-UV projection runs. Valid replacements are selected/appended and room-attached; invalid replacements are destroyed. Rebuilds existing room spatial root for unowned faces, then destroys BOTH original faces even if a replacement failed. No rollback.
void __thiscall rf_solid_flip_selected_triangle_diagonal(void *this)
{
  int v1; // eax
  _DWORD *v2; // [esp+10h] [ebp-3Ch]
  _DWORD *v3; // [esp+14h] [ebp-38h]
  _DWORD *v5; // [esp+20h] [ebp-2Ch]
  float *v6; // [esp+24h] [ebp-28h]
  _DWORD *v7; // [esp+28h] [ebp-24h]
  int v8; // [esp+2Ch] [ebp-20h]
  int v9; // [esp+30h] [ebp-1Ch]
  _DWORD *v10; // [esp+34h] [ebp-18h]
  float *link; // [esp+38h] [ebp-14h]
  int v12; // [esp+3Ch] [ebp-10h]
  _DWORD *v13; // [esp+40h] [ebp-Ch]
  int v14; // [esp+44h] [ebp-8h]
  _DWORD *i; // [esp+48h] [ebp-4h]
  _DWORD *j; // [esp+48h] [ebp-4h]
  int v17; // [esp+48h] [ebp-4h]

  v12 = *(_DWORD *)sub_552200((_DWORD *)this + 54, 0);
  v1 = sub_552200((_DWORD *)this + 54, 1);
  v9 = *(_DWORD *)v1;
  v5 = nullptr;
  v7 = nullptr;
  v13 = nullptr;
  v10 = nullptr;
  if ( *(_DWORD *)(v12 + 68) != *(_DWORD *)(*(_DWORD *)v1 + 68) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\g_solid\\g_edit.cpp",
      350,
      "The triangles cannot span a room!\nYou can hit continue.");
  v14 = *(_DWORD *)(v12 + 68);
  for ( i = *(_DWORD **)(v12 + 64); i; i = v3 )
  {
    if ( rf_pointer_array_find_index((_DWORD *)(*i + 32), v9) < 0 )
    {
      v13 = i;
    }
    else if ( v5 )
    {
      v7 = i;
    }
    else
    {
      v5 = i;
    }
    if ( i[5] == *(_DWORD *)(v12 + 64) )
      v3 = nullptr;
    else
      v3 = (_DWORD *)i[5];
  }
  for ( j = *(_DWORD **)(v9 + 64); j; j = v2 )
  {
    if ( *j != *v5 && *j != *v7 )
      v10 = j;
    if ( j[5] == *(_DWORD *)(v9 + 64) )
      v2 = nullptr;
    else
      v2 = (_DWORD *)j[5];
  }
  link = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)(v12 + 40));
  v6 = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)(v9 + 40));
  rf_geomod_face_corner_append(
    link,
    *v13,
    *((float *)v13 + 1),
    *((float *)v13 + 2),
    *((float *)v13 + 3),
    *((float *)v13 + 4));
  rf_geomod_face_corner_append(
    link,
    *v10,
    *((float *)v10 + 1),
    *((float *)v10 + 2),
    *((float *)v10 + 3),
    *((float *)v10 + 4));
  v17 = v10[5];
  rf_geomod_face_corner_append(
    link,
    *(_DWORD *)v17,
    *(float *)(v17 + 4),
    *(float *)(v17 + 8),
    *(float *)(v17 + 12),
    *(float *)(v17 + 16));
  rf_geomod_face_corner_append(
    v6,
    *v10,
    *((float *)v10 + 1),
    *((float *)v10 + 2),
    *((float *)v10 + 3),
    *((float *)v10 + 4));
  rf_geomod_face_corner_append(
    v6,
    *v13,
    *((float *)v13 + 1),
    *((float *)v13 + 2),
    *((float *)v13 + 3),
    *((float *)v10 + 4));
  v8 = v13[5];
  if ( v8 == v17 )
    v8 = *(_DWORD *)(v8 + 20);
  rf_geomod_face_corner_append(
    v6,
    *(_DWORD *)v8,
    *(float *)(v8 + 4),
    *(float *)(v8 + 8),
    *(float *)(v8 + 12),
    *(float *)(v8 + 16));
  if ( rf_geomod_face_finalize_geometry((int)link, nullptr, 0) )
  {
    rf_geomod_generated_uv_project((int)link);
    rf_pointer_array_append_dword((_DWORD *)this + 54, (int)link);
    if ( *(_DWORD *)(v12 + 68) )
      rf_geomod_room_face_attach(*(float **)(v12 + 68), (int)link);
  }
  else
  {
    rf_solid_face_remove_destroy((int *)this, link, 0);
  }
  if ( rf_geomod_face_finalize_geometry((int)v6, nullptr, 0) )
  {
    rf_geomod_generated_uv_project((int)v6);
    rf_pointer_array_append_dword((_DWORD *)this + 54, (int)v6);
    if ( *(_DWORD *)(v9 + 68) )
      rf_geomod_room_face_attach(*(float **)(v9 + 68), (int)v6);
  }
  else
  {
    rf_solid_face_remove_destroy((int *)this, v6, 0);
  }
  if ( v14 && *(_DWORD *)(v14 + 60) )
    rf_room_spatial_tree_insert_unowned_faces(*(void **)(v14 + 60), (void *)(v14 + 40));
  rf_solid_face_remove_destroy((int *)this, (_DWORD *)v12, 0);
  rf_solid_face_remove_destroy((int *)this, (_DWORD *)v9, 0);
}

