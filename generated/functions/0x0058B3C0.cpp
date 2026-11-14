// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B3C0 rf_input_shutdown_keyboard_state
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): If initialized, restores NumLock keyboard byte1 only when saved-nonzero flag193B681 is set, clears that saved flag, clears initialized and deletes critical section. Does not unregister the window callback, reset queues/counters or reset NumLock-policy byte here. No locking around teardown; callback/state routines rely on initialized guard.
void __cdecl rf_input_shutdown_keyboard_state()
{
  if ( byte_193B680 )
  {
    if ( unk_193B681 )
    {
      rf_input_set_numlock_keyboard_byte_one();
      unk_193B681 = 0;
    }
    byte_193B680 = 0;
    DeleteCriticalSection(&unk_193B668);
  }
}

