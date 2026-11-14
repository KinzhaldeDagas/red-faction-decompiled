// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A660 rf_level_browser_handle_input
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl raw input code. Raw208,200,201,209 empty query RFString6FCC98 BEFORE UI processing. Calls ui_process_frame_input(code,1); normalized action0 does nothing,1 clears panel
// request,28 requests selected level. Other actions convert key to signed character; only32<=c<127 appends query byte and arms wrapped deadline6FC974 for1000ms. No local query-length
// cap, backspace processing, row filtering or match selection; typeahead handled separately.
void __cdecl rf_level_browser_handle_input(int a1)
{
  int v1; // eax
  int v2; // [esp+10h] [ebp+8h]

  if ( a1 == 208 || a1 == 200 || a1 == 201 || a1 == 209 )
    rf_string_assign_from_cstr(unk_6FCC98, (char *)&byte_63878E);
  v2 = rf_ui_process_frame_input(a1, 1);
  if ( v2 )
  {
    if ( v2 == 1 )
    {
      rf_level_browser_clear_panel_request();
    }
    else if ( v2 == 28 )
    {
      rf_level_browser_request_selected_level();
    }
    else
    {
      v1 = rf_input_keycode_to_character(v2);
      if ( v1 >= 32 && v1 < 127 )
      {
        rf_string_append_byte_in_place(unk_6FCC98, v1);
        rf_clock_deadline_set_wrapped_offset(&dword_6FC974, 1000);
      }
    }
  }
}

