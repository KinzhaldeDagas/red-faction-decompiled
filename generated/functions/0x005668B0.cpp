// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005668B0 rf_character_cache_contains_filename_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): cdecl filename directly forwards character-cache contains-loaded-filename helper. Does not load, canonicalize or return a model handle; raw delegate result.
int __cdecl rf_character_cache_contains_filename_adapter(char *a1)
{
  return rf_character_cache_contains_loaded_filename(a1);
}

