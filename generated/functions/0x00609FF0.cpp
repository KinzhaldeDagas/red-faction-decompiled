// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609FF0 __CItan
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Intrinsic __CItan: no ordinary stack arguments; live
// extended x87 operand in ST0. Numeric result in ST0; incoming values may be narrowed by selected path. Exact dispatch admission: live DWORD0x02021F60 must be nonzero; snapshot MXCSR
// via STMXCSR and require (MXCSR&0x1F80)==0x1F80; only on success snapshot x87 CW via FNSTCW and require (CW&0x007F)==0x007F. The8-byte temporary gate stack area is reclaimed with
// LEA, preserving comparison flags used by final JNZ. This is NOT equality to a complete default FP environment: MXCSR status/rounding/DAZ/FTZ and x87 precision/rounding/high fields
// are ignored by this gate; CW bit6 is included. Global0 bypasses both hardware snapshots; failed MXCSR bypasses CW read. No CPUID, controlword/MXCSR write or own
// arithmetic/errno/error classification in admission. Gate global is not a file-backed initial value. Delegate arithmetic, special values and error/CW policy to selected kernel; no
// own SEH or runtime pointer checks. Rejected admission reserves12 bytes, FST64[ESP] copies original ST0 WITHOUT popping, CALL checkTOS_withFB (integer highDWORD classification; no
// x87 pop/load), then CALL internal default0x0060A048; reclaim12/plainRET. Input snapshot is binary64 under live FP environment, but original extended ST0 remains for kernel. EAX and
// ZF from exponent classifier are live protocol outputs, not Boolean/extra numeric arguments. Four local padding bytes are not initialized here. Accepted admission
// tail-JMP0x00616EF0, intrinsic SSE bridge pops input to aligned binary64 and initializes kernel input vector; polynomial/error policy delegated. No caller-supplied XMM formals.
double __usercall _CItan@<st0>(long double x@<st0>)
{
  int v1; // ecx
  int v2; // eax
  bool v3; // zf
  unsigned int v4; // eax
  double v5; // [esp+0h] [ebp-Ch]
  char v6; // [esp+4h] [ebp-8h]

  if ( !unk_2021F60 )
    goto __CItan_default;
  v2 = _mm_getcsr() & 0x1F80;
  v3 = v2 == 8064;
  if ( v2 == 8064 )
    v3 = (v6 & 0x7F) == 127;
  if ( v3 )
  {
    _CItan_pentium4(v1, x);
  }
  else
  {
__CItan_default:
    v4 = _checkTOS_withFB(SLODWORD(x), HIDWORD(*(unsigned __int64 *)&x));
    return crt_tan_x87_core(x, v4, v3, v5);
  }
  return x;
}

