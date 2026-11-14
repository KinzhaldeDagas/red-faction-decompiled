// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045FDD0 rf_multiplayer_menu_button_x_is_closed
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg,bool AL. ftol2_sse(buttonX6F4854) equals signed closedX ->AL1,else0. Truncated integer position,not exact float/stopped-velocity or input-state test.
// No finite/overflow admission before conversion;upper EAX incidental. Does not mutate animation state.
bool rf_multiplayer_menu_button_x_is_closed()
{
  return (int)unk_6F4854 == rf_main_menu_closed_x;
}

