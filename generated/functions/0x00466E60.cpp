// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00466E60 rf_host_menu_button_x_is_open
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg,boolAL. ftol2_sse truncates float buttonX6F5E38;AL1 iff integer equals shared openX. No exactfloat,velocity,input/currentpane or runtime
// check/mutation;upper EAX unspecified.
bool rf_host_menu_button_x_is_open()
{
  return (int)unk_6F5E38 == rf_main_menu_open_x;
}

