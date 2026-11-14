// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006115E0 __errno
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Call _getptd_noexit; nonNULL returns threadData+8, NULL returns ADDRESS of process fallback DWORD00665278. Does not return current error
// number, initialize/clear error state or force fatal thread-data allocation. Returned writable pointer differs by thread/provider availability, fallback is shared; EAX pointer
// forwarded/plain RET.
int *__cdecl _errno()
{
  DWORD *v0; // eax

  v0 = _getptd_noexit();
  if ( v0 )
    return (int *)(v0 + 2);
  else
    return (int *)&unk_665278;
}

