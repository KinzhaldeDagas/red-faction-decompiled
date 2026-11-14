// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F5C6 __calloc_crt
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(count,width), pointer returnEAX despite stored
// int-return signature. Repeatedly calloc_impl(count,width,NULLstatus), preserving original two slots; nonNULL exits, NULL and global20216EC0 exits. Optional status pointer
// deliberatelyNULL, unlike public calloc. Retry timing: delay starts0; after a failed allocation and nonzero LIVE global20216EC call Sleep(delay), compute next=delay+1000 with32-bit
// wrap, then retry only if next<=LIVE global threshold unsigned and next!=UINT_MAX. Threshold is per-delay, not a cumulative elapsed-time budget; initial failure can Sleep(0) then
// terminate without another allocation if threshold<1000. No own errno rewrite; delegate policy retained.
LPVOID __cdecl _calloc_crt(size_t Size, unsigned int a2)
{
  DWORD v2; // esi
  LPVOID v3; // edi
  int v4; // eax

  v2 = 0;
  do
  {
    v3 = _calloc_impl(Size, a2, nullptr);
    if ( v3 || !unk_20216EC )
      break;
    Sleep(v2);
    v4 = v2 + 1000;
    if ( v2 + 1000 > unk_20216EC )
      v4 = -1;
    v2 = v4;
  }
  while ( v4 != -1 );
  return v3;
}

