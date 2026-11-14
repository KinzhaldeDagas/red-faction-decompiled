// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405210 rf_ai_mode11_secondary_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block, central4042E0 mode11 callback. Secondary DWORD+692==8 ->405260; ==9 ->405570; all other values write secondary8
// only. Does not run newly selected state handler in same call, reset route/target or change primary mode. EAX/AL delegated incidental result.
char __cdecl rf_ai_mode11_secondary_dispatch(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = a1[173];
  if ( v2 == 8 )
    return rf_ai_mode11_acquire_target((int)a1);
  if ( v2 == 9 )
    return rf_ai_mode11_track_target_and_fire(a1);
  return rf_ai_secondary_state_write((int)a1, 8);
}

