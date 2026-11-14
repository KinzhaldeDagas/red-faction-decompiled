// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DEF0 __twoToTOS
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Integer-part/remainder x87 2^x helper. LiveST0=x; duplicate, FRNDINT chooses n under CURRENT CW; FSUBR/FXCH/FCHS forms x-n. F2XM1,FLD1/FADDP computes2^(x-n);
// FSCALE by integraln; FSTP ST1 discards scale temporary leaving one resultST0. Net replaces one input with one output, no memory/frame/GPR output or CW override. No own finite/range
// guard, F2XM1-domain repair or errno; hardware exceptions follow current x87 state.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Native clobber refinement: x87-only instructions
// plus RET, NO GPR writes/calls. Explicit empty spoils preserves all GPRs, especially CL odd/even classification across pow's exponentiation call. Input is extended ST0, output
// extended ST0; no extra integer outputs or caller stack arguments.
long double __usercall __spoils<> _twoToTOS@<st0>(long double a1@<st0>)
{
  _ST6 = a1;
  __asm { frndint }
  return __FSCALE__(__F2XM1__(-(_ST6 - a1)) + 1.0, _ST6);
}

