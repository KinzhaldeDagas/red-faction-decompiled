// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460540 rf_multiplayer_profile_input_enable
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. StoreBYTE6F4850=1 only. No pane/position/pending-state change,name commit,focus reset or sound. EAX unspecified. Rendering/keyboard routing separately
// require currentPane0.
void rf_multiplayer_profile_input_enable()
{
  byte_6F4850[0] = 1;
}

