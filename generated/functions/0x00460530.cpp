// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460530 rf_multiplayer_profile_input_byte_get
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg,return raw BYTE6F4850 inAL only. No normalization,runtime/pane or menu-active test;upper EAX unspecified. Does not change any state. Used by profile
// draw to clear edit latch when input inactive.
unsigned __int8 rf_multiplayer_profile_input_byte_get()
{
  return byte_6F4850[0];
}

