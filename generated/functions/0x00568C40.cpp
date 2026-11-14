// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568C40 rf_music_owned_fade
// UNREALRED VERIFIED [sound-backend]: Forwards a fade duration or parameter to the lower backend for the current owned music voice when one exists.
int *__cdecl rf_music_owned_fade(int a1)
{
  int *result; // eax

  if ( rf_music_owned_backend_voice >= 0 )
    return rf_music_backend_fade(rf_music_owned_backend_voice, a1);
  return result;
}

