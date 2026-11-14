// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004118D0 rf_entity_view_copy_referenced_position
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl destination vector,view-wrapper pointer. Dereferences wrapper DWORD0 to entity pointer, copies three-float position from entity+60 into destination, returns destination unchanged. No own wrapper/entity/destination NULL checks or source-state changes. Used by thermal screen camera fallback.
float *__cdecl rf_entity_view_copy_referenced_position(float *a1, int a2)
{
  rf_vector3_copy_return_destination(a1, (float *)(*(_DWORD *)a2 + 60));
  return a1;
}

