// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467770 rf_options_menu_button_x_is_closed
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg,boolAL. Truncate float buttonX6F6004 and compare shared closedX;AL1 iff equal. No exactfloat/stopped-velocity/mainInput/paneInput or current-selection
// check. No state mutation;upper EAX unspecified.
bool rf_options_menu_button_x_is_closed()
{
  return (int)unk_6F6004 == rf_main_menu_closed_x;
}

