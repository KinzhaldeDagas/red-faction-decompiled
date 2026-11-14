// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591360 rf_dsound_count_hardware_playing_slots
// UNREALRED VERIFIED [dsound-buffers-20261028]: Queries0x590550 for each30 slots and counts positive results. Cached paused slots excluded; hardware GetStatus failures count asnot playing. Returns count0..30.
int rf_dsound_count_hardware_playing_slots()
{
  int i; // [esp+0h] [ebp-8h]
  int v2; // [esp+4h] [ebp-4h]

  v2 = 0;
  for ( i = 0; i < 30; ++i )
  {
    if ( rf_dsound_buffer_slot_is_playing(i) > 0 )
      ++v2;
  }
  return v2;
}

