// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E390 rf_registry_read_cstring_or_default
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional section,value name,destination,default C string. First copies default UNBOUNDED into1028-byte local even though raw reader then clears first1024 bytes. Raw read failure copies default to destination and returns-1; success copies local data and returns0. Neither copy has destination capacity; initial default copy can overflow local before registry call. No REG_SZ/type or full-size NUL validation. Failure status remains-1 even when default supplied.
int __cdecl rf_registry_read_cstring_or_default(char *String1, LPCSTR lpValueName, _BYTE *a3, BYTE *a4)
{
  BYTE v4; // al
  BYTE v5; // al
  BYTE v7; // al
  _BYTE *v8; // [esp+8h] [ebp-430h]
  BYTE *v9; // [esp+Ch] [ebp-42Ch]
  _BYTE *v10; // [esp+18h] [ebp-420h]
  BYTE *v11; // [esp+1Ch] [ebp-41Ch]
  BYTE *v12; // [esp+28h] [ebp-410h]
  BYTE *v13; // [esp+2Ch] [ebp-40Ch]
  BYTE Data[1028]; // [esp+30h] [ebp-408h] BYREF

  v13 = a4;
  v12 = Data;
  do
  {
    v4 = *v13;
    *v12++ = *v13++;
  }
  while ( v4 );
  if ( rf_registry_read_raw_value(String1, lpValueName, Data, 0x400u) )
  {
    v9 = a4;
    v8 = a3;
    do
    {
      v7 = *v9;
      *v8++ = *v9++;
    }
    while ( v7 );
    return -1;
  }
  else
  {
    v11 = Data;
    v10 = a3;
    do
    {
      v5 = *v11;
      *v10++ = *v11++;
    }
    while ( v5 );
    return 0;
  }
}

