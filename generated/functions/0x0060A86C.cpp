// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A86C __findclose
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl find handle. Call imported FindClose unchanged. NonzeroBOOL ->return0. FALSE ->set *_errno()=22 then return-1. No GetLastError lookup/mapping,
// invalid-handler invocation, prevalidation or caller-handle reset; all FindClose failures map same errno22.
int __cdecl _findclose(intptr_t FindHandle)
{
  if ( FindClose((HANDLE)FindHandle) )
    return 0;
  *_errno() = 22;
  return -1;
}

