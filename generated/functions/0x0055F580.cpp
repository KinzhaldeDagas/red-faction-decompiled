// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F580 rf_string_release_buffer_keep_extent
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): If object buffer+4 is non-NULL, passes it to operator-delete wrapper55F5B0 and clears buffer pointer. Leaves stored extent+0 unchanged in all paths. Returns object pointer. Does not clear allocation bytes before freeing.
_DWORD *__thiscall rf_string_release_buffer_keep_extent(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  if ( *(this + 1) )
  {
    rf_string_deallocate_buffer((void *)*(this + 1));
    *(this + 1) = 0;
    return this;
  }
  return result;
}

