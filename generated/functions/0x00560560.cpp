// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560560 rf_string_concat_object_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Cdecl output, source object, byte. Uses strlen(source.buffer) or0, reserves length+1, copies source only when length>0, writes byte at original length and NUL after it, then copy-constructs output and destroys temporary. Appending byte0 leaves the same visible C string. Returns output; unlike prepend-byte variant, handles a NULL source buffer for an empty object.
_DWORD *__cdecl rf_string_concat_object_byte(_DWORD *a1, int a2, char a3)
{
  char v3; // dl
  _BYTE *v5; // [esp+Ch] [ebp-38h]
  char *v6; // [esp+10h] [ebp-34h]
  unsigned int v7; // [esp+14h] [ebp-30h]
  char *v8; // [esp+30h] [ebp-14h] BYREF
  _BYTE *v9; // [esp+34h] [ebp-10h]
  int v10; // [esp+40h] [ebp-4h]

  if ( *(_DWORD *)(a2 + 4) )
    v7 = strlen(*(const char **)(a2 + 4));
  else
    v7 = 0;
  rf_string_construct_reserved_extent(&v8, v7 + 1);
  v10 = 1;
  if ( v7 )
  {
    v6 = *(char **)(a2 + 4);
    v5 = v9;
    do
    {
      v3 = *v6;
      *v5++ = *v6++;
    }
    while ( v3 );
  }
  v9[v7] = a3;
  v9[v7 + 1] = 0;
  rf_string_copy_construct_from_object(a1, &v8);
  LOBYTE(v10) = 0;
  rf_string_destroy_buffer(&v8);
  return a1;
}

