// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005190A0 rf_nav_graph_find_path_with_avoid_point_5190a0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Distinct entry implementing same operations as519040:zero request output count52,clear synthetic-start adjacency count,refresh shared working/eligibility scratch,connect start with optional avoidPoint,then min-squared-cost search using that avoidPoint. Returns0 if start setup fails,otherwise searchAL. No temporary end linkage or reset of old output cost48. Actual thiscall ECX+2 stack args,RET8;no incoming x87 argument.
bool __thiscall rf_nav_graph_find_path_with_avoid_point_5190a0(void *graph, void *request, const float *avoid_point)
{
  *((_DWORD *)request + 13) = 0;
  rf_pointer_array_clear_count_keep_storage((_DWORD *)(*(_DWORD *)request + 40));
  rf_nav_graph_prepare_request_nodes(graph, (int)request);
  return rf_nav_graph_connect_start_node(graph, request, avoid_point)
      && rf_nav_graph_search_min_squared_cost(graph, request, avoid_point);
}

