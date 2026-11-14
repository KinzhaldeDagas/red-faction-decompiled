// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467AF0 rf_options_menu_focus_next
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Increment focus6F5FFC;if signed>=EXACT5,set0;always sound40. No disabled-button skipping,negative-index repair or callback. Does not use a dynamic count
// or reset paneInput.
int rf_options_menu_focus_next()
{
  if ( ++dword_6F5FFC >= 5 )
    dword_6F5FFC = 0;
  return rf_gamesound_play_event(40, 0, 0.0, 1.0);
}

