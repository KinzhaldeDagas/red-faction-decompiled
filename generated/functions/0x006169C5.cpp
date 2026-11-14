// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006169C5 _usepowhlp
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal x87 pow helper bridge: ST0 EXPONENT,ST1
// BASE, EBP runtime frame used on error; no ordinary incoming stack slots. Save ESI, allocate116=result8+x87 save108 bytes, ESI scratch. PUSH result pointer, SUB8/FSTP original
// exponent then SUB8/FSTP original base, so actual cdecl powhlp(base,exponent,resultPointer) order is base FIRST (old pseudocode reversed formal names). Waiting FSAVE scratch+8 after
// operand copies resets x87; CALL powhlp, ADD20 argument bytes, FRSTOR saved state, FLD64 scratch result, reclaim116, restoreESI. EAX status0 ->RET; nonzero tail-JMP60DE79 writes
// frame errorBYTE1 then OR CL,CL/RET using SAME own return-PC. This path does NOT discard return address and is ordinary tail return, unlike ffexpm1/Augment nonlocal exits. Caller
// admits non-NaN infinite cases; powhlp can leave output unwritten on unhandled input, so no general unconditional-success promise. Normal input pair replaced by one binary64-derived
// ST0 result (net depth-1), EAX status retained, other volatile GPRs reflect delegate; no own SSE save/errno/NULL validation/SEH.
double __usercall usepowhlp@<st0>(long double exponent@<st0>, long double base@<st1>, void *frame@<ebp>)
{
  int v4; // eax
  double result; // st7
  double *v6; // [esp+10h] [ebp-7Ch]
  double v7[15]; // [esp+14h] [ebp-78h] BYREF

  _ESI = v7;
  v6 = v7;
  __asm { fsave   byte ptr [esi+8]; UNREALRED VERIFIED: Waiting FSAVE108 bytes at scratch+8 resets x87 after operand copies. }
  v4 = _powhlp(exponent, base, v7);
  __asm { frstor  byte ptr [esi+8] }
  result = v7[0];
  if ( v4 )
    _rttosnpopde((int)frame);
  return result;
}

