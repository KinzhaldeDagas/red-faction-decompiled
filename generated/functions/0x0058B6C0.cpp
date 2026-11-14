// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B6C0 rf_input_reset_all_key_and_event_state
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Only when initialized: under critical section, zeros FIFO read/write indices, all16 keycode slots and16 parallel timestamp slots. Samples performance-clock milliseconds; for each256 scan slots clears held byte, sets last-query and key-start timestamps to now, clears accumulated down milliseconds and press/release counters. Does not change repeat/merge/modifier-enable policy, last down/up scan globals or last-event timestamp. Focus gain and loss both call it.
void __cdecl rf_input_reset_all_key_and_event_state()
{
  int v0; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  if ( byte_193B680 )
  {
    EnterCriticalSection(&unk_193B668);
    dword_193B55C = 0;
    unk_193B558 = 0;
    for ( i = 0; i < 16; ++i )
    {
      word_193A0F8[i] = 0;
      unk_193A118[i] = 0;
    }
    v0 = rf_performance_clock_elapsed_scaled(1000);
    for ( j = 0; j < 256; ++j )
    {
      byte_193B560[j] = 0;
      dword_193A958[j] = v0;
      dword_193A158[j] = v0;
      dword_193A558[j] = 0;
      dword_193AD58[j] = 0;
      dword_193B158[j] = 0;
    }
    LeaveCriticalSection(&unk_193B668);
  }
}

