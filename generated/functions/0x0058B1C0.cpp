// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B1C0 rf_input_handle_windows_key_down
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): If initialized, extracts lParam bits16..23 as scan code and adds128 when extended bit24 is set. VK44 (Print Screen) forces scan183. If merge flag193B685 is nonzero, right Shift54 becomes42 and right Alt184 becomes56; right Ctrl is not merged here. Calls shared state writer(scan,down1,messageLagMs). No direct FIFO write or range check; state writer remaps then truncates to low byte.
void __cdecl rf_input_handle_windows_key_down(int a1, int a2, int a3)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( byte_193B680 )
  {
    v3 = BYTE2(a2);
    if ( (a2 & 0x1000000) != 0 )
      v3 = BYTE2(a2) + 128;
    if ( a1 == 44 )
      v3 = 183;
    if ( unk_193B685 )
    {
      if ( v3 == 54 )
        v3 = 42;
      if ( v3 == 184 )
        v3 = 56;
    }
    rf_input_process_key_state_change(v3, 1, a3);
  }
}

