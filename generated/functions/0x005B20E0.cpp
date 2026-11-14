// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B20E0 rf_scene_cache_mark_definition_retained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): cdecl definition pointer forwards5B7F10 OR of DWORD304 with1 and returns definition. No membership/refcount/null checks.
_DWORD *__cdecl rf_scene_cache_mark_definition_retained(_DWORD *a1)
{
  return rf_scene_definition_set_retained_flag1(a1);
}

