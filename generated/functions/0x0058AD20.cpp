// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AD20 rf_mouse_button_has_release_count
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Mouse enabled required;returns bool(release DWORD0x193A0B8+16*index>0),elsefalse. No count reset,index validation or lock.
bool __cdecl rf_mouse_button_has_release_count(int a1)
{
  return byte_193A06D && dword_193A0B8[4 * a1] > 0;
}

