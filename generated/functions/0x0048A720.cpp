// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A720 rf_mover_is_waiting_or_idle
// UNREALRED VERIFIED [mission-mover-events-20261020] Returns true when mover is waiting (flags+0x318 bit1) OR inactive (target index+0x2FC == -1). Reverse_Mover uses this predicate before its directional reversal; this is not a rotating flag check.
bool __cdecl rf_mover_is_waiting_or_idle(int a1)
{
  if ( !a1 )
    return 0;
  return (*(_DWORD *)(a1 + 792) & 1) != 0 || *(_DWORD *)(a1 + 764) == -1;
}

