// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00498230 rf_ctf_broadcast_flag_returned_packet34
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(raw byte red selector, optional player), mode1 only. Fixed7-byte packet: opcode34 at0, payload WORD1=4, selector normalized nonzero=>1 atBYTE3, player network id BYTE4 from
// DWORD[player+4608]+20 orFF for null player, red/blue capture BYTE5/6. Broadcasts(buffer,7,0) without own authority/runtime guard or nonnull-player net-pointer check. Does not
// mutate flag/carrier/score state or rearm return timers, so it cannot undo the both-timer reset in return_flag_home.
int __cdecl rf_ctf_broadcast_flag_returned_packet34(char a1, int a2)
{
  int result; // eax
  unsigned __int8 Src; // [esp+14h] [ebp-208h] BYREF
  __int16 v4; // [esp+15h] [ebp-207h]
  bool v5; // [esp+17h] [ebp-205h]
  char v6; // [esp+18h] [ebp-204h]
  char v7; // [esp+19h] [ebp-203h]
  char v8; // [esp+1Ah] [ebp-202h]

  result = rf_multiplayer_game_mode_get();
  if ( result == 1 )
  {
    Src = 34;
    v5 = a1 != 0;
    if ( a2 )
      v6 = *(_BYTE *)(*(_DWORD *)(a2 + 4608) + 20);
    else
      v6 = -1;
    v7 = byte_77D6E0;
    v8 = byte_77D6E1;
    v4 = 4;
    return rf_server_broadcast_packet(&Src, 7, 0);
  }
  return result;
}

