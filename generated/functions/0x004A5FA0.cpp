// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5FA0 rf_client_leave_game_notify_and_exit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(raw id BYTE,raw reason BYTE), runtime1/authority EXACT0. Sends unreliable left_game7 to shared server704EF4 BEFORE player-id lookup. If resolved pointer equals local pointer,
// shows reason modal(title88E208),resets auxiliary level string,tears down runtime,requests panel13 forced1. Other/unresolved id still sends but performs no own player removal. No
// explicit nonnull-local comparison guard: null lookup equals null local also takes exit branch. No transport acknowledgement/source/id validation; caller-controlled low bytes
// preserved.
int __cdecl rf_client_leave_game_notify_and_exit(char a1, char a2)
{
  int result; // eax
  char *v3; // [esp+4h] [ebp-8h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    rf_multiplayer_send_left_game_unreliable_packet7((int)&dword_704EF4, a1, a2);
    result = (int)rf_player_find_by_network_id(a1);
    if ( result == rf_local_fpgun_player )
    {
      v3 = (char *)rf_multiplayer_left_game_reason_text(a2);
      rf_ui_show_ok_modal(dword_88E208, v3, nullptr, 0);
      rf_level_reset_auxiliary_name_string();
      rf_multiplayer_runtime_teardown();
      return rf_ui_request_panel_immediate(13, 1);
    }
  }
  return result;
}

