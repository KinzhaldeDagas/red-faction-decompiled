// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461C60 rf_browser_begin_refresh_existing_rows
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. If primary record pointerNULL,set capacity6F5198=512,allocate arrays461080(512);otherwise preserve capacity. Clear BYTE6F51A2,call LAN broadcast query
// delegate,read scaled performance clock(1000) into6F51A4,clear cursor6F5190,set deadline6F5334 wrapped offset0. For EACH existing108-byte live row:DWORD96=current captured
// timestamp,WORD94=FFFF(-1 ping),flagsDWORD104|=20000000,BYTE100=0. Does not clear row names/IP/port/otherflags,live/visible counts,selection,mod labels or resort/rebuild list. No
// pointer/result/capacity recheck after allocation or own LAN/online/runtime admission beyond delegated query. Return residue,not discovered count/completion.
void *rf_browser_begin_refresh_existing_rows()
{
  void *result; // eax
  int i; // [esp+0h] [ebp-4h]

  if ( !dword_6F52CC )
  {
    unk_6F5198 = 512;
    rf_browser_allocate_record_and_index_arrays_once(512);
  }
  unk_6F51A2 = 0;
  rf_multiplayer_lan_broadcast_query();
  unk_6F51A4 = rf_performance_clock_elapsed_scaled(1000);
  unk_6F5190 = 0;
  result = (void *)rf_clock_deadline_set_wrapped_offset(&dword_6F5334, 0);
  for ( i = 0; i < unk_6F51A8; ++i )
  {
    *((_DWORD *)dword_6F52CC + 27 * i + 24) = unk_6F51A4;
    *((_WORD *)dword_6F52CC + 54 * i + 47) = -1;
    *((_DWORD *)dword_6F52CC + 27 * i + 26) |= 0x20000000u;
    result = dword_6F52CC;
    *((_BYTE *)dword_6F52CC + 108 * i + 100) = 0;
  }
  return result;
}

