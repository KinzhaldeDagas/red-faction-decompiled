// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1300 rf_music_backend_fade
// UNREALRED VERIFIED [sound-backend]: Forwards a fade duration or parameter for a valid lower backend music voice handle.
int *__cdecl rf_music_backend_fade(int a1, int a2)
{
  int *result; // eax

  result = (int *)rf_sound_backend_ready;
  if ( rf_sound_backend_ready && a1 != -1 && rf_sound_backend_mode == 1 )
    return rf_dsound_begin_fade_stop_by_play_handle(a1, a2);
  return result;
}

