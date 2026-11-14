// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596E00 rf_file_transfer_next_wire_id
// UNREALRED VERIFIED [file-transfer-20261028]: Returns current unsigned16-bit counter at0x1BC3CC4 and increments it, explicitly wrapping0xFFFF to0. No collision scan against live slots; global state is not synchronized here.
unsigned __int16 rf_file_transfer_next_wire_id()
{
  unsigned __int16 v1; // [esp+0h] [ebp-4h]

  v1 = word_1BC3CC4[0];
  if ( word_1BC3CC4[0] == 0xFFFF )
    word_1BC3CC4[0] = 0;
  else
    ++word_1BC3CC4[0];
  return v1;
}

