// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C660 rf_entity_clear_state814_mask20000
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(entity), no null/type/mode guard. Clears ONLY mask20000 in entity DWORD+2068(814h),returns entity in EAX. Does not clear40000 or any other field; gameplay meaning not
// inferred.
int __cdecl rf_entity_clear_state814_mask20000(int a1)
{
  *(_DWORD *)(a1 + 2068) &= ~0x20000u;
  return a1;
}

