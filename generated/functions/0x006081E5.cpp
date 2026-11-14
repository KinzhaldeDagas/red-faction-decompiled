// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006081E5 _atol
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 10 instructions/22 bytes. Cdecl invoke 0x0060B4B0 _strtol with actual ordered4-byte slots
// [callerDWORD0(EBP+8), 0x00000000, 0x0000000A]. Order derived from every raw PUSH, not inherited callee prototype. Own ADD ESP/POP ECX reclaim exactly12 bytes after delegate; caller
// original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct application-data write, allocation, parsing, formatting, conversion or lock policy
// in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no Boolean/errno normalization. Any failure, locale/default behavior,
// storage bounds or nonreturn policy is delegated.
int __cdecl atol(const char *String)
{
  return strtol(String, nullptr, 10);
}

