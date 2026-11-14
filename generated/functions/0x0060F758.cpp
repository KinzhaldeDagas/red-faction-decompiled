// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F758 __SEH_prolog4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal SEH4 frame-building adapter, retain
// conservative old prototype because ordinary C call/return cannot describe ESP/EBP outputs. Entry ESP=S stack {helperReturnPC,rawScopeTable,rawLocalSize,...}, incomingEBP old frame.
// Push except_handler4 PC then previousFS:0; load EAX=localSize fromS+8, replace that slot with oldEBP, set EBP=S+8. Subtract unsigned raw localSize fromESP, push liveEBX/ESI/EDI.
// XOR scopeTable at EBP-4 with global securityCookie; push cookie XOR newEBP, store resultingESP at EBP-18h. Push original helperReturnPC fromEBP-8, move encoded scopeTable
// intoEBP-8, set tryLevel EBP-4=-2, set EAX=EBP-10h and FS:0=EAX, RET to copied helperReturnPC. EAX points registration, EBP/ESP deliberately transformed; final ESP=S-24-localSize.
// ECX/EDX and live EBX/ESI/EDI unchanged, old nonvolatiles saved for epilog. No ordinary stack cleanup or Boolean result, scopeTable dereference, cookie check, NULL/size/overflow
// guard or stack probe. Original caller subsequently uses standard frame with original application return at EBP+4; old pseudocode alloca/return expression omits chain/frame surgery.
_DWORD *__usercall _SEH_prolog4@<eax>(int a1@<ebp>, int a2, int a3)
{
  int v3; // eax
  void *v4; // esp
  _DWORD v6[2]; // [esp-8h] [ebp-8h] BYREF
  unsigned int retaddr; // [esp+0h] [ebp+0h]
  int v8; // [esp+4h] [ebp+4h]

  v6[1] = _except_handler4;
  v6[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v3 = a3;
  a3 = a1;
  v4 = alloca(v3);
  v8 = -2;
  retaddr = (unsigned int)&a3 ^ dword_664BD8;
  return v6;
}

