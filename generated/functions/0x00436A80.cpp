// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436A80 rf_entity_has_attached_use_vehicle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Cdecl entity pointer, AL bool. Null entity false; otherwise resolves ENTITY+512 handle with entity resolver and returns true only when resolved object exists and shared Use classifier0x4B7C30 returns EXACT integer1. No recursive attachment walk, class-name test, common+48 owner lookup or entity mutation. Resolved pointer class fields are not additionally checked by this predicate.
bool __cdecl rf_entity_has_attached_use_vehicle(int a1)
{
  _DWORD *v2; // [esp+0h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 512));
  return v2 && rf_object_get_use_classification(v2) == 1;
}

