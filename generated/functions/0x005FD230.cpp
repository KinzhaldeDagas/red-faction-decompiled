// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FD230 rf_jpeg_add_huff_table
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:add_huff_table matched): Localcdecl(cinfo,tablePointerSlot,bits17,symbols). Allocates280-byte Huffman table ifNULL via0x5FF3A0;copiesbits[0..16],sumsunsignedbits1..16. Sum outside1..256 invokeserror8 BadHuffTable. Copies exactlysumbytes to huffval+17,sets sent_table276=0. Does not clearunused huffval bytes,validate Kraft/code-tree completeness here or set compressionstate. APIvoid.
void *__cdecl rf_jpeg_add_huff_table(int a1, int *a2, int a3, void *Src)
{
  int v4; // ecx
  void *result; // eax
  int i; // [esp+0h] [ebp-8h]
  int Size; // [esp+4h] [ebp-4h]

  if ( !*a2 )
    *a2 = rf_jpeg_alloc_huff_table(a1);
  v4 = *a2;
  *(_DWORD *)v4 = *(_DWORD *)a3;
  *(_DWORD *)(v4 + 4) = *(_DWORD *)(a3 + 4);
  *(_DWORD *)(v4 + 8) = *(_DWORD *)(a3 + 8);
  *(_DWORD *)(v4 + 12) = *(_DWORD *)(a3 + 12);
  *(_BYTE *)(v4 + 16) = *(_BYTE *)(a3 + 16);
  Size = 0;
  for ( i = 1; i <= 16; ++i )
    Size += *(unsigned __int8 *)(i + a3);
  if ( Size < 1 || Size > 256 )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 8;
    (**(void (__cdecl ***)(int))a1)(a1);
  }
  result = memcpy((void *)(*a2 + 17), Src, Size);
  *(_DWORD *)(*a2 + 276) = 0;
  return result;
}

