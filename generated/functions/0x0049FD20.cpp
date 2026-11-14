// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049FD20 rf_multiplayer_receive_and_dispatch_queued_packets
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// No arguments, no own runtime/global-enabled guard. Polls UDP queues, chooses buffer77FF20+(old BYTE78BF20<<14),then increments nesting BYTE without bounds and drains
// positive-length unreliable receives into SAME buffer, finds peer by endpoint,dispatches each via49FB50. Nonpositive receive stops that loop. No exception cleanup protecting nesting
// counter.
// Authority EXACT1: saves next player before callbacks,skips local,net pointer unguarded,drains each valid reliable handle until nonpositive or player no longer live; source is that
// net record address. Other authority values use unguarded local net handle and shared source704EF4,drain until nonpositive,without per-callback live check. Native reliable calls
// push third16384 capacity-like word, but verified callee59BC30 consumes only handle/destination and copies stored length WITHOUT capacity; do not treat extra caller word as
// protection. On ordinary completion decrements nesting BYTE and returns new byte AL. Callback may mutate player list/runtime; no received-packet size clamp here.
unsigned __int8 rf_multiplayer_receive_and_dispatch_queued_packets()
{
  _DWORD *v1; // [esp+0h] [ebp-30h]
  _DWORD *j; // [esp+10h] [ebp-20h]
  _DWORD *v3; // [esp+18h] [ebp-18h]
  char *i; // [esp+1Ch] [ebp-14h]
  int v5; // [esp+24h] [ebp-Ch]
  int v6; // [esp+24h] [ebp-Ch]
  int v7; // [esp+24h] [ebp-Ch]
  int v8[2]; // [esp+28h] [ebp-8h] BYREF

  rf_network_poll_udp_into_receive_queues();
  for ( i = (char *)&unk_77FF20 + 0x4000 * byte_78BF20[0]++;
        ;
        rf_multiplayer_dispatch_packet_envelopes((int)i, v5, (int)v8, v3) )
  {
    v5 = rf_network_receive_unreliable(i, v8);
    if ( v5 <= 0 )
      break;
    v3 = rf_player_find_by_network_endpoint((int)v8);
  }
  if ( rf_multiplayer_server_authority == 1 )
  {
    for ( j = (_DWORD *)dword_87C324; j; j = v1 )
    {
      if ( *j == dword_87C324 )
        v1 = nullptr;
      else
        v1 = (_DWORD *)*j;
      if ( j != (_DWORD *)rf_local_fpgun_player )
      {
        do
        {
          if ( *(_DWORD *)(j[1152] + 16) == -1 )
            break;
          v6 = rf_reliable_udp_receive_in_order(*(_DWORD *)(j[1152] + 16), i);
          if ( v6 <= 0 )
            break;
          rf_multiplayer_dispatch_packet_envelopes((int)i, v6, j[1152], j);
        }
        while ( rf_player_record_is_in_live_list(j) );
      }
    }
  }
  else if ( *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16) != -1 )
  {
    while ( 1 )
    {
      v7 = rf_reliable_udp_receive_in_order(*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16), i);
      if ( v7 <= 0 )
        break;
      rf_multiplayer_dispatch_packet_envelopes((int)i, v7, (int)&dword_704EF4, (_DWORD *)rf_local_fpgun_player);
    }
  }
  return --byte_78BF20[0];
}

