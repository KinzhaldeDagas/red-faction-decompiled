// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D4D3 __EH_prolog3_catch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal EH3 catch frame prolog, not ordinary
// function: EAX=raw frame-handler PC, entry ESP=S stack {helperReturnPC,rawLocalSize,applicationReturnPC,...}, incomingEBP old caller frame. Push EAX handler then previous FS:0,
// compute frameAddress=S+4, subtract raw localSize fromESP, push EBX/ESI/EDI. Store oldEBP atframeAddress,setEBP=frameAddress. Push global securityCookie XOR newEBP; saveESP into
// EBP-10h. Push helperReturnPC fromEBP-4, replace EBP-4 with tryLevel-1, set EAX=EBP-Ch, FS:0=EAX, RET to copied helperReturnPC. Resulting ESP=S-24-localSize; chain
// {previous,handler} at EBP-Ch/EBP-8, application return at EBP+4. EAX output registration address, EBP/ESP transformed; ECX/EDX/live EBX/ESI/EDI unchanged, nonvolatiles saved. No
// own handler call, input/size/pointer guard, scope validation, stack probe or cookie check. Verified CallUnexpected caller supplies localSize4 and own handler6298F3; resulting
// cookie at EBP-20h matches that handler's record-relative check. Existing approximate prototype retained; native ABI contract takes precedence over pseudocode.
_DWORD *__usercall _EH_prolog3_catch@<eax>(int a1@<eax>)
{
  _DWORD v3[2]; // [esp-8h] [ebp-8h] BYREF
  int retaddr; // [esp+0h] [ebp+0h]

  v3[1] = a1;
  v3[0] = NtCurrentTeb()->NtTib.ExceptionList;
  retaddr = -1;
  return v3;
}

