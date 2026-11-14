// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614180 __VEC_memcpy
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(destination,source,unsigned byte count),
// returns original destination. Compute SIGNED int32 pointer remainders modulo16 for both. Both0: bulk=count-(count&127), call fastcopy_I only if bulknonzero, then REP MOVSB tail at
// end. Equal nonzero signed remainders: prefix=16-sourceRemainder, copy prefix bytes FORWARD with REP MOVSB WITHOUT clamping to count, then recurse with advanced
// pointers/count-prefix wrapped. Unequal remainders: copy entire count forward using REP MOVSD then0..3 MOVSB. Negative unaligned pointers can produce prefix17..31. Direct helper is
// not overlap-aware and short equal-unaligned calls can overrun/underflow; parent memcpy only selects it for count>=256, matching low4 bits and nonharmful-forward direction. Count0
// safe for aligned/unequal alignment branches. ESI/EDI/EBX preserved, incoming DF assumed clear; no errno/allocation/capacity checks.
__m128i *__cdecl _VEC_memcpy(__m128i *a1, const __m128i *a2, unsigned int a3)
{
  int v3; // ecx
  __m128i *result; // eax
  unsigned int v5; // ecx
  unsigned int v6; // [esp+4h] [ebp-18h]

  v3 = (int)a2 % 16;
  result = a1;
  if ( ((int)a1 % 16) | ((int)a2 % 16) )
  {
    if ( v3 == (int)a1 % 16 )
    {
      qmemcpy(a1, a2, 16 - v3);
      _VEC_memcpy((__m128i *)((char *)a1 + 16 - v3), (const __m128i *)((char *)a2 + 16 - v3), a3 - (16 - v3));
    }
    else
    {
      qmemcpy(a1, a2, a3);
    }
    return a1;
  }
  else
  {
    v5 = a3 & 0x7F;
    v6 = v5;
    if ( a3 != v5 )
    {
      fastcopy_I(a1, a2, a3 - v5);
      result = a1;
      v5 = v6;
    }
    if ( v5 )
    {
      qmemcpy(&result->m128i_i8[a3 - v5], &a2->m128i_i8[a3 - v5], v6);
      return a1;
    }
  }
  return result;
}

