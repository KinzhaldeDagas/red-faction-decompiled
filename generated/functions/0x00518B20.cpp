// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518B20 rf_nav_route_trace_parents_cost_sum
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Cdecl request,node;returns float-rounded x87 value through stored double ABI. Node==request.start0 appends start through518BA0 and returns0. Else if parent60 nonNULL,recurses to parent,stores returned value as FLOAT,appends current node,returns float(parentResult+CURRENT CUMULATIVE cost56). Therefore sums all prefix costs,not only edge lengths or final g-cost. Recursion visits root-to-goal when appending;output cap4 retains FIRST4 nodes,while cost accumulation continues beyond cap. Missing parent returnsFLT_MAX without appending that node;callers higher in chain can still append/add. No cycle/depth guard or rollback.
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Recursively visit parent to Start, append in root→goal order. FLOAT-round each returned cumulative-prefix-cost addition; result is SUM of cumulative node costs, not just final shortest-path g-cost.518BA0 keeps FIRST FOUR path nodes while cost traversal continues beyond cap. Missing parent yieldsFLT_MAX; native cycles have no depth guard (host unsupported-domain guard must be explicit).
double __cdecl rf_nav_route_trace_parents_cost_sum(int *a1, int a2)
{
  float v4; // [esp+4h] [ebp-4h]

  if ( a2 == *a1 )
  {
    rf_nav_route_append_node_first_four((int)a1, *a1);
    return 0.0;
  }
  else if ( *(_DWORD *)(a2 + 60) )
  {
    v4 = rf_nav_route_trace_parents_cost_sum(a1, *(_DWORD *)(a2 + 60));
    rf_nav_route_append_node_first_four((int)a1, a2);
    return (float)(v4 + *(float *)(a2 + 56));
  }
  else
  {
    return 3.4028235e38;
  }
}

