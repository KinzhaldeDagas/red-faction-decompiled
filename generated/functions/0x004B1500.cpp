// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1500 rf_client_mode2_set_team1_score_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Cdecl lowBYTE value. Same runtime1 authority0 mode2 admission as4B14B0; write7B2609 unchanged lowBYTE. No validation/clamp, packet, other team mutation or consistent
// success return. Does not act on server/different game mode.
int __cdecl rf_client_mode2_set_team1_score_byte(char a1)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    result = rf_multiplayer_game_mode_get();
    if ( result == 2 )
      unk_7B2609 = a1;
  }
  return result;
}

