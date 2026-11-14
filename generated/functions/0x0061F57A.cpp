// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061F57A __ismbblead
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 11 instructions/24 bytes. Cdecl invoke 0x0061F527 ?x_ismbbtype_l@@YAHPAUlocaleinfo_struct@@IHH@Z with
// actual ordered4-byte slots [0x00000000, callerDWORD0(EBP+8), 0x00000000, 0x00000004]. Order derived from every raw PUSH, not inherited callee prototype. Own ADD ESP/POP ECX reclaim
// exactly16 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct application-data write, allocation, parsing,
// formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no Boolean/errno normalization.
// Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated.
int __cdecl _ismbblead(unsigned int Ch)
{
  return x_ismbbtype_l(nullptr, Ch, 0, 4);
}

