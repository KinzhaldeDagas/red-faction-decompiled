// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448FF0 rf_vfile_raw_crc32_or_zero
// UNREALRED VERIFIED [event-registry-crc-20261028]: Constructs temporary VFile and calls0x5939E0 with output dword and filename. Any nonzero status returns0; status0 returns computed raw CRC, so failure and legitimate zero CRC are indistinguishable. Destroys temporary VFile in both paths.
int __cdecl rf_vfile_raw_crc32_or_zero(char *String2)
{
  int v2; // [esp+4h] [ebp-138h]
  int v3; // [esp+Ch] [ebp-130h] BYREF
  int self[71]; // [esp+10h] [ebp-12Ch] BYREF
  int v5; // [esp+138h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v5 = 0;
  if ( rf_vfile_compute_raw_crc32(self, &v3, String2, (int)byte_98967F) )
  {
    v5 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
  else
  {
    v2 = v3;
    v5 = -1;
    rf_vfile_destruct_close_if_open(self);
    return v2;
  }
}

