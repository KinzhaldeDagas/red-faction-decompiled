// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574D20 rf_bitmap_find_loaded_handle_by_name
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Computes0x574DD0 hash, linearly probes pointer hash table0x189734C with signed index%(slotcount0x663F14+1) until null. Match requires record hash DWORD+32 equality AND case-insensitive full string comparison; returns record stored handle+36. Null table entry returns-1. No probe limit/tombstone handling, null name or negative-hash correction. Does not load file, change references or resolve animation time.
int __cdecl rf_bitmap_find_loaded_handle_by_name(char *String2)
{
  char *String1; // [esp+4h] [ebp-Ch]
  signed int v3; // [esp+8h] [ebp-8h]
  signed int v4; // [esp+Ch] [ebp-4h]

  v3 = rf_bitmap_name_hash_rotate6_lower_abs(String2);
  v4 = v3;
  for ( String1 = *((char **)dword_189734C + v3 % (dword_663F14 + 1));
        String1;
        String1 = *((char **)dword_189734C + v4 % (dword_663F14 + 1)) )
  {
    if ( *((_DWORD *)String1 + 8) == v3 && !_stricmp(String1, String2) )
      return *(_DWORD *)(dword_1897344 + 108 * ((int)&String1[-dword_1897344] / 108) + 36);
    ++v4;
  }
  return -1;
}

