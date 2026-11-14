// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D31F __fptrap
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 4 instructions/9 bytes. Cdecl invoke 0x0060A3D4 __amsg_exit with actual ordered4-byte slots [0x00000002].
// Order derived from every raw PUSH, not inherited callee prototype. Own ADD ESP/POP ECX reclaim exactly4 bytes after delegate; caller original arguments remain for caller cleanup,
// plain RET. No branch, argument validation, direct application-data write, allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after
// CALL: raw delegate result registers forwarded if delegate returns, no Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is
// delegated.
int _fptrap()
{
  return _amsg_exit(2);
}

