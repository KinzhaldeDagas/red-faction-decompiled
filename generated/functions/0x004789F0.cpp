// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004789F0 rf_u32_has_exactly_one_set_bit
// UNREALRED VERIFIED [level-lifecycle-20261028]: Counts set bits across all32 bits and returns count==1. Zero false; sign-bit-only0x80000000 true. Used for power-of-two texture-dimension warnings, but does not require positive signed input.
BOOL __cdecl rf_u32_has_exactly_one_set_bit(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  unsigned int i; // [esp+4h] [ebp-4h]

  v2 = 0;
  for ( i = 0; i < 0x20; ++i )
  {
    if ( (a1 & (1 << i)) != 0 )
      ++v2;
  }
  return v2 == 1;
}

