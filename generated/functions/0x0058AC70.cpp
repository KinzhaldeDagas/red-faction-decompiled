// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AC70 rf_mouse_get_button_double_click_byte
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Enabled mouse returns raw BYTE0x193A0B1+16*index;disabled returns0. UI double-click handling reads this stored flag;helper does not calculate timing,normalize,clear or validate index.
char __cdecl rf_mouse_get_button_double_click_byte(int a1)
{
  if ( byte_193A06D )
    return unk_193A0B1[16 * a1];
  else
    return 0;
}

