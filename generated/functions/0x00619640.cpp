// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00619640 __global_unwind2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl TargetFrame. Buildframe/saveEBX/ESI/EDI andextraEBP,call RtlUnwind(TargetFrame,localLanding619658,NULL,NULL). Landing restores
// extraEBP/nonvolatiles,ESP=EBP,oldEBP,RET. No own exception-list traversal/cookie check or caller-slot purge; API owns actual global unwind and may transfer directly to landing.
void __cdecl _global_unwind2(PVOID TargetFrame)
{
  RtlUnwind(TargetFrame, &gu_return, nullptr, nullptr);
}

