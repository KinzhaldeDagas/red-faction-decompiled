// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459560 rf_main_menu_is_fully_open
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Loads current-X binary32 to x87, invokes605F00 integer conversion, compares resulting full EAX with stored open-X DWORD. Returns AL1 on
// equality elseAL0; upper EAX remains conversion residue. Test is converted-integer equality, not exact float equality, inequality crossing, or vertical-position test. Conversion
// helper owns out-of-range/NaN behavior.
bool rf_main_menu_is_fully_open()
{
  return (int)rf_main_menu_current_x == rf_main_menu_open_x;
}

