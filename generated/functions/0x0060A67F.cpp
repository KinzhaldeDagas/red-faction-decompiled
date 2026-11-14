// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A67F __c_exit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 6 instructions/15 bytes. Cdecl invoke 0x0060A518 _doexit with actual ordered4-byte slots [0x00000000,
// 0x00000001, 0x00000001]. Order derived from every raw PUSH, not inherited callee prototype. Own ADD ESP/POP ECX reclaim exactly12 bytes after delegate; caller original arguments
// remain for caller cleanup, plain RET. No branch, argument validation, direct application-data write, allocation, parsing, formatting, conversion or lock policy in wrapper. Only
// frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or
// nonreturn policy is delegated.
void __cdecl _c_exit()
{
  doexit(0, 1, 1);
}

