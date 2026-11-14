// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605B30 crt_tail_call_member0_with_ecx_receiver
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime EH tail-call adapter; KEEP library flag. Exact four instructions, no ordinary cdecl body: at entry stack[R return address,object,codeTarget],
// POP EAX capturesR, POP ECX capturesobject, XCHG EAX,[ESP] placesR over original codeTarget slot and loadsTarget intoEAX, then JMP EAX. Target sees ECX=object and its own return
// addressR at currentESP, with no explicit member arguments. A normal targetRET returns to adapter caller with BOTH original DWORD arguments consumed (callee cleanup8), not saved
// prototype's ordinary cdecl cleanup. No own RET, target/object NULL/type validation or separate application result; integer/x87 return and exceptions come straight from tail target.
// Native XCHG is an instruction, not a call to InterlockedExchange; positive-SP decompiler expression is misleading. Fresh EH caller60E864/65 pushes target then object, CALL60E868,
// and performs no caller stack cleanup. Runtime exception destructor/catch-builder context, not game ownership. Existing generic prototype retained conservatively; contract states
// actual stack rearrangement.
// positive sp value has been detected, the output may be wrong!
int __cdecl crt_tail_call_member0_with_ecx_receiver(int a1, int a2)
{
  __int32 v3; // [esp-8h] [ebp-8h]
  _UNKNOWN *retaddr; // [esp+0h] [ebp+0h] BYREF

  return ((int (*)(void))_InterlockedExchange((volatile __int32 *)&retaddr, v3))();
}

