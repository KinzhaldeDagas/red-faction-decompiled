// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060AD30 __fpclass
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(double), int native classification mask. First
// DWORD read at argument BYTE+6 extends2 bytes past8-byte value, unused high16 masked away. Original raw exponent7FF -> FLD input, allocate stack8, FSTP QWORD, then sptype on THAT
// stored copy. Map returned special code1->200h(+infinity),2->4(-infinity),3->2(quietNaN),4 or other->1(signaling/fallback). This is NOT a raw-bit-only special classifier: signaling
// NaN can be quieted or raise invalid per x87 masks BEFORE sptype; no CW save/change/exception catch. Finite exponent0+nonzero fraction -> sign?10h:80h (negative/positive subnormal),
// returned without FP compare. Remaining finite values use FLDZ/FCOMP input/FNSTSW and TEST AH,44h parity: equal signed zero ->sign?20h:40h; unequal normal ->sign?8:100h. Sign taken
// from original bits. No errno, allocation beyond stack slots or restoration of FP status; classification can change exception flags. Does not promise signaling-NaN code based on
// original bits after its FP copy.
int __cdecl _fpclass(double X)
{
  int v1; // eax
  int v2; // eax
  int v4; // ecx

  if ( (HIWORD(X) & 0x7FF0) == 0x7FF0 )
  {
    v1 = _sptype(X) - 1;
    if ( v1 )
    {
      v2 = v1 - 1;
      if ( !v2 )
        return 4;
      if ( v2 != 1 )
        return 1;
      return 2;
    }
    else
    {
      return 512;
    }
  }
  else
  {
    v4 = HIWORD(X) & 0x8000;
    if ( (HIWORD(X) & 0x7FF0) == 0 && ((HIDWORD(X) & 0xFFFFF) != 0 || LODWORD(X)) )
    {
      return (HIWORD(X) & 0x8000) != 0 ? 16 : 128;
    }
    else if ( 0.0 == X )
    {
      return v4 != 0 ? 32 : 64;
    }
    else
    {
      return v4 != 0 ? 8 : 256;
    }
  }
}

