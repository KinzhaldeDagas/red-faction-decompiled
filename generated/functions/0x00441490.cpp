// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441490 rf_gameplay_pause_then_route_chat_key
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl keyDWORD,return AL incidental preserved. Always invoke gameplay_ui_pause_event_callback(key) FIRST,then query shared
// game-pause gate. Only paused AL EXACT1 suppresses further handling;other values continue. Query runtime-filtered chat active getter45B4B0;only AL EXACT1 forwards ORIGINAL key to
// chat handler45AC90. Does not poll input queue,normalize key,send directly or use initial pause snapshot: pause is queried AFTER callback may change UI state. No uniform
// consumed/handled return;retains whichever guard or handler AL. Original instructions/type unchanged.
char __cdecl rf_gameplay_pause_then_route_chat_key(int a1)
{
  char result; // al

  rf_gameplay_ui_pause_event_callback(a1);
  result = rf_game_pause_gate_query();
  if ( result != 1 )
  {
    result = rf_multiplayer_chat_active_byte_get();
    if ( result == 1 )
      return rf_multiplayer_chat_handle_key(a1);
  }
  return result;
}

