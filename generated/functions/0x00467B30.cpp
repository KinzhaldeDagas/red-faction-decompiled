// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467B30 rf_options_menu_focus_previous
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Decrement focus6F5FFC;if signednegative,setEXACT4;always sound40. No disabled-button skipping or upper-corrupt-index repair,callback or pane routing.
int rf_options_menu_focus_previous()
{
  if ( --dword_6F5FFC < 0 )
    dword_6F5FFC = 4;
  return rf_gamesound_play_event(40, 0, 0.0, 1.0);
}

