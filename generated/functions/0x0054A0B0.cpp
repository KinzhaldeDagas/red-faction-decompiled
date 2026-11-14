// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054A0B0 rf_uint32_maximum_two_values
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Cdecl two unsigned32 values,returns larger using unsigned comparison;equal returns second identical value. No signed/float comparison,mutation or saturation.
unsigned int __cdecl rf_uint32_maximum_two_values(unsigned int a1, unsigned int a2)
{
  if ( a1 <= a2 )
    return a2;
  else
    return a1;
}

