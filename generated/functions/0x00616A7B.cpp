// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616A7B __ctrandisp2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native runtime dispatcher accepts descriptor in EDX plus TWO DOUBLE64 stack values, returns numeric result in ST0. PUSH EBP/MOV EBP,ESP, reserve0x2D0
// bytes,save EBX. Copy caller DOUBLE0 at EBP+8 and DOUBLE1 at EBP+16 through cdecl616C44 __fload calls (ADD8 each), thereby constructing two x87 inputs internally rather than
// consuming caller ST0/ST1 parameters. Save x87 control word at frame-164,OR frame-712 mask2,set frame-143 byte1; CALL60DD27 __trandisp2 using EDX descriptor and owned EBP frame,
// then CALL616AC3 ctranexit and its native fall-through through616C10. Exit restores original x87 control word and preserves ST0 numeric result or reloads error-handler result into
// ST0, then dispatcher restores EBX/frame and plain RET. Caller retains16 argument bytes; descriptor register consumes no stack slot. EAX is runtime scratch, not numeric return. No
// own descriptor validation, argument NULL checks, output pointer or heap allocation; arithmetic/special-value/exception dispatch remains delegated. Corrected custom ABI removes
// false incoming ST0/ST1 and EAX-return types.
double __usercall _ctrandisp2@<st0>(const void *descriptor@<edx>, double a2, double a3)
{
  double v3; // st7
  double v4; // st6
  long double v5; // st7
  int savedregs; // [esp+2D4h] [ebp+0h] BYREF

  v3 = _fload(a2);
  v4 = _fload(a3);
  v5 = _trandisp2(descriptor, &savedregs, v3, v4);
  return ctranexit(&savedregs, v5);
}

