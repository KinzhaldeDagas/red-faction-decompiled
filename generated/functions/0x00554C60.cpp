// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00554C60 rf_face_collect_reverse_edge_neighbors
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): For each source corner vertex, scans its incident faces excluding source. Locates that vertex in candidate and checks that candidate NEXT corner vertex has source in its incident-face list. Appends matching candidate faces to output WITHOUT clearing or deduplication; repeated/shared-edge matches may repeat. Returns incidental source/ring pointer.
int *__stdcall rf_face_collect_reverse_edge_neighbors(_DWORD *a1, int *a2)
{
  int *result; // eax
  _DWORD *corner_for_vertex_unchecked; // eax
  int *v4; // [esp+0h] [ebp-1Ch]
  int *v5; // [esp+Ch] [ebp-10h]
  int j; // [esp+10h] [ebp-Ch]
  int v7; // [esp+14h] [ebp-8h]
  int *i; // [esp+18h] [ebp-4h]

  result = a2;
  for ( i = (int *)a2[16]; i; i = v4 )
  {
    v7 = *i;
    for ( j = 0; j < rf_receiver_get_first_dword((void *)(v7 + 32)); ++j )
    {
      v5 = *(int **)sub_552200((_DWORD *)(v7 + 32), j);
      if ( v5 != a2 )
      {
        corner_for_vertex_unchecked = rf_face_find_corner_for_vertex_unchecked(v5, v7);
        if ( rf_pointer_array_find_index((_DWORD *)(*(_DWORD *)corner_for_vertex_unchecked[5] + 32), (int)a2) > -1 )
          rf_pointer_array_append_dword(a1, (int)v5);
      }
    }
    result = a2;
    if ( i[5] == a2[16] )
    {
      v4 = nullptr;
    }
    else
    {
      result = (int *)i[5];
      v4 = result;
    }
  }
  return result;
}

