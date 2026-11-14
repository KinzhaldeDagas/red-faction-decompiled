// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040E5B0 rf_ai_choose_shared_route_node_or_edge_endpoints
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(pointA,required owner ENTITY,pointB,optional dimension-source ENTITY), canonical AL0/1. Compute grounded BYTE1 only if
// owner predicates437F60 and then437FD0 both returnzero; first true short-circuits. Optional dimension-source supplies FLOAT radius+1984,height+1988, otherwise both0; owner
// dimensions are reread for its own tests. AFTER those predicate/dimension accesses, owner DWORD+1364==EXACT3 returns1 WITHOUT writing endpoint slots. Cache signed node count from
// worldSolid+768 first DWORD. Phase1 iterates nodes in array order using unchecked552200. For each call40E830(pointA,ownerRadius,ownerHeight,grounded,node); only result EXACT2 skips
// second call. Then40E830(pointB,otherRadius,otherHeight,sameOwnerGrounded,node); any result!=2 accepts first encountered node, writes ONLY owner DWORD+1692=node, returns1; +1696
// remains stale. These containment delegates mutate each examined node working position+12 and squared-distance scratch+56, even on eventual failure. Phase2 iterates same cached
// signed node count; each adjacency count atnode+40 is reread for every signed inner bound test. Unchecked adjacency accessor yields neighbor; consider edge only UNSIGNED
// nodePointer<=neighborPointer, including equality. Call40E950(pointA,ownerRadius,node,neighbor,&scratch) and require FULL EAX==EXACT0,
// then40E950(pointB,otherRadius,node,neighbor,&sameScratch) and require EAX!=2; helper result1 scratch is ignored. First accepted edge ends search. Compute squared distances from
// OWNER COMMON position+60 to node then neighbor; first ST0 spills binary64, both helpers ultimately return FLOAT32-rounded squared sums. Only ordered neighborDistance>nodeDistance
// stores1692=node,1696=neighbor; neighbor<=node OR UNORDERED reverses them. Ties therefore prefer neighbor. Returns1 after both writes. Exhaustion returns0 without clearing prior
// owner endpoint slots, preserving helper/node side effects. No nearest-node/global-best-edge selection, target resolution, path search, independent finite/null checks or rollback.
char __cdecl rf_ai_choose_shared_route_node_or_edge_endpoints(int a1, int a2, int a3, int a4)
{
  int v5; // eax
  double v6; // [esp+10h] [ebp-30h]
  int v7; // [esp+18h] [ebp-28h] BYREF
  float *v8; // [esp+1Ch] [ebp-24h]
  int j; // [esp+20h] [ebp-20h]
  float *v10; // [esp+24h] [ebp-1Ch]
  int v11; // [esp+28h] [ebp-18h]
  float v12; // [esp+2Ch] [ebp-14h]
  int i; // [esp+30h] [ebp-10h]
  float v14; // [esp+34h] [ebp-Ch]
  int first_dword; // [esp+38h] [ebp-8h]
  char v16; // [esp+3Fh] [ebp-1h]

  v16 = 0;
  if ( !rf_entity_descriptor_mode_is_12_15_13_11_or9(a2) )
    v16 = !rf_entity_movement_is_index4_or7(a2);
  v12 = 0.0;
  v14 = 0.0;
  if ( a4 )
  {
    v12 = *(float *)(a4 + 1984);
    v14 = *(float *)(a4 + 1988);
  }
  if ( *(_DWORD *)(a2 + 1364) == 3 )
    return 1;
  first_dword = rf_receiver_get_first_dword((void *)(rf_world_solid + 768));
  for ( i = 0; i < first_dword; ++i )
  {
    v11 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), i);
    if ( sub_40E830(a1, *(float *)(a2 + 1984), *(float *)(a2 + 1988), v16, (float *)v11) != 2
      && sub_40E830(a3, v12, v14, v16, (float *)v11) != 2 )
    {
      *(_DWORD *)(a2 + 1692) = v11;
      return 1;
    }
  }
  i = 0;
LABEL_14:
  if ( i >= first_dword )
    return 0;
  v10 = *(float **)sub_552200((_DWORD *)(rf_world_solid + 768), i);
  for ( j = 0; ; ++j )
  {
    v5 = rf_receiver_get_first_dword(v10 + 10);
    if ( j >= v5 )
    {
      ++i;
      goto LABEL_14;
    }
    v8 = *(float **)sub_552200((_DWORD *)v10 + 10, j);
    if ( v10 <= v8
      && !rf_route_edge_classify_point_clearance(a1, *(float *)(a2 + 1984), (int)v10, (int)v8, (float *)&v7)
      && rf_route_edge_classify_point_clearance(a3, v12, (int)v10, (int)v8, (float *)&v7) != 2 )
    {
      break;
    }
  }
  v6 = rf_vector_distance_squared((const float *)(a2 + 60), v10);
  if ( rf_vector_distance_squared((const float *)(a2 + 60), v8) <= v6 )
  {
    *(_DWORD *)(a2 + 1692) = v8;
    *(_DWORD *)(a2 + 1696) = v10;
  }
  else
  {
    *(_DWORD *)(a2 + 1692) = v10;
    *(_DWORD *)(a2 + 1696) = v8;
  }
  return 1;
}

