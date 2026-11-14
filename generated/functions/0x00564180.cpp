// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564180 rf_character_cache_lookup_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl filename plus cacheByte, directly returns character_cache_get_or_load. No pooled handle, character instance, material table, filename copy or cleanup in adapter.
int __cdecl rf_character_cache_lookup_adapter(char *String1, char a2)
{
  return rf_character_cache_get_or_load(String1, a2);
}

