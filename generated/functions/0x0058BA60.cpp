// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BA60 rf_input_enqueue_event_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Recovered cdecl16-bit keycode. When initialized, locks, stores code at current write index and wraps/increments write index modulo16. Unlike normal producer, does NOT compare next index to read, reject code0, apply modifiers, update key state/counters or write parallel timestamp. Can overwrite queued entries or make write==read and cause queue to appear empty.
void __cdecl rf_input_enqueue_event_unchecked(unsigned __int16 keycode)
{
  int v1; // [esp+0h] [ebp-4h]

  if ( byte_193B680 )
  {
    EnterCriticalSection(&unk_193B668);
    v1 = dword_193B55C + 1;
    if ( dword_193B55C + 1 >= 16 )
      v1 = 0;
    word_193A0F8[dword_193B55C] = keycode;
    dword_193B55C = v1;
    LeaveCriticalSection(&unk_193B668);
  }
}

