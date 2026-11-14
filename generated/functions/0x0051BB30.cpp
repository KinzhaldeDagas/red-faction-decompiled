// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051BB30 rf_solid_split_existing_vertex_into_face_edges
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Cdecl solid,existing vertex; caller pop8 returns number of FACE HELPER successes, not number of corners inserted. If authored-room array144 count nonzero, iterate array156 room trees at room60. DFS using fixed1024 DWORD local stack, unchecked capacity/root NULL; prune via inclusive node bounds0/12, push child32 then36 (36 visited first), call51B9D0 for every spatial face list24. This branch has NO face metadata bit8 exclusion and no individual face AABB test. Else flat solid face-list112: require inclusive face bounds16/28 and metadata bit8 CLEAR before51B9D0. Increment per true return, no dedup across tree lists/rooms beyond vertex membership check in callee; true does not guarantee mutation. No
// spatial rebuild or bounds expansion here.
int __cdecl rf_solid_split_existing_vertex_into_face_edges(int a1, float *a2)
{
  int first_dword; // eax
  int k; // [esp+0h] [ebp-1018h]
  _DWORD *j; // [esp+4h] [ebp-1014h]
  int v6; // [esp+8h] [ebp-1010h]
  int v7; // [esp+Ch] [ebp-100Ch]
  _DWORD v8[1024]; // [esp+10h] [ebp-1008h]
  int i; // [esp+1010h] [ebp-8h]
  int v10; // [esp+1014h] [ebp-4h]

  v10 = 0;
  if ( rf_receiver_get_first_dword((void *)(a1 + 144)) )
  {
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((void *)(a1 + 156));
      if ( i >= first_dword )
        break;
      v8[0] = *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 156), i) + 60);
      v7 = 1;
      while ( v7 > 0 )
      {
        v6 = v8[--v7];
        if ( rf_aabb_contains_point_inclusive(a2, (float *)v6, (float *)(v6 + 12)) )
        {
          if ( *(_DWORD *)(v6 + 32) )
            v8[v7++] = *(_DWORD *)(v6 + 32);
          if ( *(_DWORD *)(v6 + 36) )
            v8[v7++] = *(_DWORD *)(v6 + 36);
          for ( j = (_DWORD *)rf_receiver_get_first_dword((void *)(v6 + 24));
                j;
                j = (_DWORD *)rf_face_next_spatial_node_link((int)j) )
          {
            if ( rf_geomod_split_vertex_on_first_face_edge(a1, a2, j) )
              ++v10;
          }
        }
      }
    }
  }
  else
  {
    for ( k = rf_receiver_get_first_dword((void *)(a1 + 112)); k; k = rf_solid_face_next_link(k) )
    {
      if ( rf_aabb_contains_point_inclusive(a2, (float *)(k + 16), (float *)(k + 28))
        && !rf_face_metadata_has_flag8((_DWORD *)(k + 40))
        && rf_geomod_split_vertex_on_first_face_edge(a1, a2, (_DWORD *)k) )
      {
        ++v10;
      }
    }
  }
  return v10;
}

