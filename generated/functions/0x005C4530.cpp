// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C4530 rf_d3d8_display_mode_check_stub_true
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Unconditionally returns byte 1. Display-mode caller 573710 first requests depth32, then would try depth16 only on false; this stub always accepts the first attempt. No argument reads or device validation.
char rf_d3d8_display_mode_check_stub_true()
{
  return 1;
}

