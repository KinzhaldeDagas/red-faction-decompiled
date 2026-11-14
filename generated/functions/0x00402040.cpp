// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402040 rf_ai_acquire_probe_and_dispatch_weapon_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): One required AI block. Snapshots retained target DWORD+704 before deadline test. Block+732 deadline elapsed
// any-nonzero calls weighted selector402160(owner,FLOAT25,extra signed difficulty6612A4+2), cleans12bytes; native selector consumes first TWO args only. Uses new result even-1.
// BEFORE new collision probes, tests existing BYTE+668 any-nonzero: OR AI flags+1328 mask8; if CURRENT primary mode+640==6 and mask0x00800000 clear, calls40B2D0(block) then returns
// full EAX1 immediately. This special return happens even when selector returned-1, without rearming scan deadline, committing target, probing or dispatching401670. All other elapsed
// paths rearm+732 from unchecked signed difficulty-indexed DWORD table661274. Nonelapsed paths keep saved retained target and do not rearm. Chosen raw handle!=-1: resolve COMMON
// object; only valid object runs4025D0(block,object), but resolution failure does NOT suppress guarded target setter40BA80(block,raw handle) or401670(block). Ignores target-setter
// result; normal return is ZERO-EXTENDED delegated AL from401670, not its full EAX. Handle-1 returns full EAX0. No own source-null, dead, authority, selected-weapon or target-type
// gate.
int __cdecl rf_ai_acquire_probe_and_dispatch_weapon_action(int a1)
{
  int v2; // [esp+8h] [ebp-Ch]
  int v3; // [esp+Ch] [ebp-8h]
  unsigned __int8 v4; // [esp+13h] [ebp-1h]

  v3 = *(_DWORD *)(a1 + 704);
  if ( rf_replicator_has_elapsed((int *)(a1 + 732)) )
  {
    v3 = rf_ai_choose_weighted_target_handle(*(_DWORD **)a1, 25.0);
    if ( *(_BYTE *)(a1 + 668) )
    {
      *(_DWORD *)(a1 + 1328) |= 8u;
      if ( *(_DWORD *)(a1 + 640) == 6 && ((unsigned int)&unk_800000 & *(_DWORD *)(a1 + 1328)) == 0 )
      {
        sub_40B2D0((int *)a1);
        return 1;
      }
    }
    rf_replicator_arm_milliseconds((int *)(a1 + 732), dword_661274[dword_6612A4]);
  }
  v4 = 0;
  if ( v3 != -1 )
  {
    v2 = rf_object_resolve_handle(v3);
    if ( v2 )
      rf_ai_refresh_target_collision_and_corridor_probes((_DWORD *)a1, v2);
    sub_40BA80((int *)a1, v3);
    return (unsigned __int8)rf_ai_dispatch_selected_primary_weapon_action((int *)a1);
  }
  return v4;
}

