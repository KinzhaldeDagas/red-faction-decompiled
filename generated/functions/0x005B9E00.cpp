// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9E00 rf_v3c_cache_release_unretained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Scans original V3C count. Nonnull entries with asset DWORD140&1 stay,compacted in original order to next retained slot;unmarked entries deleted with flags1 and nulled. Retained bit unchanged. Final count=OLD count minus number DELETED,not retained-prefix length; existing NULL holes therefore are not subtracted and can remain inside logical count. Does not repair model handles still pointing at deleted assets; EAX scan bookkeeping.
int rf_v3c_cache_release_unretained()
{
  int result; // eax
  int v1; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int v3; // [esp+14h] [ebp-4h]

  v3 = 0;
  v1 = 0;
  for ( i = 0; i < unk_1D6DA20; ++i )
  {
    if ( (&unk_1D6D250)[i] )
    {
      if ( (unsigned __int8)rf_v3c_asset_test_flag1((&unk_1D6D250)[i]) )
      {
        if ( v1 < i )
        {
          (&unk_1D6D250)[v1] = (&unk_1D6D250)[i];
          (&unk_1D6D250)[i] = nullptr;
        }
        ++v1;
      }
      else
      {
        if ( (&unk_1D6D250)[i] )
          rf_v3c_asset_base_scalar_deleting_destructor((&unk_1D6D250)[i], 1);
        (&unk_1D6D250)[i] = nullptr;
        ++v3;
      }
    }
    result = i + 1;
  }
  unk_1D6DA20 -= v3;
  return result;
}

