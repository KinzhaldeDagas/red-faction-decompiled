// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E3A0 rf_three_dword_zero_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Stores0 at receiver offsets0,4,8,returns receiver. Sole observed direct caller57E380 initializes tail at+8034. Replaces misleading std::_Vector_val constructor label with exact neutral behavior:three zeroed DWORDs alone do not prove STL three-pointer semantics or ownership.
_DWORD *__thiscall rf_three_dword_zero_construct(_DWORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  return this;
}

