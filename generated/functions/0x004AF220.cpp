// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AF220 rf_server_activate_peer_and_send_world_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(player), no own runtime/authority/player/net-null guard. Immediately sets player net[+4608] DWORD+12 state2, then sets connection+16 minimum resend delay333ms and sends
// GeoMod packet17 history. Traverses entity list root68211C until sentinel681E90 via object+652, delegating49A530(peer,entity) only when entity DWORD+2064 mask0x1 and common
// DWORD+124 mask0x2 are BOTH clear. Iterates signed index0..<78C248 and resolves handles78BF28[index], sending each nonnull item through4A16D0(peer,item,index). Then traverses item
// list6FB1C4 to sentinel6FAF38 via+652; when4A0580(object id+44)<0 sends4A16D0(peer,item,-1). No count clamp/null-list-node guard.
// Native clutter loop tests only emptiness against sentinel666D18 (does not count all nodes): nonempty root rf_clutter_list_head invokes4AB4F0(peer). Always calls4ABE70(peer), then
// game mode1 sends CTF packet33; game mode1 OR2 sends team-score packet53. Finally calls netgame_update packet26 helper,4AF9E0(peer),4AFB20(peer) in order, propagating final callee EAX.
// Delegated helpers not otherwise decoded here retain their existing identities; this function verifies synchronization order, filters and peer state transition, not internal
// meanings of unresolved leaf helpers.
int __cdecl rf_server_activate_peer_and_send_world_state(int a1)
{
  int v2; // [esp+0h] [ebp-1Ch]
  int i; // [esp+4h] [ebp-18h]
  int k; // [esp+8h] [ebp-14h]
  int j; // [esp+10h] [ebp-Ch]
  int v6; // [esp+14h] [ebp-8h]

  *(_DWORD *)(*(_DWORD *)(a1 + 4608) + 12) = 2;
  rf_reliable_udp_set_minimum_resend_delay(*(_DWORD *)(*(_DWORD *)(a1 + 4608) + 16), 333);
  rf_multiplayer_send_pregame_boolean_history17(a1);
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(i + 2064) & 1) == 0 && (*(_DWORD *)(i + 124) & 2) == 0 )
      rf_server_sync_entity_spawn_to_peer(a1, i);
  }
  for ( j = 0; j < dword_78C248; ++j )
  {
    v2 = rf_item_resolve_handle(dword_78BF28[j]);
    if ( v2 )
      rf_server_sync_item_create_to_peer(a1, v2, j);
  }
  for ( k = unk_6FB1C4; (_UNKNOWN *)k != &unk_6FAF38; k = *(_DWORD *)(k + 652) )
  {
    if ( rf_server_item_sync_slot_find(*(_DWORD *)(k + 44)) < 0 )
      rf_server_sync_item_create_to_peer(a1, k, -1);
  }
  if ( (_UNKNOWN *)rf_clutter_list_head != &unk_666D18 )
    rf_server_send_clutter_active_bitset_packet29(a1);
  rf_server_send_pregame_remote_charge_packet19(a1);
  v6 = rf_multiplayer_game_mode_get();
  if ( v6 == 1 )
  {
    rf_ctf_send_flag_state_packet33(a1);
LABEL_22:
    rf_server_send_team_score_packet53(a1);
    goto LABEL_23;
  }
  if ( v6 == 2 )
    goto LABEL_22;
LABEL_23:
  rf_multiplayer_send_netgame_update_packet26(a1);
  rf_server_send_pregame_glass_bitset18(a1);
  return rf_multiplayer_send_state_info_done_packet10(a1);
}

