// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FDE0 rf_string_trim_trailing_space_tab_lf
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): If buffer exists, scans backward from strlen-1 over only space/tab/LF. When all bytes are trimmed, frees/clears buffer without changing extent; otherwise writes NUL after last retained byte. Does not update stored extent or shrink allocation. CR retained. EAX incidental: object pointer, retained index or release result.
_DWORD *__thiscall rf_string_trim_trailing_space_tab_lf(int this)
{
  _DWORD *result; // eax
  signed int i; // [esp+18h] [ebp-4h]

  result = (_DWORD *)this;
  if ( *(_DWORD *)(this + 4) )
  {
    for ( i = strlen(*(const char **)(this + 4)) - 1;
          i >= 0
       && (*(_BYTE *)(*(_DWORD *)(this + 4) + i) == 32
        || *(_BYTE *)(*(_DWORD *)(this + 4) + i) == 9
        || *(_BYTE *)(*(_DWORD *)(this + 4) + i) == 10);
          --i )
    {
      ;
    }
    if ( i < 0 )
    {
      return rf_string_release_buffer_keep_extent((_DWORD *)this);
    }
    else
    {
      *(_BYTE *)(i + *(_DWORD *)(this + 4) + 1) = 0;
      return (_DWORD *)i;
    }
  }
  return result;
}

