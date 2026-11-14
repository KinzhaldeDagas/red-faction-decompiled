// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442700 rf_resume_game_input_audio_and_notify_client
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(raw prior-state DWORD). Clear DWORD6E6AC0, set mouse centering permission raw1, enable centering
// request, call mouse reset58A950 TWICE in succession. Only input argument EXACT10 suppresses58B6C0 full key/event reset; every other signed/unsigned bit pattern calls it. Then
// unpause448BA0(force1), fade menu-owned music45A0D0, call568A00 with raw slots(0,-1), ignoring all results. Finally only multiplayer BYTE704E81 EXACT1 AND authority BYTE704E82
// EXACT0 sends4B07B0 packet11. After send, XOR EDX,EDX makes following JNZ back-edge unreachable: no polling/retry loop. Other MP values including nonzero2 skip packet; no
// connection/local-player validation here. Return full EAX is zero-extended MP byte on skipped-send paths and raw send-helper EAX otherwise, not a resume status. Earlier input/audio
// changes persist independently of later pause/network helper outcomes.
int __cdecl rf_resume_game_input_audio_and_notify_client(int a1)
{
  int result; // eax

  unk_6E6AC0 = 0;
  rf_mouse_set_centering_permission_byte(1);
  rf_mouse_enable_centering_request();
  rf_mouse_reset_buttons_and_motion();
  rf_mouse_reset_buttons_and_motion();
  if ( a1 != 10 )
    rf_input_reset_all_key_and_event_state();
  rf_game_unpause_unless_locked(1);
  rf_main_menu_fade_owned_music();
  rf_sound_backend_set_paused(0);
  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    return rf_client_send_in_game_packet11();
  return result;
}

