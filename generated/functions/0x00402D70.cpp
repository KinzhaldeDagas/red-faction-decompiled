// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402D70 rf_ai_build_alternative_route_from_global_points
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Cdecl(AI block,LOWBYTE force); explicit AL0 on rejection/failure, special success handling below. BOTH
// runtime/splitscreen bytes0 returns0 before block dereference; ANY nonzero enters. Owner crouch predicate any-nonzero rejects. Force BYTE0 consumes one rand() and uses native
// signed-remainder-by64 sequence; only remainder0 proceeds. Any nonzero force byte skips this random admission, not the remaining checks. Calls410340(owner full handle+44,0) and
// ignores its result; helper resets/rebuilds shared global candidate point count6663F8 before later tests. No-write local vector constructor; signed count<=0 returns0.
// Calls402C70(block,&preferredPoint); AL0 returns0 WITHOUT trying fallback points. Preferred route_build(owner handle,&preferredPoint) any-nonzero AL ORs AI flags DWORD+1328
// mask0x02000008 (mask0x02000000 and8 together), returns canonicalAL1. Only preferred builder AL0 triggers fallback signed loop i=0..count-1, count re-read each iteration, trying
// global points6665D8+12*i in ORIGINAL order; selected preferred point may be retried if it appears in the list. First fallback builder any-nonzero AL returns that EXACT delegated
// byte, WITHOUT ORing0x02000008. Exhaustion AL0. No explicit route reset/rollback on failed builds, own dead/target/type/authority admission or independent point-count cap; partial
// delegate/global-list effects remain even on return0.
char __cdecl rf_ai_build_alternative_route_from_global_points(int *a1, char a2)
{
  char v3; // [esp+3h] [ebp-11h]
  int i; // [esp+4h] [ebp-10h]
  float v5[3]; // [esp+8h] [ebp-Ch] BYREF

  if ( !rf_multiplayer_runtime_mode && !rf_splitscreen_runtime_active )
    return 0;
  if ( rf_entity_is_crouched_state810(*a1) || !a2 && rand() % 64 )
    return 0;
  rf_ai_collect_path_record_candidate_points(*(_DWORD *)(*a1 + 44), 0);
  rf_vector3_default_construct_noop(v5);
  if ( dword_6663F8 <= 0 )
    return 0;
  if ( !rf_ai_choose_maximum_segment_residual_point(a1, v5) )
    return 0;
  if ( rf_ai_route_build(*(_DWORD *)(*a1 + 44), (int)v5) )
  {
    a1[332] |= (unsigned int)&unk_2000008;
    return 1;
  }
  else
  {
    for ( i = 0; i < dword_6663F8; ++i )
    {
      v3 = rf_ai_route_build(*(_DWORD *)(*a1 + 44), (int)&flt_6665D8[3 * i]);
      if ( v3 )
        return v3;
    }
    return 0;
  }
}

