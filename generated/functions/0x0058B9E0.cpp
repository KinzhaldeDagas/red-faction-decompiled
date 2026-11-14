// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B9E0 rf_input_dequeue_event
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Returns0 when uninitialized or ring empty. Under lock, reads unsigned16 keycode at read index, increments/wraps index at16. Does not read or clear the parallel timestamp entry, and does not emit release events. Normal producer preserves one empty ring slot; unchecked enqueue helper can violate that invariant.
int rf_input_dequeue_event()
{
  int v1; // [esp+0h] [ebp-4h]

  v1 = 0;
  if ( !byte_193B680 )
    return 0;
  EnterCriticalSection(&unk_193B668);
  if ( dword_193B55C != unk_193B558 )
  {
    v1 = (unsigned __int16)word_193A0F8[unk_193B558++];
    if ( unk_193B558 >= 0x10u )
      unk_193B558 = 0;
  }
  LeaveCriticalSection(&unk_193B668);
  return v1;
}

