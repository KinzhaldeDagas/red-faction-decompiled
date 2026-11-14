// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4A40 rf_vfile_compare_raw_crc32
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): cdecl(filename,expectedCRC32). NULL/empty filename ->-1. Otherwise constructs local virtual file, calls open(filename,1,raw
// immediate0x0098967F); nonzero open result ->destroy file and return-1. Open0: computes rawCRC32(&output,NULL,0x0098967F); nonzero CRC delegate result OR different32-bit CRC
// ->destroy and return1; matching CRC with result0 ->destroy and return0. The push immediate0x98967F is not a dereference of IDA byte_98967F label. SEH cleanup closes/destroys local
// file on unwind. No source filename length limit, case normalization, asynchronous transfer, expected-value sign interpretation or caller-state change.
int __cdecl rf_vfile_compare_raw_crc32(char *Str, int a2)
{
  int v3; // [esp+20h] [ebp-130h] BYREF
  int self[71]; // [esp+24h] [ebp-12Ch] BYREF
  int v5; // [esp+14Ch] [ebp-4h]

  if ( !Str || !strlen(Str) )
    return -1;
  rf_vfile_construct_unopened(self);
  v5 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, byte_98967F) )
  {
    v5 = -1;
    rf_vfile_destruct_close_if_open(self);
    return -1;
  }
  else if ( rf_vfile_compute_raw_crc32(self, &v3, nullptr, (int)byte_98967F) || v3 != a2 )
  {
    v5 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 1;
  }
  else
  {
    v5 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
}

