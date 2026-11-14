// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1290 rf_music_backend_reset
// UNREALRED VERIFIED [sound-backend]: Requests the lower backend reset operation for a valid music voice handle.
signed int __cdecl rf_music_backend_reset(int a1)
{
  signed int result; // eax

  result = rf_sound_backend_ready;
  if ( rf_sound_backend_ready && a1 != -1 && rf_sound_backend_mode == 1 )
    return rf_dsound_cancel_fade_by_play_handle(a1);
  return result;
}

