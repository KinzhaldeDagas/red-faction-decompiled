// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E910 rf_vpackfile_add_to_lookup_table
// UNREALRED VERIFIED [vpp-streaming] Open-addresses the 20,713-slot filename table. Case-insensitive equal names replace the stored entry pointer, so the later member wins.
int __cdecl rf_vpackfile_add_to_lookup_table(int a1)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = *(_DWORD *)a1 / 20713;
  v2 = *(_DWORD *)a1 % 20713;
  for ( i = 0; i < 20713; ++i )
  {
    if ( rf_vpackfile_lookup_table[2 * v2] == -1 )
    {
      rf_vpackfile_lookup_table[2 * v2] = *(_DWORD *)a1;
      unk_1C67474[2 * v2] = a1;
      return a1;
    }
    if ( !_stricmp(*(const char **)(unk_1C67474[2 * v2] + 4), *(const char **)(a1 + 4)) )
    {
      unk_1C67474[2 * v2] = a1;
      return v2;
    }
    if ( ++v2 >= 20713 )
      v2 = 0;
    result = i + 1;
  }
  return result;
}

