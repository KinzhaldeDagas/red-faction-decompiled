// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FD1B0 rf_jpeg_std_huff_tables
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:std_huff_tables matched): Installs IJG standard Huffman tables:DC luminance slot84,AC luminance100,DCchrominance88,ACchrominance104. Uses localhelper0x5FD230 with original17-byte code-length arrays andsymbol arrays;missing tablesallocated permanent. Existingtable content replaced,sent flags cleared. No direct bitstream emission;APIvoid.
void *__cdecl rf_jpeg_std_huff_tables(int *a1)
{
  rf_jpeg_add_huff_table((int)a1, a1 + 21, (int)&unk_6476D4, &unk_647610);
  rf_jpeg_add_huff_table((int)a1, a1 + 25, (int)&off_64761C, &unk_647630);
  rf_jpeg_add_huff_table((int)a1, a1 + 22, (int)&off_6475FC, &unk_647610);
  return rf_jpeg_add_huff_table((int)a1, a1 + 26, (int)&off_647540, &unk_647558);
}

