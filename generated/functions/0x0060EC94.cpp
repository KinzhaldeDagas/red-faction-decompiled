// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060EC94 ___BuildCatchObject
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(const exceptionRecord*,destinationBase,const
// HandlerType*,const CatchableType*), no semantic result (old int return incidental). Before try, compute destination=base directly if handler adjectives bit80000000 set, else
// base+dispCatchObj+12; no own pointer guard. Arm SEH4 try0 using original65EBE8 scope: filter60ED19 returns1, handler60ED1D restoresESP then terminate. Call BuildCatchObjectHelper
// with all four original slots, reclaim16. Code1: AdjustPointer(exception.object,&Catchable.PMD), push adjusted source,raw copyFunction,destination,call native adapter605B30. Adapter
// consumes destination/codeTarget slots, tail-transfers target with ECX=destination and ONE remaining stack source argument; target must perform member cleanup4. Code2: push
// compatibility virtual-base flag1 BEFORE adjustment, then source/codeTarget/destination; target sees source,1 and must cleanup8. Wrapper has NO explicit source/flag pop. Generic
// adapter prototype hides these extra member args in pseudocode. Other helper values (normally0) skip constructor; native DEC/DEC leaves incidental EAX-2 for0, not a failure code
// promised to caller. Ignore constructor EAX, disarm/SEH epilog/plain RET. Entire helper/adjust/member call is inside wrapper's catch-all termination scope, including helper's own
// pre-try faults; initial wrapper address calculation is outside it. No ctor allocation, object freeing, decoded target, copy rollback or returned status. Original CatchIt ignores
// EAX.
void __cdecl __BuildCatchObject(
        const struct EHExceptionRecord *a1,
        void *a2,
        const HandlerType *a3,
        const CatchableType *a4)
{
  char *v4; // ebx
  int v5; // eax

  if ( a3->adjectives >= 0 )
    v4 = (char *)a2 + a3->dispCatchObj + 12;
  else
    v4 = (char *)a2;
  v5 = __BuildCatchObjectHelper(a1, a2, a3, a4) - 1;
  if ( v5 )
  {
    if ( v5 == 1 )
    {
      __AdjustPointer(a1->params.pExceptionObject, &a4->thisDisplacement);
      crt_tail_call_member0_with_ecx_receiver((int)v4, (int)a4->copyFunction);
    }
  }
  else
  {
    __AdjustPointer(a1->params.pExceptionObject, &a4->thisDisplacement);
    crt_tail_call_member0_with_ecx_receiver((int)v4, (int)a4->copyFunction);
  }
}

