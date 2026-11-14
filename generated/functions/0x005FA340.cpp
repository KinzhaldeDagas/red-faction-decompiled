// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA340 rf_bluebeard_sound_metadata_find
// UNREALRED VERIFIED [mission-mover-effects-20261013] Looks up the bluebeard sound metadata. Normal sorted path bsearch uses0x5FA4A0, which compares basenames ignoring Windows directories and case. Unsorted fallback uses full string comparison. Caller0x5C0220 falls back to static record0x664940; RF.exe bytes there have loop flags+0xA8=0 and status+0xAC=0x100003E8.
// UNREALRED VERIFIED [combat-native-pickup-source-20261111] Lookup miss returns null;5C0220 substitutes static664940 whose loop flags are0. A known absent optional table/record is nonlooping metadata, not successful PCM playback. Host centralized resolver distinguishes proved absent source entry from index/read/parse failure; its source/world/request fences prevent stale or nested publication from becoming current.
_DWORD *__cdecl rf_bluebeard_sound_metadata_find(char *String1)
{
  char v2; // al
  _BYTE *v3; // [esp+8h] [ebp-CCh]
  char *v4; // [esp+Ch] [ebp-C8h]
  _DWORD *v5; // [esp+10h] [ebp-C4h]
  _BYTE Key[184]; // [esp+14h] [ebp-C0h] BYREF
  int i; // [esp+D0h] [ebp-4h]

  if ( unk_1F6D24B )
  {
    v4 = String1;
    v3 = Key;
    do
    {
      v2 = *v4;
      *v3++ = *v4++;
    }
    while ( v2 );
    v5 = bsearch(
           Key,
           &unk_1F6D330,
           0x1000u,
           0xB4u,
           (_CoreCrtNonSecureSearchSortCompareFunction)rf_bluebeard_sound_basename_compare);
    if ( !v5 || (v5[43] & 0x10000000) != 0 )
      return v5;
    else
      return nullptr;
  }
  else
  {
    for ( i = 0; i < 4096; ++i )
    {
      if ( (unk_1F6D3DC[45 * i] & 0x10000000) != 0 && !_stricmp(String1, (const char *)&unk_1F6D330 + 180 * i) )
        return (_DWORD *)((char *)&unk_1F6D330 + 180 * i);
    }
    return nullptr;
  }
}

