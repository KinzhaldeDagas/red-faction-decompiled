// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052CC40 rf_geomod_split_vertex_propagate_to_adjacent_faces
// UNREALRED VERIFIED [finite-split-20261028] Uses common incidence of BOTH edge endpoints plus exclusion of selected operand (bit 0x800000). Keep this distinct from target-face bit0x08 and endpoint all-incidence bit0x08 consistency checked by 0x51A7C0. Finite paired edge ownership is stricter than merely lying on a collinear triangle edge.
// UNREALRED VERIFIED [combat-native-query-20261104]: Restricted shared-edge vertex propagation excludes operand0 in mode6. Incidence is by endpoint vertex identity, not coordinate equality. Preserve coincident-but-distinct source vertices and shared new intersection IDs.
void __cdecl rf_geomod_split_vertex_propagate_to_adjacent_faces(int a1, float *a2, float *a3, float *a4, int a5)
{
  int first_dword; // esi
  int v6; // eax
  int *v7; // eax
  int v8; // eax
  _DWORD *v9; // [esp+8h] [ebp-24h]
  void *v10[3]; // [esp+Ch] [ebp-20h] BYREF
  int i; // [esp+18h] [ebp-14h]
  int v12; // [esp+1Ch] [ebp-10h]
  int v13; // [esp+28h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(a2 + 8);
  v12 = rf_receiver_get_first_dword(a3 + 8) + first_dword;
  rf_dword_array_construct_capacity(v10, v12);
  v13 = 0;
  for ( i = 0; ; ++i )
  {
    v6 = rf_receiver_get_first_dword(a2 + 8);
    if ( i >= v6 )
      break;
    v7 = (int *)sub_552200((_DWORD *)a2 + 8, i);
    rf_pointer_array_append_dword(v10, *v7);
  }
  for ( i = 0; ; ++i )
  {
    v8 = rf_receiver_get_first_dword(a3 + 8);
    if ( i >= v8 )
      break;
    v9 = *(_DWORD **)sub_552200((_DWORD *)a3 + 8, i);
    if ( rf_geomod_face_operand_get(v9 + 10) != a5 )
    {
      if ( rf_pointer_array_count_matches(v10, (int)v9) )
        rf_geomod_face_edge_split_insert_vertex(v9, a2, a3, a4);
    }
  }
  v13 = -1;
  rf_pointer_array_destroy_backing_storage(v10);
}

