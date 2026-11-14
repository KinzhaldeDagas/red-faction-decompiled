// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048B180 rf_mover_clear_paused
// UNREALRED VERIFIED [mission-mover-events-20261020] Clears only mover flags+0x318 bit0x80. Does not start an inactive mover or reset clocks; used by Mover_Pause reverse handler0x5015F0.
int __cdecl rf_mover_clear_paused(int a1)
{
  int result; // eax

  if ( a1 )
  {
    *(_DWORD *)(a1 + 792) &= ~0x80u;
    return a1;
  }
  return result;
}

