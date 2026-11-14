// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459F70 rf_main_menu_select_previous_enabled
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Up to8 iterations: store wrapped selected-1, then JNS on subtraction result; negative result becomes7, nonnegative kept, and enabled
// BYTE6F2A61+68*selected tested. First nonzero ends search; exhaustion still plays568050(event40,0,float0,float1), even without a newly enabled selection. For valid0..7 inputs cyclic
// previous; arbitrary invalid positive values and INT_MIN wrap are not bounds-normalized. No focus/draw/action call; forwards sound EAX.
int rf_main_menu_select_previous_enabled()
{
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < 8; ++i )
  {
    if ( --rf_main_menu_selected_index < 0 )
      rf_main_menu_selected_index = 7;
    if ( unk_6F2A61[68 * rf_main_menu_selected_index] )
      break;
  }
  return rf_gamesound_play_event(40, 0, 0.0, 1.0);
}

