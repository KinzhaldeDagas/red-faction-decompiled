// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004600A0 rf_multiplayer_menu_focus_next_enabled
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Up to EXACT4 attempts:increment focus6F484C;wrap0 when signed focus>=focus-list count6F49FC;test contiguous button BYTE9 at6F48A1+68*focus,stop if
// nonzero. No negative-index repair,empty-count guard,proof of at least one enabled item or sound. If all disabled,returns after4 attempts with whatever focus results. Uses fixed4
// attempts independent of count.
void rf_multiplayer_menu_focus_next_enabled()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 4; ++i )
  {
    ++dword_6F484C;
    if ( dword_6F484C >= rf_receiver_get_first_dword(unk_6F49FC) )
      dword_6F484C = 0;
    if ( unk_6F48A1[68 * dword_6F484C] )
      break;
  }
}

