// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E660 rf_bitset_prefix_matches_value_legacy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Recovered thiscall unsigned requestedBits,valueByte. Clamp n to unsigned(storedByteCount<<3),with32-bit wrap. First checks n>>3 COMPLETE bytes are allZERO,independent of requested value;any nonzero returns false. Then start=n&FFFFFFF8,limit=(start+n)&7,loops j=start;j<limit checking bit(j)==(valueByte!=0). For ordinary n>=8,start>=8 and limit<=7,so tail loop NEVER RUNS;remaining partial bits ignored. For n<8,checks requested bits against requested truth value normally. n0 returns true. This is not a correct all-bits-match predicate for true or non-byte-aligned prefixes>=8;preserve verified loop-bound/whole-byte quirks. No backing validation.
unsigned __int8 __thiscall rf_bitset_prefix_matches_value_legacy(const void *this, unsigned int a2, unsigned __int8 a3)
{
  unsigned int i; // [esp+8h] [ebp-Ch]
  unsigned int j; // [esp+8h] [ebp-Ch]

  if ( a2 > 8 * *((_DWORD *)this + 1) )
    a2 = 8 * *((_DWORD *)this + 1);
  for ( i = 0; i < a2 >> 3; ++i )
  {
    if ( *(_BYTE *)(*(_DWORD *)this + i) )
      return 0;
  }
  for ( j = a2 & 0xFFFFFFF8; j < (((unsigned __int8)a2 + (a2 & 0xF8)) & 7); ++j )
  {
    if ( rf_bitset_get_bit_unchecked(this, j) != (a3 != 0) )
      return 0;
  }
  return 1;
}

