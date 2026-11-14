// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590E90 rf_dsound_pause_all_playing_slots
// UNREALRED VERIFIED [dsound-buffers-20261028]: Walks30 slots,queries hardware playing0x590550. For each playing slot calls Stop+72 then sets cached pause mask2 regardless Stop result. Does not rewind cursor,release resources or stop streaming timers. No global mutex in body.
void rf_dsound_pause_all_playing_slots()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 30; ++i )
  {
    if ( rf_dsound_buffer_slot_is_playing(i) )
    {
      (*(void (__stdcall **)(int))(*(_DWORD *)unk_1BA1820[11 * i] + 72))(unk_1BA1820[11 * i]);
      unk_1BA1848[11 * i] |= 2u;
    }
  }
}

