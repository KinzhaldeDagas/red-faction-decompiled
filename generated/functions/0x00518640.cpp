// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518640 rf_nav_graph_connect_start_node
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Actual THISCALL ECX graph,request pointer,optional avoidPoint pointer,RET8. No incoming x87 argument. Clears no lists itself. If request hints4 AND8 nonNULL,appends both to synthetic start node(request0) neighbor array40. If only hint4 exists,appends it;hint8 alone is ignored and nearest-start search is used. With no hint4,calls518320(graph,request,startNode.working12,avoidPoint);NULL returnsfalse,else appends found node. ReturnsAL1 on success. Hints bypass nearest distance/dimension/clearance checks in this function;not deduplicated or reciprocally connected. Corrected old stdcall omitted ECX;false ST0 input was type inference.
bool __thiscall rf_nav_graph_connect_start_node(void *graph, void *request, const float *avoid_point)
{
  void *nearest_start_node; // [esp+4h] [ebp-4h]

  if ( *((_DWORD *)request + 1) && *((_DWORD *)request + 2) )
  {
    rf_pointer_array_append_dword((_DWORD *)(*(_DWORD *)request + 40), *((_DWORD *)request + 1));
    rf_pointer_array_append_dword((_DWORD *)(*(_DWORD *)request + 40), *((_DWORD *)request + 2));
  }
  else if ( *((_DWORD *)request + 1) )
  {
    rf_pointer_array_append_dword((_DWORD *)(*(_DWORD *)request + 40), *((_DWORD *)request + 1));
  }
  else
  {
    nearest_start_node = rf_nav_graph_find_nearest_start_node(
                           graph,
                           request,
                           (const float *)(*(_DWORD *)request + 12),
                           avoid_point);
    if ( !nearest_start_node )
      return 0;
    rf_pointer_array_append_dword((_DWORD *)(*(_DWORD *)request + 40), (int)nearest_start_node);
  }
  return 1;
}

