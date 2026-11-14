// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458500 rf_key_help_reset_row_cursor
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments. Writes shared signed DWORDs661E24=10(leftX),661E28=50(nextY),661E2C=15(row step),661E30=250(right-column X offset). No render/delegate
// call, allocation, argument read or explicit EAX assignment. Both key-help renderers call before rows; no independent/thread-local cursor or prior-state preservation.
void rf_key_help_reset_row_cursor()
{
  dword_661E24 = 10;
  dword_661E28 = 50;
  dword_661E2C = 15;
  dword_661E30 = 250;
}

