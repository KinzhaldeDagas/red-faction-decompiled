// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609DD0 _exp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Public _exp: ordinary cdecl one binary64 stack
// operand (8 caller-owned bytes). Numeric result in ST0; no extra vector/register numeric arguments. Exact dispatch admission: live DWORD0x02021F60 must be nonzero; snapshot MXCSR
// via STMXCSR and require (MXCSR&0x1F80)==0x1F80; only on success snapshot x87 CW via FNSTCW and require (CW&0x007F)==0x007F. The8-byte temporary gate stack area is reclaimed with
// LEA, preserving comparison flags used by final JNZ. This is NOT equality to a complete default FP environment: MXCSR status/rounding/DAZ/FTZ and x87 precision/rounding/high fields
// are ignored by this gate; CW bit6 is included. Global0 bypasses both hardware snapshots; failed MXCSR bypasses CW read. No CPUID, controlword/MXCSR write or own
// arithmetic/errno/error classification in admission. Gate global is not a file-backed initial value. Delegate arithmetic, special values and error/CW policy to selected kernel; no
// own SEH or runtime pointer checks. Rejected admission jumps to0x609E47 (a chunk currently owned by __CIexp): EDX=descriptor0x665CBA, tail JMP __ctrandisp1, which loads own stack
// double; this cross-function chunk does not imply an absent default path. No function-boundary reassignment. Accepted admission tail-JMP0x616548, MOVLPD XMM0 from original caller
// double then fall through exp SSE kernel0x61654E.
double __cdecl exp(double X)
{
  int v1; // eax
  bool v2; // zf
  char v4; // [esp+0h] [ebp-8h]

  if ( !unk_2021F60 )
    goto __exp_default;
  v1 = _mm_getcsr() & 0x1F80;
  v2 = v1 == 8064;
  if ( v1 == 8064 )
    v2 = (v4 & 0x7F) == 127;
  if ( !v2 )
__exp_default:
    JUMPOUT(0x609E47);
  return crt_exp_sse2_kernel(X, X);
}

