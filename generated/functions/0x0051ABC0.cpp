// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051ABC0 rf_solid_merge_vertex_into_survivor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): ECX solid plus survivor and removed vertex stack args. Snapshots removed incident faces, fan-triangulates each from removed corner if it contains survivor, otherwise from next corner, selectDerived0. Resnapshots resulting removed-vertex incidence; destroys faces already containing survivor, otherwise replaces removed corner pointer with survivor, adds face uniquely to survivor incidence, finalizes and regenerates UVs. Removes removed vertex from solid array120 and destroys it. Does not move survivor XYZ and ignores finalize failure; no rollback.
void __thiscall rf_solid_merge_vertex_into_survivor(int *this, int a2, int a3)
{
  int first_dword; // eax
  int *v4; // eax
  int v5; // eax
  int v6; // eax
  int *v7; // eax
  int v8; // eax
  void *v10[3]; // [esp+8h] [ebp-24h] BYREF
  void *v11; // [esp+14h] [ebp-18h]
  void *corner_for_vertex_unchecked; // [esp+18h] [ebp-14h]
  int i; // [esp+1Ch] [ebp-10h]
  int v14; // [esp+28h] [ebp-4h]

  rf_dword_array_construct_capacity(v10, 0);
  v14 = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a3 + 32));
    if ( i >= first_dword )
      break;
    v4 = (int *)sub_552200((_DWORD *)(a3 + 32), i);
    rf_pointer_array_append_dword(v10, *v4);
  }
  for ( i = 0; ; ++i )
  {
    v5 = rf_receiver_get_first_dword(v10);
    if ( i >= v5 )
      break;
    v11 = *(void **)sub_552200(v10, i);
    corner_for_vertex_unchecked = rf_face_find_corner_for_vertex_unchecked(v11, a3);
    if ( rf_geomod_face_contains_shared_vertex(v11, a2) )
      rf_solid_triangulate_face_fan_from_corner(this, v11, corner_for_vertex_unchecked, 0);
    else
      rf_solid_triangulate_face_fan_from_corner(this, v11, *((void **)corner_for_vertex_unchecked + 5), 0);
  }
  rf_pointer_array_release_storage(v10);
  for ( i = 0; ; ++i )
  {
    v6 = rf_receiver_get_first_dword((void *)(a3 + 32));
    if ( i >= v6 )
      break;
    v7 = (int *)sub_552200((_DWORD *)(a3 + 32), i);
    rf_pointer_array_append_dword(v10, *v7);
  }
  for ( i = 0; ; ++i )
  {
    v8 = rf_receiver_get_first_dword(v10);
    if ( i >= v8 )
      break;
    v11 = *(void **)sub_552200(v10, i);
    if ( rf_geomod_face_contains_shared_vertex(v11, a2) )
    {
      rf_solid_face_remove_destroy(this, v11, 0);
    }
    else
    {
      corner_for_vertex_unchecked = rf_face_find_corner_for_vertex_unchecked(v11, a3);
      *(_DWORD *)corner_for_vertex_unchecked = a2;
      rf_pointer_array_append_unique((_DWORD *)(a2 + 32), (int)v11);
      rf_geomod_face_finalize_geometry((int)v11, 0, 0);
      rf_geomod_generated_uv_project((int)v11);
    }
  }
  rf_pointer_array_remove_first(this + 30, a3);
  rf_geomod_vertex_destroy_and_release_to_pool(a3);
  v14 = -1;
  rf_pointer_array_destroy_backing_storage(v10);
}

