// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461D70 rf_multiplayer_menu_toggle_lan
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. TrackerActiveBYTE6F51A2==EXACT1 OR signed queryCursor6F51B0>=0 plays sound2 but DOES NOT reject toggle. Normalize logical-not checkbox6F5DB8 and mirror boolean6F52DB.
// NewLAN1:sound44,SAVE online caches463150 BEFORE clearing live/visible/displayselection/rawselection,also scroll0/cancel0,then refresh461C60. NewLAN0:sound45,clear
// live/visible/displayselection/rawselection,load caches462BE0;does not explicitly clear scroll/cancel here. Both rebuild indices. Refresh delegate broadcasts3-byte type0 on7755 and
// arms shared deadline5334 OFFSET0,not1000ms. No branch directly enforces session/runtime admission;return residue.
void rf_multiplayer_menu_toggle_lan()
{
  if ( unk_6F51A2 == 1 || unk_6F51B0 >= 0 )
    rf_gamesound_play_event(2, 0, 0.0, 1.0);
  byte_6F5DB8[0] = byte_6F5DB8[0] == 0;
  unk_6F52DB = byte_6F5DB8[0] != 0;
  if ( byte_6F5DB8[0] )
  {
    rf_gamesound_play_event(44, 0, 0.0, 1.0);
    rf_browser_save_cache_and_favorites();
    unk_6F51A8 = 0;
    MEMORY[0x6F5088] = 0;
    unk_6F52E0 = 0;
    dword_661F9C = -1;
    unk_6F52E4 = 0;
    unk_6F51A1 = 0;
    rf_browser_begin_refresh_existing_rows();
  }
  else
  {
    rf_gamesound_play_event(45, 0, 0.0, 1.0);
    unk_6F51A8 = 0;
    MEMORY[0x6F5088] = 0;
    unk_6F52E0 = 0;
    dword_661F9C = -1;
    rf_browser_load_cache_and_favorites();
  }
  rf_browser_rebuild_filtered_sorted_row_indices();
}

