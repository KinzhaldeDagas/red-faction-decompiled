// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00554D30 rf_solid_bevel_selected_faces_by_scale
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Rebuilds selected vertices; partitions them into interior(all incident faces selected) and boundary. Duplicates every selected face with separate new corner vertices, scales each duplicate about its own arithmetic centroid, and projects UVs. Builds bridging quads between adjacent selected duplicates once for higher selected index, or between old edge and duplicate edge when adjacent face is unselected. Caps interior vertices by ordering duplicate vertices through previous-corner adjacency; no progress guard, so malformed topology can loop forever. Boundary vertices receive triangles to adjacent duplicate vertices. Boundary dedup scratch checks source-face pointer but appends NEW triangle pointer, so
// repeated source faces are not reliably suppressed. Deletes original selected faces and interior vertices, then selects generated faces <=4 corners directly; larger caps are replaced by selected centroid triangle fans. Finalize failures ignored, no transaction, no explicit room attachment for direct generated faces.
void __thiscall rf_solid_bevel_selected_faces_by_scale(_DWORD *this, float a2)
{
  int first_dword; // eax
  int *v3; // eax
  int v4; // eax
  int *v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int *v13; // eax
  int v14; // eax
  int v15; // eax
  _DWORD **v16; // eax
  int v17; // eax
  _DWORD *v19; // [esp+18h] [ebp-E8h]
  float *v20; // [esp+1Ch] [ebp-E4h]
  int v21; // [esp+24h] [ebp-DCh]
  int v22; // [esp+28h] [ebp-D8h]
  int m; // [esp+2Ch] [ebp-D4h]
  int v24; // [esp+30h] [ebp-D0h]
  _DWORD *v25; // [esp+34h] [ebp-CCh]
  int *v26; // [esp+3Ch] [ebp-C4h]
  int v27; // [esp+40h] [ebp-C0h]
  void *v28[3]; // [esp+44h] [ebp-BCh] BYREF
  int v29; // [esp+50h] [ebp-B0h]
  int v30; // [esp+54h] [ebp-ACh]
  _DWORD *v31; // [esp+58h] [ebp-A8h]
  int v32; // [esp+5Ch] [ebp-A4h]
  int *v33; // [esp+60h] [ebp-A0h]
  int v34; // [esp+64h] [ebp-9Ch]
  int v35; // [esp+68h] [ebp-98h]
  float *v36; // [esp+6Ch] [ebp-94h]
  float *link; // [esp+70h] [ebp-90h]
  int v38; // [esp+74h] [ebp-8Ch]
  int v39; // [esp+78h] [ebp-88h]
  int v40; // [esp+7Ch] [ebp-84h]
  float *v41; // [esp+80h] [ebp-80h]
  int v42; // [esp+84h] [ebp-7Ch]
  _DWORD *v43; // [esp+88h] [ebp-78h]
  int v44; // [esp+8Ch] [ebp-74h]
  int index; // [esp+90h] [ebp-70h]
  int v46; // [esp+94h] [ebp-6Ch]
  char v47; // [esp+9Bh] [ebp-65h]
  int k; // [esp+9Ch] [ebp-64h]
  void *v49[3]; // [esp+A0h] [ebp-60h] BYREF
  void *v50[3]; // [esp+ACh] [ebp-54h] BYREF
  void *v51[3]; // [esp+B8h] [ebp-48h] BYREF
  void *v52[3]; // [esp+C4h] [ebp-3Ch] BYREF
  int i; // [esp+D0h] [ebp-30h]
  void *v54[3]; // [esp+D4h] [ebp-2Ch] BYREF
  int j; // [esp+E0h] [ebp-20h]
  int v56; // [esp+E4h] [ebp-1Ch]
  void *v57[3]; // [esp+E8h] [ebp-18h] BYREF
  int v58; // [esp+FCh] [ebp-4h]

  rf_dword_array_construct_capacity(v54, 0);
  v58 = 0;
  rf_dword_array_construct_capacity(v49, 0);
  LOBYTE(v58) = 1;
  rf_dword_array_construct_capacity(v51, 0);
  LOBYTE(v58) = 2;
  for ( i = rf_receiver_get_first_dword(this + 28); i; i = rf_solid_face_next_link(i) )
    ;
  rf_solid_select_vertices_of_selected_faces((void **)this);
  for ( j = 0; ; ++j )
  {
    first_dword = rf_receiver_get_first_dword(this + 51);
    if ( j >= first_dword )
      break;
    v56 = *(_DWORD *)sub_552200(this + 51, j);
    v47 = 1;
    for ( k = 0; k < rf_receiver_get_first_dword((void *)(v56 + 32)) && v47; ++k )
    {
      v3 = (int *)sub_552200((_DWORD *)(v56 + 32), k);
      if ( rf_pointer_array_find_index(this + 54, *v3) < 0 )
        v47 = 0;
    }
    if ( v47 )
      rf_pointer_array_append_dword(v49, v56);
    else
      rf_pointer_array_append_dword(v54, v56);
  }
  rf_dword_array_construct_capacity(v52, 0);
  LOBYTE(v58) = 3;
  for ( j = 0; ; ++j )
  {
    v4 = rf_receiver_get_first_dword(this + 54);
    if ( j >= v4 )
      break;
    v5 = (int *)sub_552200(this + 54, j);
    i = (int)rf_solid_duplicate_face_with_new_vertices(this, *v5);
    rf_face_scale_vertices_about_corner_centroid((_DWORD *)i, a2);
    rf_pointer_array_append_dword(v52, i);
    rf_pointer_array_append_dword(v51, i);
  }
  rf_dword_array_construct_capacity(v57, 0);
  LOBYTE(v58) = 4;
  for ( j = 0; ; ++j )
  {
    v6 = rf_receiver_get_first_dword(this + 54);
    if ( j >= v6 )
      break;
    i = *(_DWORD *)sub_552200(this + 54, j);
    v46 = *(_DWORD *)sub_552200(v52, j);
    rf_pointer_array_release_storage(v57);
    rf_face_collect_reverse_edge_neighbors(v57, (int *)i);
    for ( k = 0; k < rf_receiver_get_first_dword(v57); ++k )
    {
      v43 = *(_DWORD **)sub_552200(v57, k);
      v42 = *(_DWORD *)(i + 64);
      v44 = *(_DWORD *)(v46 + 64);
      while ( !rf_geomod_face_contains_shared_vertex(v43, *(_DWORD *)v42)
           || !rf_geomod_face_contains_shared_vertex(v43, **(_DWORD **)(v42 + 20)) )
      {
        v42 = *(_DWORD *)(v42 + 20);
        v44 = *(_DWORD *)(v44 + 20);
      }
      index = rf_pointer_array_find_index(this + 54, (int)v43);
      if ( index >= 0 )
      {
        if ( index > j )
        {
          v7 = rf_pointer_array_find_index(this + 54, (int)v43);
          v38 = *(_DWORD *)sub_552200(v52, v7);
          v40 = v43[16];
          v39 = *(_DWORD *)(v38 + 64);
          while ( !rf_geomod_face_contains_shared_vertex((_DWORD *)i, *(_DWORD *)v40)
               || !rf_geomod_face_contains_shared_vertex((_DWORD *)i, **(_DWORD **)(v40 + 20)) )
          {
            v40 = *(_DWORD *)(v40 + 20);
            v39 = *(_DWORD *)(v39 + 20);
          }
          link = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)(i + 40));
          rf_geomod_face_corner_append(link, **(_DWORD **)(v39 + 20), 0.0, 0.0, 0.0, 0.0);
          rf_geomod_face_corner_append(link, *(_DWORD *)v39, 0.0, 0.0, 0.0, 0.0);
          rf_geomod_face_corner_append(link, **(_DWORD **)(v44 + 20), 0.0, 0.0, 0.0, 0.0);
          rf_geomod_face_corner_append(link, *(_DWORD *)v44, 0.0, 0.0, 0.0, 0.0);
          rf_geomod_face_finalize_geometry((int)link, nullptr, 0);
          rf_geomod_generated_uv_project((int)link);
          rf_pointer_array_append_dword(v51, (int)link);
        }
      }
      else
      {
        v41 = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)(i + 40));
        rf_geomod_face_corner_append(v41, *(_DWORD *)v42, 0.0, 0.0, 0.0, 0.0);
        rf_geomod_face_corner_append(v41, **(_DWORD **)(v42 + 20), 0.0, 0.0, 0.0, 0.0);
        rf_geomod_face_corner_append(v41, **(_DWORD **)(v44 + 20), 0.0, 0.0, 0.0, 0.0);
        rf_geomod_face_corner_append(v41, *(_DWORD *)v44, 0.0, 0.0, 0.0, 0.0);
        rf_geomod_face_finalize_geometry((int)v41, nullptr, 0);
        rf_geomod_generated_uv_project((int)v41);
        rf_pointer_array_append_dword(v51, (int)v41);
      }
    }
  }
  rf_dword_array_construct_capacity(v50, 0);
  LOBYTE(v58) = 5;
  for ( j = 0; ; ++j )
  {
    v8 = rf_receiver_get_first_dword(v49);
    if ( j >= v8 )
      break;
    v56 = *(_DWORD *)sub_552200(v49, j);
    for ( k = 0; k < rf_receiver_get_first_dword((void *)(v56 + 32)); ++k )
    {
      i = *(_DWORD *)sub_552200((_DWORD *)(v56 + 32), k);
      v9 = rf_pointer_array_find_index(this + 54, i);
      v32 = *(_DWORD *)sub_552200(v52, v9);
      v31 = *(_DWORD **)(i + 64);
      v33 = *(int **)(v32 + 64);
      while ( *v31 != v56 )
      {
        v31 = (_DWORD *)v31[5];
        v33 = (int *)v33[5];
      }
      rf_pointer_array_append_dword(v50, *v33);
    }
    v34 = *(_DWORD *)sub_552200(v50, 0);
    rf_pointer_array_erase_index_unchecked(v50, 0);
    v10 = sub_552200((_DWORD *)(v34 + 32), 0);
    v36 = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)(*(_DWORD *)v10 + 40));
    rf_geomod_face_corner_append(v36, v34, 0.0, 0.0, 0.0, 0.0);
    v35 = 1;
    while ( rf_receiver_get_first_dword(v50) > 0 )
    {
      for ( k = 0; k < rf_receiver_get_first_dword((void *)(v34 + 32)); ++k )
      {
        i = *(_DWORD *)sub_552200((_DWORD *)(v34 + 32), k);
        v30 = *(_DWORD *)rf_face_find_corner_for_vertex_unchecked((_DWORD *)i, v34)[6];
        v29 = rf_pointer_array_find_index(v50, v30);
        if ( v29 > -1 )
        {
          v34 = v30;
          rf_geomod_face_corner_append(v36, v30, 0.0, 0.0, 0.0, 0.0);
          ++v35;
          rf_pointer_array_erase_index_unchecked(v50, v29);
        }
      }
    }
    rf_geomod_face_finalize_geometry((int)v36, nullptr, 0);
    rf_geomod_generated_uv_project((int)v36);
    rf_pointer_array_append_dword(v51, (int)v36);
  }
  for ( j = 0; ; ++j )
  {
    v11 = rf_receiver_get_first_dword(v54);
    if ( j >= v11 )
      break;
    v56 = *(_DWORD *)sub_552200(v54, j);
    rf_pointer_array_release_storage(v50);
    for ( k = 0; ; ++k )
    {
      v12 = rf_receiver_get_first_dword((void *)(v56 + 32));
      if ( k >= v12 )
        break;
      v13 = (int *)sub_552200((_DWORD *)(v56 + 32), k);
      v27 = rf_pointer_array_find_index(this + 54, *v13);
      if ( v27 > -1 )
      {
        i = *(_DWORD *)sub_552200((_DWORD *)(v56 + 32), k);
        v14 = sub_552200(v52, v27);
        v25 = *(_DWORD **)(i + 64);
        v26 = *(int **)(*(_DWORD *)v14 + 64);
        while ( *v25 != v56 )
        {
          v25 = (_DWORD *)v25[5];
          v26 = (int *)v26[5];
        }
        rf_pointer_array_append_dword(v50, *v26);
      }
    }
    rf_dword_array_construct_capacity(v28, 0);
    LOBYTE(v58) = 6;
    for ( k = 0; ; ++k )
    {
      v15 = rf_receiver_get_first_dword(v50);
      if ( k >= v15 )
        break;
      v22 = *(_DWORD *)sub_552200(v50, k);
      v24 = rf_receiver_get_first_dword((void *)(v22 + 32));
      for ( m = 0; m < v24; ++m )
      {
        i = *(_DWORD *)sub_552200((_DWORD *)(v22 + 32), m);
        if ( rf_pointer_array_find_index(v28, i) < 0 )
        {
          v21 = *(_DWORD *)rf_face_find_corner_for_vertex_unchecked((_DWORD *)i, v22)[6];
          if ( rf_pointer_array_find_index(v50, v21) > -1 )
          {
            v20 = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)(i + 40));
            rf_geomod_face_corner_append(v20, v56, 0.0, 0.0, 0.0, 0.0);
            rf_geomod_face_corner_append(v20, v22, 0.0, 0.0, 0.0, 0.0);
            rf_geomod_face_corner_append(v20, v21, 0.0, 0.0, 0.0, 0.0);
            rf_geomod_face_finalize_geometry((int)v20, nullptr, 0);
            rf_geomod_generated_uv_project((int)v20);
            rf_pointer_array_append_dword(v51, (int)v20);
            rf_pointer_array_append_dword(v28, (int)v20);
          }
        }
      }
    }
    LOBYTE(v58) = 5;
    rf_pointer_array_destroy_backing_storage(v28);
  }
  for ( j = rf_receiver_get_first_dword(this + 54) - 1; j >= 0; --j )
  {
    v16 = (_DWORD **)sub_552200(this + 54, j);
    rf_solid_face_remove_destroy(this, *v16, 0);
  }
  for ( j = rf_receiver_get_first_dword(v49) - 1; j >= 0; --j )
  {
    v56 = *(_DWORD *)sub_552200(v49, j);
    rf_pointer_array_remove_first(this + 30, v56);
    rf_geomod_vertex_destroy_and_release_to_pool(v56);
  }
  for ( j = 0; ; ++j )
  {
    v17 = rf_receiver_get_first_dword(v51);
    if ( j >= v17 )
      break;
    v19 = *(_DWORD **)sub_552200(v51, j);
    if ( rf_geomod_face_corner_count(v19) <= 4 )
      rf_pointer_array_append_dword(this + 54, (int)v19);
    else
      rf_solid_subdivide_face_centroid_fan(this, (int)v19, 0, 1);
  }
  LOBYTE(v58) = 4;
  rf_pointer_array_destroy_backing_storage(v50);
  LOBYTE(v58) = 3;
  rf_pointer_array_destroy_backing_storage(v57);
  LOBYTE(v58) = 2;
  rf_pointer_array_destroy_backing_storage(v52);
  LOBYTE(v58) = 1;
  rf_pointer_array_destroy_backing_storage(v51);
  LOBYTE(v58) = 0;
  rf_pointer_array_destroy_backing_storage(v49);
  v58 = -1;
  rf_pointer_array_destroy_backing_storage(v54);
}

