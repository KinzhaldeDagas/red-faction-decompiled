// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058EFC0 rf_dsound_initialize_backend_slot_fields
// UNREALRED VERIFIED [dsound-playback-20261028]: Loops30 slots through0x58EFF0 clear helper,returns30. No release of existing DS/3D interfaces or streams; preserves fields left stale by clear helper,including cached volume/fade step/deadline. Requires lifecycle ordering to avoid orphaned resources.
int rf_dsound_initialize_backend_slot_fields()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 30; ++i )
  {
    rf_dsound_buffer_slot_clear_fields(i);
    result = i + 1;
  }
  return result;
}

