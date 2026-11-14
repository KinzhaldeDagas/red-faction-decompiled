// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464C50 rf_browser_queue_selected_server_query
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg,initially untyped ABI preserved. Always clear cancel and arm UIhold57DC1000. Only signed valid rawselected661F9C0..<liveCount:OR queued40000000,reset retryBYTE1000,set
// single-queryBYTE6F52D8=1. No send,query-order cursor change,old await-bit clear,global counter reset or dirty flag. Invalid selection still clears cancel/arms hold. No useful
// uniform EAX result.
int rf_browser_queue_selected_server_query()
{
  int result; // eax

  unk_6F51A1 = 0;
  result = rf_clock_deadline_set_wrapped_offset(&dword_6F57DC, 1000);
  if ( dword_661F9C >= 0 )
  {
    result = dword_661F9C;
    if ( dword_661F9C < dword_6F51A8 )
    {
      *((_DWORD *)dword_6F52CC + 27 * dword_661F9C + 26) |= 0x40000000u;
      result = 108 * dword_661F9C;
      *((_BYTE *)dword_6F52CC + 108 * dword_661F9C + 100) = 0;
      unk_6F52D8 = 1;
    }
  }
  return result;
}

