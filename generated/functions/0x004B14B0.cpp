// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B14B0 rf_client_mode2_set_team0_score_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Cdecl lowBYTE value. Write global7B2608 only when runtimeBYTE EXACT1,authorityBYTE EXACT0,and game-mode delegate EXACT2. No clamp, addition, notification or packet.
// Other states preserve byte; nominal int return runtime/delegate residue, not assigned value or uniform success. Server authority nonzero values all reject.
int __cdecl rf_client_mode2_set_team0_score_byte(char a1)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    result = rf_multiplayer_game_mode_get();
    if ( result == 2 )
      unk_7B2608 = a1;
  }
  return result;
}

