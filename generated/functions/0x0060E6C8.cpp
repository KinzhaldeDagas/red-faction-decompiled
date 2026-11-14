// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E6C8 ___FrameUnwindFilter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(const EXCEPTION_POINTERS*), filter EAX0 on
// every normal return. Read ExceptionRecord pointer then code without NULL/length checks. CodeE0434F4D: getptd, signed DWORD PTD+90h>0 ->getptd AGAIN and decrement its DWORD+90h;
// else leave it. CodeE06D7363: getptd, clear DWORD+90h to0, TAIL JMP noreturn terminate, no own frame teardown/return. All other codes return0 with no PTD fetch. This is
// continue-search, not a general catch/handler decision1. Repeated PTD getters not cached, counter decrement conditional signed positive, no locking. Original native filter called by
// FrameUnwindToState's inner SEH scope; its handler can only be selected if filter behavior changes, since local returning paths always0.
int __cdecl __FrameUnwindFilter(const struct _EXCEPTION_POINTERS *a1)
{
  DWORD ExceptionCode; // eax
  DWORD *v2; // eax

  ExceptionCode = a1->ExceptionRecord->ExceptionCode;
  if ( ExceptionCode == -532459699 )
  {
    if ( (int)_getptd()[36] > 0 )
    {
      v2 = _getptd();
      --v2[36];
    }
  }
  else if ( ExceptionCode == -529697949 )
  {
    _getptd()[36] = 0;
    terminate();
  }
  return 0;
}

