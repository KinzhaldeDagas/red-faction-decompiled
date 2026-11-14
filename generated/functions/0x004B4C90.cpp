// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4C90 rf_server_apply_pong_callback25
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Recovered [4B4C90,4B4CE4), cdecl(unused payload,source endpoint). Runtime1/authority EXACT1 finds player by source; if found and net+4608 nonnull invokes
// net_statistics_accept_latency_response(net+28). No payload access/length check,local exclusion,handle/state2 guard or own outstanding-probe check. Delegate handles missing
// outstanding stamp by still arming1200ms retry. Descriptor25 is pong; this is separate from state-update26.
void __cdecl rf_server_apply_pong_callback25(const void *payload, const void *sender)
{
  _DWORD *v2; // [esp+0h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v2 = rf_player_find_by_network_endpoint((int)sender);
    if ( v2 )
    {
      if ( v2[1152] )
        rf_net_statistics_accept_latency_response((int *)(v2[1152] + 28));
    }
  }
}

