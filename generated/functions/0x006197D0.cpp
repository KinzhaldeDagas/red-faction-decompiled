// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006197D0 __CIpow_pentium4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): 25-byte two-operand x87/SSE pow boundary. Establishframe,reserve16,alignESP down16. FXCH ST1,then FSTP QWORD[ESP] stores/pops originalST1, nextFSTP
// QWORD[ESP+8] stores/pops originalST0; two current-CW64-bit rounding points. CALL pow_pentium4 kernel using staged values;LEAVE/RET. No wrapper MOVQ XMM initialization or explicit
// extra XMM arguments despite pseudocode. Kernel owns register inputs/result/special values; no result reload or domain arithmetic in shim.
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Refinement after complete downstream native kernel
// verification: incoming scratch XMM/GPR registers are not numeric parameters. The aligned shim consumes its incoming x87 argument(s), stages binary64 argument images using
// current-CW FSTP, and returns the kernel binary64 numeric result in ST0. The kernel independently initializes every packed-arithmetic lane; no incoming numeric ST0 remains after
// argument staging. LEAVE restores saved EBP/original ESP; plain RET; no caller stack arguments are read. No claim that FSTP preserves excess incoming precision or rolls back FP
// status. FXCH ST1 makes original base the first QWORD at aligned ESP, then original exponent is next QWORD at ESP+8. CALL006197E9 reads only these two stack doubles; the shim does
// not initialize or pass XMM arguments.
double __usercall _CIpow_pentium4@<st0>(long double exponent@<st0>, long double base@<st1>)
{
  return crt_pow_sse2_kernel(exponent, base);
}

