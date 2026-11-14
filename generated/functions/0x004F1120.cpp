// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F1120 rf_ui_panel_close_transition_is_ready
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Cdecl panel ID, returns raw AL:2 main_menu_is_active_or_fully_closed,3 4541F0,4 467430,6 457E90,7 455E70,14 467770,15 45FDD0,30 464F90,32 466EF0. ALL other IDs including negative/outside2..32 return AL1. Does not normalize child AL, initiate close, change pending/active panel or prove every unsupported panel is actually closed. Original PE selector/jump tables verified.
char __cdecl rf_ui_panel_close_transition_is_ready(int a1)
{
  char result; // al

  switch ( a1 )
  {
    case 2:
      result = rf_main_menu_is_active_or_fully_closed();
      break;
    case 3:
      result = rf_extras_menu_button_x_trunc_is_closed();
      break;
    case 4:
      result = rf_intro_panel_close_ready();
      break;
    case 6:
      result = rf_frontend_float6f23cc_matches_dword6f29c8();
      break;
    case 7:
      result = rf_frontend_float6f1f84_matches_dword6f29c8();
      break;
    case 14:
      result = rf_options_menu_button_x_is_closed();
      break;
    case 15:
      result = rf_multiplayer_menu_button_x_is_closed();
      break;
    case 30:
      result = rf_browser_input_enabled_or_main_x_closed();
      break;
    case 32:
      result = rf_host_menu_button_x_is_closed();
      break;
    default:
      result = 1;
      break;
  }
  return result;
}

