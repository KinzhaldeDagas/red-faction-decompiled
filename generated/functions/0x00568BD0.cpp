// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568BD0 rf_music_owned_stop
// UNREALRED VERIFIED [sound-backend]: Stops the owned music backend voice when present, then clears both owned voice and resource handles.
int *rf_music_owned_stop()
{
  int *result; // eax

  if ( rf_music_owned_backend_voice >= 0 )
  {
    result = rf_sound_backend_voice_stop(rf_music_owned_backend_voice);
    rf_music_owned_backend_voice = -1;
  }
  if ( rf_music_owned_sound_handle >= 0 )
    rf_music_owned_sound_handle = -1;
  return result;
}

