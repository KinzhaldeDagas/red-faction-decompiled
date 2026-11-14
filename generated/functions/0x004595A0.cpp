// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004595A0 rf_main_menu_is_active_or_fully_closed
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Any nonzero BYTE661E88 returns AL1 without loading/converting X. Otherwise converts current-X through605F00 and returns AL1 iff full converted
// EAX equals closed-X DWORD, elseAL0. Upper EAX is not normalized. No vertical/velocity test or inclusive bound comparison; sentinel byte and interaction-active byte are distinct.
bool rf_main_menu_is_active_or_fully_closed()
{
  return byte_661E88 || (int)rf_main_menu_current_x == rf_main_menu_closed_x;
}

