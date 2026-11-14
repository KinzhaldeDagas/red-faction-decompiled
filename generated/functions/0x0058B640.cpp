// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B640 rf_input_numlock_keyboard_byte_nonzero
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Calls GetKeyboardState and returns byte144!=0. Tests all bits, not just toggle bit0, and does not check getter success.
bool rf_input_numlock_keyboard_byte_nonzero()
{
  BYTE KeyState[260]; // [esp+0h] [ebp-108h] BYREF

  GetKeyboardState(KeyState);
  return KeyState[144] != 0;
}

