// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464F90 rf_browser_input_enabled_or_main_x_closed
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg,boolAL. Any nonzero inputBYTE661F95 ->AL1 immediately;otherwise truncate float mainX6F5194 and compare closedXDWORD6F29C8. Thus true can mean input enabled while panel
// open;not a pure closed-position predicate. No speed/active/exact-float test or mutation;upper EAX incidental.
bool rf_browser_input_enabled_or_main_x_closed()
{
  return byte_661F95 || (int)unk_6F5194 == unk_6F29C8;
}

