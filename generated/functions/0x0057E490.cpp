// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E490 rf_bitset_bind_borrowed_storage
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Thiscall(receiver,buffer,signed bitCount). Writes pointer0,byteCount4=(bitCount+7)>>3 using wrapped32-bit ADD and arithmetic SAR,owned byte8=0;returns receiver. Does not release prior owned buffer,zero supplied storage or preserve logical non-byte-aligned bit count. No NULL/count validation.
_DWORD *__thiscall rf_bitset_bind_borrowed_storage(_DWORD *this, int a2, int a3)
{
  *this = a2;
  *(this + 1) = (a3 + 7) >> 3;
  *((_BYTE *)this + 8) = 0;
  return this;
}

