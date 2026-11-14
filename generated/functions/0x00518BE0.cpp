// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518BE0 rf_nav_graph_find_path_to_request_target
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall graph,request,RET4;AL0/1. Sets output count52=0,clears synthetic start neighbor count40(keeps backing),calls518210 to refresh shared eligibility/working positions,then518640 with avoidNULL. Failed start setup returns0 immediately. If request BYTE34==1,connects temporary end via5186F0;on success searches518770 with avoidNULL,then removes LAST graph entry and LAST entry from each nonNULL endpoint hint16/20 adjacency even when search failed. No saved membership lookup/cycle/underflow guard;assumes appended entries are still last. Successful search copies endNode.working12 to endNode ORIGINAL position0 via vector assignment;failed search clears output count again. Returns
// search result. If BYTE34!=1,clears endNode.ineligible53 and start hint4.ineligible53 when present,then searches without temporary attachment/copy. Does not reset shared source-node state afterward or reset request48 on setup failure. Actual code takes no ST0 input;typed false hidden x87 argument removed.
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Directed graph wrapper prepares shared nodes, connects syntheticStart, optionally appends syntheticEnd via5186F0 under requestbyte34==1, invokes518770 and removes LAST graph entry and trailing endpoint-hint adjacency entries in native order even on failed search. Success copies End.working to End.original; failure clearscount. Keep scratch/lifetime ownership across host callbacks and do not erase newer reentrant publication.
bool __thiscall rf_nav_graph_find_path_to_request_target(void *graph, void *request)
{
  int first_dword; // eax
  int v4; // [esp-4h] [ebp-18h]
  int v5; // [esp-4h] [ebp-18h]
  float copy_result[3]; // [esp+4h] [ebp-10h] BYREF
  bool v8; // [esp+13h] [ebp-1h]

  *((_DWORD *)request + 13) = 0;
  rf_pointer_array_clear_count_keep_storage((_DWORD *)(*(_DWORD *)request + 40));
  rf_nav_graph_prepare_request_nodes(graph, (int)request);
  if ( !rf_nav_graph_connect_start_node(graph, request, nullptr) )
    return 0;
  if ( *((_BYTE *)request + 34) == 1 )
  {
    v8 = 0;
    if ( rf_nav_graph_connect_temporary_end_node(graph, (int *)request) == 1 )
    {
      v8 = rf_nav_graph_search_min_squared_cost(graph, request, nullptr);
      first_dword = rf_receiver_get_first_dword(graph);
      rf_pointer_array_erase_index_unchecked(graph, first_dword - 1);
      if ( *((_DWORD *)request + 4) )
      {
        v4 = rf_receiver_get_first_dword((void *)(*((_DWORD *)request + 4) + 40)) - 1;
        rf_pointer_array_erase_index_unchecked((_DWORD *)(*((_DWORD *)request + 4) + 40), v4);
      }
      if ( *((_DWORD *)request + 5) )
      {
        v5 = rf_receiver_get_first_dword((void *)(*((_DWORD *)request + 5) + 40)) - 1;
        rf_pointer_array_erase_index_unchecked((_DWORD *)(*((_DWORD *)request + 5) + 40), v5);
      }
    }
    if ( v8 )
      rf_vector_copy(*((float **)request + 3), copy_result, (const float *)(*((_DWORD *)request + 3) + 12));
    else
      *((_DWORD *)request + 13) = 0;
    return v8;
  }
  else
  {
    *(_BYTE *)(*((_DWORD *)request + 3) + 53) = 0;
    if ( *((_DWORD *)request + 1) )
      *(_BYTE *)(*((_DWORD *)request + 1) + 53) = 0;
    return rf_nav_graph_search_min_squared_cost(graph, request, nullptr);
  }
}

