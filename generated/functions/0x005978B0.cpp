// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005978B0 rf_file_transfer_reset_all_slots
// UNREALRED VERIFIED [file-transfer-20261028]: First releases every active slot through0x597DC0, including deletion of receive temporary files. Then clears all60 flags, sets all peer fields+420=-1 and clears first byte of global receive-prefix string aVsx. Does not reset other fields or protocol ID counter. Incidental final EAX=436*59.
int rf_file_transfer_reset_all_slots()
{
  int result; // eax
  signed int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 60; ++i )
  {
    if ( (unk_1BC3CC8[109 * i] & 1) != 0 )
      rf_file_transfer_release_slot_delete_receive_file(i);
    result = i + 1;
  }
  for ( j = 0; j < 60; ++j )
  {
    unk_1BC3CC8[109 * j] = 0;
    result = 436 * j;
    unk_1BC3E6C[109 * j] = -1;
  }
  aVsx[0] = 0;
  return result;
}

