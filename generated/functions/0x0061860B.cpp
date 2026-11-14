// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061860B __errcode
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl raw lowBYTE flags (corrected unsigned-byte
// type),full EAX code0..5. Priority tests: bit20h ->5; else08h ->1; else04h ->2; else01h ->3; else02h ->4; else0. Multiple bits choose first listed,not OR of codes. Native loads only
// BYTE[EBP+8];bit10h and every unlisted/high bit ignored. Last path explicitly MOVZX AL thenAND2/double; other paths write full EAX constants. No errno,validation,callback or FP
// operation. Record private flag-to-code mapping without assuming it is the same format as raw x87 status or logical control masks.
int __cdecl _errcode(unsigned __int8 a1)
{
  if ( (a1 & 0x20) != 0 )
    return 5;
  if ( (a1 & 8) != 0 )
    return 1;
  if ( (a1 & 4) != 0 )
    return 2;
  if ( (a1 & 1) != 0 )
    return 3;
  return 2 * (a1 & 2);
}

