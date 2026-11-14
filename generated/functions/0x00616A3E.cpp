// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616A3E __cintrindisp1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Intrinsic unary dispatch adapter: EDX descriptor,
// ECX context, live extended ST0; no ordinary stack arguments/semantic fpstat input. Establish EBP scratch frame0x2D0 bytes, save EBX, waiting FSTCW to frame-0xA4. If
// global0x666060==0, FST binary64 input to frame-0x86 WITHOUT popping, then join normal dispatch; nonzero skips that input snapshot. Call trandisp1 with own
// EBP,descriptor/context/liveST0. On selected-target return set byte frame-0x2C8 bit0 and clearbit1, call cintrinexit, restoreEBX/frame, plainRET. Own frame record/padding otherwise
// not initialized here. FP result whatever dispatch/exit helpers leave in ST0; no own integer result, stack operand, allocation or SEH. CW/error policy delegated to selected
// target/exit helper.
long double __usercall _cintrindisp1@<st0>(void *a1@<edx>, unsigned int a2@<ecx>, long double a3@<st0>)
{
  long double v3; // st7
  int savedregs; // [esp+2D4h] [ebp+0h] BYREF

  v3 = _trandisp1(a1, a2, &savedregs, a3);
  return cintrinexit((long double *)&savedregs, v3);
}

