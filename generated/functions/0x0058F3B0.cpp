// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058F3B0 rf_dsound_release_all_backend_slots_wrapper
// UNREALRED VERIFIED [dsound-creation-20261028]: Loops30 backend slots through0x58F3E0 and returns30. Does not clear fade flags, so fading records can survive this release loop; no source sample cleanup here. Same behavior as0x591030 wrapper.
int rf_dsound_release_all_backend_slots_wrapper()
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

