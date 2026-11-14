// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A90F0 rf_text_list_is_empty
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Recovered code0x5A90F0..0x5A9114. Thiscall returns bool(first pointer+732==sentinel this+724). No count,extent or selected-pointer test;does not mutate/reflow list.
bool __thiscall rf_text_list_is_empty(void *list)
{
  return *((_DWORD *)list + 183) == (_DWORD)list + 724;
}

