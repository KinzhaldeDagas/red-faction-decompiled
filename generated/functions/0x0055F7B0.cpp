// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F7B0 rf_string_is_empty_or_space_tab_lf
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Recovered thiscall predicate. Returns true immediately if is_empty says true; otherwise checks every index0..storedExtent-1 for exactly space/tab/LF. Does not stop at NUL or use strlen once inside loop. CR and other bytes reject. Inherits is_empty positive-extent/NULL-buffer hazard. Result is byte AL.
bool __thiscall rf_string_is_empty_or_space_tab_lf(const void *this)
{
  int i; // [esp+4h] [ebp-4h]

  if ( rf_string_is_empty((int *)this) )
    return 1;
  for ( i = 0; i < *(_DWORD *)this; ++i )
  {
    if ( *(_BYTE *)(*((_DWORD *)this + 1) + i) != 32
      && *(_BYTE *)(*((_DWORD *)this + 1) + i) != 9
      && *(_BYTE *)(*((_DWORD *)this + 1) + i) != 10 )
    {
      return 0;
    }
  }
  return 1;
}

