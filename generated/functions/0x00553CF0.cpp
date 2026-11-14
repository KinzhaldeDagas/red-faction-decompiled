// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553CF0 rf_solid_split_selected_boundary_vertices_and_bridge
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Rebuilds selected vertices204 from selected faces216. Identifies selected vertices incident to any unselected face. Duplicates each boundary vertex and rewires ONLY unselected incident-face corners to its duplicate, updating both incidence arrays; selected faces retain original vertex pointers. For each directed selected boundary edge whose next vertex is also in boundary set and has no opposite selected edge, allocates quad(originalA,duplicateA,duplicateB,originalB), all four UV floats zero. Quads are linked into solid by allocator but this routine never finalizes, UV-projects, selects, or room-attaches them. No positions are moved and no rollback/validity guards. Temporary arrays are destroyed.
void __thiscall rf_solid_split_selected_boundary_vertices_and_bridge(void **this)
{
  int first_dword; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int *v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int *v10; // eax
  int *v11; // eax
  int *v12; // eax
  int *v13; // eax
  float *link; // [esp+18h] [ebp-60h]
  int index; // [esp+1Ch] [ebp-5Ch]
  float *v17; // [esp+20h] [ebp-58h]
  float *v18; // [esp+24h] [ebp-54h]
  void *v19[3]; // [esp+28h] [ebp-50h] BYREF
  int j; // [esp+34h] [ebp-44h]
  void *v21[3]; // [esp+38h] [ebp-40h] BYREF
  void *v22[3]; // [esp+44h] [ebp-34h] BYREF
  _DWORD *v23; // [esp+50h] [ebp-28h]
  void *v24[3]; // [esp+54h] [ebp-24h] BYREF
  _DWORD *corner_for_vertex_unchecked; // [esp+60h] [ebp-18h]
  int i; // [esp+64h] [ebp-14h]
  int v27; // [esp+68h] [ebp-10h]
  int v28; // [esp+74h] [ebp-4h]

  rf_solid_select_vertices_of_selected_faces(this);
  rf_dword_array_construct_capacity(v24, 0);
  v28 = 0;
  rf_dword_array_construct_capacity(v19, 0);
  LOBYTE(v28) = 1;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(this + 51);
    if ( i >= first_dword )
      break;
    v27 = *(_DWORD *)sub_552200(this + 51, i);
    for ( j = 0; ; ++j )
    {
      v2 = rf_receiver_get_first_dword((void *)(v27 + 32));
      if ( j >= v2 )
        break;
      v23 = *(_DWORD **)sub_552200((_DWORD *)(v27 + 32), j);
      if ( rf_pointer_array_find_index(this + 54, (int)v23) < 0 )
      {
        rf_pointer_array_append_unique(v24, v27);
        break;
      }
    }
  }
  rf_dword_array_construct_capacity(v22, 0);
  LOBYTE(v28) = 2;
  for ( i = 0; ; ++i )
  {
    v3 = rf_receiver_get_first_dword(v24);
    if ( i >= v3 )
      break;
    v17 = *(float **)sub_552200(v24, i);
    v18 = rf_solid_vertex_copy_append(this, v17);
    rf_pointer_array_append_dword(v19, (int)v18);
    rf_pointer_array_release_storage(v22);
    for ( j = 0; ; ++j )
    {
      v4 = rf_receiver_get_first_dword(v17 + 8);
      if ( j >= v4 )
        break;
      v23 = *(_DWORD **)sub_552200((_DWORD *)v17 + 8, j);
      if ( rf_pointer_array_find_index(this + 54, (int)v23) < 0 )
      {
        corner_for_vertex_unchecked = rf_face_find_corner_for_vertex_unchecked(v23, (int)v17);
        *corner_for_vertex_unchecked = v18;
        rf_pointer_array_append_unique((_DWORD *)v18 + 8, (int)v23);
        rf_pointer_array_append_dword(v22, (int)v23);
      }
    }
    for ( j = 0; ; ++j )
    {
      v5 = rf_receiver_get_first_dword(v22);
      if ( j >= v5 )
        break;
      v6 = (int *)sub_552200(v22, j);
      rf_pointer_array_remove_first((int *)v17 + 8, *v6);
    }
  }
  rf_dword_array_construct_capacity(v21, 0);
  LOBYTE(v28) = 3;
  for ( i = 0; ; ++i )
  {
    v7 = rf_receiver_get_first_dword(v24);
    if ( i >= v7 )
      break;
    v27 = *(_DWORD *)sub_552200(v24, i);
    rf_pointer_array_release_storage(v21);
    for ( j = 0; ; ++j )
    {
      v8 = rf_receiver_get_first_dword((void *)(v27 + 32));
      if ( j >= v8 )
        break;
      v23 = *(_DWORD **)sub_552200((_DWORD *)(v27 + 32), j);
      if ( rf_pointer_array_find_index(this + 54, (int)v23) >= 0 )
        rf_pointer_array_append_dword(v21, (int)v23);
    }
    for ( j = 0; ; ++j )
    {
      v9 = rf_receiver_get_first_dword(v21);
      if ( j >= v9 )
        break;
      v23 = *(_DWORD **)sub_552200(v21, j);
      corner_for_vertex_unchecked = rf_face_find_corner_for_vertex_unchecked(v23, v27);
      index = rf_pointer_array_find_index(v24, *(_DWORD *)corner_for_vertex_unchecked[5]);
      if ( index >= 0 && !rf_face_array_has_other_directed_edge(v27, *(_DWORD *)corner_for_vertex_unchecked[5], v21, j) )
      {
        link = (float *)rf_solid_face_allocate_link(this, v23 + 10);
        v10 = (int *)sub_552200(v24, i);
        rf_geomod_face_corner_append(link, *v10, 0.0, 0.0, 0.0, 0.0);
        v11 = (int *)sub_552200(v19, i);
        rf_geomod_face_corner_append(link, *v11, 0.0, 0.0, 0.0, 0.0);
        v12 = (int *)sub_552200(v19, index);
        rf_geomod_face_corner_append(link, *v12, 0.0, 0.0, 0.0, 0.0);
        v13 = (int *)sub_552200(v24, index);
        rf_geomod_face_corner_append(link, *v13, 0.0, 0.0, 0.0, 0.0);
      }
    }
  }
  LOBYTE(v28) = 2;
  rf_pointer_array_destroy_backing_storage(v21);
  LOBYTE(v28) = 1;
  rf_pointer_array_destroy_backing_storage(v22);
  LOBYTE(v28) = 0;
  rf_pointer_array_destroy_backing_storage(v19);
  v28 = -1;
  rf_pointer_array_destroy_backing_storage(v24);
}

