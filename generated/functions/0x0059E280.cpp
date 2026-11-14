// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E280 rf_registry_read_string_object
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional section,value name,destination RF string object. Reads up to1024 raw bytes into1028-byte local through0x59E020. Failure returns-1 without assigning destination; success assigns C string through0x55FFA0,returns0. Does not validate REG_SZ or guarantee a terminator for full1024-byte result. No destination capacity argument; string object helper handles its own allocation.
int __cdecl rf_registry_read_string_object(char *String1, LPCSTR lpValueName, _DWORD *a3)
{
  BYTE Data[1028]; // [esp+0h] [ebp-408h] BYREF

  if ( rf_registry_read_raw_value(String1, lpValueName, Data, 0x400u) )
    return -1;
  rf_string_assign_from_cstr(a3, (char *)Data);
  return 0;
}

