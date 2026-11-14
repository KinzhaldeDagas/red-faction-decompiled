// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00619774 __NLG_Call
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): CALL EAX thenRET. Caller supplies function entry inEAX; helper contributes one return-address slot and no explicit arguments, frame, validation or cleanup.
// Callee result registers forwarded, no Boolean/status normalization; Target stack contains new CALL return PC above helper original return PC; original helper arguments are not
// repushed.
int __usercall _NLG_Call@<eax>(int (*a1)(void)@<eax>)
{
  return a1();
}

