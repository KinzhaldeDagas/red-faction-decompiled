// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459FE0 rf_main_menu_update_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments.58AB60 reads absolute pointer into two localDWORDs and shared193A03C;458BE0(x,y,buttonPointers6F29E4,count8) returns hit. Negative hit exits; no
// explicit upper-bound check. With58ACF0(button0) AL nonzero: if hit differs, store selected FIRST then play event40, then always459990(hit). Otherwise reads58AD50 relative deltas
// into two locals/shared193A03C; any nonzero delta admits hover update, as does ordered Xvelocity!=DOUBLE0 OR unordered NaN velocity via TEST AH44/JNP. Exactly equal signed-zero
// velocity and both deltas0 skip hover. On admitted hover, play40 only if selection changes, then store hit AFTER sound. Click path stores before sound, hover after, so
// callback/shared-state effects are not a snapshot. No own interaction flag, current-position gate, focus assignment, pointer clamping or input-consumption guarantee; helpers own hit
// geometry and button counts.
void rf_main_menu_update_pointer()
{
  int v0; // [esp+8h] [ebp-14h] BYREF
  int v1; // [esp+Ch] [ebp-10h] BYREF
  int physical_x; // [esp+10h] [ebp-Ch] BYREF
  int physical_y; // [esp+14h] [ebp-8h] BYREF
  int v4; // [esp+18h] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  v4 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)rf_main_menu_button_pointers, 8);
  if ( v4 >= 0 )
  {
    if ( rf_mouse_button_has_press_count(0) )
    {
      if ( rf_main_menu_selected_index != v4 )
      {
        rf_main_menu_selected_index = v4;
        rf_gamesound_play_event(40, 0, 0.0, 1.0);
      }
      rf_main_menu_dispatch_action(v4);
    }
    else
    {
      rf_mouse_get_relative_deltas(&v1, &v0, &unk_193A03C);
      if ( v1 || v0 || rf_main_menu_x_velocity != 0.0 )
      {
        if ( rf_main_menu_selected_index != v4 )
          rf_gamesound_play_event(40, 0, 0.0, 1.0);
        rf_main_menu_selected_index = v4;
      }
    }
  }
}

