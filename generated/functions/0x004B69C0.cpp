// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B69C0 rf_file_transfer_route_received_payload
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): Recovered [4B69C0,4B6A35). Cdecl(payload,sourceEndpoint), TWO consumed args. Client runtime1/authority0 chooses
// localPlayer.net4608 reliable handle+16 without local/net guard and ignores source here. All other role values resolve source player; missing ->return, otherwise unguarded
// source.net+16. Handle EXACT-1 skips, any other value calls file_transfer_dispatch_packet(payload,handle) with8-byte caller cleanup. No own packet length, buffer validation,
// net-state/connection test, transfer allocation or normalized return.
void __cdecl rf_file_transfer_route_received_payload(void *a1, void *a2)
{
  _DWORD *v2; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
  {
    v2 = rf_player_find_by_network_endpoint((int)a2);
    if ( !v2 )
      return;
    v3 = *(_DWORD *)(v2[1152] + 16);
  }
  else
  {
    v3 = *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 16);
  }
  if ( v3 != -1 )
    rf_file_transfer_dispatch_packet((char *)a1, v3);
}

