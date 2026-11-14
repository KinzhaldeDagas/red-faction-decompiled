// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B310 rf_input_initialize_keyboard_state
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Runs only if initialized193B680==0; otherwise returns that nonzero flag in EAX. Stores merge byte193B685 and first argument193A0F0, enables repeat byte663F58=1, initializes critical section193B668, samples performance-clock milliseconds to193B660, and calls reset-all while inside the lock. VERIFIED: reset-all itself tests initialized, which is still0 here, so that initialization-time reset is a no-op. Stores NumLock-policy byte193B682; only value1 attempts legacy suppression and resets it to0 on return-1. Registers window-message callback, registers shutdown via atexit, then sets initialized1. Return EAX is atexit result or prior flag, not a uniform success boolean.
int __cdecl rf_input_initialize_keyboard_state(int a1, char a2, char a3)
{
  int result; // eax

  result = (unsigned __int8)byte_193B680;
  if ( !byte_193B680 )
  {
    unk_193B685 = a3;
    unk_193A0F0 = a1;
    byte_663F58 = 1;
    InitializeCriticalSection(&unk_193B668);
    EnterCriticalSection(&unk_193B668);
    unk_193B660 = rf_performance_clock_elapsed_scaled(1000);
    rf_input_reset_all_key_and_event_state();
    LeaveCriticalSection(&unk_193B668);
    unk_193B682 = a2;
    if ( a2 == 1 && rf_input_prepare_legacy_numlock_suppression() == -1 )
      unk_193B682 = 0;
    rf_window_register_message_observer_unchecked((int)rf_input_window_message_callback);
    result = atexit(rf_input_shutdown_keyboard_state);
    byte_193B680 = 1;
  }
  return result;
}

