// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060ED26 ?CatchIt@@YAXPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAU_CONTEXT@@PAXPBU_s_FuncInfo@@PBU_s_HandlerType@@PBU_s_CatchableType@@PBU_s_TryBlockMapEntry@@H1E@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Mixed ABI EBX=const HandlerType*,EDI=const
// TryBlockMapEntry*,ESI=registration*, seven caller-popped stack slots {exception*,context*,dispatcherContext,const FuncInfo*,optional CatchableType*,signed catchDepth,optional
// targetFrameRegistration*}. Return void on normal NULL continuation; other path abandons stack via JumpToContinuation. Corrected old shifted stack types and register record types.
// If CatchableType nonNULL call BuildCatchObject(exception,registration,handler,catchable),reclaim16; foreign catch-all supplies NULL and skips object construction. Stdcall
// UnwindNestedFrames(targetFrame if nonNULL else registration,exception). Cdecl FrameUnwindToState(registration,dispatcherContext,FuncInfo,tryLow), leave its16 stack bytes pending.
// Store full registration.stateDWORD+8=tryHigh+1 modulo32. Load ECX=handler.addressOfHandler+12, call CallCatchBlock with six stack slots
// {exception,registration,context,FuncInfo,catchDepth,100h notify}; one ADD ESP40 reclaims BOTH prior unwind16 and catch24. Returned EAX NULL ->plain RET to search caller; nonNULL
// push registration/continuation and call JumpToContinuation, which restores parent stack/frame and JMPs rather than returning. No own SEH scope, handler/state/map/target validation,
// cookie, exception filter, loop or status interpretation beyond NULL. Selected records/registers are inputs, not phantom extra stack arguments.
void __usercall CatchIt(
        const HandlerType *a1@<ebx>,
        const TryBlockMapEntry *a2@<edi>,
        struct EHRegistrationNode *a3@<esi>,
        struct EHExceptionRecord *ExceptionRecord,
        struct _CONTEXT *a5,
        void *a6,
        const struct _s_FuncInfo *a7,
        const CatchableType *a8,
        int a9,
        struct EHRegistrationNode *TargetFrame)
{
  void *v10; // eax

  if ( a8 )
    __BuildCatchObject(ExceptionRecord, a3, a1, a8);
  if ( TargetFrame )
    _UnwindNestedFrames(TargetFrame, ExceptionRecord);
  else
    _UnwindNestedFrames(a3, ExceptionRecord);
  __FrameUnwindToState(a3, a6, a7, a2->tryLow);
  a3->state = a2->tryHigh + 1;
  v10 = CallCatchBlock(a1->addressOfHandler, ExceptionRecord, a3, a5, a7, a9, 0x100u);
  if ( v10 )
    _JumpToContinuation(v10, a3);
}

