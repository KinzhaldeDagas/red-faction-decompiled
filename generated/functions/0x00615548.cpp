// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00615548 @_EH4_LocalUnwind@16
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Fastcall ECX registration,EDX target level plus TWO stackDWORDs(frame,cookiePointer),RET8. Save oldEBP then setEBP=stackframe; cdecl
// local_unwind4(cookiePointer,registration,level),ADD12;restoreoldEBP. No own cookie dereference/validation or handler walk. Raw delegateEAX returned; decorated16 counts two
// registers+two stack slots, only8 bytes purged.
void __fastcall _EH4_LocalUnwind(_DWORD *a1, unsigned int a2, void *a3, unsigned int *a4)
{
  _local_unwind4(a3, a4, a1, a2);
}

