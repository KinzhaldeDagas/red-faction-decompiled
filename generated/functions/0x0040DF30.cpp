// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040DF30 rf_ai_build_avoid_route_with_target_adjustment
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(full owner HANDLE,avoid-point pointer), explicit AL0/1. Resolve ENTITY; missing returns0 with no own route/request writes.
// For resolved owner, reset embedded route+1416 via40ECC0, then publish shared request40DE20(owner), ignoring both returns. Resolve owner raw target HANDLE+1376 as ENTITY; any
// resolved target sets request FLOAT+44 at666428 to4.0, otherwise initializer0 remains. Query519040 with ECX=worldSolid+768 and two stack pointers(&request6663FC,avoidPoint); any
// nonzero AL admits, zero returns0 without rollback. Query itself clears result count and mutates shared graph scratch; no own world/avoid-pointer guard. On admitted query copy
// request DWORD+52(666430) into route DWORD+0 BEFORE SIGNED count>=2 gate. Count<2 returns0 retaining copied count and prior side effects. Count>=2 writes route DWORD+20=0,+24=1;
// arms embedded deadline route+308(owner+1724) at clock-relative0 milliseconds; copies owner retained point+2004 into route vector+332(owner+1748), ignoring assignment result;
// returnsAL1. Failure does not repeat reset, restore shared request/graph, restore previous route or clear destination owner+1772. Upper EAX incidental.
char __cdecl rf_ai_build_avoid_route_with_target_adjustment(int a1, float *avoid_point)
{
  float copy_result[3]; // [esp+0h] [ebp-18h] BYREF
  float *v4; // [esp+Ch] [ebp-Ch]
  float *v5; // [esp+10h] [ebp-8h]

  v5 = (float *)rf_entity_resolve_handle(a1);
  if ( !v5 )
    return 0;
  rf_ai_route_reset((int)(v5 + 354));
  rf_ai_publish_owner_route_search_request(v5);
  if ( rf_entity_resolve_handle(*((_DWORD *)v5 + 344)) )
    unk_666428 = 4.0;
  if ( !rf_nav_graph_find_path_with_avoid_point_519040((void *)(rf_world_solid + 768), &dword_6663FC, avoid_point) )
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

