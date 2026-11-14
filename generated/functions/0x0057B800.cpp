// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B800 rf_vfile_is_valid_search_root_id
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl id, AL boolean. Special decimal9999999 (0x98967F) accepted. Otherwise rejects signed negative or >=512; accepts0 without requiring root pointer, and accepts1..511 only if registered-root pointer at1897490+12*id nonnull. Raw signed branches verify bounds despite unsigned inferred prototype. Does not validate extension/flags fields or actual directory existence.
bool __cdecl rf_vfile_is_valid_search_root_id(int a1)
{
  if ( (char *)a1 == byte_98967F )
    return 1;
  if ( (unsigned int)a1 >= 0x200 )
    return 0;
  return a1 <= 0 || dword_1897490[3 * a1];
}

