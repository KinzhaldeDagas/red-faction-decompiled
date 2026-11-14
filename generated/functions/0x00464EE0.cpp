// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464EE0 rf_browser_leave_save_and_release
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Clear pendingIP;main/title speeds=-shared open speed/-661E60,input661F95=0. Write registry ListLAN=(browserLAN6F52DB==EXACT1);only browserLAN==0 saves caches (other
// nonzero values skip). Release record/index arrays. If favorites pointer nonNULL,delete then zero pointer AND favoriteCount;NULL pointer preserves old favoriteCount. Clear
// active6F52CA. Retain build latch6F52CB for reuse. No explicit trackerActive/cancel/per-row query reset or tracker-pool shutdown in own body;does not immediately set closed
// coordinates. Return residue.
void rf_browser_leave_save_and_release()
{
  rf_join_pending_ipv4_clear();
  unk_6F52BC = -rf_ui_open_transition_speed;
  unk_6F52B8 = -flt_661E60;
  byte_661F95 = 0;
  rf_registry_write_dword(nullptr, "ListLAN", unk_6F52DB == 1);
  if ( !unk_6F52DB )
    rf_browser_save_cache_and_favorites();
  rf_browser_release_record_and_index_arrays();
  if ( dword_6F52E8 )
  {
    operator delete(dword_6F52E8);
    dword_6F52E8 = nullptr;
    dword_6F52EC = 0;
  }
  unk_6F52CA = 0;
}

