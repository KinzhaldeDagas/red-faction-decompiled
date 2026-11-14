// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449B70 rf_geomod_network_history_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl noargs. Walks circular network-history list, saving each node's next+0 BEFORE calling history-node unlink/delete449BB0. Stops at history sentinel. Does not touch execution
// queue, active Boolean phase, saved32-byte admission records or smoke emitters. Count decreases in per-node helper, not an unconditional count reset here. No
// cycle/NULL/sentinel-integrity guard or cleanup of operation payload resources.
void rf_geomod_network_history_clear()
{
  _DWORD **i; // [esp+0h] [ebp-8h]
  _DWORD *v1; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD **)rf_geomod_network_history_head; i != &rf_geomod_network_history_head; i = (_DWORD **)v1 )
  {
    v1 = *i;
    rf_geomod_network_history_node_remove_delete(i);
  }
}

