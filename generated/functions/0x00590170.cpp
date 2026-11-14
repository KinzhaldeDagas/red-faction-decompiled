// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590170 rf_sound_find_sample_index_by_name
// UNREALRED VERIFIED [dsound-creation-20261028]: Computes0x590120 case-sensitive hash; scans indices0..registry count0x1BA1818-1,requires hash+516 equality AND case-insensitive name comparison. Returns first index or-1. Case-only variants can miss because their hashes differ. Does not check file path,source offset,mode,reference count or buffer occupancy.
int __cdecl rf_sound_find_sample_index_by_name(char *String2)
{
  int v2; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v2 = rf_sound_name_hash_rotate6_case_sensitive(String2);
  for ( i = 0; i < unk_1BA1818; ++i )
  {
    if ( unk_1951A0C[148 * i] == v2 && !_stricmp((const char *)&unk_1951808 + 592 * i, String2) )
      return i;
  }
  return -1;
}

