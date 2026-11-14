// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9F10 rf_v3c_cache_remove_pointer_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Scans cache for FIRST exact pointer match; destroys matched nonnull asset withflags1,zeros slot,shifts following entries left. Regardless whether pointer FOUND, writesNULL at slot OLD count,then reloads count and decrements it. Thus absent pointer still drops logical last entry; empty cache becomes count-1. Clears slot OLD count rather than new last slot,leaving duplicate/stale old-last pointer beyond shortened prefix after normal removal. No retained/refcount/null/size guards; EAX old scan bound,not success.
int __cdecl rf_v3c_cache_remove_pointer_unchecked(char *a1)
{
  int result; // eax
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < unk_1D6DA20; ++i )
  {
    if ( (&unk_1D6D250)[i] == a1 )
    {
      if ( (&unk_1D6D250)[i] )
        rf_v3c_asset_base_scalar_deleting_destructor((&unk_1D6D250)[i], 1);
      (&unk_1D6D250)[i] = nullptr;
      break;
    }
  }
  while ( 1 )
  {
    result = unk_1D6DA20 - 1;
    if ( i >= unk_1D6DA20 - 1 )
      break;
    (&unk_1D6D250)[i] = (char *)unk_1D6D254[i];
    ++i;
  }
  (&unk_1D6D250)[unk_1D6DA20--] = nullptr;
  return result;
}

