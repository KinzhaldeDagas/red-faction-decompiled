// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D8DA __frnd
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl oneDOUBLE64. FLD argument,FRNDINT under CURRENT x87 CW, FSTP QWORD local thenFLD local beforeRET. ReturnedST0 is rounded-to-integral value after
// explicit64-bit store/reload,not arbitrary extended temporary; no own CW save/change, NaN/overflow check or errno. EAX unspecified.
double __cdecl _frnd(double a1)
{
  double result; // st7

  _ST7 = a1;
  __asm { frndint }
  return result;
}

