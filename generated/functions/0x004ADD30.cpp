// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ADD30 rf_multiplayer_apply_rate_change_payload27
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Recovered native function4ADD30..4ADDDA (RET4ADDD9), original descriptor27 at662A8C. Cdecl payload pointer; dispatcher-supplied source extra stack word ignored, no payload length.
// Read networkID BYTE0 and rate WORD1, zero-extend rate. Find player by claimed networkID; if found unguarded net1200 write DWORD2492=rate. This update precedes ANY runtime/authority
// gate and has no minimum/maximum clamp. Then only runtime1 authority EXACT1: invoke broadcast wrapper4ADD00(id,rate) EVEN IF player lookup failed, then interval_recompute(player)
// even if NULL (delegate handles own admission). Local-pointer gate inside broadcast wrapper still applies. No sender-to-playerID binding, input size validation, change-only
// suppression or registry update. No meaningful return value in callback.
void __cdecl rf_multiplayer_apply_rate_change_payload27(const unsigned __int8 *payload)
{
  unsigned __int16 v1; // [esp+0h] [ebp-10h]
  unsigned __int8 v2; // [esp+7h] [ebp-9h]
  _DWORD *v3; // [esp+8h] [ebp-8h]

  v2 = *payload;
  v1 = *(_WORD *)(payload + 1);
  v3 = rf_player_find_by_network_id(*payload);
  if ( v3 )
    *(_DWORD *)(v3[1152] + 2492) = v1;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    rf_multiplayer_broadcast_rate_change_if_local27(v2, v1);
    rf_multiplayer_peer_update_interval_recompute((int)v3);
  }
}

