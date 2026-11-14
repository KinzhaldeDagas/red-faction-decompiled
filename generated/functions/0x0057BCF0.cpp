// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057BCF0 rf_vfile_find_optical_volume_and_update_root_drive
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl requested volume index or decimal9999998 (0x98967E) for any configured label. If label count exactly0 returns-1. Scans drive letters A..Z using root A:\ and GetDriveTypeA==5, then successful GetVolumeInformationA. Any-label mode compares volume name case-insensitively against configured labels, lowest matching index; specific mode directly indexes requested label without range/negative validation. First matching drive writes ONLY first byte1898C90=drive letter and returns label index. No match returns-1 and preserves previous media-root drive letter. Does not validate media contents or change root directory tail.
int __cdecl rf_vfile_find_optical_volume_and_update_root_drive(int a1)
{
  int j; // [esp+0h] [ebp-118h]
  CHAR RootPathName[4]; // [esp+4h] [ebp-114h] BYREF
  CHAR VolumeNameBuffer[260]; // [esp+8h] [ebp-110h] BYREF
  int v5; // [esp+110h] [ebp-8h]
  int i; // [esp+114h] [ebp-4h]

  *(_DWORD *)RootPathName = (char *)&loc_5C3A63 + 1;
  v5 = -1;
  if ( !dword_189CE98 )
    return -1;
  for ( i = 0; i < 26; ++i )
  {
    RootPathName[0] = i + 65;
    if ( GetDriveTypeA(RootPathName) == 5
      && GetVolumeInformationA(RootPathName, VolumeNameBuffer, 0x100u, nullptr, nullptr, nullptr, nullptr, 0) )
    {
      if ( (_UNKNOWN *)a1 == &unk_98967E )
      {
        for ( j = 0; j < dword_189CE98; ++j )
        {
          if ( !_stricmp(VolumeNameBuffer, &unk_1898D90[256 * j]) )
          {
            v5 = j;
            break;
          }
        }
      }
      else if ( !_stricmp(VolumeNameBuffer, &unk_1898D90[256 * a1]) )
      {
        v5 = a1;
      }
      if ( v5 >= 0 )
      {
        LOBYTE(dword_1898C90) = RootPathName[0];
        return v5;
      }
    }
  }
  return v5;
}

