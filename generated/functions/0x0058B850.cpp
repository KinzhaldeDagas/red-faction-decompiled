// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B850 rf_input_query_down_time_fraction
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Returns0 when uninitialized or unsigned scan>=256. Under lock, elapsed=uint32(now-lastQuery), updates lastQuery=now. If elapsed>1ms: held key uses uint32(now-keyStart) and sets keyStart=now; released key consumes accumulatedDownMs and clears it. Returns float(unsigned numerator/elapsed), without clamping. If elapsed<=1, sets keyStart=now and returns held?1:0, retaining accumulatedDownMs. Held branch does not consume older accumulated release time. Native32-bit tick arithmetic; no FIFO access.
double __cdecl rf_input_query_down_time_fraction(unsigned int a1)
{
  int v3; // [esp+14h] [ebp-Ch]
  unsigned int v4; // [esp+18h] [ebp-8h]
  int v5; // [esp+1Ch] [ebp-4h]

  if ( !byte_193B680 )
    return 0.0;
  if ( a1 >= 0x100 )
    return 0.0;
  EnterCriticalSection(&unk_193B668);
  v5 = rf_performance_clock_elapsed_scaled(1000);
  v4 = v5 - dword_193A958[a1];
  dword_193A958[a1] = v5;
  if ( v4 > 1 )
  {
    if ( byte_193B560[a1] )
    {
      v3 = v5 - dword_193A158[a1];
      dword_193A158[a1] = v5;
    }
    else
    {
      v3 = dword_193A558[a1];
      dword_193A558[a1] = 0;
    }
    LeaveCriticalSection(&unk_193B668);
    return (float)((double)(unsigned int)v3 / (double)v4);
  }
  else
  {
    dword_193A158[a1] = v5;
    if ( byte_193B560[a1] )
    {
      LeaveCriticalSection(&unk_193B668);
      return 1.0;
    }
    else
    {
      LeaveCriticalSection(&unk_193B668);
      return 0.0;
    }
  }
}

