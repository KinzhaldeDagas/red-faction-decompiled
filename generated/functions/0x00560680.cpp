// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560680 rf_string_concat_byte_object
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Cdecl output, byte, source object. Computes source strlen or0, reserves length+1, writes leading byte at offset0, then UNCONDITIONALLY copies source buffer including NUL into temporary+1. VERIFIED: normal empty object has bufferNULL, but the copy loop still reads it at560737 despite earlier length fallback0. Copy-constructs output, destroys temporary and returns output when it reaches tail. No fix applied.
_DWORD *__cdecl rf_string_concat_byte_object(_DWORD *a1, char a2, int a3)
{
  char v3; // al
  char *v5; // [esp+Ch] [ebp-38h]
  char *v6; // [esp+10h] [ebp-34h]
  unsigned int v7; // [esp+14h] [ebp-30h]
  char *v8[2]; // [esp+30h] [ebp-14h] BYREF
  int v9; // [esp+40h] [ebp-4h]

  if ( *(_DWORD *)(a3 + 4) )
    v7 = strlen(*(const char **)(a3 + 4));
  else
    v7 = 0;
  rf_string_construct_reserved_extent(v8, v7 + 1);
  v9 = 1;
  *rf_string_byte_pointer_or_zero_sentinel((int *)v8, 0) = a2;
  v6 = *(char **)(a3 + 4);
  v5 = v8[1] + 1;
  do
  {
    v3 = *v6;
    *v5++ = *v6++;
  }
  while ( v3 );
  rf_string_copy_construct_from_object(a1, v8);
  LOBYTE(v9) = 0;
  rf_string_destroy_buffer(v8);
  return a1;
}

