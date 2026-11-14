// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435640 rf_entity_select_movement13_after_uncrouch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity), heterogeneous register result. Attached-use-vehicle predicate EXACTAL1 returns immediately
// withAL1 and no own state writes. Otherwise crouch810 ANYnonzero requires4361B0 uncrouch ANYnonzero; AL0 returns0 without post-gate own stores, retaining delegate effects. Admitted
// path clears physics DWORD424bit1; ONLY438010 movement-kind predicate EXACTAL1 replaces vertical velocity FLOAT328 with global jump-speed681E1C, other bytes preserve it.
// Request445740(13), store returned descriptor pointer2136, then context DWORD2140=ADDRESS7BEB0C. Registry may fall back0; no lookup result check. Committed path EAX is descriptor
// pointer, not normalized success. No own NULL/finite/authority/dead test, timer reset, ground probe or rollback.
char __cdecl rf_entity_select_movement13_after_uncrouch(int a1)
{
  char *v1; // eax

  LOBYTE(v1) = rf_entity_has_attached_use_vehicle(a1);
  if ( (unsigned __int8)v1 != 1 )
  {
    if ( !rf_entity_is_crouched_state810(a1) || (LOBYTE(v1) = rf_entity_try_apply_standing_shape_centers(a1), (_BYTE)v1) )
    {
      *(_DWORD *)(a1 + 424) &= ~1u;
      if ( sub_438010(a1) )
        *(float *)(a1 + 328) = unk_681E1C;
      v1 = sub_445740(0xDu);
      *(_DWORD *)(a1 + 2136) = v1;
      *(_DWORD *)(a1 + 2140) = &unk_7BEB0C;
    }
  }
  return (char)v1;
}

