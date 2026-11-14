// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C6D0 rf_entity_clear_state814_mask40000
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(entity), no null/type/mode guard. Clears ONLY mask40000 in entity DWORD+2068(814h),returns entity in EAX. No allocation/network send or20000 clear.
int __cdecl rf_entity_clear_state814_mask40000(int a1)
{
  *(_DWORD *)(a1 + 2068) &= ~0x40000u;
  return a1;
}

