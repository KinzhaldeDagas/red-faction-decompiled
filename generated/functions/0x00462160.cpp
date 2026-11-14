// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462160 rf_browser_remove_favorite_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Cdecl(rawRow). Require signed0<=row<liveCount6F51A8. Clear live flagsDWORD104 high80000000 BEFORE binary endpoint lookup in100-byte favorite array6F52E8/count6F52EC. Lookup
// receives IPv4DWORD84 and DWORD88 (helper compares lowWORD port). Hit:decrement favoriteCount,shift successive100-byte records left using25 DWORD copies each. Miss leaves live
// favorite flag cleared. No own storage/count/capacity validation,cache write,display rebuild or rollback.
void __cdecl rf_browser_remove_favorite_row(int a1)
{
  int i; // [esp+8h] [ebp-8h]
  int v2; // [esp+Ch] [ebp-4h] BYREF

  if ( a1 >= 0 && a1 < unk_6F51A8 )
  {
    *((_DWORD *)dword_6F52CC + 27 * a1 + 26) &= ~0x80000000;
    if ( rf_endpoint_array100_find_or_insertion_index(
           *((_DWORD *)dword_6F52CC + 27 * a1 + 21),
           *((_DWORD *)dword_6F52CC + 27 * a1 + 22),
           &v2) )
    {
      --dword_6F52EC;
      for ( i = v2; i < dword_6F52EC; ++i )
        qmemcpy((void *)(unk_6F52E8 + 100 * i), (const void *)(unk_6F52E8 + 100 * (i + 1)), 0x64u);
    }
  }
}

