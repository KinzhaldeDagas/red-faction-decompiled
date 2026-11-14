// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E26A0 rf_multiplayer_player_add_frags
// UNREALRED VERIFIED [local-multiplayer-score-20261028] Adds signed delta to signed16-bit frags at Player+0x2C score-record pointer,+0x2, then stores the low16 bits. Mode2 with delta+1 also advances the relevant team total. For Deathmatch, explicit self-kill is-1, a distinct resolved attacker is+1, and a missing attacker does not enter this adder from0x429820.
char __cdecl rf_multiplayer_player_add_frags(int a1, int a2)
{
  int v2; // eax

  *(_WORD *)(*(_DWORD *)(a1 + 44) + 2) += a2;
  v2 = rf_multiplayer_game_mode_get();
  if ( v2 == 2 && a2 == 1 )
  {
    if ( *(_BYTE *)(a1 + 48) )
      LOBYTE(v2) = rf_multiplayer_increment_team1_score_wrapped_byte();
    else
      LOBYTE(v2) = rf_multiplayer_increment_team0_score_wrapped_byte();
  }
  return v2;
}

