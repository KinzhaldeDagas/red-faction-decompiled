// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B250 rf_input_handle_windows_key_up
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Same Windows scan extraction, Print Screen override and optional right Shift/Alt merge as key-down path. For scan183, deliberately synthesizes shared writer down1 then up0 on KEYUP, accommodating Print Screen key-up-only delivery. Other scans produce only up0. Guarded by initialized flag; forwards message lag unchanged.
void __cdecl rf_input_handle_windows_key_up(int a1, int a2, int a3)
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
    if ( v3 == 183 )
    {
      rf_input_process_key_state_change(183, 1, a3);
      rf_input_process_key_state_change(183, 0, a3);
    }
    else
    {
      rf_input_process_key_state_change(v3, 0, a3);
    }
  }
}

