// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606AF0 _atan
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Public _atan: ordinary cdecl one binary64 stack
// operand (8 caller-owned bytes). Numeric result in ST0; no extra vector/register numeric arguments. Exact dispatch admission: live DWORD0x02021F60 must be nonzero; snapshot MXCSR
// via STMXCSR and require (MXCSR&0x1F80)==0x1F80; only on success snapshot x87 CW via FNSTCW and require (CW&0x007F)==0x007F. The8-byte temporary gate stack area is reclaimed with
// LEA, preserving comparison flags used by final JNZ. This is NOT equality to a complete default FP environment: MXCSR status/rounding/DAZ/FTZ and x87 precision/rounding/high fields
// are ignored by this gate; CW bit6 is included. Global0 bypasses both hardware snapshots; failed MXCSR bypasses CW read. No CPUID, controlword/MXCSR write or own
// arithmetic/errno/error classification in admission. Gate global is not a file-backed initial value. Delegate arithmetic, special values and error/CW policy to selected kernel; no
// own SEH or runtime pointer checks. Rejected admission EDX=&caller DOUBLE, CALL fload_withFB, then native fall-through into internal default0x00606B88; loader returns live extended
// ST0 plus EAX/flags, original argument remains on caller stack. Accepted admission tail-JMP0x00611648; native entry loads low64 of kernel input vector from same caller DOUBLE, then
// falls through SSE body. MOVLPD preserves upper64; MOVQ clears upper64. Preserved existing noncontiguous default/fast-load chunks; not a separate caller vector ABI.
double __cdecl atan(double X)
{
  int v1; // eax
  bool v2; // zf
  unsigned int v3; // eax
  long double v4; // st7
  char v6; // [esp+0h] [ebp-8h]

  if ( unk_2021F60 )
  {
    v1 = _mm_getcsr() & 0x1F80;
    v2 = v1 == 8064;
    if ( v1 == 8064 )
      v2 = (v6 & 0x7F) == 127;
    if ( v2 )
      return crt_atan_sse2_kernel(X, X);
  }
  v4 = _fload_withFB(&X);
  return crt_atan_x87_core(v4, v3, v2, X);
}

