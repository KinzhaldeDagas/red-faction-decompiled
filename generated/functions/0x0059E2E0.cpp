// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E2E0 rf_registry_read_cstring
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional section,value name,destination C string buffer. Reads1024 raw bytes into1028-byte local; failure-1 leaves destination unchanged. Success copies through first NUL without destination bound,returns0. Raw reader checks no registry type and does not force NUL after full-size value,so scanning may pass initialized data. No default fallback here.
int __cdecl rf_registry_read_cstring(char *String1, LPCSTR lpValueName, _BYTE *a3)
{
  BYTE v3; // al
  BYTE *v6; // [esp+Ch] [ebp-40Ch]
  BYTE Data[1028]; // [esp+10h] [ebp-408h] BYREF

  if ( rf_registry_read_raw_value(String1, lpValueName, Data, 0x400u) )
    return -1;
  v6 = Data;
  do
  {
    v3 = *v6;
    *a3++ = *v6++;
  }
  while ( v3 );
  return 0;
}

