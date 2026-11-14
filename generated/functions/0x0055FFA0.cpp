// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FFA0 rf_string_assign_from_cstr
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall destination and nullable C string. NULL source releases and assigns empty. Exact source==destination.buffer is a no-op. Otherwise if strlen(source)==stored extent, copies in place only when destination buffer exists; differing length releases then assigns from source. Returns destination. Does not handle an interior pointer into its own buffer safely when reallocation is needed; base-pointer self check does not cover overlapping interior source.
_DWORD *__thiscall rf_string_assign_from_cstr(_DWORD *this, char *Source)
{
  char v3; // al
  _BYTE *v4; // [esp+8h] [ebp-1Ch]
  char *v5; // [esp+Ch] [ebp-18h]

  if ( Source )
  {
    if ( Source != (char *)*(this + 1) )
    {
      if ( strlen(Source) == *this )
      {
        if ( *(this + 1) )
        {
          v5 = Source;
          v4 = (_BYTE *)*(this + 1);
          do
          {
            v3 = *v5;
            *v4++ = *v5++;
          }
          while ( v3 );
        }
      }
      else
      {
        rf_string_release_buffer_keep_extent(this);
        rf_string_assign_cstr_bounded((int)this, Source, -1);
      }
    }
    return this;
  }
  else
  {
    rf_string_release_buffer_keep_extent(this);
    rf_string_assign_cstr_bounded((int)this, (char *)byte_64080A, -1);
    return this;
  }
}

