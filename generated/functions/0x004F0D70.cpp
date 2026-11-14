// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0D70 rf_ui_dispatch_panel_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Cdecl(panel ID,DWORD payload),void. Original PE byte-selector/jump tables verified. ID->callee:2 main_menu_initialize,3 453F50,4 00467360,6 457860,7 4555D0,11 442700,14 467440,15 45FAA0,16 4580E0,18 4AE510,19 453450,20 46DA30,21 46F950,23 452D30,24 44F4A0,30 463CC0,31 4AE4F0,32 466BC0,33 4B0660,34 4A5BB0. Case2 passes ADDRESS of own stack payload (not a public output pointer);11/14/15/23/24 push payload VALUE, each caller-popped4. Other cases supply no explicit stack arguments, even when stale callee types hide passed values or infer an ECX receiver (notably apparent18 for case20). Unsupported IDs including5/8/9/10/12/13/17/22/25..29 and unsigned-outside2..34 do nothing.
// Does not change active/pending panel globals or validate payload here.
void __cdecl rf_ui_dispatch_panel_initialize(int a1, int a2)
{
  switch ( a1 )
  {
    case 2:
      rf_main_menu_initialize();
      break;
    case 3:
      rf_extras_menu_initialize_once_and_open();
      break;
    case 4:
      rf_intro_panel_initialize();
      break;
    case 6:
      rf_save_list_b_initialize();
      break;
    case 7:
      rf_save_list_a_initialize();
      break;
    case 11:
      rf_resume_game_input_audio_and_notify_client(a2);
      break;
    case 14:
      rf_options_menu_enter_and_build();
      break;
    case 15:
      rf_multiplayer_menu_enter();
      break;
    case 16:
      rf_frontend_help_initialize_noop();
      break;
    case 18:
      rf_splitscreen_reset_input_and_apply_weapon_profile();
      break;
    case 19:
      rf_endgame_panel_initialize_text_font_bitmap_and_deadline();
      break;
    case 20:
      rf_persona_history_panel_initialize((void *)(a1 - 2));
      break;
    case 21:
      rf_demo_upsell_initialize();
      break;
    case 23:
      rf_credits_panel_initialize_scroll_fade_and_cached_bitmap();
      break;
    case 24:
      rf_bomb_defuse_panel_initialize_or_resume(a2);
      break;
    case 30:
      rf_browser_enter_and_build_controls();
      break;
    case 31:
      rf_splitscreen_set_pending_and_request_panel5();
      break;
    case 32:
      rf_host_menu_enter_and_build();
      break;
    case 33:
      rf_client_state_sync_arm_eight_second_timer();
      break;
    case 34:
      sub_4A5BB0();
      break;
    default:
      return;
  }
}

