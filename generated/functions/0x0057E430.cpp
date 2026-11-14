// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E430 rf_bitset_allocate_owned_uninitialized
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Recovered thiscall bitCount. byteCount=(bitCount+7) with32-bit wrap then arithmetic right shift3;operator-new(byteCount),overwrite pointer0. If pointerNULL return-1 WITHOUT updating old byteCount/owned flag;otherwise stores byteCount4,owned byte8=1,returns0. Does not free previous pointer or initialize bits;negative/overflowing counts can become huge unsigned allocations. Allocation exceptions propagate;NULL check does not catch throws.
int __thiscall rf_bitset_allocate_owned_uninitialized(void *this, int Size)
{
  int Sizea; // [esp+10h] [ebp+8h]

  Sizea = (Size + 7) >> 3;
  *(_DWORD *)this = operator new(Sizea);
  if ( !*(_DWORD *)this )
    return -1;
  *((_DWORD *)this + 1) = Sizea;
  *((_BYTE *)this + 8) = 1;
  return 0;
}

