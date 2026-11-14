// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B13C0 rf_multiplayer_choose_balanced_team_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No arguments. Raw game mode0 returns AL0 without counting. ANY nonzero game mode counts team0/team1 in wrapping unsigned BYTES via4B1340, chooses AL1 when team0 count>team1, AL0
// when team1>team0, ties use native signed rand()%2 (CRT rand ordinarily nonnegative). Does not restrict mode to1/2 or check runtime/authority; no state mutation except rand
// delegate. Counts include local/pending/disconnected list players and ignore team values other than0/1. Semantic result is team BYTE in AL; direct team branches also leave full EAX
// canonical0/1 because earlier MOVZX clears its high bits. Tie path preserves the signed rand remainder in EAX (normally0/1).
char rf_multiplayer_choose_balanced_team_byte()
{
  int v0; // eax
  unsigned __int8 v2; // [esp+6h] [ebp-2h] BYREF
  unsigned __int8 v3; // [esp+7h] [ebp-1h] BYREF

  if ( rf_multiplayer_game_mode_get() )
  {
    rf_multiplayer_count_team_player_bytes(&v3, &v2);
    if ( v3 <= (int)v2 )
    {
      if ( v2 <= (int)v3 )
        return rand() % 2;
      else
        LOBYTE(v0) = 0;
    }
    else
    {
      LOBYTE(v0) = 1;
    }
  }
  else
  {
    LOBYTE(v0) = 0;
  }
  return v0;
}

