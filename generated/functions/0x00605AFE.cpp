// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605AFE ?_JumpToContinuation@@YGXPAXPAUEHRegistrationNode@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Nonreturning native continuation transfer, two
// stdcall-style stack inputs {destinationPC,EH registration*}; no CALL of destination and no own RET. Save frame+12 locally, unlink CURRENT fs:0 record by assigning
// fs:0=*(DWORD*)fs:0, load EAX=destination, EBX=registration, EBP=registration+12, ESP=*(DWORD*)(registration-4), then JMP EAX. Entry ECX not consumed, saved EBX/old frame
// deliberately not restored because stack context abandoned. Destination receives those registers and restored stack, not two callback arguments. No registration-chain search,
// NULL/cookie/target check, cleanup fallback or return to caller. Original CatchIt pushes registration then continuation PC returned by CallCatchBlock.
void __stdcall _JumpToContinuation(void *a1, struct EHRegistrationNode *a2)
{
  ((void (__stdcall *)(void *, struct EHRegistrationNode *))a1)(a1, a2);
}

