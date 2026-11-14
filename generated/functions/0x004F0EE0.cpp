// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0EE0 rf_ui_dispatch_panel_begin_close
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Cdecl(panel ID,DWORD payload,low BYTE immediate),void. Original PE selector/jump tables verified. Routes:2 main_menu_begin_close_once,3 4541D0,4 467420,6 457E60,7 455E40,11 442810,14 467710,15 45FD70,16 4580F0,18/31 4AED40,19 453AF0,20 46E910,21 46FB20,23 453420,24 451500,30 464EE0,32 466E80. Cases2/14/15 push address of OWN stack payload followed by zero-extended immediate byte (native push order byte then address);4/23 pass payload VALUE plus byte;11 passes payload value only;32 passes byte only. Remaining routes no explicit stack args. Unsupported IDs, including33/34 despite initialization routes, return without calls. Does not itself run transition polling/frame
// rendering or commit new panel; ignored parameters in callees remain distinct from supplied native arguments.
void __cdecl rf_ui_dispatch_panel_begin_close(int a1, int a2, char a3)
{
  switch ( a1 )
  {
    case 2:
      rf_main_menu_begin_close_once();
      break;
    case 3:
      rf_extras_menu_close_and_clear_active();
      break;
    case 4:
      rf_intro_panel_begin_close_noop();
      break;
    case 6:
      rf_frontend_release_array6f26ac_and_reverse_motion();
      break;
    case 7:
      rf_frontend_release_array6f21ac_and_reverse_motion();
      break;
    case 11:
      rf_pause_game_input_audio_and_stop_primary_weapon();
      break;
    case 14:
      rf_options_menu_leave_and_save_player_configuration();
      break;
    case 15:
      rf_multiplayer_menu_leave_and_commit_name((int)&a2, a3);
      break;
    case 16:
      rf_frontend_help_close_noop();
      break;
    case 18:
    case 31:
      rf_splitscreen_stop_announcer_disable_mouse_and_pause();
      break;
    case 19:
      rf_endgame_panel_close_noop();
      break;
    case 20:
      rf_persona_history_noop();
      break;
    case 21:
      rf_demo_upsell_noop();
      break;
    case 23:
      rf_credits_panel_close_clear_byte6EFEB2();
      break;
    case 24:
      rf_sequence_panel_close_noop();
      break;
    case 30:
      rf_browser_leave_save_and_release();
      break;
    case 32:
      rf_host_menu_leave_and_persist_lan(a3);
      break;
    default:
      return;
  }
}

