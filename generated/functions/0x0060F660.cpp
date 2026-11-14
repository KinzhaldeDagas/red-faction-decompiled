// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F660 __recalloc_crt
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(block,count,width), repeatedly
// recalloc(original three slots). NonNULL returns; NULL with WIDTH0 stops. Count/product are NOT tested for retry admission, so count0,width>0 can retry a total-size-zero operation
// on the same original block. Global20216EC0 also stops. Retry timing: delay starts0; after a failed allocation and nonzero LIVE global20216EC call Sleep(delay), compute
// next=delay+1000 with32-bit wrap, then retry only if next<=LIVE global threshold unsigned and next!=UINT_MAX. Threshold is per-delay, not a cumulative elapsed-time budget; initial
// failure can Sleep(0) then terminate without another allocation if threshold<1000. No own errno rewrite; delegate policy retained.
void *__cdecl _recalloc_crt(void *Block, size_t Count, size_t Size)
{
  DWORD v3; // esi
  void *v4; // edi
  int v5; // eax

  v3 = 0;
  do
  {
    v4 = _recalloc(Block, Count, Size);
    if ( v4 || !Size || !unk_20216EC )
      break;
    Sleep(v3);
    v5 = v3 + 1000;
    if ( v3 + 1000 > unk_20216EC )
      v5 = -1;
    v3 = v5;
  }
  while ( v5 != -1 );
  return v4;
}

