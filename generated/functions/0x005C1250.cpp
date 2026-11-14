// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1250 rf_sound_backend_voice_stop
// UNREALRED VERIFIED [sound-backend]: Stops a valid lower backend voice handle.
int *__cdecl rf_sound_backend_voice_stop(int a1)
{
  int *result; // eax

  result = (int *)rf_sound_backend_ready;
  if ( rf_sound_backend_ready && a1 != -1 && rf_sound_backend_mode == 1 )
    return rf_dsound_stop_release_by_play_handle(a1);
  return result;
}

