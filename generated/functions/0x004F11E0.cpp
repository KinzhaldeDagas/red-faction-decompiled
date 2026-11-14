// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F11E0 rf_ui_dispatch_panel_frame
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Cdecl(panel ID,low BYTE frame option),void. Original PE direct34-entry table verified.1 calls4F1440 startup loader;2 main_menu_frame;3 454210;4 467410;5 447BE0;6 457EB0;7 455E90;8 requests panel11 with0;9 explicit no-op;10 passes global local-player pointer to level-state-cache capture then447BE0;11 calls unhide-owner predicate and ONLY AL EXACT1 selects cutscene frame, otherwise445060;13 prepares multiplayer-menu state then requests panel2 with0.14 467790;15 45FDF0;16 458100;18 4AE550;19 453920;20 persona_history_render;21 46F9D0;23 452E10;24 44FB80;30 464FC0;32 466F10;33 invalidates active world light list then4B0670;34 4A5F00.
// Routes2/3/4/6/7/11/14/15/16/18/19/20/21/23/24/30/32 forward zero-extended option byte as one caller-popped DWORD, even where saved child types hide it. IDs12/17/22/25..29/31 and unsigned-outside1..34 no-op. No blanket panel init/close or generic frame-status return.
void __cdecl rf_ui_dispatch_panel_frame(int a1, char a2)
{
  switch ( a1 )
  {
    case 1:
      sub_4F1440();
      break;
    case 2:
      rf_main_menu_frame(a2);
      break;
    case 3:
      rf_extras_menu_frame(a2);
      break;
    case 4:
      rf_intro_panel_frame_allow_mouse_centering();
      break;
    case 5:
      rf_ui_execute_level_load_transition();
      break;
    case 6:
      rf_frontend_b_frame_dispatch_and_draw(a2);
      break;
    case 7:
      rf_frontend_a_frame_dispatch_and_draw(a2);
      break;
    case 8:
      rf_ui_request_panel_immediate(11, 0);
      break;
    case 10:
      rf_level_state_cache_capture_current();
      rf_ui_execute_level_load_transition();
      break;
    case 11:
      if ( rf_unhide_global_owner_present() )
        rf_cutscene_update_and_render_frame(a2);
      else
        rf_game_frame_update_and_render_single_local_view(a2);
      break;
    case 13:
      rf_prepare_multiplayer_menu_without_session();
      rf_ui_request_panel_immediate(2, 0);
      break;
    case 14:
      rf_options_menu_update_and_draw(a2);
      break;
    case 15:
      rf_multiplayer_menu_update_and_draw(a2);
      break;
    case 16:
      rf_frontend_help_frame(a2);
      break;
    case 18:
      rf_splitscreen_update_render_and_check_match_end(a2);
      break;
    case 19:
      rf_endgame_panel_frame_event_scroll_and_render(a2);
      break;
    case 20:
      rf_persona_history_render(a2);
      break;
    case 21:
      rf_demo_upsell_frame();
      break;
    case 23:
      rf_credits_panel_frame_input_scroll_render_and_exit(a2);
      break;
    case 24:
      rf_bomb_defuse_panel_update_and_render(a2);
      break;
    case 30:
      rf_browser_update_queries_and_draw(a2);
      break;
    case 32:
      rf_host_menu_update_and_draw(a2);
      break;
    case 33:
      rf_light_invalidate_active_world_list();
      rf_client_state_sync_update_and_check_timeout();
      break;
    case 34:
      sub_4A5F00();
      break;
    default:
      return;
  }
}

