// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00497A40 rf_ctf_broadcast_flag_taken_packet31
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(nullable player). Requires mode1 and nonnull player. Fixed6-byte packet: opcode31 at0, payload WORD1=3, player network id BYTE3 from DWORD[player+4608]+20, red capture BYTE4
// and blue capture BYTE5. Broadcasts(buffer,6,0) without own runtime/authority or player-net null guard. If a local player exists with different team byte, arms deferred enemy-pickup
// sound timer77D730 for0ms after broadcast. Does not play sound immediately, increment counters or set carrier. Raw EAX return is incidental.
int __cdecl rf_ctf_broadcast_flag_taken_packet31(int a1)
{
  int result; // eax
  unsigned __int8 Src; // [esp+Ch] [ebp-208h] BYREF
  __int16 v3; // [esp+Dh] [ebp-207h]
  char v4; // [esp+Fh] [ebp-205h]
  char v5; // [esp+10h] [ebp-204h]
  char v6; // [esp+11h] [ebp-203h]

  result = rf_multiplayer_game_mode_get();
  if ( result == 1 )
  {
    if ( a1 )
    {
      Src = 31;
      v4 = *(_BYTE *)(*(_DWORD *)(a1 + 4608) + 20);
      v5 = byte_77D6E0;
      v6 = byte_77D6E1;
      v3 = 3;
      result = rf_server_broadcast_packet(&Src, 6, 0);
      if ( rf_local_fpgun_player )
      {
        result = *(unsigned __int8 *)(a1 + 48);
        if ( result != *(unsigned __int8 *)(rf_local_fpgun_player + 48) )
          return rf_replicator_arm_milliseconds(&unk_77D730, 0);
      }
    }
  }
  return result;
}

