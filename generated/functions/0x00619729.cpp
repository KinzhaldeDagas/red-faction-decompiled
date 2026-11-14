// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00619729 __abnormal_termination
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Noargs. EAX0; read current FS:0 record; only if handlerDWORD+4==unwind_handler then read nested pointer atrecord+12 and itsDWORD+12,compare
// withrecordDWORD+8. Exact equality returns1,all other admitted paths0. No NULL/corrupted-chain guard or traversal of multiple records;predicate on current unwind metadata, no
// cleanup performed.
int __cdecl _abnormal_termination()
{
  int result; // eax
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // ecx

  result = 0;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  if ( (int (__cdecl *)(const struct _EXCEPTION_RECORD *, void *, void *, void **, const _DWORD *))ExceptionList->Handler == _unwind_handler )
    return ExceptionList[1].Next == *((struct _EXCEPTION_REGISTRATION_RECORD **)ExceptionList[1].Handler + 3);
  return result;
}

