// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605B8B ___CxxFrameHandler3
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Native handler adapter with EAX=FuncInfo*, four
// caller-popped stack slots {ExceptionRecord*,registration*,context*,dispatcherContext}; plain RET. Save EBX/ESI/EDI, CLD, save entry EAX. Call InternalCxxFrameHandler with eight
// ordered DWORD slots {original0,original1,original2,original3,entryEAX,0 catchDepth,0 marker,0 recursive}; reclaim32, preserve/return helper EAX, restore saved registers/frame. No
// own exception-code filtering, FuncInfo decoding, cookie/argument validation, local unwind or exception-chain installation. Corrected shared helper prototype restores
// context/dispatcher/depth interpretation; old helper type made pseudocode mislabel these native stack slots. CLD changes direction flag, no restoring old DF.
int __usercall __CxxFrameHandler3@<eax>(
        struct _s_FuncInfo *a1@<eax>,
        struct EHExceptionRecord *a2,
        struct EHRegistrationNode *a3,
        struct _CONTEXT *a4,
        void *a5)
{
  return __InternalCxxFrameHandler(a2, a3, a4, a5, a1, 0, nullptr, 0);
}

