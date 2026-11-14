// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048B140 rf_mover_set_paused
// UNREALRED VERIFIED [mission-mover-events-20261020] Sets mover flags+0x318 bit0x80 then calls the empty0x48AC30 helper. Does not clear speed, targets, elapsed/ramp clocks, wait deadline or play/stop audio. Linear update honors this bit; rotating update0x489010 does not.
void __cdecl rf_mover_set_paused(int a1)
{
  if ( a1 )
  {
    *(_DWORD *)(a1 + 792) |= 0x80u;
    rf_mover_stop_noop();
  }
}

