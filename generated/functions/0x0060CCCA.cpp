// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CCCA __CIfmod
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Ten-byte compiler-intrinsic fmod boundary: MOV EDX descriptor664D90 then TAIL JMP616A00 cintrindisp2. Inputs already live in ST0/ST1, not ECX object or
// caller doubles loaded here; returned floating result ST0. No own stack/frame, arithmetic, status capture or FP-status formal. Corrected custom floating ABI; internal dispatcher
// saves originals and invokes verified trandisp2/exit chain.
double __usercall _CIfmod@<st0>(long double operand1@<st1>, long double operand0@<st0>)
{
  return _cintrindisp2(&unk_664D90, operand1, operand0);
}

