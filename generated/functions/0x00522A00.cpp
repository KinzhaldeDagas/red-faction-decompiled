// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00522A00 rf_world_decal_gather_faces_and_align_orientation
// UNREALRED VERIFIED [decal-projection-20261028]: Logically clears scratch arrays0xA7063C/faces and0xCFACA4/normal vec3s. With primary owner, DFSes owner and neighboring owner trees at+60, optionally secondary and neighbors; overlaps node AABB with decal+188/+200, pushes children+32/+36. Node face list+24 excludes portals, liquids, face flags0x10, requires dot(face normal,decal forward row+36)>-0.5 and0x522F10 proximity. Without primary scans context+72 solid faces+112 similarly but does NOT explicitly exclude liquids in this candidate branch. Appends each selected face and unique normal through0x525DF0. Sums normals; if nonzero normalizes and negates. Flag4 uses random vector/cross product to build orientation; otherwise orientation-from-direction. Does not build clipping planes itself. DFS local storage has no explicit capacity guard; can mutate input matrix and global scratch state.
float *__cdecl rf_world_decal_gather_faces_and_align_orientation(float *a1)
{
  int first_dword; // eax
  float *v2; // eax
  float *result; // eax
  float *v4; // eax
  float v5; // [esp+0h] [ebp-106Ch] BYREF
  int v6; // [esp+4h] [ebp-1068h]
  int v7; // [esp+8h] [ebp-1064h]
  float copy_result[3]; // [esp+Ch] [ebp-1060h] BYREF
  float v9[5]; // [esp+18h] [ebp-1054h] BYREF
  float v10[3]; // [esp+2Ch] [ebp-1040h] BYREF
  float v11[3]; // [esp+38h] [ebp-1034h] BYREF
  float *k; // [esp+44h] [ebp-1028h]
  float *j; // [esp+48h] [ebp-1024h]
  float v14; // [esp+4Ch] [ebp-1020h]
  int i; // [esp+50h] [ebp-101Ch]
  int v16; // [esp+54h] [ebp-1018h]
  float destination[1028]; // [esp+58h] [ebp-1014h] BYREF
  int m; // [esp+1068h] [ebp-4h]

  rf_pointer_array_clear_count_keep_storage(unk_A7063C);
  rf_pointer_array_clear_count_keep_storage(dword_CFACA4);
  v16 = 0;
  if ( *((_DWORD *)a1 + 16) )
  {
    destination[v16++ + 3] = *(float *)(*((_DWORD *)a1 + 16) + 60);
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(*((_DWORD *)a1 + 16) + 108)); ++i )
      destination[v16++ + 3] = *(float *)(*(_DWORD *)sub_552200((_DWORD *)(*((_DWORD *)a1 + 16) + 108), i) + 60);
    if ( *((_DWORD *)a1 + 17) )
    {
      destination[v16++ + 3] = *(float *)(*((_DWORD *)a1 + 17) + 60);
      for ( i = 0; i < rf_receiver_get_first_dword((void *)(*((_DWORD *)a1 + 17) + 108)); ++i )
        destination[v16++ + 3] = *(float *)(*(_DWORD *)sub_552200((_DWORD *)(*((_DWORD *)a1 + 17) + 108), i) + 60);
    }
    while ( v16 > 0 )
    {
      v14 = destination[--v16 + 3];
      if ( rf_aabb_overlap_inclusive((float *)LODWORD(v14), (float *)(LODWORD(v14) + 12), a1 + 47, a1 + 50) )
      {
        if ( *(_DWORD *)(LODWORD(v14) + 32) )
          destination[v16++ + 3] = *(float *)(LODWORD(v14) + 32);
        if ( *(_DWORD *)(LODWORD(v14) + 36) )
          destination[v16++ + 3] = *(float *)(LODWORD(v14) + 36);
        for ( j = (float *)rf_receiver_get_first_dword((void *)(LODWORD(v14) + 24));
              j;
              j = (float *)rf_face_next_spatial_node_link((int)j) )
        {
          if ( !rf_face_is_portal((__int16 *)j + 20)
            && !rf_face_is_liquid((_DWORD *)j + 10)
            && !rf_face_flags_test_bit10((_DWORD *)j + 10)
            && rf_vector_dot(j, a1 + 9) > -0.5
            && rf_world_decal_face_near_center((int)j, a1) )
          {
            rf_vector3_copy_return_destination(&v5, j);
            rf_vector_array_find_or_append_vec3(dword_CFACA4, v5, v6, v7);
            rf_pointer_array_append_dword(unk_A7063C, (int)j);
          }
        }
      }
    }
  }
  else
  {
    for ( k = (float *)rf_receiver_get_first_dword((void *)(*((_DWORD *)a1 + 18) + 112));
          k;
          k = (float *)rf_solid_face_next_link((int)k) )
    {
      if ( !rf_face_is_portal((__int16 *)k + 20)
        && !rf_face_flags_test_bit10((_DWORD *)k + 10)
        && rf_vector_dot(k, a1 + 9) > -0.5
        && rf_world_decal_face_near_center((int)k, a1) )
      {
        rf_vector3_copy_return_destination(&v5, k);
        rf_vector_array_find_or_append_vec3(dword_CFACA4, v5, v6, v7);
        rf_pointer_array_append_dword(unk_A7063C, (int)k);
      }
    }
  }
  rf_vector3_set_components_return_destination(destination, 0.0, 0.0, 0.0);
  for ( m = 0; ; ++m )
  {
    first_dword = rf_receiver_get_first_dword(dword_CFACA4);
    if ( m >= first_dword )
      break;
    v2 = (float *)rf_vector_array12_element_address_unchecked(dword_CFACA4, m);
    rf_vector_accumulate(destination, v2);
  }
  result = (float *)rf_vector3_is_exact_zero(destination);
  if ( !result )
  {
    rf_vector_normalize_reciprocal_sqrt(destination);
    v4 = rf_vector_negate(destination, v9);
    rf_vector_copy(destination, copy_result, v4);
    if ( ((_DWORD)a1[20] & 4) != 0 )
    {
      rf_vector3_default_construct_noop(v10);
      rf_random_unit_vector_from_z_and_azimuth(v10);
      rf_vector_cross(v10, v11, destination);
      rf_vector_normalize_reciprocal_sqrt(v11);
      return (float *)rf_orientation_from_forward_and_right_hint(a1 + 3, destination, v11);
    }
    else
    {
      return rf_orientation_matrix_from_direction(a1 + 3, (int)destination);
    }
  }
  return result;
}

