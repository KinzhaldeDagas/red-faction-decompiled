// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460110 rf_multiplayer_menu_focus_previous_enabled
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. At most4 attempts:decrement focus6F484C;when signed negative set count6F49FC-1;test contiguous record BYTE9,stop on any nonzero. No
// empty-count/upper-corrupt-index guard or success indicator/sound. Empty list may yield-1 and unchecked record addressing;does not skip more than4 attempts.
void rf_multiplayer_menu_focus_previous_enabled()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 4; ++i )
  {
    if ( --dword_6F484C < 0 )
      dword_6F484C = rf_receiver_get_first_dword(unk_6F49FC) - 1;
    if ( unk_6F48A1[68 * dword_6F484C] )
      break;
  }
}

