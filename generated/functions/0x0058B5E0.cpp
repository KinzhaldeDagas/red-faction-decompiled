// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B5E0 rf_input_prepare_legacy_numlock_suppression
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Calls GetVersionExA with size148. Platform ID2 returns-1 without suppression. Other platforms test WHOLE keyboard byte144 for nonzero; when nonzero, set saved flag193B681=1 and force that byte0. Returns0 whether original byte was zero or clearing succeeded. OS-version and keyboard-state API statuses are unchecked. Shutdown later restores byte1, not an exact saved byte.
int rf_input_prepare_legacy_numlock_suppression()
{
  struct _OSVERSIONINFOA VersionInformation; // [esp+0h] [ebp-A0h] BYREF

  VersionInformation.dwOSVersionInfoSize = 148;
  GetVersionExA(&VersionInformation);
  if ( VersionInformation.dwPlatformId == 2 )
    return -1;
  if ( rf_input_numlock_keyboard_byte_nonzero() )
  {
    unk_193B681 = 1;
    rf_input_set_numlock_keyboard_byte_zero();
  }
  return 0;
}

