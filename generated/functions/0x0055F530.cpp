// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F530 rf_string_reset_and_reserve_extent
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Releases existing buffer, writes requested signed extent to DWORD+0, and for nonzero allocates extent+1 bytes then writes ONLY buffer[0]=NUL. Zero yields NULL buffer. Leaves other allocated bytes uninitialized. Does not validate negative extent itself (constructor wrapper clamps it). EAX varies: allocation path leaves buffer pointer, zero path object pointer; inferred _BYTE* return is not a uniform object result.
_BYTE *__thiscall rf_string_reset_and_reserve_extent(_DWORD *this, int a2)
{
  _BYTE *result; // eax

  rf_string_release_buffer_keep_extent(this);
  result = this;
  *this = a2;
  if ( a2 )
  {
    *(this + 1) = operator new[](*this + 1);
    result = (_BYTE *)*(this + 1);
    *result = 0;
  }
  else
  {
    *(this + 1) = 0;
  }
  return result;
}

