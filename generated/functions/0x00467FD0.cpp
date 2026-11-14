// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467FD0 rf_options_menu_pane_input_byte_get
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Return raw BYTE6F6000 inAL only;no normalization or upper-EAX guarantee. No mainInput,current/pendingpane,coordinate or runtime test. No mutation.
unsigned __int8 rf_options_menu_pane_input_byte_get()
{
  return byte_6F6000[0];
}

