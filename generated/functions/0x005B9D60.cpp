// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9D60 rf_v3c_cache_contains_filename
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Scans pointer cache1D6D250 up to count1D6DA20 and _stricmp(entry,name)==0 returns1,else0. Does not canonicalize extension/path or skip NULL slots before comparison. No load/retention mutation/null-name guard.
int __cdecl rf_v3c_cache_contains_filename(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_1D6DA20; ++i )
  {
    if ( !_stricmp((&unk_1D6D250)[i], String2) )
      return 1;
  }
  return 0;
}

