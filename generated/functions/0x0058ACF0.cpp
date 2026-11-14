// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058ACF0 rf_mouse_button_has_press_count
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Signed button index. Mouse enabled BYTE0x193A06D required;returns bool(press DWORD0x193A0B4+16*index>0),elsefalse. Does not consume/reset count,lock or validate index. Three-button records begin0x193A0B0,stride16.
bool __cdecl rf_mouse_button_has_press_count(int a1)
{
  return byte_193A06D && unk_193A0B4[4 * a1] > 0;
}

