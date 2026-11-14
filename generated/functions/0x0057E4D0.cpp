// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E4D0 rf_bitset_allocate_from_byte_arena
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Recovered thiscall(receiver,arena,bitCount). Rounded bytes via wrappedADD7/arithmeticSAR3,allocates from arena5E7660,overwrites pointer0. NULL result returns-1 leaving byteCount4/ownership8 stale;success stores count,owned0,returns0. Borrowed lifetime follows arena,not bitset destructor. No old-pointer release or zero-fill;no count validation.
int __thiscall rf_bitset_allocate_from_byte_arena(void *this, void *a2, int a3)
{
  unsigned int v5; // [esp+10h] [ebp+Ch]

  v5 = (a3 + 7) >> 3;
  *(_DWORD *)this = rf_byte_arena_allocate(a2, v5);
  if ( !*(_DWORD *)this )
    return -1;
  *((_DWORD *)this + 1) = v5;
  *((_BYTE *)this + 8) = 0;
  return 0;
}

