// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A823 __mbspbrk
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 10 instructions/23 bytes. Cdecl invoke 0x0061A756 __mbspbrk_l with actual ordered4-byte slots
// [callerDWORD0(EBP+8), callerDWORD1(EBP+12), 0x00000000]. Order derived from every raw PUSH, not inherited callee prototype. Own ADD ESP/POP ECX reclaim exactly12 bytes after
// delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct application-data write, allocation, parsing, formatting, conversion
// or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no Boolean/errno normalization. Any failure,
// locale/default behavior, storage bounds or nonreturn policy is delegated. Appended literalNULL selects helper locale/default parameter; wrapper does not snapshot a locale.
unsigned __int8 *__cdecl _mbspbrk(const unsigned __int8 *String, const unsigned __int8 *Control)
{
  return _mbspbrk_l(String, Control, nullptr);
}

