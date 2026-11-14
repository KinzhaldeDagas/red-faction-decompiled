// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589B30 rf_character_cache_release_and_clear_loaded
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Calls full record release588100 then redundantly clears loaded bit1 in flags+68 and returns original pointer bits in EAX. Release already resets all flags; this wrapper adds no shared-reference accounting of its own.
int __cdecl rf_character_cache_release_and_clear_loaded(int a1)
{
  rf_character_record_release_resources(a1);
  *(_DWORD *)(a1 + 68) &= ~1u;
  return a1;
}

