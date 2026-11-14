// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061CE10 __mbsnbicoll
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 11 instructions/26 bytes. Cdecl invoke 0x0061CD22 __mbsnbicoll_l with actual ordered4-byte slots
// [callerDWORD0(EBP+8), callerDWORD1(EBP+12), callerDWORD2(EBP+16), 0x00000000]. Order derived from every raw PUSH, not inherited callee prototype. Own ADD ESP/POP ECX reclaim
// exactly16 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct application-data write, allocation, parsing,
// formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no Boolean/errno normalization.
// Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated. Appended literalNULL selects helper locale/default parameter; wrapper does not snapshot a
// locale.
int __cdecl _mbsnbicoll(const unsigned __int8 *Str1, const unsigned __int8 *Str2, size_t MaxCount)
{
  return _mbsnbicoll_l(Str1, Str2, MaxCount, nullptr);
}

