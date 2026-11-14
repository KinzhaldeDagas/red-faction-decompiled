// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609742 _vsprintf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 11 instructions/26 bytes. Cdecl invoke 0x006096C4 __vsprintf_l with actual ordered4-byte slots
// [callerDWORD0(EBP+8), callerDWORD1(EBP+12), 0x00000000, callerDWORD2(EBP+16)]. Order derived from every raw PUSH, not inherited callee prototype. Own ADD ESP/POP ECX reclaim
// exactly16 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct application-data write, allocation, parsing,
// formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no Boolean/errno normalization.
// Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated.
int __cdecl vsprintf(char *const Buffer, const char *const Format, va_list ArgList)
{
  return _vsprintf_l(Buffer, Format, nullptr, ArgList);
}

