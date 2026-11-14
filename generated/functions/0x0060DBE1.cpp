// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DBE1 __cfltcvt
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 14 instructions/35 bytes. Cdecl invoke 0x0060DB59 __cfltcvt_l with actual ordered4-byte slots
// [callerDWORD0(EBP+8), callerDWORD1(EBP+12), callerDWORD2(EBP+16), callerDWORD3(EBP+20), callerDWORD4(EBP+24), callerDWORD5(EBP+28), 0x00000000]. Order derived from every raw PUSH,
// not inherited callee prototype. Own ADD ESP/POP ECX reclaim exactly28 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument
// validation, direct application-data write, allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers
// forwarded if delegate returns, no Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated. Appended literalNULL selects
// helper locale/default parameter; wrapper does not snapshot a locale.
int __cdecl _cfltcvt(_DWORD *a1, char *a2, unsigned int a3, int a4, size_t Size, int a6)
{
  return _cfltcvt_l(a1, a2, a3, a4, Size, a6, nullptr);
}

