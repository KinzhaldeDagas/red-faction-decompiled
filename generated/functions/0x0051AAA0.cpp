// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051AAA0 rf_geomod_split_vertex_propagate_to_incident_faces
// UNREALRED CORRECTION [finite-split-20261028] Prior union wording is incorrect: copies endpoint A incident-face pointers into a temporary array, then iterates endpoint B and uses pointer membership COUNT helper 0x521210 at 0x51AB74. Only faces incident to BOTH endpoints reach insertion 0x51AB90. Exact endpoint-pointer edge adjacency is then required by 0x51A7C0. This is common incidence, not union or arbitrary collinearity.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Three stack vertex pointers A,B,split; RET12; saved ECX merely forwarded to an insertion routine which does not use it. Allocate temporary DWORD array capacity=count(A.incidence32)+count(B.incidence32), copy only A incidence pointers, then iterate B incidence and test pointer membership count against that snapshot. ONLY common incident faces reach51A7C0, which further requires exact adjacent endpoint pointers and matching bit8 category. This is intersection, not union. B duplicates may revisit but face-already-contains-split guard suppresses another insertion. Releases temporary backing with exception cleanup. No geometric test, no iteration over global solid faces, no finalization or return value.
void __stdcall rf_geomod_split_vertex_propagate_to_incident_faces(float *a1, float *a2, float *a3)
{
  int first_dword; // esi
  int v4; // eax
  int *v5; // eax
  int v6; // eax
  _DWORD *v7; // [esp+Ch] [ebp-24h]
  void *v8[3]; // [esp+10h] [ebp-20h] BYREF
  int i; // [esp+1Ch] [ebp-14h]
  int v10; // [esp+20h] [ebp-10h]
  int v11; // [esp+2Ch] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(a1 + 8);
  v10 = rf_receiver_get_first_dword(a2 + 8) + first_dword;
  rf_dword_array_construct_capacity(v8, v10);
  v11 = 0;
  for ( i = 0; ; ++i )
  {
    v4 = rf_receiver_get_first_dword(a1 + 8);
    if ( i >= v4 )
      break;
    v5 = (int *)sub_552200((_DWORD *)a1 + 8, i);
    rf_pointer_array_append_dword(v8, *v5);
  }
  for ( i = 0; ; ++i )
  {
    v6 = rf_receiver_get_first_dword(a2 + 8);
    if ( i >= v6 )
      break;
    v7 = *(_DWORD **)sub_552200((_DWORD *)a2 + 8, i);
    if ( rf_pointer_array_count_matches(v8, (int)v7) )
      rf_geomod_face_edge_split_insert_vertex(v7, a1, a2, a3);
  }
  v11 = -1;
  rf_pointer_array_destroy_backing_storage(v8);
}

