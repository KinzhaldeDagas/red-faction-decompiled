// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F780 rf_string_is_empty
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Returns true if stored extent<=0 OR buffer[0]==NUL. For positive extent, dereferences buffer without NULL guard. Since release/trim can clear buffer while retaining positive extent, such a record can fault here. Does not compute strlen or repair extent.
bool __thiscall rf_string_is_empty(int *this)
{
  return *this <= 0 || *(_BYTE *)*(this + 1) == 0;
}

