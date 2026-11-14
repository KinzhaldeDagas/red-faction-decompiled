// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449EA0 rf_geomod_execution_queue_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl noargs. Walks pending circular queue, snapshots current next before remove_destroy449EE0, stops at sentinel. Per-node helper decrements count and destroys associated smoke
// emitters. Does not explicitly reset execution-active BYTE, elapsed timer, Boolean phase or saved/network histories. Empty-list EAX is head/sentinel value; nonempty normal clear
// returns final per-node remaining count, not uniform success. No snapshot of full list or integrity guard.
int rf_geomod_execution_queue_clear()
{
  int result; // eax
  _DWORD **i; // [esp+0h] [ebp-8h]
  _DWORD *v2; // [esp+4h] [ebp-4h]

  result = rf_geomod_execution_queue_head;
  for ( i = (_DWORD **)rf_geomod_execution_queue_head; i != &rf_geomod_execution_queue_head; i = (_DWORD **)v2 )
  {
    v2 = *i;
    result = rf_geomod_execution_queue_node_remove_destroy(i);
  }
  return result;
}

