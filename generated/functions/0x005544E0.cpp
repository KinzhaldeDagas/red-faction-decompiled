// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005544E0 rf_face_array_has_other_directed_edge
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Scans caller face pointer array except excluded index. Returns byte1 if another face contains both vertex pointers and the corner for second vertex has next20 vertex equal to first; otherwise0. This is a directed reverse-edge test, with no geometric-position comparison.
char __stdcall rf_face_array_has_other_directed_edge(int a1, int a2, _DWORD *a3, int a4)
{
  _DWORD *v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(a3); ++i )
  {
    v5 = *(_DWORD **)sub_552200(a3, i);
    if ( a4 != i
      && rf_geomod_face_contains_shared_vertex(v5, a1)
      && rf_geomod_face_contains_shared_vertex(v5, a2)
      && *(_DWORD *)rf_face_find_corner_for_vertex_unchecked(v5, a2)[5] == a1 )
    {
      return 1;
    }
  }
  return 0;
}

