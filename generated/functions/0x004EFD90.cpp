// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EFD90 rf_localization_copy_escaped_string_without_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl source C string. Calls escaped-string pool store with index-1, so no indexed-table publication; returns its pointer orNULL. Shares its cursor, capacity arithmetic, escape handling and lack of explicit destination NUL termination.
_BYTE *__cdecl rf_localization_copy_escaped_string_without_index(const char *a1)
{
  return rf_localization_store_escaped_string(a1, -1);
}

