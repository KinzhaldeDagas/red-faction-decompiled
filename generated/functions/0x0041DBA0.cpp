// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041DBA0 rf_corpse_is_eviction_protected
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] Corpse eviction protection predicate: corpse+0x29C bit0x2 OR bit0x40 OR common flags+0x7C bit0x4000. This protects retirement, not inclusion in endpoint mover occupancy.
bool __cdecl rf_corpse_is_eviction_protected(int a1)
{
  return (*(_DWORD *)(a1 + 668) & 2) != 0
      || (*(_DWORD *)(a1 + 668) & 0x40) != 0
      || (*(_DWORD *)(a1 + 124) & 0x4000) != 0;
}

