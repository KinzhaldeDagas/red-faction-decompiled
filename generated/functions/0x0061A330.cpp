// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A330 __d_inttype
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(double), native integer/parity classifier
// EAX0/1/2. FLD/FSTP argument before fpclass; if returned classification mask90h nonzero (either signed subnormal), return0. Otherwise frnd(input) using CURRENT x87 CW (verified
// helper FLD/FRNDINT/FSTP QWORD/FLD), compare to original via FCOMP/FNSTSW TEST AH,44h parity. Unequal OR unordered ->0. Equal -> FMUL original by exact double0.5 at630FB8, FSTP
// QWORD local (binary64 rounding), frnd(that half), compare. Equal ordered half ->2; unequal/unordered half ->1. For ordinary finite integral inputs this is even2/odd1; nonintegral0.
// Native ALSO returns2 for both signed zeros and both infinities if FP operations return normally; NaN comparison yields0, or FP exception can escape. No finite-only guard, CW
// reset/save, errno or overflow handling. x87 rounding/precision/exception state applies; half is explicitly stored as binary64 before second round/compare. Does not return ST0
// numeric result.
int __cdecl _d_inttype(double X)
{
  if ( (_fpclass(X) & 0x90) != 0 || _frnd(X) != X )
    return 0;
  if ( _frnd(X * 0.5) == X * 0.5 )
    return 2;
  return 1;
}

