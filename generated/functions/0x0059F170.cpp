// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F170 rf_vpackfile_find
// UNREALRED VERIFIED [vpp-streaming] Canonicalizes a request to its final-backslash basename, hashes it, and performs case-insensitive lookup in the shared VPP member table.
int __cdecl rf_vpackfile_find(char *Str)
{
  signed int v2; // [esp+0h] [ebp-118h]
  int v3; // [esp+8h] [ebp-110h]
  int i; // [esp+Ch] [ebp-10Ch]
  char String2[260]; // [esp+10h] [ebp-108h] BYREF

  rf_path_copy_basename_after_backslash(String2, Str);
  v2 = rf_vpackfile_calc_file_name_checksum(String2);
  v3 = v2 % 20713;
  for ( i = 0; i < 20713; ++i )
  {
    if ( rf_vpackfile_lookup_table[2 * v3] == -1 )
      return 0;
    if ( rf_vpackfile_lookup_table[2 * v3] == v2 )
    {
      if ( !*(_DWORD *)(unk_1C67474[2 * v3] + 4) )
        return 0;
      if ( !_stricmp(*(const char **)(unk_1C67474[2 * v3] + 4), String2) )
        return unk_1C67474[2 * v3];
    }
    if ( ++v3 >= 20713 )
      v3 = 0;
  }
  return 0;
}

