// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609E0C __CIexp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Intrinsic __CIexp: no ordinary stack arguments; live
// extended x87 operand in ST0. Numeric result in ST0; incoming values may be narrowed by selected path. Exact dispatch admission: live DWORD0x02021F60 must be nonzero; snapshot MXCSR
// via STMXCSR and require (MXCSR&0x1F80)==0x1F80; only on success snapshot x87 CW via FNSTCW and require (CW&0x007F)==0x007F. The8-byte temporary gate stack area is reclaimed with
// LEA, preserving comparison flags used by final JNZ. This is NOT equality to a complete default FP environment: MXCSR status/rounding/DAZ/FTZ and x87 precision/rounding/high fields
// are ignored by this gate; CW bit6 is included. Global0 bypasses both hardware snapshots; failed MXCSR bypasses CW read. No CPUID, controlword/MXCSR write or own
// arithmetic/errno/error classification in admission. Gate global is not a file-backed initial value. Delegate arithmetic, special values and error/CW policy to selected kernel; no
// own SEH or runtime pointer checks. Rejected admission reaches0x609E51: EDX=descriptor0x665CBA, tail JMP __cintrindisp1 with original ST0 and native ECX context. No input
// rounding/copy or own stack double on this default path. Stored custom ABI keeps incoming ECX context (dispatcher retains bit10); it is not a second numeric operand. Same function
// also owns public-exp default chunk0x609E47 (EDX descriptor then tail __ctrandisp1); preserve existing chunk ownership. Accepted admission tail-JMP0x616530 intrinsic SSE bridge,
// which pops ST0 to aligned binary64 before kernel0x61654E.
double __usercall _CIexp@<st0>(long double x@<st0>, unsigned int dispatchContext@<ecx>)
{
  int v2; // eax
  bool v3; // zf
  char v4; // [esp+0h] [ebp-8h]

  if ( !unk_2021F60 )
    return _cintrindisp1(&unk_665CBA, dispatchContext, x);
  v2 = _mm_getcsr() & 0x1F80;
  v3 = v2 == 8064;
  if ( v2 == 8064 )
    v3 = (v4 & 0x7F) == 127;
  if ( !v3 )
    return _cintrindisp1(&unk_665CBA, dispatchContext, x);
  _CIexp_pentium4(x);
  return x;
}

