// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AAE0 rf_mouse_clear_three_button_transients
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: When enabled,enters critical section0x193A044,for3 records stride16 clears double-click BYTE+1,release DWORD+8,press DWORD+4,then leaves. Does NOT clear held BYTE+0,absolute position,relative/wheel deltas or keyboard state. Disabled no-op.
void rf_mouse_clear_three_button_transients()
{
  int i; // [esp+0h] [ebp-4h]

  if ( byte_193A06D )
  {
    EnterCriticalSection(&unk_193A044);
    for ( i = 0; i < 3; ++i )
    {
      unk_193A0B1[16 * i] = 0;
      dword_193A0B8[4 * i] = 0;
      unk_193A0B4[4 * i] = 0;
    }
    LeaveCriticalSection(&unk_193A044);
  }
}

