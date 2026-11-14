// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004541B0 rf_extras_menu_button_x_trunc_is_open
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments, canonicalAL0/1. Truncate FLOAT buttonX6F1DB0 via native605F00, compare resulting
// integer with current signed open bound661E44 (PE11), setAL1 iff equal. Tests TRUNCATED coordinate, not exact float equality, velocity0, titlebar position or active flag; values
// in[11,12) normally admit. No finite guard; native invalid-conversion behavior remains helper-owned, upperEAX incidental.
bool rf_extras_menu_button_x_trunc_is_open()
{
  return (int)unk_6F1DB0 == rf_main_menu_open_x;
}

