// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462230 rf_browser_add_favorite_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Cdecl(rawRow). Require signed0<=row<liveCount. Set live favorite flag80000000 BEFORE lookup/capacity test. Existing endpoint returns without updating favorite metadata. Miss
// and signed favoriteCount<512:export row100 to stack,increment count,carry/swap100-byte records from insertion index to newCount-1,reading old unused tail slot then discarding final
// carry. Full favorites still leaves live flag set;no rollback,allocation,storageNULL/negative favoriteCount guard,disk write or display rebuild. Endpoint order maintained by
// verified binary-search insertion position.
void __cdecl rf_browser_add_favorite_row(int a1)
{
  int i; // [esp+8h] [ebp-DCh]
  _BYTE v2[104]; // [esp+Ch] [ebp-D8h] BYREF
  _BYTE v3[100]; // [esp+74h] [ebp-70h] BYREF
  int v4; // [esp+E0h] [ebp-4h] BYREF

  if ( a1 >= 0 && a1 < unk_6F51A8 )
  {
    *((_DWORD *)dword_6F52CC + 27 * a1 + 26) |= 0x80000000;
    if ( !rf_endpoint_array100_find_or_insertion_index(
            *((_DWORD *)dword_6F52CC + 27 * a1 + 21),
            *((_DWORD *)dword_6F52CC + 27 * a1 + 22),
            &v4)
      && dword_6F52EC < 512 )
    {
      rf_browser_export_row_to_cache100(a1, (int)v2);
      ++dword_6F52EC;
      for ( i = v4; i < dword_6F52EC; ++i )
      {
        qmemcpy(v3, (const void *)(unk_6F52E8 + 100 * i), sizeof(v3));
        qmemcpy((void *)(unk_6F52E8 + 100 * i), v2, 0x64u);
        qmemcpy(v2, v3, 0x64u);
      }
    }
  }
}

