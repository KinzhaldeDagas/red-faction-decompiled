// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461B20 rf_browser_row_matches_mode_filter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl raw row index,bool AL. FilterDWORD6F5994 EXACT3 ->AL1 WITHOUT dereferencing row. Every other filter value compares recordDWORD80 atbase6F52CC+108*row
// with rawfilter;equal1,else0. No filter0..2/index/count/base admission,mod-label matching,locale comparison or flags/ping check. Does not alter row/list/selection.
bool __cdecl rf_browser_row_matches_mode_filter(int a1)
{
  return unk_6F5994 == 3 || *((_DWORD *)dword_6F52CC + 27 * a1 + 20) == unk_6F5994;
}

