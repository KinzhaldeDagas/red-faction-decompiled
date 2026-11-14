// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2740 rf_cd_find_optical_drive_by_marker
// UNREALRED VERIFIED [save-validation-20261028]: Enumerates A: through Z: with GetDriveTypeA==5. Successful volume query then tests RedFaction.ico/music.vpp with findfirst. Optional selector RF_1 requires icon, RF_2 requires music; null accepts either. Selector is not a volume-label comparison. Returns zero-based drive index, -1 if no optical drive, or -3 when optical drives lack accepted marker. Preserves/restores current directory.
int __cdecl rf_cd_find_optical_drive_by_marker(char *String1)
{
  char *v3; // [esp+8h] [ebp-584h]
  CHAR v4; // [esp+Fh] [ebp-57Dh]
  char *v5; // [esp+14h] [ebp-578h]
  CHAR *v6; // [esp+18h] [ebp-574h]
  char *v8; // [esp+20h] [ebp-56Ch]
  CHAR v9; // [esp+27h] [ebp-565h]
  char *v10; // [esp+2Ch] [ebp-560h]
  CHAR *v11; // [esp+30h] [ebp-55Ch]
  int v12; // [esp+34h] [ebp-558h]
  int v13; // [esp+38h] [ebp-554h] BYREF
  char FileName[516]; // [esp+3Ch] [ebp-550h] BYREF
  CHAR RootPathName[4]; // [esp+240h] [ebp-34Ch] BYREF
  CHAR Buffer[264]; // [esp+244h] [ebp-348h] BYREF
  struct _finddata64i32_t FindData; // [esp+34Ch] [ebp-240h] BYREF
  CHAR VolumeNameBuffer[260]; // [esp+474h] [ebp-118h] BYREF
  int v19; // [esp+57Ch] [ebp-10h]
  intptr_t FindHandle; // [esp+580h] [ebp-Ch]
  int i; // [esp+584h] [ebp-8h]
  int v22; // [esp+588h] [ebp-4h]

  v22 = -1;
  v19 = 0;
  GetCurrentDirectoryA(0x104u, Buffer);
  for ( i = 0; i < 26; ++i )
  {
    *(_DWORD *)RootPathName = &loc_5C3A78;
    RootPathName[0] = i + 65;
    if ( GetDriveTypeA(RootPathName) == 5 )
    {
      v22 = -3;
      if ( GetVolumeInformationA(RootPathName, VolumeNameBuffer, 0x100u, nullptr, nullptr, nullptr, nullptr, 0) )
      {
        v12 = 0;
        v13 = 0;
        memset(FileName, 0, 512);
        v11 = RootPathName;
        v10 = FileName;
        do
        {
          v9 = *v11;
          *v10++ = *v11++;
        }
        while ( v9 );
        v8 = (char *)&v13 + 3;
        while ( *++v8 )
          ;
        strcpy(v8, "RedFaction.ico");
        FindHandle = _findfirst64i32(FileName, &FindData);
        if ( FindHandle != -1 )
        {
          v12 = 1;
          _findclose(FindHandle);
        }
        v6 = RootPathName;
        v5 = FileName;
        do
        {
          v4 = *v6;
          *v5++ = *v6++;
        }
        while ( v4 );
        v3 = (char *)&v13 + 3;
        while ( *++v3 )
          ;
        strcpy(v3, "music.vpp");
        FindHandle = _findfirst64i32(FileName, &FindData);
        if ( FindHandle != -1 )
        {
          v13 = 1;
          _findclose(FindHandle);
        }
        if ( String1 )
        {
          if ( !_stricmp(String1, "RF_1") && v12 )
            v19 = 1;
          if ( !_stricmp(String1, "RF_2") && v13 )
            v19 = 1;
        }
        else if ( v12 || v13 )
        {
          v19 = 1;
        }
        if ( v19 )
        {
          v22 = i;
          break;
        }
      }
    }
  }
  SetCurrentDirectoryA(Buffer);
  return v22;
}

