// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EFC70 rf_localization_get_string_pointer_slot
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl default C string,index. Returns ADDRESS OF POINTER SLOT, not string contents. Signed index>=0 returns88D438+4*index without bounds/NULL/loaded checks and ignores default string. Negative index first stores literal fallback string and returns88C498+4*returnedFallbackIndex. If fallback store fails returning0, returns fallback slot0 after that helper has already published/incremented its attempted entry; no own failure test.
int __cdecl rf_localization_get_string_pointer_slot(const char *a1, int a2)
{
  if ( a2 >= 0 )
    return 4 * a2 + 8967224;
  else
    return 4 * rf_localization_store_literal_fallback_string(a1) + 8963224;
}

