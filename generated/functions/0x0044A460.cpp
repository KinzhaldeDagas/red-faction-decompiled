// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A460 rf_geomod_cutter_registry_find_or_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, embedded cutter literal geometry,all vertex/index/UV words and registry/procedural accessors,original ECX/stack flow and PE bytes): Cdecl name C string,caller pops4,returns integer registry INDEX. Signed scan0..global count6EDEDC-1 of12-byte records at6EDEE0: compare record string case-insensitively,return first matching index immediately without inspecting cached solid pointer. On miss assign name to current record string, call53AD10(name),store resulting pointer (includingNULL) at6EDEE8+12*CURRENTglobalCount,increment count,returncount-1. Constructor call occurs BEFORE countincrement; raw code rereads count after call. Unknown names therefore still consume entries and cachedNULL match is NOT retried. No capacity check,loading from disk,solid clone,duplicate insertion on ordinary match,NULL-name guard,locking or
// rollback of assigned string on downstream failure. Record owns string and cachedpointer; this body does not destroy prior solids.
int __cdecl rf_geomod_cutter_registry_find_or_append(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_6EDEDC; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)&byte_6EDEE0[12 * i], String2) )
      return i;
  }
  rf_string_assign_from_cstr(&byte_6EDEE0[12 * dword_6EDEDC], String2);
  unk_6EDEE8[3 * dword_6EDEDC++] = (int)rf_geomod_embedded_cutter_create(String2);
  return dword_6EDEDC - 1;
}

