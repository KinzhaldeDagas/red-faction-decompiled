// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005186F0 rf_nav_graph_connect_temporary_end_node
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall graph,request,RET4. If endpoint hints16 AND20 nonNULL,appends end node(request12) to BOTH hint neighbor arrays40. With hint16 only,appends there;hint20 alone returnsfalse with no append. Then appends end node to graph array and returns1. Does not validate/deduplicate hints,end pointer or memberships. Caller518BE0 later removes LAST entries,assuming these exact appends;not a permanent graph edit.
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Temporary target attachment preserves endpoint hint order, including identical/non-null hints and repeated appended entries. Caller cleanup removes native trailing entries; a safe host mapping may use synthetic identities but must not conflate append-unique or erase-all with exact append/remove order.
char __thiscall rf_nav_graph_connect_temporary_end_node(_DWORD *this, int *a2)
{
  if ( a2[4] && a2[5] )
  {
    rf_pointer_array_append_dword((_DWORD *)(a2[4] + 40), a2[3]);
    rf_pointer_array_append_dword((_DWORD *)(a2[5] + 40), a2[3]);
  }
  else
  {
    if ( !a2[4] )
      return 0;
    rf_pointer_array_append_dword((_DWORD *)(a2[4] + 40), a2[3]);
  }
  rf_pointer_array_append_dword(this, a2[3]);
  return 1;
}

