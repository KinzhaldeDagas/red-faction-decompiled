// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449BB0 rf_geomod_network_history_node_remove_delete
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl node pointer. Unlinks next0/prev4, clears those links, raw operator delete(node), decrements network-history count. Unlike execution-queue node destructor, NEVER
// reads/destroys six trailing DWORDs108..131: history nodes share132-byte allocation but do not initialize/own those smoke fields. Operation100 payload is non-owning data. No
// pointer/list/count validation, active-operation cancellation or sound/particle cleanup.
void __cdecl rf_geomod_network_history_node_remove_delete(_DWORD **a1)
{
  *a1[1] = *a1;
  (*a1)[1] = a1[1];
  *a1 = nullptr;
  a1[1] = nullptr;
  operator delete(a1);
  --rf_geomod_network_history_count;
}

