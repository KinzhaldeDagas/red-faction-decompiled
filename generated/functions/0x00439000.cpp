// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00439000 rf_entity_is_parent_jeep_relation0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl entity pointer, canonicalAL0/1. NULL0. ENTITY-resolve raw full handle entity+512; authored jeep
// predicate ANYnonzero required (its NULL-owner result0 handles failed resolve). Unchecked pointer-array accessor(parent+2252,index0) yields relation pointer; return1 iff relation
// DWORD4 equals input entity full handle44, else0. No parent array count/entry NULL check, key test, COMMON child re-resolution, player identity or driver/passenger label inferred.
// No writes. This is reciprocal raw-handle equality for a particular parent relation, not own-jeep relation existence4390E0.
bool __cdecl rf_entity_is_parent_jeep_relation0(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 512));
  return rf_entity_has_jeep_flag(v2)
      && *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(v2 + 2252), 0) + 4) == *(_DWORD *)(a1 + 44);
}

