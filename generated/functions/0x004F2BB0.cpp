// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2BB0 rf_archive_collect_startup_metadata
// UNREALRED VERIFIED [save-validation-20261028]: Optionally forms configured archive basename + .vpp at0x6630FC through0x4F0330. Iterates two nonempty archive names at0x006630E4 stride24. Stores VFile size at0x88E67C[i] unless result=-4, and nonzero result of0x448FF0 at0x88E674[i]. The second helper value is not established here; do not assume a particular checksum algorithm.
// UNREALRED VERIFIED [event-registry-crc-20261028]: Further verified: helper0x448FF0 supplies raw zero-seeded, non-complemented reflected CRC32 using polynomial0xEDB88320. Nonzero CRC updates0x88E674[i], zero leaves previous stored value unchanged; size and CRC are collected separately.
int rf_archive_collect_startup_metadata()
{
  char v1; // [esp+23h] [ebp-245h]
  char *v2; // [esp+28h] [ebp-240h]
  char *v3; // [esp+2Ch] [ebp-23Ch]
  int size; // [esp+30h] [ebp-238h]
  int v5; // [esp+30h] [ebp-238h]
  _BYTE v6[260]; // [esp+34h] [ebp-234h] BYREF
  int i; // [esp+138h] [ebp-130h]
  int self[71]; // [esp+13Ch] [ebp-12Ch] BYREF
  int v9; // [esp+264h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v9 = 0;
  memset(v6, 0, 256);
  if ( rf_command_line_copy_enabled_archive_basename(v6) )
  {
    v3 = v6;
    v2 = byte_6630FC;
    do
    {
      v1 = *v3;
      *v2++ = *v3++;
    }
    while ( v1 );
    strcat(byte_6630FC, ".vpp");
  }
  for ( i = 0; i < 2; ++i )
  {
    if ( &aTablesVpp[24 * i + 1 + strlen(&aTablesVpp[24 * i])] != &aTablesVpp[24 * i + 1] )
    {
      size = rf_vfile_get_size((int)self, &aTablesVpp[24 * i], (int)byte_98967F);
      if ( size != -4 )
        unk_88E67C[i] = size;
      v5 = rf_vfile_raw_crc32_or_zero(&aTablesVpp[24 * i]);
      if ( v5 )
        unk_88E674[i] = v5;
    }
  }
  v9 = -1;
  return rf_vfile_destruct_close_if_open(self);
}

