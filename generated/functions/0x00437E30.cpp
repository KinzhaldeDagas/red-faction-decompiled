// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437E30 rf_entity_has_attached_use_turret
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl entity pointer, canonicalAL0/1 only. NULL returns0. Resolve full DWORD entity512 as ENTITY
// through433EE0; missing/non-type0 object returns0. For resolved owner call4B7C30 with ECX=owner, no stackargs, and require its full EAX shared $Use classification EXACT4 (authored
// turret). No reciprocal slot/key check, runtime turret flag requirement, self/cycle/health/authority test or mutation. ENTITY classification uses owner class660 DWORD436; raw handle
// is not treated as a pointer or tested only against-1.
bool __cdecl rf_entity_has_attached_use_turret(int a1)
{
  _DWORD *v2; // [esp+0h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 512));
  return v2 && rf_object_get_use_classification(v2) == 4;
}

