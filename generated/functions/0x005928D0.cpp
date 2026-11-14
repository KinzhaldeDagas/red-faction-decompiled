// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005928D0 rf_vfile_loose_lookup_clear_bucket_heads
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl init called by57B920. Sets all32768 DWORD bucket heads at1BA1F00 toNULL and auxiliary DWORD1BA1EF8 to0, returns32768 in EAX. Does not free preexisting linked nodes or payloads; intended initialization. See592550 lookup and592920 destruction for corresponding bucket storage.
int rf_vfile_loose_lookup_clear_bucket_heads()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 0x8000; ++i )
  {
    dword_1BA1F00[i] = 0;
    result = i + 1;
  }
  unk_1BA1EF8 = 0;
  return result;
}

