// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006169B7 notanint
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native MOV EAX,0 then shortJMP sharedRET6169B6. Does not pop/inspectST0 or recompute integer predicate; originalx87 input and flags preserved. This is result
// arm of classifier616991, not a general new integer test.
void notanint()
{
  isintTOSret();
}

