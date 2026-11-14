// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F3F0 rf_string_assign_cstr_bounded
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Releases current buffer first. Sets stored extent to strlen(source) or0, truncating to limit only when limit>=0 and smaller. Nonzero extent allocates extent+1 bytes, strncpy extent bytes and adds NUL; zero clears extent and buffer. Returns destination pointer. No source-alias guard: source into the old destination buffer becomes dangling before strlen/copy. Negative limit means unrestricted source length, not allocation capacity.
int __thiscall rf_string_assign_cstr_bounded(int this, char *Source, int a3)
{
  rf_string_release_buffer_keep_extent((_DWORD *)this);
  if ( Source )
    *(_DWORD *)this = strlen(Source);
  else
    *(_DWORD *)this = 0;
  if ( a3 >= 0 && a3 < *(_DWORD *)this )
    *(_DWORD *)this = a3;
  if ( *(_DWORD *)this )
  {
    *(_DWORD *)(this + 4) = operator new[](*(_DWORD *)this + 1);
    strncpy(*(char **)(this + 4), Source, *(_DWORD *)this);
    *(_BYTE *)(*(_DWORD *)(this + 4) + *(_DWORD *)this) = 0;
  }
  else
  {
    *(_DWORD *)this = 0;
    *(_DWORD *)(this + 4) = 0;
  }
  return this;
}

