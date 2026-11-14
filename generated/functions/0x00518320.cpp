// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518320 rf_nav_graph_find_nearest_start_node
// UNREALRED VERIFIED [combat-panic-20261104]: Startnode search: exclude request-ineligible nodes and float-rounded squared distance>2500RF²; choose strictnearest remaining so equal-distance ties preserve poolorder. Optional518510 is bypassed by panic literal0; mandatory518590 must report clearance, rejected candidate marked then nextnearest tried. Endpoint hints in518640 bypass this search; do not discard hints or substitute AABB/UE nearestnav heuristics.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Actual THISCALL ECX graph,request,startPoint3f,optional avoidPoint3f,RET12;returns NODE POINTER in EAX orNULL,no incoming ST0 argument. If graph count<1 returnsNULL. Resets each node closed52=0;node ineligible53 EXACTLY1 is marked52=1 and excluded;others get float squared distance56 from startPoint,excluded only if ordered>2500. Repeatedly scans pool for first eligible strict-nearest distance(ties preserve pool order). Optional avoidPoint tests518510 using request44 threshold. Then mandatory518590(world gate36,node,startPoint,radius24,UNUSED height28) must return1 to accept. Rejection marks52=1 and tries next;mandatory-clearance rejection exits when candidate count<1. No
// finite/index/pointer validation;NaN distances are not rejected by ordered2500 gate. Hints in518640 bypass this search. Corrected false custom x87/void inference and three stack argument pointers;existing combat summary retained.
void *__thiscall rf_nav_graph_find_nearest_start_node(
        void *graph,
        void *request,
        const float *start_point,
        const float *avoid_point)
{
  int v6; // [esp+Ch] [ebp-18h]
  float *node; // [esp+10h] [ebp-14h]
  float v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+18h] [ebp-Ch]
  int first_dword; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]
  int j; // [esp+20h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(graph);
  if ( first_dword < 1 )
    return nullptr;
  for ( i = 0; i < rf_receiver_get_first_dword(graph); ++i )
  {
    v9 = *(_DWORD *)sub_552200(graph, i);
    *(_BYTE *)(v9 + 52) = 0;
    if ( *(_BYTE *)(v9 + 53) == 1 )
    {
      *(_BYTE *)(v9 + 52) = 1;
      --first_dword;
    }
    else
    {
      *(float *)(v9 + 56) = rf_vector_distance_squared(start_point, (const float *)(v9 + 12));
      if ( *(float *)(v9 + 56) > 2500.0 )
      {
        *(_BYTE *)(v9 + 52) = 1;
        --first_dword;
      }
    }
  }
  do
  {
    while ( 1 )
    {
      node = nullptr;
      v8 = 0.0;
      for ( j = 0; j < rf_receiver_get_first_dword(graph); ++j )
      {
        v6 = *(_DWORD *)sub_552200(graph, j);
        if ( !*(_BYTE *)(v6 + 52) && (!node || v8 > (double)*(float *)(v6 + 56)) )
        {
          v8 = *(float *)(v6 + 56);
          node = (float *)v6;
        }
      }
      if ( !node )
        return nullptr;
      if ( !avoid_point
        || rf_nav_segment_avoids_point_except_start(avoid_point, start_point, node + 3, *((float *)request + 11)) )
      {
        break;
      }
      *((_BYTE *)node + 52) = 1;
      --first_dword;
    }
    if ( rf_nav_node_to_point_clearance_sweep(
           *((void **)request + 9),
           node,
           start_point,
           *((float *)request + 6),
           *((float *)request + 7)) )
    {
      return node;
    }
    *((_BYTE *)node + 52) = 1;
    --first_dword;
  }
  while ( first_dword >= 1 );
  return nullptr;
}

