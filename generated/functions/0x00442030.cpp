// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442030 rf_gameplay_ui_pause_event_callback
// UNREALRED VERIFIED [cutscene-playback-20261028]: Event byte1 requests deferred panel2. Event bytes69 or198 query global cutscene-owner presence; only when absent toggles pause helpers: if pause query==1 calls0x448BA0(1), else0x448B40(1). Other codes have no persistent effect here. Return register varies across branches; not consumed-event boolean. No key-name interpretation asserted for numeric codes.
char __cdecl rf_gameplay_ui_pause_event_callback(char a1)
{
  char result; // al

  result = a1;
  if ( a1 == 1 )
    return rf_ui_request_panel_deferred(2, 0, 0);
  if ( a1 == 69 || (unsigned __int8)a1 == 198 )
  {
    result = rf_unhide_global_owner_present();
    if ( !result )
    {
      if ( rf_game_pause_gate_query() == 1 )
        return rf_game_unpause_unless_locked(1);
      else
        return rf_game_pause_unless_multiplayer_or_already_paused(1);
    }
  }
  return result;
}

