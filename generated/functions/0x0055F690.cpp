// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F690 rf_string_construct_reserved_extent
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Thiscall destination and requested extent. Initializes buffer pointerNULL, then resets/reserves requested extent when>=0 else0. Returns destination. Reserve sets stored extent and an empty C string, not a string of that many initialized characters.
_DWORD *__thiscall rf_string_construct_reserved_extent(_DWORD *this, int a2)
{
  *(this + 1) = 0;
  if ( a2 >= 0 )
    rf_string_reset_and_reserve_extent(this, a2);
  else
    rf_string_reset_and_reserve_extent(this, 0);
  return this;
}

