// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F581 __malloc_crt
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(size), repeatedly malloc(same original size),
// retain resultEDI; nonNULL returns immediately. NULL plus zero global20216EC returnsNULL; otherwise retry schedule below. Retry timing: delay starts0; after a failed allocation and
// nonzero LIVE global20216EC call Sleep(delay), compute next=delay+1000 with32-bit wrap, then retry only if next<=LIVE global threshold unsigned and next!=UINT_MAX. Threshold is
// per-delay, not a cumulative elapsed-time budget; initial failure can Sleep(0) then terminate without another allocation if threshold<1000. No own errno rewrite; delegate policy
// retained.
void *__cdecl _malloc_crt(size_t Size)
{
  DWORD v1; // esi
  void *v2; // edi
  int v3; // eax

  v1 = 0;
  do
  {
    v2 = malloc(Size);
    if ( v2 || !unk_20216EC )
      break;
    Sleep(v1);
    v3 = v1 + 1000;
    if ( v1 + 1000 > unk_20216EC )
      v3 = -1;
    v1 = v3;
  }
  while ( v3 != -1 );
  return v2;
}

