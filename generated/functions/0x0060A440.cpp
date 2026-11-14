// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A440 __lockexit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 4 instructions/9 bytes. Cdecl invoke 0x00611A98 __lock with actual ordered4-byte slots [0x00000008]. Order
// derived from every raw PUSH, not inherited callee prototype. Own ADD ESP/POP ECX reclaim exactly4 bytes after delegate; caller original arguments remain for caller cleanup, plain
// RET. No branch, argument validation, direct application-data write, allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw
// delegate result registers forwarded if delegate returns, no Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated.
void _lockexit()
{
  _lock(8);
}

