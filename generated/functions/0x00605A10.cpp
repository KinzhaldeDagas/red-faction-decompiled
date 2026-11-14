// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605A10 __CIsqrt
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Compiler intrinsic entry receives numeric ST0. Reserve12 local bytes; FST QWORD at ESP WITHOUT popping original ST0; call60DF78 checkTOS helper, which reads
// saved highDWORD and returns exponent/highword plus comparison flags. Call605A2D shared sqrt kernel using same stack image and live ST0; ADD12 and RET. Unsigned-integer ST0 formal
// is false; corrected floating input/output prototype. Kernel owns domain/CW/special-value handling; this20-byte shim does not itself execute FSQRT.
double __usercall _CIsqrt@<st0>(long double value@<st0>)
{
  bool v1; // zf
  double original; // [esp+0h] [ebp-Ch]

  _checkTOS_withFB(SLODWORD(value), HIDWORD(*(unsigned __int64 *)&value));
  return crt_sqrt_x87_core(value, v1, original);
}

