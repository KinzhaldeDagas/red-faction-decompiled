// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AC50 rf_mouse_get_button_held_byte
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Enabled mouse returns raw held BYTE0x193A0B0+16*index;disabled returns0. No press/release count consumption,normalization,index bound or lock.
char __cdecl rf_mouse_get_button_held_byte(int a1)
{
  if ( byte_193A06D )
    return unk_193A0B0[16 * a1];
  else
    return 0;
}

