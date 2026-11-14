// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E560 rf_bitset_get_bit_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Returns BOOL from backing[index arithmeticSAR3] & (1<<(index&7)). Least-significant-bit first. No signed index/range/NULL checks;negative indices address before backing,rounded padding bits accessible.
BOOL __thiscall rf_bitset_get_bit_unchecked(_DWORD *this, int a2)
{
  return ((1 << (a2 & 7)) & *(unsigned __int8 *)(*this + (a2 >> 3))) != 0;
}

