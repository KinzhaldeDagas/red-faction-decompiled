// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9F00 rf_v3c_cache_mark_asset_retained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): cdecl asset pointer forwards5BA010 OR of DWORD140 with1 and returns asset. No cache membership test, refcount increment or pointer validation.
_DWORD *__cdecl rf_v3c_cache_mark_asset_retained(_DWORD *a1)
{
  return rf_v3c_asset_set_flag1(a1);
}

