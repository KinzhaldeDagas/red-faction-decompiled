// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BB80 rf_input_take_press_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Uninitialized or unsigned scan>=256 returns0. Under critical section, returns press counter193AD58[scan] and clears it. Producer increments only on transition from not-held to held, not on allowed OS-repeat enqueues.
int __cdecl rf_input_take_press_count(unsigned int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( !byte_193B680 )
    return 0;
  if ( a1 >= 0x100 )
    return 0;
  EnterCriticalSection(&unk_193B668);
  v2 = dword_193AD58[a1];
  dword_193AD58[a1] = 0;
  LeaveCriticalSection(&unk_193B668);
  return v2;
}

