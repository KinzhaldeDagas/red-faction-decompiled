// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DE79 __rttosnpopde
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal frame EBP and live CL. Store BYTE[EBP-144]=1, OR CL,CL sets flags from unchangedCL, RET. No x87 pop, new numeric result, frame teardown or stack
// arg. EAX unchanged; body name does not imply value popping. Error-byte/flags are distinct outputs.
void __usercall _rttosnpopde(int a1@<ebp>)
{
  *(_BYTE *)(a1 - 144) = 1;
}

