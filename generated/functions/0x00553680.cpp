// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553680 rf_vertex_collect_incident_edge_neighbors
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): For each incident face in vertex+32, locates the matching circular corner through 534D30 and appends the vertices in its next20 and previous24 corners uniquely into caller array. Does not clear output or validate the corner lookup. Return is loop bookkeeping.
int __stdcall rf_vertex_collect_incident_edge_neighbors(int a1, _DWORD *a2)
{
  int result; // eax
  _DWORD **v3; // eax
  _DWORD *corner_for_vertex_unchecked; // [esp+4h] [ebp-Ch]
  int v5; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  result = rf_receiver_get_first_dword((void *)(a1 + 32));
  v5 = result;
  for ( i = 0; i < v5; ++i )
  {
    v3 = (_DWORD **)sub_552200((_DWORD *)(a1 + 32), i);
    corner_for_vertex_unchecked = rf_face_find_corner_for_vertex_unchecked(*v3, a1);
    rf_pointer_array_append_unique(a2, *(_DWORD *)corner_for_vertex_unchecked[5]);
    rf_pointer_array_append_unique(a2, *(_DWORD *)corner_for_vertex_unchecked[6]);
    result = i + 1;
  }
  return result;
}

