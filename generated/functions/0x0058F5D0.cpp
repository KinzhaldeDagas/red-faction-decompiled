// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058F5D0 rf_sound_release_all_sample_records
// UNREALRED VERIFIED [dsound-creation-20261028]: Calls0x58F610 for all4096 fixed sample records,returns4096. Does not decrement/reset global registry count0x1BA1818 or check record occupancy before each cleanup; cleanup helper tolerates negative index only,not an occupancy test.
int rf_sound_release_all_sample_records()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 4096; ++i )
  {
    rf_sound_sample_release_formats_file_buffers(i);
    result = i + 1;
  }
  return result;
}

