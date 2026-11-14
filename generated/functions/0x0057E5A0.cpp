// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E5A0 rf_bitset_set_bit_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Thiscall index,valueDWORD;sets selected bit when value nonzero,clears otherwise. Byte offset=index arithmeticSAR3,mask1<<(index&7);writes one byte,returns resulting byte as0..255 integer. No bounds/ownership/NULL checks;borrowed storage is writable.
int __thiscall rf_bitset_set_bit_unchecked(_DWORD *this, int a2, int a3)
{
  int result; // eax

  if ( a3 )
    result = (1 << (a2 & 7)) | *(unsigned __int8 *)(*this + (a2 >> 3));
  else
    result = ~(1 << (a2 & 7)) & *(unsigned __int8 *)(*this + (a2 >> 3));
  *(_BYTE *)((a2 >> 3) + *this) = result;
  return result;
}

