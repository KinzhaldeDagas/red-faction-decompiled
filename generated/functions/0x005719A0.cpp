// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005719A0 rf_rgba8_construct_components_return_self
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Thiscall four byte-valued arguments, each in a four-byte stack slot. Writes them consecutively at this+0,+1,+2,+3 and returns this. RET16; no clamping, conversion or adjacent writes. Same component order used by nearby RF color setters.
_BYTE *__thiscall rf_rgba8_construct_components_return_self(_BYTE *this, char a2, char a3, char a4, char a5)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = a5;
  return this;
}

