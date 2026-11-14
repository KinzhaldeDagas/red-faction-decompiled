// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00523C40 rf_world_decal_project_candidate_or_tree_faces
// UNREALRED VERIFIED [decal-projection-20261028]: If global candidate faces array0xA7063C nonempty projects exactly those via0x5230F0. Otherwise with primary owner DFSes primary/secondary and neighbors trees+60, only overlapping node AABBs, skips face flag0x10 then projects node face list+24. Without primary but alternate context+232 nonnull first releases attached polygons and projects all its solid faces+112. Otherwise projects context+72 faces+112 skipping flag0x10. Local DFS has no capacity check; return register incidental traversal result. Core projector supplies detailed rejection/clipping gates.
float *__cdecl rf_world_decal_project_candidate_or_tree_faces(float *a1)
{
  float *result; // eax
  int *v2; // eax
  int first_dword; // eax
  int m; // [esp+0h] [ebp-101Ch]
  int k; // [esp+4h] [ebp-1018h]
  int j; // [esp+8h] [ebp-1014h]
  int v7; // [esp+Ch] [ebp-1010h]
  int v8; // [esp+10h] [ebp-100Ch]
  _DWORD v9[1025]; // [esp+14h] [ebp-1008h]
  int i; // [esp+1018h] [ebp-4h]

  if ( rf_receiver_get_first_dword(unk_A7063C) <= 0 )
  {
    if ( *((_DWORD *)a1 + 16) )
    {
      v9[0] = *(_DWORD *)(*((_DWORD *)a1 + 16) + 60);
      v8 = 1;
      for ( i = 0; ; ++i )
      {
        first_dword = rf_receiver_get_first_dword((void *)(*((_DWORD *)a1 + 16) + 108));
        if ( i >= first_dword )
          break;
        v9[v8++] = *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(*((_DWORD *)a1 + 16) + 108), i) + 60);
      }
      result = a1;
      if ( *((_DWORD *)a1 + 17) )
      {
        v9[v8++] = *(_DWORD *)(*((_DWORD *)a1 + 17) + 60);
        for ( i = 0; ; ++i )
        {
          result = (float *)rf_receiver_get_first_dword((void *)(*((_DWORD *)a1 + 17) + 108));
          if ( i >= (int)result )
            break;
          v9[v8++] = *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(*((_DWORD *)a1 + 17) + 108), i) + 60);
        }
      }
      while ( v8 > 0 )
      {
        v7 = v9[--v8];
        result = (float *)rf_aabb_overlap_inclusive((float *)v7, (float *)(v7 + 12), a1 + 47, a1 + 50);
        if ( (_BYTE)result )
        {
          if ( *(_DWORD *)(v7 + 32) )
            v9[v8++] = *(_DWORD *)(v7 + 32);
          if ( *(_DWORD *)(v7 + 36) )
            v9[v8++] = *(_DWORD *)(v7 + 36);
          result = (float *)rf_receiver_get_first_dword((void *)(v7 + 24));
          for ( j = (int)result; j; j = (int)result )
          {
            if ( !rf_face_flags_test_bit10((_DWORD *)(j + 40)) )
              rf_world_decal_clip_and_attach_face_polygon((int)a1, j, 0);
            result = (float *)rf_face_next_spatial_node_link(j);
          }
        }
      }
    }
    else if ( *((_DWORD *)a1 + 58) )
    {
      rf_world_decal_release_attached_polygons((int)a1);
      result = (float *)rf_receiver_get_first_dword((void *)(*((_DWORD *)a1 + 58) + 112));
      for ( k = (int)result; k; k = (int)result )
      {
        rf_world_decal_clip_and_attach_face_polygon((int)a1, k, 0);
        result = (float *)rf_solid_face_next_link(k);
      }
    }
    else
    {
      result = (float *)rf_receiver_get_first_dword((void *)(*((_DWORD *)a1 + 18) + 112));
      for ( m = (int)result; m; m = (int)result )
      {
        if ( !rf_face_flags_test_bit10((_DWORD *)(m + 40)) )
          rf_world_decal_clip_and_attach_face_polygon((int)a1, m, 0);
        result = (float *)rf_solid_face_next_link(m);
      }
    }
  }
  else
  {
    for ( i = 0; ; ++i )
    {
      result = (float *)rf_receiver_get_first_dword(unk_A7063C);
      if ( i >= (int)result )
        break;
      v2 = (int *)sub_552200(unk_A7063C, i);
      rf_world_decal_clip_and_attach_face_polygon((int)a1, *v2, 0);
    }
  }
  return result;
}

