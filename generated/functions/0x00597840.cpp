// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00597840 rf_file_transfer_service_all_slots
// UNREALRED VERIFIED [file-transfer-20261028]: Scans60 records at0x1BC3CC8 stride436. Calls0x596C40 for active bit1 with none of terminal bits0x380 set. Returns loop value60, not aggregate transfer success. Does not itself release terminal records.
int rf_file_transfer_service_all_slots()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 60; ++i )
  {
    if ( (unk_1BC3CC8[109 * i] & 1) != 0 && (unk_1BC3CC8[109 * i] & 0x380) == 0 )
      rf_file_transfer_service_record(&unk_1BC3CC8[109 * i]);
    result = i + 1;
  }
  return result;
}

