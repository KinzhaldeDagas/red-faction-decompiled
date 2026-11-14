// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E3F0 rf_bitset_construct_borrowed_storage
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Thiscall(receiver,buffer,bitCount) calls57E490 bind-borrowed operation and returns receiver. No allocation,zero-fill or validation. Header pointer0,rounded byteCount4,owned byte8=0;original logical bit count not retained.
_DWORD *__thiscall rf_bitset_construct_borrowed_storage(_DWORD *this, int a2, int a3)
{
  rf_bitset_bind_borrowed_storage(this, a2, a3);
  return this;
}

