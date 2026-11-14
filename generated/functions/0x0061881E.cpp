// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061881E __ctrlfp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl TWO stack DWORD slots
// {rawNewValue,rawMask},int old native x87 CW SIGN-EXTENDED from16bits; entryECX not an input (old fastcall one-int16 prototype false). Waiting FSTCW stores only WORD into four-byte
// local. Compute ((oldLocalDWORD &~rawMask)|(rawNewValue &rawMask)) then MOVZX AX,so uninitialized high localWORD does not affect final low16. Overwrite own by-value mask stack slot
// with zero-extended newWORD,FLDCW that WORD. Return MOVSX old localWORD,not new CW or logical control87 flags. High mask/value bits discarded; no readback
// normalization,errno,parameter validation,status clear,SEH or old-state rollback. FSTCW WAIT may deliver pending FP exceptions; loads use live environment. Does not save
// floating/SSE data or modify MXCSR. Corrected ABI makes original callers' two pushes/ADD8 visible.
int __cdecl _ctrlfp(unsigned int a1, unsigned int a2)
{
  __int16 v2; // cx

  return v2;
}

