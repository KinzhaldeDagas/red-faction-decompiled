// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004118F0 rf_entity_view_copy_referenced_matrix_2016
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl destination matrix,view-wrapper pointer. Dereferences wrapper DWORD0 to entity pointer, copy-constructs nine-float matrix from entity+2016 into destination, returns destination unchanged. No own wrapper/entity/destination NULL checks or state changes to source. Used by thermal screen camera fallback.
int __cdecl rf_entity_view_copy_referenced_matrix_2016(int a1, _DWORD *a2)
{
  rf_matrix3_copy_construct(a1, (const void *)(*a2 + 2016));
  return a1;
}

