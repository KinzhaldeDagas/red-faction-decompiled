// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00519040 rf_nav_graph_find_path_with_avoid_point_519040
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall graph,request,avoidPoint,RET8;returnsAL0/1. Sets output count52=0,clears synthetic start neighbor count40,refreshes node eligibility/working positions518210,connects start518640 using avoidPoint,then searches518770 with same avoidPoint if setup succeeds;else0. No temporary end attachment/copy,post-query state reset or request48 reset on failure. Same operations as distinct5190A0. Corrected pointer args and false inferred ST0 input;ordinary ECX/2-stack-DWORD ABI.
bool __thiscall rf_nav_graph_find_path_with_avoid_point_519040(void *graph, void *request, const float *avoid_point)
{
  *((_DWORD *)request + 13) = 0;
  rf_pointer_array_clear_count_keep_storage((_DWORD *)(*(_DWORD *)request + 40));
  rf_nav_graph_prepare_request_nodes(graph, (int)request);
  return rf_nav_graph_connect_start_node(graph, request, avoid_point)
      && rf_nav_graph_search_min_squared_cost(graph, request, avoid_point);
}

