// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BBE0 rf_input_take_release_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Recovered signed scan-index helper; requires initialized and0<=scan<256, otherwise0. Under lock returns release counter193B158[scan] and zeros it. Producer increments on every delivered up, including unmatched/repeated up calls.
int __cdecl rf_input_take_release_count(int scan_code)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( !byte_193B680 )
    return 0;
  if ( (unsigned int)scan_code >= 0x100 )
    return 0;
  EnterCriticalSection(&unk_193B668);
  v2 = dword_193B158[scan_code];
  dword_193B158[scan_code] = 0;
  LeaveCriticalSection(&unk_193B668);
  return v2;
}

