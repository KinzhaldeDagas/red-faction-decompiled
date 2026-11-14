// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592700 rf_vfile_enumerate_registered_loose_files
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: Only592830 registered loose-key producer: direct root *.* FindData.name BASENAMES, lowercase, skip directories, extension-mask admit.592550 lowercases COMPLETErequest and5925C0 exactcompares key. Therefore relative BACKSLASH-qualified canonical requests miss loose table and proceed to VPP final-backslash basename, matching host VPP-only qualified path. No trim; forwardslash/highbyte normalization remains a separate domain.
intptr_t __cdecl rf_vfile_enumerate_registered_loose_files(int a1)
{
  intptr_t result; // eax
  char *SubStr; // [esp+0h] [ebp-538h]
  intptr_t FindHandle; // [esp+4h] [ebp-534h]
  struct _finddata64i32_t FindData; // [esp+8h] [ebp-530h] BYREF
  char FileName[1028]; // [esp+130h] [ebp-408h] BYREF

  rf_vfile_build_loose_path(a1, "*.*", FileName);
  rf_cstring_lowercase_in_place(FileName);
  result = _findfirst64i32(FileName, &FindData);
  FindHandle = result;
  if ( result >= 0 )
  {
    do
    {
      if ( FindData.name[0] != 46 )
      {
        rf_cstring_lowercase_in_place(FindData.name);
        if ( (FindData.attrib & 0x10) == 0 )
        {
          SubStr = rf_cstring_find_first_character(FindData.name, 46);
          if ( SubStr )
          {
            if ( rf_cstring_find_first_substring((char *)dword_1897494[3 * a1], SubStr) )
            {
              rf_vfile_loose_lookup_find_or_insert_mixed_return(FindData.name, a1);
              ++unk_1BA1EF8;
            }
          }
        }
      }
    }
    while ( !_findnext64i32(FindHandle, &FindData) );
    return _findclose(FindHandle);
  }
  return result;
}

