// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560260 rf_string_concat_object_cstr
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Cdecl output, left RF object, nullable right C string. NULL right copy-constructs left unchanged. Otherwise reserves left stored extent+strlen(right), copies left only when its buffer exists, then strcat right when reserved sum nonzero. Copy-constructs output, destroys temporary and returns output. No overflow or output/source alias guard.
_DWORD *__cdecl rf_string_concat_object_cstr(_DWORD *a1, char **a2, const char *a3)
{
  char v4; // dl
  char *v5; // [esp+30h] [ebp-30h]
  char *v6; // [esp+34h] [ebp-2Ch]
  char *v7; // [esp+4Ch] [ebp-14h] BYREF
  char *v8; // [esp+50h] [ebp-10h]
  int v9; // [esp+5Ch] [ebp-4h]

  if ( a3 )
  {
    rf_string_construct_reserved_extent(&v7, (int)&(*a2)[strlen(a3)]);
    v9 = 1;
    if ( v7 )
    {
      if ( a2[1] )
      {
        v6 = a2[1];
        v5 = v8;
        do
        {
          v4 = *v6;
          *v5++ = *v6++;
        }
        while ( v4 );
      }
      strcat(v8, a3);
    }
    rf_string_copy_construct_from_object(a1, &v7);
    LOBYTE(v9) = 0;
    rf_string_destroy_buffer(&v7);
    return a1;
  }
  else
  {
    rf_string_copy_construct_from_object(a1, a2);
    v9 = 0;
    return a1;
  }
}

