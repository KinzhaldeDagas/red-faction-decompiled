// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1340 rf_sound_backend_voice_is_playing
// UNREALRED VERIFIED [sound-backend]: Queries the active lower backend for whether a voice handle is still playing.
bool __cdecl rf_sound_backend_voice_is_playing(int a1)
{
  char v2; // [esp+7h] [ebp-1h]

  if ( !rf_sound_backend_ready )
    return 0;
  v2 = 0;
  if ( rf_sound_backend_mode == 1 )
    return rf_dsound_play_handle_is_playing_or_paused(a1);
  return v2;
}

