// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589B60 rf_character_cache_release_unpinned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Recovered no-argument sweep across64 slots. For loaded bit1 set and pin bit2 clear, calls589B30. Unlike5898E0 this pass tests bit2, not bit8. Does not return freed-count statistics.
void __cdecl rf_character_cache_release_unpinned()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    if ( (dword_18D0A74[1686 * i] & 1) != 0 && (dword_18D0A74[1686 * i] & 2) == 0 )
      rf_character_cache_release_and_clear_loaded((int)&byte_18D0A30[6744 * i]);
  }
}

