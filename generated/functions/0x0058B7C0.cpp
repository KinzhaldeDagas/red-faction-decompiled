// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B7C0 rf_input_reset_scan_code_state
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Recovered cdecl scan index. When initialized, locks, samples now, clears held byte, sets last-query/key-start times now and zeros accumulated-down, press count and release count for that index. Does NOT validate scan index before indexing all six arrays. Does not remove queued events or change global policies.
void __cdecl rf_input_reset_scan_code_state(int scan_code)
{
  int v1; // eax

  if ( byte_193B680 )
  {
    EnterCriticalSection(&unk_193B668);
    v1 = rf_performance_clock_elapsed_scaled(1000);
    byte_193B560[scan_code] = 0;
    dword_193A958[scan_code] = v1;
    dword_193A158[scan_code] = v1;
    dword_193A558[scan_code] = 0;
    dword_193AD58[scan_code] = 0;
    dword_193B158[scan_code] = 0;
    LeaveCriticalSection(&unk_193B668);
  }
}

