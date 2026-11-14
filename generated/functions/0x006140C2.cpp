// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006140C2 ___getgmtimebuf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, borrowed struct tm* EAX/NULL (corrected
// false int signature). getptd_noexit;NULL ->errno12/NULL. Reuseexisting PTD+68 pointer. Missing slot: malloc_crt(36),publish result toPTD+68 immediately;NULL
// ->errno12/NULL,successreturnpointer WITHOUT zero/fill. Ownership remains PTD,shared/reused by localtime wrapper; no callerfree obligation, fallbackglobalbuffer, invalidcallback,
// ownlock or initialization of tmfields.
struct tm *__cdecl __getgmtimebuf()
{
  DWORD *v0; // eax
  DWORD *v1; // esi
  void *v3; // eax

  v0 = _getptd_noexit();
  v1 = v0;
  if ( v0 )
  {
    if ( v0[17] )
      return (struct tm *)v1[17];
    v3 = _malloc_crt(0x24u);
    v1[17] = (DWORD)v3;
    if ( v3 )
      return (struct tm *)v1[17];
  }
  *_errno() = 12;
  return nullptr;
}

