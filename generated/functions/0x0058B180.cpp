// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B180 rf_input_set_numlock_keyboard_byte_zero
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Gets Win32 keyboard-state array, writes entire byte144 (VK_NUMLOCK)=0, and calls SetKeyboardState. Does not mask only the toggle bit. GetKeyboardState return is unchecked; returns SetKeyboardState BOOL. This changes API keyboard-state bytes, not RF scan-state array.
BOOL rf_input_set_numlock_keyboard_byte_zero()
{
  BYTE KeyState[260]; // [esp+0h] [ebp-108h] BYREF

  GetKeyboardState(KeyState);
  KeyState[144] = 0;
  return SetKeyboardState(KeyState);
}

