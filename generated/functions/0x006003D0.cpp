// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006003D0 rf_jpeg_jcopy_block_row
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jutils.c:jcopy_block_row matched): Recoveredoriginalfunction0x6003D0..0x6003EC. Cdecl(inputBlockRow,outputBlockRow,unsignednumBlocks),memcpy(output,input,numBlocks<<7). Eachblock64signed16coefficients=128bytes. No overlap/bounds/32-bitshift-overflowguardorallocation. VoidAPI;incidentalEAXmemcpyresult.
void __cdecl rf_jpeg_jcopy_block_row(const __int16 *input_row, __int16 *output_row, unsigned int num_blocks)
{
  memcpy(output_row, input_row, num_blocks << 7);
}

