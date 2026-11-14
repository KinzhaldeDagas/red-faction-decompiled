// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006119D5 __mtinitlocknum
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw lock index),returns1/0. Before checking
// existing pointer, heap2021854==0 invokes FF_MSGBANNER,NMSG_WRITE(30),crtExitProcess(255); if exit returns continue. No index bounds/sign guard: tableentry665280+index*8. Existing
// nonNULL pointer returns1. Otherwisemalloc_crt24; NULL ->errno12/0. Lockglobal10/armSEH,recheck target. A raced installed pointer frees private candidate andreturns1. StillNULL
// ->crtInitCritSecAndSpinCount(candidate,4000); success publish pointer,return1; failurefreecandidate,errno12,return0. Normal/unwind finallyunlock10. KindDWORD untouched, no
// caller-CS acquisition, allocation leak rollback on thrown init helper, or sentinel validation beyond pointerNULL.
int __cdecl _mtinitlocknum(int a1)
{
  struct _RTL_CRITICAL_SECTION *v2; // edi
  int v3; // [esp+10h] [ebp-1Ch]

  v3 = 1;
  if ( !MEMORY[0x2021854] )
  {
    _FF_MSGBANNER();
    _NMSG_WRITE(30);
    __crtExitProcess(0xFFu);
  }
  if ( *(&lpCriticalSection + 2 * a1) )
    return 1;
  v2 = (struct _RTL_CRITICAL_SECTION *)_malloc_crt(0x18u);
  if ( v2 )
  {
    _lock(10);
    if ( *(&lpCriticalSection + 2 * a1) )
    {
      free(v2);
    }
    else if ( __crtInitCritSecAndSpinCount(v2, 0xFA0u) )
    {
      *(&lpCriticalSection + 2 * a1) = v2;
    }
    else
    {
      free(v2);
      *_errno() = 12;
      v3 = 0;
    }
    _unlock(10);
    return v3;
  }
  else
  {
    *_errno() = 12;
    return 0;
  }
}

