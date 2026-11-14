// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589D90 rf_character_cache_release_record_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Thin cdecl wrapper around full record release588100. Returns that helper EAX; no extra flag, reference or NULL checks.
int __cdecl rf_character_cache_release_record_wrapper(int a1)
{
  return rf_character_record_release_resources(a1);
}

