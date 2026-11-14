// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466EF0 rf_host_menu_button_x_is_closed
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg,boolAL. Compare truncated float buttonX6F5E38 with shared closedX,AL1 iff equal. No velocity,exactfloat,mainInput/paneInput/currentpane predicate or
// state mutation. Does not itself complete pending-pane transition.
bool rf_host_menu_button_x_is_closed()
{
  return (int)unk_6F5E38 == rf_main_menu_closed_x;
}

