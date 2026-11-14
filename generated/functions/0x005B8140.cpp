// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8140 rf_v3c_asset_cache_release_all
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Loops global pointer cache1D6D250 up to count1D6DA20; for each nonnull entry invokes V3C base scalar-deleting destructor withflags1 and zeros slot. Sets count0. Does not free array storage, reset other cache globals or deduplicate shared pointers; return EAX incidental1/index/deleter result.
int rf_v3c_asset_cache_release_all()
{
  int result; // eax
  int i; // [esp+Ch] [ebp-4h]

  result = 1;
  for ( i = 0; i < unk_1D6DA20; ++i )
  {
    result = i;
    if ( (&unk_1D6D250)[i] )
    {
      result = (int)(&unk_1D6D250)[i];
      if ( result )
        result = (int)rf_v3c_asset_base_scalar_deleting_destructor((&unk_1D6D250)[i], 1);
      (&unk_1D6D250)[i] = nullptr;
    }
  }
  unk_1D6DA20 = 0;
  return result;
}

