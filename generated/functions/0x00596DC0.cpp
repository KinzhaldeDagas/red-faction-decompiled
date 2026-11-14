// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596DC0 rf_file_transfer_find_inactive_slot
// UNREALRED VERIFIED [file-transfer-20261028]: Scans60 records at0x1BC3CC8 stride436; returns first index whose flags bit1 is clear, or-1. Does not reserve or initialize the returned record.
int rf_file_transfer_find_inactive_slot()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 60; ++i )
  {
    if ( (unk_1BC3CC8[109 * i] & 1) == 0 )
      return i;
  }
  return -1;
}

