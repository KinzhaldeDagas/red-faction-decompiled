// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E510 rf_registry_write_cstring_without_terminator
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional section,value name,C string. Calls raw writer0x59DB40 type1(REG_SZ),data pointer,length=strlen(data) EXACTLY,excluding terminating NUL. For empty string sends count0. Returns raw0/-1. No length bound or null guard. The raw reader zero-fill can mask this omission for shorter-than-capacity values.
int __cdecl rf_registry_write_cstring_without_terminator(char *String1, LPCSTR lpValueName, BYTE *lpData)
{
  return rf_registry_write_raw_value(String1, lpValueName, 1u, lpData, strlen((const char *)lpData));
}

