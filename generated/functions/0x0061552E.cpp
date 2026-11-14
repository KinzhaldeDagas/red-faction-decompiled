// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061552E @_EH4_GlobalUnwind@4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): ECX target exception frame, no caller stack slots. Establishframe/saveEBX/ESI/EDI,push four stdcall RtlUnwind
// slots(targetFrame,localReturnPoint615543,NULL,NULL),CALL import thunk. Local landing point restores nonvolatiles/frame andRET. No own exception record, target callback invocation
// or frame-list traversal; unwind API owns control transfer.
void __thiscall _EH4_GlobalUnwind(PVOID TargetFrame)
{
  RtlUnwind(TargetFrame, &ReturnPoint, nullptr, nullptr);
}

