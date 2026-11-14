// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616A00 __cintrindisp2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal intrinsic two-argument math dispatcher: EDX descriptor and liveST0/ST1 inputs;no incoming ECX object,caller doubles or fpstat formal.
// Establishframe/reserve0x2D0/saveEBX,save x87CW. Ifglobal666060==0,FXCH/FST QWORD[frame-134]/FXCH/FST QWORD[frame-126] save originaltwo values WITHOUT popping;nonzero skips
// originalsaves. Call verified trandisp2 with currentdescriptor/frame/operands. OR frameDWORD-712 mask3,call sharedcintrinexit,restoreEBX/frame/RET; numeric resultST0,notEAX. No own
// floating arithmetic beyond save/stackexchange; special/error behavior delegated to verifiedchain. Corrected custom floating ABI removes staleintreturn/fpstat inputs and
// propagatesCIfmod result.
long double __usercall _cintrindisp2@<st0>(
        const void *descriptor@<edx>,
        long double operand1@<st1>,
        long double operand0@<st0>)
{
  long double v3; // st7
  int savedregs; // [esp+2D4h] [ebp+0h] BYREF

  v3 = _trandisp2(descriptor, &savedregs, operand0, operand1);
  return cintrinexit((long double *)&savedregs, v3);
}

