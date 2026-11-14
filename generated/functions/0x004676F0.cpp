// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004676F0 rf_options_menu_button_x_is_open
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg,boolAL. Truncate float buttonX6F6004 via ftol2_sse;AL1 iff integer equals shared openX. No exactfloat/velocity/input/pane test or mutation. Position
// is6F6004 (animation467CE0 confirms),not6F6018. Upper EAX unspecified.
bool rf_options_menu_button_x_is_open()
{
  return (int)unk_6F6004 == rf_main_menu_open_x;
}

