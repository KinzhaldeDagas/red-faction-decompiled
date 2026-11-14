// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F1EC ___InternalCxxFrameHandler
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl eight slots
// {exception*,registration*,context*,dispatcherContext,FuncInfo*,signed catchDepth,markerRegistration*,BYTE recursive}. Corrected formerly shifted context/dispatcher and HandlerType*
// depth typing. Return disposition1 on all local normal paths; forward-compat callback result returned raw. Getptd then skip ordinary handling ONLY when PTD+20Ch==0,exceptionCode
// neitherE06D7363 nor80000026,FuncInfo magic&1FFFFFFF>=19930522 AND byte FuncInfo+20h mask1 set. Otherwise flags&66h: if DWORD FuncInfo+4 nonzero AND catchDepth==0 call
// FrameUnwindToState(registration,dispatcherContext,FuncInfo,-1); ignore result,return1. Dispatch path eligible when nTryBlocks(+Ch)nonzero OR masked magic>=19930521 and FuncInfo+1Ch
// nonNULL. For C++ codeE06D7363, parameterCount>=3 and exception magicDWORD+14h UNSIGNED>19930522: dereference ThrowInfo pointer exception+1Ch,load callback+8; if nonNULL call it
// with original first7 slots plus ZERO-EXTENDED recursiveBYTE,return raw EAX. Else FindHandler(exception,registration,context,dispatcherContext,FuncInfo,RAW original eighth
// DWORD,signed catchDepth,marker),ignore return,return1. Only forward-compat path explicitly narrows eighth slot before forwarding. No own NULL/record-size/map validation, cookie,
// local SEH, state update or recursion limit. Callee owns handler search/unwind; preserve EBX/ESI/EDI.
int __cdecl __InternalCxxFrameHandler(
        struct EHExceptionRecord *a1,
        struct EHRegistrationNode *a2,
        struct _CONTEXT *a3,
        void *a4,
        const struct _s_FuncInfo *a5,
        int a6,
        struct EHRegistrationNode *a7,
        unsigned __int8 a8)
{
  int (__cdecl *pForwardCompat)(); // edx

  if ( _getptd()[131]
    || a1->ExceptionCode == -529697949
    || a1->ExceptionCode == -2147483610
    || (*(_DWORD *)a5 & 0x1FFFFFFFu) < 0x19930522
    || (a5->EHFlags & 1) == 0 )
  {
    if ( (a1->ExceptionFlags & 0x66) != 0 )
    {
      if ( a5->maxState )
      {
        if ( !a6 )
          __FrameUnwindToState(a2, a4, a5, -1);
      }
    }
    else if ( a5->nTryBlocks || (*(_DWORD *)a5 & 0x1FFFFFFFu) >= 0x19930521 && a5->pESTypeList )
    {
      if ( a1->ExceptionCode == -529697949 && a1->NumberParameters >= 3 && a1->params.magicNumber > 0x19930522 )
      {
        pForwardCompat = a1->params.pThrowInfo->pForwardCompat;
        if ( pForwardCompat )
          return ((int (__cdecl *)(struct EHExceptionRecord *, struct EHRegistrationNode *, struct _CONTEXT *, void *, const struct _s_FuncInfo *, int, struct EHRegistrationNode *, _DWORD))pForwardCompat)(
                   a1,
                   a2,
                   a3,
                   a4,
                   a5,
                   a6,
                   a7,
                   a8);
      }
      FindHandler(a1, a2, a3, a4, a5, a8, a6, a7);
    }
  }
  return 1;
}

