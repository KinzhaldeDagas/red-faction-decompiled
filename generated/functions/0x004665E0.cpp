// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004665E0 rf_host_menu_focus_next
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Increment focusDWORD6F5E34;when signed>=focus-list6F5E94 count,set0. Always sound40. No disabled-control skipping,negative-index
// repair,nonempty-list guard or pane routing;empty count can leave0 invalid. Does not invoke callback.
int rf_host_menu_focus_next()
{
  ++dword_6F5E34;
  if ( dword_6F5E34 >= rf_receiver_get_first_dword(unk_6F5E94) )
    dword_6F5E34 = 0;
  return rf_gamesound_play_event(40, 0, 0.0, 1.0);
}

