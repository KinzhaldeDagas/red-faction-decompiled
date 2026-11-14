// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045FD50 rf_multiplayer_menu_button_x_is_open
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg,bool AL. Convert float buttonX6F4854 to signed integer via ftol2_sse (truncTowardZero),compare with openX global;returnAL1 iff equal. Does not test
// exact float equality,velocity zero,menu active/profile state,or transition completion. Conversion/exception behavior delegated;no finite-range guard. Upper EAX not promised bool.
bool rf_multiplayer_menu_button_x_is_open()
{
  return (int)unk_6F4854 == rf_main_menu_open_x;
}

