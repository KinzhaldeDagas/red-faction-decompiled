// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00494C50 rf_server_send_team_score_packet53
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl optional destination player. Requires mode1,authority EXACT1 and raw game mode1 or2. Mode1 reads getters499DA0/499DB0;mode2 uses4B1550/4B1560. EACH result AL zero-extended
// toWORD,so only unsigned8-bit score retained. Builds7-byte packet opcode53,payload lengthWORD1=4,scoreWORD3/5. Nonnull destination calls reliable queue4A0070(destination,packet,7,0)
// directly. NULL destination traverses player circle,skips local,requires net4608 nonnull AND netDWORD12 EXACT2,queues each. No local score reset,packet result check or broader mode
// admission. Return lowWORD incidental,not defined success/count.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Compiled descriptor53 ->recovered494E80 confirms two score WORDs are consumed as lowBYTE only via MOVZX before client setters. Receiver switches game mode1
// CTF red/blue,mode2 team0/team1;no own authority check in callback,client setters own admission. Existing7-byte reliable serialization/audience unchanged.
__int16 __cdecl rf_server_send_team_score_packet53(int a1)
{
  int v1; // eax
  int *v3; // [esp+0h] [ebp-228h]
  int *i; // [esp+4h] [ebp-224h]
  unsigned __int8 Src[3]; // [esp+18h] [ebp-210h] BYREF
  __int16 v6; // [esp+1Bh] [ebp-20Dh]
  __int16 v7; // [esp+1Dh] [ebp-20Bh]
  __int16 team0_score_byte; // [esp+21Ch] [ebp-Ch]
  __int16 team1_score_byte; // [esp+220h] [ebp-8h]
  int v10; // [esp+224h] [ebp-4h]

  LOWORD(v1) = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v1 = rf_multiplayer_game_mode_get();
    v10 = v1;
    if ( v1 == 1 || v10 == 2 )
    {
      if ( v10 == 1 )
      {
        team0_score_byte = (unsigned __int8)rf_ctf_red_capture_byte_get();
        team1_score_byte = (unsigned __int8)rf_ctf_blue_capture_byte_get();
      }
      else
      {
        team0_score_byte = (unsigned __int8)rf_multiplayer_get_team0_score_byte();
        team1_score_byte = (unsigned __int8)rf_multiplayer_get_team1_score_byte();
      }
      Src[0] = 53;
      v6 = team0_score_byte;
      v7 = team1_score_byte;
      LOWORD(v1) = 4;
      *(_WORD *)&Src[1] = 4;
      if ( a1 )
      {
        LOWORD(v1) = rf_multiplayer_queue_reliable_packet(a1, Src, 7u, 0);
      }
      else
      {
        for ( i = (int *)dword_87C324; i; i = v3 )
        {
          if ( i != (int *)rf_local_fpgun_player && i[1152] && *(_DWORD *)(i[1152] + 12) == 2 )
            rf_multiplayer_queue_reliable_packet((int)i, Src, 7u, 0);
          LOWORD(v1) = (_WORD)i;
          if ( *i == dword_87C324 )
          {
            v3 = nullptr;
          }
          else
          {
            v1 = *i;
            v3 = (int *)*i;
          }
        }
      }
    }
  }
  return v1;
}

