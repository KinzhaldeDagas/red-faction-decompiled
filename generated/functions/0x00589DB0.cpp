// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589DB0 rf_character_cache_mark_record_retained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): ORs flags DWORD+68 with0x10 and returns record pointer bits. No loaded/pointer validation or resource allocation.
int __cdecl rf_character_cache_mark_record_retained(int a1)
{
  *(_DWORD *)(a1 + 68) |= 0x10u;
  return a1;
}

