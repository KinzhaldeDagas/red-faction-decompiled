// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F1060 rf_ui_panel_open_transition_is_ready
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Cdecl panel ID, returns raw AL from delegated readiness query:2 main_menu_is_fully_open,3 4541B0,4 467400,6 457E40,7 455E20,14 4676F0,15 45FD50,30 464EC0,32 466E60. ALL other IDs including negative/outside2..32 return AL1. No normalization of child AL, panel initialization/state write, or general active-panel test. Selector/jump-table mappings verified against full original PE bytes.
char __cdecl rf_ui_panel_open_transition_is_ready(int a1)
{
  char result; // al

  switch ( a1 )
  {
    case 2:
      result = rf_main_menu_is_fully_open();
      break;
    case 3:
      result = rf_extras_menu_button_x_trunc_is_open();
      break;
    case 4:
      result = rf_intro_panel_open_ready();
      break;
    case 6:
      result = rf_frontend_float6f23cc_matches_dword661e58();
      break;
    case 7:
      result = rf_frontend_float6f1f84_matches_dword661e58();
      break;
    case 14:
      result = rf_options_menu_button_x_is_open();
      break;
    case 15:
      result = rf_multiplayer_menu_button_x_is_open();
      break;
    case 30:
      result = rf_browser_main_x_is_open();
      break;
    case 32:
      result = rf_host_menu_button_x_is_open();
      break;
    default:
      result = 1;
      break;
  }
  return result;
}

