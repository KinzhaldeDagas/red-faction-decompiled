// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459990 rf_main_menu_dispatch_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl raw DWORD index. Unsigned index>7, including negatives, skips actions but STILL plays568050(event41,0,float0,float1). Full original32-byte jump
// table459A64 proves index0->459A90;1->459C60(panel6);2->459C80(panel7);3->459CA0;4->459E10(panel14);5->5987D0 environment restore THEN459E50 return/pop;6->459E30(panel3);7 branches
// on6F29DC previous-panel snapshot. Nonzero7 calls459EA0 quit-current modal; zero7 passes localized globals88E094/88E098,Yes callback459E80,No callback459520,option0 to46F2A0.
// Constant-zero branches bypass English alternatives. No enabled-byte guard, selection write or bounds table read for invalid indices. Always plays event41 after ordinary
// action/modal return, regardless admission/refusal, forwards sound EAX. Callbacks are passed, not invoked by dispatch. Existing load/save helper names are not used as proof of
// physical widget ordering or actual panel6/7 semantic identity.
int __cdecl rf_main_menu_dispatch_action(int a1)
{
  switch ( a1 )
  {
    case 0:
      rf_main_menu_show_new_game_dialog();
      break;
    case 1:
      rf_main_menu_open_load_panel();
      break;
    case 2:
      rf_main_menu_open_save_panel();
      break;
    case 3:
      rf_main_menu_handle_multiplayer_action();
      break;
    case 4:
      rf_main_menu_open_options_panel();
      break;
    case 5:
      rf_audio_environment_restore_saved_room_level();
      rf_main_menu_return_to_game();
      break;
    case 6:
      rf_main_menu_open_extras_panel();
      break;
    case 7:
      if ( rf_main_menu_has_previous_panel )
        rf_main_menu_show_quit_game_dialog();
      else
        rf_ui_show_yes_no_modal(
          unk_88E094,
          unk_88E098,
          (int)rf_main_menu_quit_application_yes,
          (int)rf_main_menu_begin_open_transition,
          0);
      break;
    default:
      return rf_gamesound_play_event(41, 0, 0.0, 1.0);
  }
  return rf_gamesound_play_event(41, 0, 0.0, 1.0);
}

