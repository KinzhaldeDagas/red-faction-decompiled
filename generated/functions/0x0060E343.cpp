// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E343 __getptd
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Call getptd_noexit, save resultESI. NonNULL returns same pointer. NULL invokes amsg_exit(16); if fatal helper unexpectedly returns, pop its
// argument and still return originalNULL, no retry/re-fetch. ESI preserved. No separate thread allocation/NULL dereference in this wrapper; fatal policy delegated.
DWORD *_getptd()
{
  DWORD *v0; // esi

  v0 = _getptd_noexit();
  if ( !v0 )
    _amsg_exit(16);
  return v0;
}

