// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B400 rf_input_set_numlock_keyboard_byte_one
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Gets Win32 keyboard-state array, writes entire VK_NUMLOCK byte144=1 and calls SetKeyboardState. Does not restore any prior high pressed-state bit. Returns setter BOOL; getter status unchecked.
BOOL rf_input_set_numlock_keyboard_byte_one()
{
  BYTE KeyState[260]; // [esp+0h] [ebp-108h] BYREF

  GetKeyboardState(KeyState);
  KeyState[144] = 1;
  return SetKeyboardState(KeyState);
}

