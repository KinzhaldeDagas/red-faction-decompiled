// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060FB10 __CIsin_pentium4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete24-byte x87/SSE runtime boundary shim. PUSH EBP/MOV EBP,ESP, reserve8 bytes then AND ESP,0xFFFFFFF0 (may reserve additional alignment padding). FSTP
// QWORD[ESP] rounds/stores and POPS incoming ST0 using current x87 control word; MOVQ xmm0,[ESP] loads low64 raw value and clears upper64 of that XMM register. CALL0060FB2E start_10;
// LEAVE restores original stack/frame, plain RET. Wrapper itself reads no caller stack arguments and explicitly stages no other XMM/GPR operands. Kernel owns calculation, result
// register/state, scratch registers and special-value behavior; old decompiler lists of other XMM inputs are not proved by shim body alone. No local x87 reload of result after
// kernel, memory output or stack-buffer escape except kernel-local use. Alignment/probe/return conventions recorded from raw instructions; does not establish kernel decompilation
// success.
long double __usercall _CIsin_pentium4@<st0>(double a1@<st0>)
{
  return crt_sin_sse2_kernel(a1, a1);
}

