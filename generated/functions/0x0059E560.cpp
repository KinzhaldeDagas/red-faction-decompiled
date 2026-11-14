// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E560 rf_registry_read_dword_or_default
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional section,value name,DWORD output,fallback DWORD. Raw reader requests4bytes and ignores registry type/actual length. Query success0 returns0 even if fewer than4 bytes; zero-fill supplies remaining bytes. Failure stores fallback and returns-1. No pointer validation or integer parsing.
int __cdecl rf_registry_read_dword_or_default(char *String1, LPCSTR lpValueName, LPBYTE lpData, int a4)
{
  if ( !rf_registry_read_raw_value(String1, lpValueName, lpData, 4u) )
    return 0;
  *(_DWORD *)lpData = a4;
  return -1;
}

