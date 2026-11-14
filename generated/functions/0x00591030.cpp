// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591030 rf_dsound_stop_release_all_slots
// UNREALRED VERIFIED [dsound-buffers-20261028]: Calls0x58F3E0 for all30 slots,returns30. Does NOT override fade mask8; fading records may survive this purported stop-all path. No device/list reset here.
int rf_dsound_stop_release_all_slots()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 30; ++i )
  {
    rf_dsound_buffer_slot_stop_release_unless_fading(i);
    result = i + 1;
  }
  return result;
}

