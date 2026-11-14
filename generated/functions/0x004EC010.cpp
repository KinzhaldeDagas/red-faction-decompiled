// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EC010 rf_player_initialize_fpgun_runtime_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Assumes player nonNULL, returns player EAX. Zero DWORD model52/56; disarm3972; pending3968=-1. F32zero4312/4316; state4320/4324=-1; F32zero4136,4132,4144,4140; DWORD4148=-1. Clear target-lock request3996/ready3997,target4000=-1,arm4008 at0ms. Clear scanner4016; DWORD4024/4028/4216/4224=-1. No whole-record memset, zoom3988/3989/factor3992 reset, other lock-timer initialization or global handle/node/cache cleanup.
int __cdecl rf_player_initialize_fpgun_runtime_members(int a1)
{
  *(_DWORD *)(a1 + 52) = 0;
  *(_DWORD *)(a1 + 56) = 0;
  rf_replicator_reset((_DWORD *)(a1 + 3972));
  *(_DWORD *)(a1 + 3968) = -1;
  *(float *)(a1 + 4312) = 0.0;
  *(float *)(a1 + 4316) = 0.0;
  *(_DWORD *)(a1 + 4320) = -1;
  *(_DWORD *)(a1 + 4324) = -1;
  *(float *)(a1 + 4136) = 0.0;
  *(float *)(a1 + 4132) = 0.0;
  *(float *)(a1 + 4144) = 0.0;
  *(float *)(a1 + 4140) = 0.0;
  *(_DWORD *)(a1 + 4148) = -1;
  *(_BYTE *)(a1 + 3996) = 0;
  *(_BYTE *)(a1 + 3997) = 0;
  *(_DWORD *)(a1 + 4000) = -1;
  rf_replicator_arm_milliseconds((int *)(a1 + 4008), 0);
  *(_BYTE *)(a1 + 4016) = 0;
  *(_DWORD *)(a1 + 4024) = -1;
  *(_DWORD *)(a1 + 4028) = -1;
  *(_DWORD *)(a1 + 4216) = -1;
  *(_DWORD *)(a1 + 4224) = -1;
  return a1;
}

