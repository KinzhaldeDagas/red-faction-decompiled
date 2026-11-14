// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F356 __initp_eh_hooks_0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Encode fixed terminate function pointer, store encodedEAX at global20213C0,return same encoded value. One4-byte pushed slot reclaimed POP ECX.
// No decode/callback invocation, once/lock or old-value return; exact encoder semantics are separately verified.
PVOID _initp_eh_hooks_0()
{
  PVOID result; // eax

  result = _encode_pointer(terminate);
  unk_20213C0 = result;
  return result;
}

