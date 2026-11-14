// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B840 rf_vfile_shutdown_roots_and_lookup_tables
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl atexit callback. For each of four32832-byte slots189CEB0, nonzero slot DWORD0 triggers close_stdio_or_vpp on pointer at slot+32816 (18A4EE0+stride*i). Clears root and extension pointers for all512 twelve-byte records, preserving byte flags at+8. Releases shared string pool then frees filename-hash nodes/payloads via592920. Clears first byte of data root and optical root; clears first byte of each configured256-byte volume-label slot; label count=0 and initialized byte189CE90=0. Does not clear shared archive buffer189745C/capacity/name or own/free that caller buffer. No rollback or label-count bound check.
void __cdecl rf_vfile_shutdown_roots_and_lookup_tables()
{
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]
  int k; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 4; ++i )
  {
    if ( unk_189CEB0[8208 * i] )
      rf_vfile_close_stdio_or_vpp((_DWORD *)unk_18A4EE0[8208 * i]);
  }
  for ( j = 0; j < 512; ++j )
  {
    dword_1897490[3 * j] = 0;
    dword_1897494[3 * j] = 0;
  }
  rf_vpackfile_release_shared_string_pool();
  rf_vfile_loose_lookup_free_bucket_chains();
  unk_189CD90 = 0;
  LOBYTE(dword_1898C90) = 0;
  for ( k = 0; k < dword_189CE98; ++k )
    unk_1898D90[256 * k] = 0;
  dword_189CE98 = 0;
  unk_189CE90 = 0;
}

