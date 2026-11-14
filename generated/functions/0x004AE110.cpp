// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE110 rf_server_process_respawn_request_packet_14
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Original descriptor14 at6629F0. Cdecl payload pointer; dispatcher source argument ignored, length not supplied. Only runtime1 authority EXACT1. Read raw signed selectionDWORD0 then
// unsigned networkID BYTE4, find player by THAT claimed ID. No binding between source endpoint and selected player's net record in this body (older 'connection-owned' comment
// corrected). Missing player returns. Resolve current player handle+20; missing object ALLOWS respawn. If object exists, require object_is_entity and entity_is_dead both nonzero AL;
// other object/live entity rejects. On admission store raw selection Player+3932 without range validation, call server_respawn_player. No local/default character canonicalization or
// packet-size guard here. Nominal char result is AL residue/delegate, not consistent request status.
char __cdecl rf_server_process_respawn_request_packet_14(int *a1)
{
  _DWORD *v1; // eax
  int v3; // [esp+0h] [ebp-14h]
  int v4; // [esp+8h] [ebp-Ch]
  int v5; // [esp+Ch] [ebp-8h]

  LOBYTE(v1) = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v4 = *a1;
    v1 = rf_player_find_by_network_id(*((_BYTE *)a1 + 4));
    v5 = (int)v1;
    if ( v1 )
    {
      v3 = rf_object_resolve_handle(v1[5]);
      if ( !v3 || (LOBYTE(v1) = rf_object_is_entity(v3), (_BYTE)v1) && (LOBYTE(v1) = rf_entity_is_dead(v3), (_BYTE)v1) )
      {
        *(_DWORD *)(v5 + 3932) = v4;
        LOBYTE(v1) = (unsigned __int8)rf_server_respawn_player(v5);
      }
    }
  }
  return (char)v1;
}

