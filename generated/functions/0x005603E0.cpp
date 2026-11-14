// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005603E0 rf_string_concat_cstr_object
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Cdecl output, nullable left C string, right RF object. NULL left copy-constructs right. Otherwise reserves strlen(left)+right stored extent, copies left, appends right when buffer exists, then copy-constructs output and destroys temporary. Returns output. No overflow or output/source alias guard.
_DWORD *__cdecl rf_string_concat_cstr_object(_DWORD *a1, const char *a2, char **a3)
{
  char v4; // al
  char *v5; // [esp+30h] [ebp-30h]
  const char *v6; // [esp+34h] [ebp-2Ch]
  char *v7; // [esp+4Ch] [ebp-14h] BYREF
  char *v8; // [esp+50h] [ebp-10h]
  int v9; // [esp+5Ch] [ebp-4h]

  if ( a2 )
  {
    rf_string_construct_reserved_extent(&v7, (int)&(*a3)[strlen(a2)]);
    v9 = 1;
    if ( v7 )
    {
      v6 = a2;
      v5 = v8;
      do
      {
        v4 = *v6;
        *v5++ = *v6++;
      }
      while ( v4 );
      if ( a3[1] )
        qmemcpy(&v8[strlen(v8)], a3[1], &a3[1][strlen(a3[1]) + 1] - a3[1]);
    }
    rf_string_copy_construct_from_object(a1, &v7);
    LOBYTE(v9) = 0;
    rf_string_destroy_buffer(&v7);
    return a1;
  }
  else
  {
    rf_string_copy_construct_from_object(a1, a3);
    v9 = 0;
    return a1;
  }
}

