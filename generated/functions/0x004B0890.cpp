// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0890 rf_multiplayer_apply_client_in_game_payload11
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Recovered4B0890..4B08EA, lastRET4B08E9; descriptor11. Cdecl payload pointer only consumed; source extra word ignored. Read unsigned networkID BYTE0,
// find player by claimed ID. If found unguarded player.net4608, OR netflagsDWORD8 with mask0x8; missing player no store. No runtime/server/source ownership/state/length checks,
// duplicate suppression, response or new entity creation. No meaningful callback return.
void __cdecl rf_multiplayer_apply_client_in_game_payload11(const unsigned __int8 *payload)
{
  _DWORD *v1; // [esp+4h] [ebp-8h]

  v1 = rf_player_find_by_network_id(*payload);
  if ( v1 )
    *(_DWORD *)(v1[1152] + 8) |= 8u;
}

