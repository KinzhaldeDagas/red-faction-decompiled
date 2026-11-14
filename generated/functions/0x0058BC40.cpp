// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BC40 rf_input_event_queue_not_empty
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Returns false when uninitialized; otherwise compares FIFO write/read indices under critical section. Equal indices mean empty, including when unchecked enqueue has wrapped a full queue onto read index. Does not dequeue or pump Windows messages.
BOOL rf_input_event_queue_not_empty()
{
  BOOL v1; // [esp+0h] [ebp-4h]

  if ( !byte_193B680 )
    return 0;
  EnterCriticalSection(&unk_193B668);
  v1 = dword_193B55C != unk_193B558;
  LeaveCriticalSection(&unk_193B668);
  return v1;
}

