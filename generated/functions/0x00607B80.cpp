// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00607B80 _strftime
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 13 instructions/31 bytes. Cdecl invoke 0x006079DC __Strftime_l with actual ordered4-byte slots
// [callerDWORD0(EBP+8), callerDWORD1(EBP+12), callerDWORD2(EBP+16), callerDWORD3(EBP+20), 0x00000000, 0x00000000]. Order derived from every raw PUSH, not inherited callee prototype.
// Own ADD ESP/POP ECX reclaim exactly24 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct application-data
// write, allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no
// Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated. Appended literalNULL selects helper locale/default parameter;
// wrapper does not snapshot a locale.
size_t __cdecl strftime(char *Buffer, size_t SizeInBytes, const char *Format, const struct tm *Tm)
{
  return _Strftime_l(Buffer, SizeInBytes, Format, Tm, nullptr, nullptr);
}

