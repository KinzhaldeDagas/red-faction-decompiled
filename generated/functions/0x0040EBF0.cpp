// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040EBF0 rf_ai_build_avoid_route_with_default_parameter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(full owner HANDLE,avoid-point pointer), explicit AL0/1. ENTITY resolution failure returns0 with no own route/request
// writes. Resolved owner: reset embedded route+1416 via40ECC0, publish shared request40DE20(owner), ignore both returns, then query distinct5190A0 with ECX=worldSolid+768 and
// stack(&request6663FC,avoidPoint). Unlike40DF30 does NOT resolve owner target or replace request FLOAT+44: initializer0 remains. Query any nonzero AL admits; zero returns0 retaining
// reset/request/graph side effects. Admitted query copies request result count+52(666430) to route DWORD+0 before SIGNED count>=2 gate. Count<2 returns0 without second reset. Success
// writes route DWORD+20=0,+24=1; arms route+308(owner+1724) deadline clock-relative0ms; copies owner retained point+2004 into route vector+332(owner+1748), returnsAL1. Query5190A0
// performs same operations as519040 but is a distinct entry. No direct world/avoid-point/null/capacity checks, failure rollback, own output-cost clear or destination owner+1772
// mutation. Upper EAX incidental.
char __cdecl rf_ai_build_avoid_route_with_default_parameter(int a1, float *avoid_point)
{
  float copy_result[3]; // [esp+0h] [ebp-14h] BYREF
  float *v4; // [esp+Ch] [ebp-8h]
  float *v5; // [esp+10h] [ebp-4h]

  v5 = (float *)rf_entity_resolve_handle(a1);
  if ( !v5 )
    return 0;
  rf_ai_route_reset((int)(v5 + 354));
  rf_ai_publish_owner_route_search_request(v5);
  if ( !rf_nav_graph_find_path_with_avoid_point_5190a0((void *)(rf_world_solid + 768), &dword_6663FC, avoid_point) )
    return 0;
  v4 = v5 + 354;
  *((_DWORD *)v5 + 354) = unk_666430;
  if ( *(int *)v4 < 2 )
    return 0;
  v4[5] = 0.0;
  *((_DWORD *)v4 + 6) = 1;
  rf_replicator_arm_milliseconds((int *)v4 + 77, 0);
  rf_vector_copy(v4 + 83, copy_result, v5 + 501);
  return 1;
}

