// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4DA0 rf_multiplayer_send_netgame_update_packet26
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(optional peer), runtime1/authority EXACT1. Original descriptor26 is netgame_update, NOT pong (25 is pong). Always constructs mask7 (bits1,2,4),opcode26,player-count BYTE
// counting ALL list players modulo256. Serializes EVERY list player regardless advertised byte count/state: idBYTE; net metric WORD+1452; BYTE=low8(trunc_x87(net float+1456*255.0))
// with temporary round-toward-zero control and no clamp; score record+44 WORD+2 and WORD+4. No net/score null guards. Then two floats6FC428(shared seconds clock)/704EE4 via x87
// single temporaries.
// For ordinary N players,total=13+8*N,payload=10+8*N,with uint16 cursor and no packet-buffer bound/count<=255 check. Byte count may wrap while actual serialization continues. Nonnull
// peer queues unreliable;null uses common unreliable fanout; no own flush/state mutation. Retains no semantic success result. Previous pong names/table claims corrected from PE
// registry and indirect dispatcher evidence.
int __cdecl rf_multiplayer_send_netgame_update_packet26(int a1)
{
  int result; // eax
  _DWORD *v2; // [esp+Ch] [ebp-244h]
  _DWORD *v3; // [esp+10h] [ebp-240h]
  char v4; // [esp+3Bh] [ebp-215h]
  _DWORD *i; // [esp+3Ch] [ebp-214h]
  _DWORD *j; // [esp+3Ch] [ebp-214h]
  unsigned __int16 v7; // [esp+44h] [ebp-20Ch]
  unsigned __int16 v8; // [esp+44h] [ebp-20Ch]
  unsigned __int16 v9; // [esp+44h] [ebp-20Ch]
  unsigned __int16 v10; // [esp+44h] [ebp-20Ch]
  char Src; // [esp+48h] [ebp-208h] BYREF
  __int16 Src_1; // [esp+49h] [ebp-207h]
  char Src_3; // [esp+4Bh] [ebp-205h]
  char v14; // [esp+4Ch] [ebp-204h]
  char v15; // [esp+24Fh] [ebp-1h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v15 = 7;
    Src = 26;
    Src_3 = 7;
    v4 = 0;
    for ( i = (_DWORD *)dword_87C324; i; i = v3 )
    {
      ++v4;
      if ( *i == dword_87C324 )
        v3 = nullptr;
      else
        v3 = (_DWORD *)*i;
    }
    v14 = v4;
    v7 = 5;
    for ( j = (_DWORD *)dword_87C324; j; j = v2 )
    {
      *(&Src + v7++) = *(_BYTE *)(j[1152] + 20);
      if ( (v15 & 1) != 0 )
      {
        *(_WORD *)(&Src + v7) = *(_WORD *)(j[1152] + 1452);
        v8 = v7 + 2;
        *(&Src + v8) = (int)(*(float *)(j[1152] + 1456) * 255.0);
        v7 = v8 + 1;
      }
      if ( (v15 & 2) != 0 )
      {
        *(_WORD *)(&Src + v7) = *(_WORD *)(j[11] + 2);
        v9 = v7 + 2;
        *(_WORD *)(&Src + v9) = *(_WORD *)(j[11] + 4);
        v7 = v9 + 2;
      }
      if ( *j == dword_87C324 )
        v2 = nullptr;
      else
        v2 = (_DWORD *)*j;
    }
    if ( (v15 & 4) != 0 )
    {
      *(_DWORD *)(&Src + v7) = dword_6FC428;
      v10 = v7 + 4;
      *(_DWORD *)(&Src + v10) = dword_704EE4;
      v7 = v10 + 4;
    }
    Src_1 = v7 - 3;
    if ( a1 )
      return rf_network_queue_unreliable_player_packet(a1, &Src, v7);
    else
      return rf_multiplayer_broadcast_unreliable_packet(&Src, v7);
  }
  return result;
}

