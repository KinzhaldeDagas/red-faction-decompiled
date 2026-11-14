// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004390E0 rf_entity_jeep_second_relation_resolves_object
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): One cdecl entity pointer, canonical AL0/1. NULL returns0. Authored jeep predicate ANY nonzero required; otherwise0. Calls
// unchecked552200(this=entity+2252,index=1), dereferences returned element pointer to relation pointer, then relation DWORD+4 as full COMMON-object handle. COMMON resolver any
// nonNULL returns1 else0; no ENTITY-type requirement or equality with owner/related player. No relation-array count/capacity/NULL guards and no writes. Authored flag alone does not
// guarantee second relation exists.
bool __cdecl rf_entity_jeep_second_relation_resolves_object(int a1)
{
  int v2; // eax

  if ( !a1 )
    return 0;
  if ( !rf_entity_has_jeep_flag(a1) )
    return 0;
  v2 = sub_552200((_DWORD *)(a1 + 2252), 1);
  return rf_object_resolve_handle(*(_DWORD *)(*(_DWORD *)v2 + 4)) != 0;
}

