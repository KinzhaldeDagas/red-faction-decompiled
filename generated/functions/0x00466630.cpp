// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466630 rf_host_menu_focus_previous
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Decrement focus6F5E34;if signed negative,set focus-list count-1. Always sound40. No disabled skipping,nonempty count/upper-corrupt-index guard or
// callback. Empty count may yield-1.
int rf_host_menu_focus_previous()
{
  if ( --dword_6F5E34 < 0 )
    dword_6F5E34 = rf_receiver_get_first_dword(unk_6F5E94) - 1;
  return rf_gamesound_play_event(40, 0, 0.0, 1.0);
}

