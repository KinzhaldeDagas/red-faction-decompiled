// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C746 __strdate
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl caller buffer. Call strdate_s(buffer,literal9), preserve original buffer only when helper status==0; any nonzero status ->NULL using NEG/SBB/NOT/AND.
// Does not receive/prove actual caller capacity9, allocate or normalize helper errno. No own date formatting/NULL validation.
char *__cdecl _strdate(char *Buffer)
{
  return _strdate_s(Buffer, 9u) == 0 ? Buffer : nullptr;
}

