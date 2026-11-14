// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A990 rf_text_parser_crc32_entire_loaded_buffer_raw
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): ECX parser. Constructs and resets local DWORD CRC accumulator to0 via57B280 and5E6D30, then calls reflected raw CRC update5E6D50 with parser.buffer at0 and byte count at268. Returns raw zero-seeded/non-complemented CRC in EAX. Covers whole loaded buffer, independent of current cursor/line, excluding file-loader appended NUL when size268 is original file length. Does not repair missing/stale size268 after load_owned_cstring5790F0; no buffer or negative-length validation. Does not advance parser cursor.
unsigned int __thiscall rf_text_parser_crc32_entire_loaded_buffer_raw(void *self)
{
  int v3; // [esp+8h] [ebp-4h] BYREF

  rf_crc32_accumulator_construct_zero(&v3);
  rf_crc32_accumulator_reset_zero(&v3);
  return rf_crc32_update_reflected_raw(&v3, *(_BYTE **)self, *((_DWORD *)self + 67));
}

