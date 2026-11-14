// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A0460 rf_network_flush_all_reliable_queues
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Recovered original function [4A0460,4A04C5), no arguments, caller-cleaned RET. Traverses circular player-list87C324 via DWORD0 to root repeat/null, skipping local player only when
// authority byte EXACTLY1. Calls flush_player_reliable_queue for admitted players, with no own runtime/state/net-pointer guard. No static incoming xrefs currently. No stable semantic
// result; this is distinct from combined flush_all_player_queues, whose local-player policy differs.
void __cdecl rf_network_flush_all_reliable_queues()
{
  _DWORD *v0; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)dword_87C324; i; i = v0 )
  {
    if ( rf_multiplayer_server_authority != 1 || i != (_DWORD *)rf_local_fpgun_player )
      rf_network_flush_player_reliable_queue((int)i);
    if ( *i == dword_87C324 )
      v0 = nullptr;
    else
      v0 = (_DWORD *)*i;
  }
}

