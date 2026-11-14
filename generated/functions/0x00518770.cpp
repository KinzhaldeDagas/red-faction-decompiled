// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518770 rf_nav_graph_search_min_squared_cost
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall graph,request,optional avoidPoint,RET8;returnsAL0/1. For each graph node whose ineligible BYTE53==0,sets cost56=FLT_MAX,parent60=NULL,closed52=0,queued54=0;ineligible nodes retain prior scratch. Synthetic start(request0) cost0,closed52=1,appended to local open array. Each iteration scans open array for STRICT minimum cost,keeps first current-array tie,removes selected entry. Does NOT mark popped nodes closed or clear queued flag. With avoidPoint,success is first popped node!=start for which518590(world gate36,node,avoidPoint,radius0,height request28) reports FALSE(occluded);with world gateNULL helper always true,so this acceptance cannot trigger. Without
// avoidPoint,success when positive request stop-radius40 STRICTLY exceeds Euclidean distance(node.working12,target original position at request12),AND clearance518590 with radius0.1,height request28 succeeds;otherwise exact target-node pointer equality also succeeds without that final clearance test. Expands neighbor array40. With avoidPoint,first tests518510(avoidPoint,current working,neighbor working,request44 squaredThreshold). Requires neighbor ineligible53==0 and closed52==0. First unqueued neighbor sets54=1 and appends to open;every eligible edge then computes float candidate=currentCost+squaredEuclideanDistance(working positions),updates parent60/cost56 only on strict improvement. Edge cost is squared length,no heuristic or sqrt;queued nodes are never reinserted after pop. On success!=start,request48 receives518B20 recursive parent-chain result:SUM OF CUMULATIVE costs,not just goal
// cost/path length. Success==start leaves48 unchanged. Destroys local open backing on all exits. No graph-size/parent-cycle/finite/negative-context validation;shared node scratch remains modified after query.
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Strict current-open minimum squared cumulative cost; retain original open insertion tie behavior, queued54 and parent60. Popped nodes are NOT automatically closed52 or de-queued54; Start is explicitlyclosed. Parent path output uses518B20/518BA0 first-four cap, not an arbitrary unlimited AStar path.
bool __thiscall rf_nav_graph_search_min_squared_cost(void *graph, void *request, const float *avoid_point)
{
  int i; // eax
  int v4; // eax
  int first_dword; // eax
  int v6; // eax
  int v7; // eax
  float v10; // [esp+14h] [ebp-3Ch]
  int v11; // [esp+18h] [ebp-38h]
  float *node; // [esp+20h] [ebp-30h]
  int v13; // [esp+24h] [ebp-2Ch]
  float v14; // [esp+28h] [ebp-28h]
  int v15; // [esp+2Ch] [ebp-24h]
  void *v16[3]; // [esp+30h] [ebp-20h] BYREF
  float *v17; // [esp+3Ch] [ebp-14h]
  int j; // [esp+40h] [ebp-10h]
  int v19; // [esp+4Ch] [ebp-4h]

  j = 0;
  for ( i = rf_receiver_get_first_dword(graph); j < i; i = rf_receiver_get_first_dword(graph) )
  {
    v4 = sub_552200(graph, j);
    v15 = *(_DWORD *)v4;
    if ( !*(_BYTE *)(*(_DWORD *)v4 + 53) )
    {
      *(float *)(v15 + 56) = 3.4028235e38;
      *(_DWORD *)(v15 + 60) = 0;
      *(_BYTE *)(v15 + 52) = 0;
      *(_BYTE *)(v15 + 54) = 0;
    }
    ++j;
  }
  *(float *)(*(_DWORD *)request + 56) = 0.0;
  *(_BYTE *)(*(_DWORD *)request + 52) = 1;
  rf_dword_array_construct_capacity(v16, 0);
  v19 = 0;
  rf_pointer_array_append_dword(v16, *(_DWORD *)request);
  v17 = nullptr;
  while ( rf_receiver_get_first_dword(v16) > 0 )
  {
    v14 = *(float *)(*(_DWORD *)sub_552200(v16, 0) + 56);
    node = *(float **)sub_552200(v16, 0);
    v13 = 0;
    for ( j = 1; ; ++j )
    {
      first_dword = rf_receiver_get_first_dword(v16);
      if ( j >= first_dword )
        break;
      v6 = sub_552200(v16, j);
      if ( v14 > (double)*(float *)(*(_DWORD *)v6 + 56) )
      {
        node = *(float **)v6;
        v14 = *(float *)(*(_DWORD *)v6 + 56);
        v13 = j;
      }
    }
    rf_pointer_array_erase_index_unchecked(v16, v13);
    if ( avoid_point )
    {
      if ( node != *(float **)request
        && !rf_nav_node_to_point_clearance_sweep(
              *((void **)request + 9),
              node,
              avoid_point,
              0.0,
              *((float *)request + 7)) )
      {
        v17 = node;
        break;
      }
    }
    else
    {
      if ( *((float *)request + 10) > 0.0
        && *((float *)request + 10) > rf_vector_distance(node + 3, (const float *)*((_DWORD *)request + 3))
        && rf_nav_node_to_point_clearance_sweep(
             *((void **)request + 9),
             node,
             *((const float **)request + 3),
             0.1,
             *((float *)request + 7)) )
      {
        v17 = node;
        break;
      }
      if ( *((float **)request + 3) == node )
      {
        v17 = node;
        break;
      }
    }
    for ( j = 0; ; ++j )
    {
      v7 = rf_receiver_get_first_dword(node + 10);
      if ( j >= v7 )
        break;
      v11 = *(_DWORD *)sub_552200((_DWORD *)node + 10, j);
      if ( (!avoid_point
         || rf_nav_segment_avoids_point_except_start(
              avoid_point,
              node + 3,
              (const float *)(v11 + 12),
              *((float *)request + 11)))
        && !*(_BYTE *)(v11 + 53)
        && !*(_BYTE *)(v11 + 52) )
      {
        if ( !*(_BYTE *)(v11 + 54) )
        {
          *(_BYTE *)(v11 + 54) = 1;
          rf_pointer_array_append_dword(v16, v11);
        }
        v10 = rf_vector_distance_squared((const float *)(v11 + 12), node + 3) + node[14];
        if ( *(float *)(v11 + 56) > (double)v10 )
        {
          *(_DWORD *)(v11 + 60) = node;
          *(float *)(v11 + 56) = v10;
        }
      }
    }
  }
  if ( v17 )
  {
    if ( v17 != *(float **)request )
      *((float *)request + 12) = rf_nav_route_trace_parents_cost_sum(request, (int)v17);
    v19 = -1;
    rf_pointer_array_destroy_backing_storage(v16);
    return 1;
  }
  else
  {
    v19 = -1;
    rf_pointer_array_destroy_backing_storage(v16);
    return 0;
  }
}

