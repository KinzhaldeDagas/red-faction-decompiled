// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591310 rf_dsound_find_buffer_slot_by_play_handle
// UNREALRED VERIFIED [dsound-buffers-20261028]: Negative handle returns-1. Otherwise scans30 backend records at0x1BA1820 stride44 for stored handleDWORD+16 equality,returns first slot or-1. Does not require DS buffer pointer or playing/paused flags to match,so stale/inactive record fields can influence lookup.
int __cdecl rf_dsound_find_buffer_slot_by_play_handle(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( a1 < 0 )
    return -1;
  for ( i = 0; i < 30 && unk_1BA1830[11 * i] != a1; ++i )
    ;
  if ( i == 30 )
    return -1;
  else
    return i;
}

