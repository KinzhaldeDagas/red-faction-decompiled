// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DCA5 _wctomb_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 12 instructions/29 bytes. Cdecl invoke 0x0061DB39 __wctomb_s_l with actual ordered4-byte slots
// [callerDWORD0(EBP+8), callerDWORD1(EBP+12), callerDWORD2(EBP+16), callerDWORD3(EBP+20), 0x00000000]. Order derived from every raw PUSH, not inherited callee prototype. Own ADD
// ESP/POP ECX reclaim exactly20 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct application-data write,
// allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no
// Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated. Appended literalNULL selects helper locale/default parameter;
// wrapper does not snapshot a locale.
errno_t __cdecl wctomb_s(int *SizeConverted, char *MbCh, rsize_t SizeInBytes, wchar_t WCh)
{
  return _wctomb_s_l(SizeConverted, MbCh, SizeInBytes, WCh, nullptr);
}

