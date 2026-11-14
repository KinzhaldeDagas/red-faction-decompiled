// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005641F0 rf_scene_definition_cache_lookup_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Direct cdecl(filename,flags) forwarding to5B1E30. Returns shared scene/VFX definition, not model handle or runtime instance. Cache loader owns allocation/publication and fatal missing/corrupt-file path; no wrapper cleanup.
char *__cdecl rf_scene_definition_cache_lookup_adapter(char *String2, int a2)
{
  return rf_scene_definition_get_or_load_cached_vsfx(String2, a2);
}

