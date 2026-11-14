// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AF950 rf_ui_window_find_navigation_left_with_wrap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Actual thiscall ECX window,two stack int coordinates x/y,RET8; EDX unused. Calls gadget-left search on root1220 if nonNULL. If shared candidate1CF7C1C stillNULL,root nonNULL,and flags584 mask8 set,repeats at window.x+width-1 and same y. No candidate/metric reset or selection assignment. Only caller5AF4C0 ignores EAX; no stable return contract.
void __thiscall rf_ui_window_find_navigation_left_with_wrap(void *self, int x, int y)
{
  if ( *((_DWORD *)self + 305) )
    rf_ui_gadget_find_navigation_candidate_left(*((_DWORD **)self + 305), x, y);
  if ( !unk_1CF7C1C && *((_DWORD *)self + 305) && (*((_DWORD *)self + 146) & 8) != 0 )
    rf_ui_gadget_find_navigation_candidate_left(
      *((_DWORD **)self + 305),
      *((_DWORD *)self + 3) + *((_DWORD *)self + 5) - 1,
      y);
}

