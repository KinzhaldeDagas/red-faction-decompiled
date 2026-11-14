// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616C11 __ctrandisp1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Stack-double unary dispatch adapter: EDX descriptor
// and ECX context plus one caller-popped binary64 operand. Establish EBP scratch frame0x2D0 bytes/saveEBX; copy two DWORDs of caller double to fload, reclaim8 bytes. fload places
// operand on x87 stack; no semantic ST0 input/fpstat argument. Waiting FSTCW to frame-0xA4, clear bit1 of otherwise retained frame byte-0x2C8, call trandisp1 with own EBP and loaded
// ST0; then ctranexit. RestoreEBX/frame, plainRET, original8 caller stack bytes remain. Result whatever dispatch/exit helpers leave in ST0, no own EAX result. No own validation, SEH,
// complete frame initialization or FP environment restoration beyond delegated exit policy.
long double __usercall _ctrandisp1@<st0>(void *a1@<edx>, unsigned int a2@<ecx>, double a3)
{
  double v3; // st7
  long double v4; // st7
  int savedregs; // [esp+2D4h] [ebp+0h] BYREF

  v3 = _fload(a3);
  v4 = _trandisp1(a1, a2, &savedregs, v3);
  return ctranexit(&savedregs, v4);
}

