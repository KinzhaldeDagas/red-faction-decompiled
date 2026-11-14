// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00577EF0 rf_bitmap_load_m2v_bytes_by_slot
// UNREALRED VERIFIED [bitmap-decoders-20261028]: Argument ordinary bitmap slot INDEX. Passes record name and address of record pixel pointer+72 to0x5E6030, returns whether resulting byte count is nonzero. Loads encoded movie bytes, not decoded image pixels. Does not validate reported movie dimensions, file type or existing pointer ownership.
bool __cdecl rf_bitmap_load_m2v_bytes_by_slot(int a1)
{
  return rf_m2v_read_whole_file_allocated((char *)(dword_1897344 + 108 * a1), (char **)(dword_1897344 + 108 * a1 + 72)) != 0;
}

