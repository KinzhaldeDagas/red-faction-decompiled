// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467310 rf_host_menu_pane_input_enable
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg. Set BYTE6F5E29=1 only. No current/pendingpane,position/velocity,focus,sound or mainInput mutation. Keyboard/pointer further route by current
// pane;enable can precede pending-pane commit. No defined EAX status.
void rf_host_menu_pane_input_enable()
{
  unk_6F5E29 = 1;
}

