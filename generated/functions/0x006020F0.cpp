// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006020F0 rf_jpeg_huff_flush_bits
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:flush_bits matched): Booleanworkingstate. emit_bits(code127,size7) padsanypartialbytetoboundarywithones,withnormalFF00stuffing. Ifemitfailsreturns0;otherwiseclearsput_buffer8/put_bits12,returns1,discardingremainingpaddingbits. Pendingcount0emitsnobyte(only7paddingbitsdiscarded). DoesnotcallFILEfflush.
int __cdecl rf_jpeg_huff_flush_bits(int a1)
{
  if ( !rf_jpeg_huff_emit_bits(a1, 127, 7) )
    return 0;
  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)(a1 + 12) = 0;
  return 1;
}

