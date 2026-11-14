// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B680 rf_input_wait_and_dequeue_event_busy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Recovered no-argument helper. If uninitialized at entry returns0. Otherwise busy-loops on event_queue_not_empty, incrementing an unused local counter, then dequeues one event. No Sleep/yield, timeout, Windows message pump or repeated initialized check at this level. If shutdown makes queue predicate permanentlyfalse, this loop can spin indefinitely. Predicate and dequeue take separate locks.
int __cdecl rf_input_wait_and_dequeue_event_busy()
{
  int v1; // [esp+0h] [ebp-4h]

  v1 = 0;
  if ( !byte_193B680 )
    return 0;
  while ( !rf_input_event_queue_not_empty() )
    ++v1;
  return rf_input_dequeue_event();
}

