// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061028B __VEC_memzero
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(destination,ignored fill slot,raw32-bit byte
// count), returns original destinationEAX. Always fills zero regardless second slot. Compute SIGNED pointer remainder r=(int32)destination%16 via CDQ/XOR/SUB. If r!=0, prefix=16-r
// (1..15 for positive pointers,17..31 for negative unaligned pointers), REP STOSB prefix WITHOUT clamping to count; recurse(destination+prefix,0,count-prefix wrapped), then return
// original destination. Aligned branch splits tail=count&127, bulk=count-tail; nonzero bulk calls fastzero_I(destination,bulk), then REP STOSB tail at destination+count-tail. Count0
// safe only on aligned branch; direct unaligned calls with count<prefix overrun/underflow. Memset606580 admits this dispatcher only for count>=256, zero fill and enabled feature
// global. No pointer/extent validation; REP assumes DF clear, alignment arithmetic preserves signed-address quirk.
int __cdecl _VEC_memzero(int a1, int a2, int a3)
{
  int result; // eax
  int v4; // edi
  int v5; // edx
  unsigned int v6; // [esp+4h] [ebp-Ch]

  result = a1;
  v4 = a1 % 16;
  if ( a1 % 16 )
  {
    memset((void *)a1, 0, 16 - v4);
    _VEC_memzero(16 - v4 + a1, 0, a3 - (16 - v4));
    return a1;
  }
  else
  {
    v5 = a3 & 0x7F;
    v6 = v5;
    if ( a3 != v5 )
    {
      fastzero_I((_OWORD *)a1, a3 - v5);
      result = a1;
      v5 = v6;
    }
    if ( v5 )
    {
      memset((void *)(a3 + result - v5), 0, v6);
      return a1;
    }
  }
  return result;
}

