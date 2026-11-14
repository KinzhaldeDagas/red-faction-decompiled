// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041E2F0 rf_corpse_is_retiring
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] Returns corpse+0x29C bit1, the already-retiring flag. Used by0x41E310 to avoid restarting the one-second fade during repeated endpoint holds.
int __cdecl rf_corpse_is_retiring(int a1)
{
  return *(_DWORD *)(a1 + 668) & 1;
}

