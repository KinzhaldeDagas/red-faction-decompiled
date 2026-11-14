// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00601E60 rf_jpeg_huff_emit_bits
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:emit_bits matched): Localboolean(workingState,unsignedcode,intsize). size0fatal40 MissingHuffmanCode;noothergeneralsize-rangeguard(validcallerssupplyboundedcodes). Maskstolowsizebits,ORsinto24-bitstagingpositionusingput_buffer8/put_bits12. While>=8pendingbits,outputsbits16..23 byte,flushesfullbufferthroughdump_buffer;onFALSEreturns0. AnyentropybyteFFfollowedby00stuffing,whichcanalsoflush/suspend. Successfulendstoresupdatedbuffer/pendingcount andreturns1. Writeslocalstatebuffer,notpersistentcinfofields;native32-bitshiftsassumevalidsize/pendingcount.
int __cdecl rf_jpeg_huff_emit_bits(int a1, int a2, int a3)
{
  int v4; // [esp+4h] [ebp-8h]
  int v5; // [esp+4h] [ebp-8h]
  int v6; // [esp+8h] [ebp-4h]

  v4 = *(_DWORD *)(a1 + 12);
  if ( !a3 )
  {
    *(_DWORD *)(**(_DWORD **)(a1 + 32) + 20) = 40;
    (***(void (__cdecl ****)(_DWORD))(a1 + 32))(*(_DWORD *)(a1 + 32));
  }
  v5 = a3 + v4;
  v6 = *(_DWORD *)(a1 + 8) | ((a2 & ((1 << a3) - 1)) << (24 - v5));
  while ( v5 >= 8 )
  {
    *(_BYTE *)(*(_DWORD *)a1)++ = BYTE2(v6);
    if ( !--*(_DWORD *)(a1 + 4) && !rf_jpeg_huff_dump_buffer((_DWORD *)a1) )
      return 0;
    if ( BYTE2(v6) == 255 )
    {
      *(_BYTE *)(*(_DWORD *)a1)++ = 0;
      if ( !--*(_DWORD *)(a1 + 4) && !rf_jpeg_huff_dump_buffer((_DWORD *)a1) )
        return 0;
    }
    v6 <<= 8;
    v5 -= 8;
  }
  *(_DWORD *)(a1 + 8) = v6;
  *(_DWORD *)(a1 + 12) = v5;
  return 1;
}

