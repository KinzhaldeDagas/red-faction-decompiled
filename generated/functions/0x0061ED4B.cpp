// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061ED4B __sopen_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 13 instructions/32 bytes. Cdecl invoke 0x0061EC7F __sopen_helper with actual ordered4-byte slots
// [callerDWORD1(EBP+12), callerDWORD2(EBP+16), callerDWORD3(EBP+20), callerDWORD4(EBP+24), callerDWORD0(EBP+8), 0x00000001]. Order derived from every raw PUSH, not inherited callee
// prototype. Own ADD ESP/POP ECX reclaim exactly24 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct
// application-data write, allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if
// delegate returns, no Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated.
errno_t __cdecl _sopen_s(int *FileHandle, const char *FileName, int OpenFlag, int ShareFlag, int PermissionMode)
{
  return _sopen_helper(FileName, OpenFlag, ShareFlag, PermissionMode, FileHandle, 1);
}

