// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F5B0 rf_multiplayer_server_accept_one_reliable_peer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Calls accept_confirmed_peer ONCE into local8-byte endpoint; -1 returns. Scans player circle in order,including local,without netNULL guard. First
// compare_endpoints(accepted endpoint,player.net,0)==0 AND pending flag net8&4 binds peer: clears bit4,stores accepted handle net16,calls4AFED0(player) roster sender,and stops. No
// new player allocation or repeated accept loop here. Unmatched accepted handle closed through close_peer(&localHandle,1). No own mode/authority check,peer-slot replacement check or
// retained-endpoint storage. Return helper artifact,not normalized success.
_DWORD *rf_multiplayer_server_accept_one_reliable_peer()
{
  _DWORD *result; // eax
  _DWORD *v1; // [esp+0h] [ebp-18h]
  int v2; // [esp+4h] [ebp-14h]
  u_long v3[2]; // [esp+8h] [ebp-10h] BYREF
  int v4; // [esp+10h] [ebp-8h] BYREF
  _DWORD *i; // [esp+14h] [ebp-4h]

  result = (_DWORD *)rf_reliable_udp_accept_confirmed_peer(v3);
  v4 = (int)result;
  if ( result != (_DWORD *)-1 )
  {
    v2 = 0;
    for ( i = (_DWORD *)dword_87C324; i; i = v1 )
    {
      if ( !rf_network_compare_endpoints((int)v3, i[1152], 0) && (*(_DWORD *)(i[1152] + 8) & 4) != 0 )
      {
        *(_DWORD *)(i[1152] + 8) &= ~4u;
        *(_DWORD *)(i[1152] + 16) = v4;
        result = (_DWORD *)rf_multiplayer_send_players_roster_packet6((int)i);
        v2 = 1;
        break;
      }
      if ( *i == dword_87C324 )
        v1 = nullptr;
      else
        v1 = (_DWORD *)*i;
      result = v1;
    }
    if ( !v2 )
      return (_DWORD *)rf_reliable_udp_close_peer(&v4, 1);
  }
  return result;
}

