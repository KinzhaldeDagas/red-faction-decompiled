// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006088EB _fread
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Complete native straight-line forwarding adapter, 12 instructions/29 bytes. Cdecl invoke 0x00608855 _fread_s with actual ordered4-byte slots
// [callerDWORD0(EBP+8), 0xFFFFFFFF, callerDWORD1(EBP+12), callerDWORD2(EBP+16), callerDWORD3(EBP+20)]. Order derived from every raw PUSH, not inherited callee prototype. Own ADD
// ESP/POP ECX reclaim exactly20 bytes after delegate; caller original arguments remain for caller cleanup, plain RET. No branch, argument validation, direct application-data write,
// allocation, parsing, formatting, conversion or lock policy in wrapper. Only frame/stack cleanup after CALL: raw delegate result registers forwarded if delegate returns, no
// Boolean/errno normalization. Any failure, locale/default behavior, storage bounds or nonreturn policy is delegated.
size_t __cdecl fread(void *Buffer, size_t ElementSize, size_t ElementCount, FILE *Stream)
{
  return fread_s(Buffer, 0xFFFFFFFF, ElementSize, ElementCount, Stream);
}

