// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F1D50 rf_startup_route_pending_level_or_main_menu
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): First invokes4E5700(global local-player pointer), no own NULL guard. Uses55F720 actual strlen of pending-level RFString6FC300, not stored extent. Positive length calls4494C0; zero/nonpositive requests panel2 with argument0. Returns selected delegate EAX unchanged; no load attempt/file-existence validation in this wrapper and no clearing of pending-level string.
int rf_startup_route_pending_level_or_main_menu()
{
  rf_player_load_configuration_file(rf_local_fpgun_player);
  if ( (int)rf_string_length_from_cstr((const char **)unk_6FC300) <= 0 )
    return rf_ui_request_panel_immediate(2, 0);
  else
    return rf_client_level_entry_initialize_and_request_panel5();
}

