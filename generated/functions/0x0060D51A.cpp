// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D51A __cftoe
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 13 instructions/32 bytes. Cdecl invoke 0x0060D44A __cftoe_l with actual ordered4-byte slots
// [callerDWORD0(EBP+8), callerDWORD1(EBP+12), callerDWORD2(EBP+16), callerDWORD3(EBP+20), callerDWORD4(EBP+24), 0x00000000]. Order derived from every raw PUSH, not inherited callee
// prototype. Own ADD ESP/POP ECX reclaim exactly24 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct
// application-data write, allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if
// delegate returns, no Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated. Appended literalNULL selects helper
// locale/default parameter; wrapper does not snapshot a locale.
int __cdecl _cftoe(double *a1, _BYTE *a2, unsigned int a3, int a4, int a5)
{
  return _cftoe_l(a1, a2, a3, a4, a5, nullptr);
}

