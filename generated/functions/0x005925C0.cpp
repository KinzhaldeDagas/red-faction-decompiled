// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005925C0 rf_vfile_loose_lookup_find_exact_name_node
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl cstring name. Hashes via592660, indexes32768-head table1BA1F00, walks node next pointer+8 and compares input with node-owned cstring pointer+4 using case-sensitive strcmp. Returns matching node pointer (declared int in current database) or0. Wrapper592550 lowercases input first and reads root id from node DWORD0; this function itself performs no case folding, root filtering or allocation. Destruction592920 frees cstring and node separately. No explicit NULL-input, hash-index-range or chain-cycle guard.
int __cdecl rf_vfile_loose_lookup_find_exact_name_node(char *a1)
{
  int i; // [esp+14h] [ebp-8h]

  for ( i = dword_1BA1F00[rf_vfile_loose_name_hash15(a1)]; i; i = *(_DWORD *)(i + 8) )
  {
    if ( !strcmp(a1, *(const char **)(i + 4)) )
      return i;
  }
  return 0;
}

