// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B4E0 _pow
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Public _pow: ordinary cdecl two binary64 stack
// operands BASE then EXPONENT (16 caller-owned bytes). Numeric result in ST0; no extra vector/register numeric arguments. Exact dispatch admission: live DWORD0x02021F60 must be
// nonzero; snapshot MXCSR via STMXCSR and require (MXCSR&0x1F80)==0x1F80; only on success snapshot x87 CW via FNSTCW and require (CW&0x007F)==0x007F. The8-byte temporary gate stack
// area is reclaimed with LEA, preserving comparison flags used by final JNZ. This is NOT equality to a complete default FP environment: MXCSR status/rounding/DAZ/FTZ and x87
// precision/rounding/high fields are ignored by this gate; CW bit6 is included. Global0 bypasses both hardware snapshots; failed MXCSR bypasses CW read. No CPUID, controlword/MXCSR
// write or own arithmetic/errno/error classification in admission. Gate global is not a file-backed initial value. Delegate arithmetic, special values and error/CW policy to selected
// kernel; no own SEH or runtime pointer checks. Rejected admission at0x60B574 loads EDX=&caller EXPONENT (entryESP+12) then CALL fload_withFB; fall through internal pow
// default0x60B57D with exponent in ST0, EAX/flags loader outputs, original BASE/EXPONENT still on stack. Accepted path tail-JMP0x6197E9, whose own entry loads BASE into XMM0 from
// stack. Native numeric result remains ST0, no vector inputs supplied by public ABI.
double __cdecl pow(double X, double Y)
{
  int v2; // eax
  bool v3; // zf
  unsigned int v5; // eax
  long double v6; // st7
  char v7; // [esp+0h] [ebp-8h]

  if ( unk_2021F60 )
  {
    v2 = _mm_getcsr() & 0x1F80;
    v3 = v2 == 8064;
    if ( v2 == 8064 )
      v3 = (v7 & 0x7F) == 127;
    if ( v3 )
      return crt_pow_sse2_kernel(X, Y);
  }
  v6 = _fload_withFB(&Y);
  return crt_pow_x87_core(v6, v5, X, Y);
}

