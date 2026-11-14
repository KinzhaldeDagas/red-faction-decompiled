// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F79D __SEH_epilog4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal SEH4 epilog, not trivialRET. Load ECX=[EBP-16],write FS:0 old exception link. POP ECX gets helper returnPC; POP EDI TWICE,POP ESI,POP EBX; MOV
// ESP,EBP;POP EBP;PUSH savedPC ECX;RET. Tears down CALLER frame and restores nonvolatile/FS chain; no own normal prologue or declared argument stack cleanup. EAX preserved, ECX
// carries returnPC; positive-SP decompiler warning is expected for special epilog ABI, not absence of cleanup.
// positive sp value has been detected, the output may be wrong!
void _SEH_epilog4()
{
  __asm { retn }
}

