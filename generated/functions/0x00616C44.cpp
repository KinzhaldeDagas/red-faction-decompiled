// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616C44 __fload
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one stack IEEE64 value, returns value in ST0. Save EBX/frame. Inspect top inputWORD: mask0x7FF0!=0x7FF0 loads original QWORD via FLD. For
// exponent-all-ones, synthesize local TBYTE: sign/exponent WORD=(originalTopWORD OR0x7FFF), middleDWORD=SHLD(originalHighDWORD,originalLowDWORD,11), lowDWORD=originalLowDWORD; FLD
// TBYTE. No arithmetic normalization or memory output, argument remains on caller stack. Restore EBX/EBP; native modifies EAX only among general caller registers, preserves ECX and
// EDX. Explicit spoils<EAX> annotation matters: EDX contains math descriptor across two loads in616A7B. x87 representation/special payload handling is native80-bit; no input
// pointer/NULL argument or heap allocation.
double __cdecl __spoils<eax> _fload(double a1)
{
  double v2; // [esp+6h] [ebp-Ah]

  if ( (HIWORD(a1) & 0x7FF0) != 0x7FF0 )
    return a1;
  HIDWORD(v2) = *(_QWORD *)&a1 >> 21;
  LODWORD(v2) = LODWORD(a1);
  return v2;
}

