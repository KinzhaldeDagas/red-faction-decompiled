// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405260 rf_ai_mode11_acquire_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block. ALWAYS405330 yaw sweep first. Deadline+732 elapsed EXACT1 ->rearm from unchecked difficulty table661274, then
// replacement predicate404AC0 EXACT1. Call weighted selector402160(owner,30.0f,extra difficulty+2), extra unused, clean12. Result!=-1 ->40BA80(block,handle), ignoring acceptance;
// write secondary9, force BYTE block+669=1, arm block+672 at0ms, reset+676 to-1. These state/timer/byte writes occur even if guarded target setter rejected handle. No immediate
// target re-resolution, own health/authority gate or float success value.
char __cdecl rf_ai_mode11_acquire_target(int a1)
{
  int v1; // eax

  rf_ai_update_authored_yaw_sweep((_DWORD *)a1);
  LOBYTE(v1) = rf_replicator_has_elapsed((int *)(a1 + 732));
  if ( (unsigned __int8)v1 == 1 )
  {
    rf_replicator_arm_milliseconds((int *)(a1 + 732), dword_661274[dword_6612A4]);
    LOBYTE(v1) = rf_ai_should_seek_replacement_target((int *)a1);
    if ( (unsigned __int8)v1 == 1 )
    {
      v1 = rf_ai_choose_weighted_target_handle(*(const float **)a1, 30.0);
      if ( v1 != -1 )
      {
        sub_40BA80((int *)a1, v1);
        rf_ai_secondary_state_write(a1, 9);
        *(_BYTE *)(a1 + 669) = 1;
        rf_replicator_arm_milliseconds((int *)(a1 + 672), 0);
        LOBYTE(v1) = (unsigned __int8)rf_replicator_reset((_DWORD *)(a1 + 676));
      }
    }
  }
  return v1;
}

