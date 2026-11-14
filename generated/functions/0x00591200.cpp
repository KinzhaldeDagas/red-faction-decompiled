// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591200 rf_dsound_play_handle_is_playing_or_paused
// UNREALRED VERIFIED [dsound-buffers-20261028]: Resolves handle; invalidfalse. Returns true if hardware playing0x590550 OR cached pause mask0x5905B0 nonzero. Does not require active fade flag or streaming timer. Stopped but cached-paused buffer still counts true.
bool __cdecl rf_dsound_play_handle_is_playing_or_paused(int a1)
{
  int buffer_slot_by_play_handle; // [esp+0h] [ebp-4h]

  buffer_slot_by_play_handle = rf_dsound_find_buffer_slot_by_play_handle(a1);
  if ( buffer_slot_by_play_handle < 0 )
    return 0;
  return rf_dsound_buffer_slot_is_playing(buffer_slot_by_play_handle)
      || rf_dsound_buffer_slot_pause_mask(buffer_slot_by_play_handle);
}

