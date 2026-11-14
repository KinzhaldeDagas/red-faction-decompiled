// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060FCE0 __CIacos_pentium4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete24-byte x87/SSE runtime boundary shim. PUSH EBP/MOV EBP,ESP, reserve8 bytes then AND ESP,0xFFFFFFF0 (may reserve additional alignment padding). FSTP
// QWORD[ESP] rounds/stores and POPS incoming ST0 using current x87 control word; MOVQ xmm0,[ESP] loads low64 raw value and clears upper64 of that XMM register. CALL0060FCFE start_11;
// LEAVE restores original stack/frame, plain RET. Wrapper itself reads no caller stack arguments and explicitly stages no other XMM/GPR operands. Kernel owns calculation, result
// register/state, scratch registers and special-value behavior; old decompiler lists of other XMM inputs are not proved by shim body alone. No local x87 reload of result after
// kernel, memory output or stack-buffer escape except kernel-local use. Alignment/probe/return conventions recorded from raw instructions; does not establish kernel decompilation
// success.
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Refinement after complete downstream native kernel
// verification: incoming scratch XMM/GPR registers are not numeric parameters. The aligned shim consumes its incoming x87 argument(s), stages binary64 argument images using
// current-CW FSTP, and returns the kernel binary64 numeric result in ST0. The kernel independently initializes every packed-arithmetic lane; no incoming numeric ST0 remains after
// argument staging. LEAVE restores saved EBP/original ESP; plain RET; no caller stack arguments are read. No claim that FSTP preserves excess incoming precision or rolls back FP
// status. FSTP QWORD[alignedESP] pops value and MOVQ XMM0 loads identical low64/clears upper64. CALL0060FCFE reads scalar XMM0 and matching stack image only.
double __usercall _CIacos_pentium4@<st0>(long double value@<st0>)
{
  return crt_acos_sse2_kernel(value, value);
}

