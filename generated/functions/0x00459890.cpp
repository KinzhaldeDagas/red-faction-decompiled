// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459890 rf_main_menu_handle_input_event
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl raw signed eventDWORD. Event200 or4111 ->459F70 previous;15 or208 ->459EF0 next;28 ->459990(current selected index), with no enabled/index validation
// on this route. Event1 dispatches5 only if6F29DC any nonzero (previous-panel snapshot), otherwise returns. All other values scan8 control-ID DWORDs at6F2A74+68*i; first matching ID
// terminates search EVEN if disabled. Enabled match sets selected=i, calls459990(i), then568050(event41,0,float0,float1). Dispatcher itself also plays event41, so this
// registered-control route has TWO activation-sound requests on ordinary return; Enter route only dispatcher sound. Disabled/no-match/escape-inactive have path-dependent residue, no
// uniform Boolean result. No own interaction gate, async queue drain or case-insensitive/text matching.
int __cdecl rf_main_menu_handle_input_event(int a1)
{
  int result; // eax
  int i; // [esp+Ch] [ebp-4h]

  result = a1;
  if ( a1 <= 200 )
  {
    if ( a1 != 200 )
    {
      if ( a1 == 1 )
      {
        if ( rf_main_menu_has_previous_panel )
          return rf_main_menu_dispatch_action(5);
        return result;
      }
      if ( a1 != 15 )
      {
        if ( a1 == 28 )
          return rf_main_menu_dispatch_action(rf_main_menu_selected_index);
        goto LABEL_15;
      }
      return rf_main_menu_select_next_enabled();
    }
    return rf_main_menu_select_previous_enabled();
  }
  if ( a1 == 208 )
    return rf_main_menu_select_next_enabled();
  if ( a1 == 4111 )
    return rf_main_menu_select_previous_enabled();
LABEL_15:
  for ( i = 0; i < 8; ++i )
  {
    if ( unk_6F2A74[17 * i] == a1 )
    {
      result = 68 * i;
      if ( unk_6F2A61[68 * i] )
      {
        rf_main_menu_selected_index = i;
        rf_main_menu_dispatch_action(i);
        return rf_gamesound_play_event(41, 0, 0.0, 1.0);
      }
      return result;
    }
    result = i + 1;
  }
  return result;
}

