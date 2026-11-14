// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004597E0 rf_main_menu_frame
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one DWORD with onlyLOWBYTE read. Always clears focus in all8 records through455F90. Only callerLOWBYTE0 and initial interaction-active byte nonzero
// admit input phase:4477F0(callback459890,extraDWORD1), then459FE0 pointer update, then449B00 focus on selected record, then451F70(local-fpgun-player+E4,action24,&localByte);
// quickload4F6F30 only when helperAL and outputbyte are BOTH nonzero. No local-player null guard, selected-index bound/enabled check, or re-test of interaction flag after callbacks.
// Always calls4595D0 with zero-extended caller byte as an UNUSED outgoing DWORD, caller cleanup4; final EAX delegated. Only initial gates suppress input, not drawing or focus clear.
int __cdecl rf_main_menu_frame(char a1)
{
  char v2; // [esp+3h] [ebp-5h] BYREF
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 8; ++i )
    rf_ui_button_clear_focus((_BYTE *)&rf_main_menu_buttons + 68 * i);
  if ( !a1 )
  {
    if ( rf_main_menu_interaction_active )
    {
      rf_ui_poll_and_dispatch_event(rf_main_menu_handle_input_event);
      rf_main_menu_update_pointer();
      rf_ui_button_set_focus((_BYTE *)&rf_main_menu_buttons + 68 * rf_main_menu_selected_index);
      if ( rf_input_binding_poll_pressed_or_held(rf_local_fpgun_player + 228, 24, &v2) )
      {
        if ( v2 )
          rf_quickload_request();
      }
    }
  }
  return rf_main_menu_update_layout_and_draw();
}

