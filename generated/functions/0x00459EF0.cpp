// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459EF0 rf_main_menu_select_next_enabled
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Up to8 iterations: wrapped32-bit selected+1 is stored first; signed result>=8 resets to0, otherwise preserved, then reads enabled
// BYTE6F2A61+68*selected. First nonzero stops; if all8 disabled, still exits after8 changes and requests568050(event40,0,float0,float1). For initially valid0..7 this is cyclic
// next-enabled search; no full normalization of arbitrary invalid initial values (negative values/INT_MAX wrap can index outside records). No selected focus update or action
// dispatch; EAX is sound helper result.
int rf_main_menu_select_next_enabled()
{
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < 8; ++i )
  {
    if ( ++rf_main_menu_selected_index >= 8 )
      rf_main_menu_selected_index = 0;
    if ( unk_6F2A61[68 * rf_main_menu_selected_index] )
      break;
  }
  return rf_gamesound_play_event(40, 0, 0.0, 1.0);
}

