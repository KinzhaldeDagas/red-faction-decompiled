// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467950 rf_options_menu_activate_item
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl raw index,original PE jump table verified.0 toggles Game pane467AA0,1 Video467A20,2 Audio467A60,3 Controls4679E0.4 disables/hides current pane
// via467AE0,sets title/button close velocities,clears UI panel request. Every input INCLUDING unsigned-outside0..4 plays sound41(0,0.0,1.0). No BYTE9/focus/input admission,mainInput
// clear,configuration save or immediate closed-coordinate write in own body. Not generic callback dispatch;fixed index switch owns actions.
int __cdecl rf_options_menu_activate_item(int a1)
{
  switch ( a1 )
  {
    case 0:
      rf_options_menu_toggle_game_pane();
      break;
    case 1:
      rf_options_menu_toggle_video_pane();
      break;
    case 2:
      rf_options_menu_toggle_audio_pane();
      break;
    case 3:
      rf_options_menu_toggle_controls_pane();
      break;
    case 4:
      rf_options_menu_hide_pane();
      unk_6F6024 = -flt_661E60;
      unk_6F601C = (double)unk_6F6124 * rf_main_menu_close_x_speed_scale;
      rf_ui_request_panel_stack_pop();
      break;
    default:
      return rf_gamesound_play_event(41, 0, 0.0, 1.0);
  }
  return rf_gamesound_play_event(41, 0, 0.0, 1.0);
}

