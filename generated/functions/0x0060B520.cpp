// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B520 __CIpow
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Intrinsic __CIpow: no ordinary stack arguments; live
// extended x87 operands: ST0 EXPONENT, ST1 BASE. Numeric result in ST0; incoming values may be narrowed by selected path. Exact dispatch admission: live DWORD0x02021F60 must be
// nonzero; snapshot MXCSR via STMXCSR and require (MXCSR&0x1F80)==0x1F80; only on success snapshot x87 CW via FNSTCW and require (CW&0x007F)==0x007F. The8-byte temporary gate stack
// area is reclaimed with LEA, preserving comparison flags used by final JNZ. This is NOT equality to a complete default FP environment: MXCSR status/rounding/DAZ/FTZ and x87
// precision/rounding/high fields are ignored by this gate; CW bit6 is included. Global0 bypasses both hardware snapshots; failed MXCSR bypasses CW read. No CPUID, controlword/MXCSR
// write or own arithmetic/errno/error classification in admission. Gate global is not a file-backed initial value. Delegate arithmetic, special values and error/CW policy to selected
// kernel; no own SEH or runtime pointer checks. Rejected admission reserves20 bytes; FXCH ST1 then FSTP64 to first local DOUBLE pops original BASE, FST64 to second DOUBLE copies
// original EXPONENT without popping, EAX loads exponent highDWORD, CALL default0x60B57D, reclaim20 and plainRET. Thus original ST0 is exponent and ST1 is base, not the old integer
// ST1 formal. Local4 padding bytes not initialized here; x87 FST conversions use live FP environment. Accepted path tail-JMP0x6197D0 intrinsic SSE bridge, which likewise FXCH then
// pops BASE/EXPONENT to16 bytes of aligned binary64 before pow kernel. No incoming XMM numeric arguments.
double __usercall _CIpow@<st0>(long double exponent@<st0>, long double base@<st1>)
{
  int v2; // eax
  bool v3; // zf
  char exponentClassification; // [esp+Ch] [ebp-8h]

  if ( !unk_2021F60 )
    return crt_pow_x87_core(base, HIDWORD(*(unsigned __int64 *)&base), exponent, base);
  v2 = _mm_getcsr() & 0x1F80;
  v3 = v2 == 8064;
  if ( v2 == 8064 )
    v3 = (exponentClassification & 0x7F) == 127;
  if ( v3 )
    return _CIpow_pentium4(exponent, base);
  else
    return crt_pow_x87_core(base, HIDWORD(*(unsigned __int64 *)&base), exponent, base);
}

