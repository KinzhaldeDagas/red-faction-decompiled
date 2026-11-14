// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553770 rf_solid_label_selected_vertex_component_recursive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Writes component label to vertex+28, collects unique immediate edge neighbors, and recursively labels only neighbors whose label equals -1 AND which occur in solid selected-vertex array204. No recursion-depth guard; label value -1 would defeat visited marking.
void __thiscall rf_solid_label_selected_vertex_component_recursive(_DWORD *this, int a2, int a3)
{
  int *v3; // eax
  int *v4; // eax
  void *v6[3]; // [esp+8h] [ebp-20h] BYREF
  int first_dword; // [esp+14h] [ebp-14h]
  int i; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  *(_DWORD *)(a2 + 28) = a3;
  rf_dword_array_construct_capacity(v6, 0);
  v9 = 0;
  rf_vertex_collect_incident_edge_neighbors(a2, v6);
  first_dword = rf_receiver_get_first_dword(v6);
  for ( i = 0; i < first_dword; ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(v6, i) + 28) == -1 )
    {
      v3 = (int *)sub_552200(v6, i);
      if ( rf_pointer_array_find_index(this + 51, *v3) >= 0 )
      {
        v4 = (int *)sub_552200(v6, i);
        rf_solid_label_selected_vertex_component_recursive(this, *v4, a3);
      }
    }
  }
  v9 = -1;
  rf_pointer_array_destroy_backing_storage(v6);
}

