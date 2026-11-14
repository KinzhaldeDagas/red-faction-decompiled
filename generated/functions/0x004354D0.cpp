// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004354D0 rf_entity_has_record_at974_or964
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity), canonicalAL0/1. First DWORD entity+2420(0x974)!=EXACT-1 admits1 immediately, otherwise
// DWORD+2404(0x964)!=-1 admits1; both-1 yields0. All other negative values count present. No active-animation/model/index validity query, class lookup, NULL guard or writes. UpperEAX
// incidental; not a general alive/ready predicate.
bool __cdecl rf_entity_has_record_at974_or964(int a1)
{
  return *(_DWORD *)(a1 + 2420) != -1 || *(_DWORD *)(a1 + 2404) != -1;
}

