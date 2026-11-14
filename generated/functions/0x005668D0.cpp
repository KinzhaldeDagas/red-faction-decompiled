// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005668D0 rf_v3c_cache_contains_filename_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): cdecl filename forwards5B9D60 case-insensitive current-cache lookup. No .v3m normalization/reload, retention mark or instance allocation.
int __cdecl rf_v3c_cache_contains_filename_adapter(char *String2)
{
  return rf_v3c_cache_contains_filename(String2);
}

