// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9DB0 rf_v3c_cache_mark_all_retained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): For each nonnull cache1D6D250 entry below count1D6DA20, ORs asset DWORD140 with1 via5BA010. No bit clearing, loading, refcount or slot compaction. EAX loop bookkeeping/undefined for empty list, not success.
int rf_v3c_cache_mark_all_retained()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_1D6DA20; ++i )
  {
    if ( (&unk_1D6D250)[i] )
      rf_v3c_asset_set_flag1((&unk_1D6D250)[i]);
    result = i + 1;
  }
  return result;
}

