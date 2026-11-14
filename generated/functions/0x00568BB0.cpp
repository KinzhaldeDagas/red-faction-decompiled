// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568BB0 rf_music_owned_is_playing
// UNREALRED VERIFIED [sound-backend]: Returns whether the owned music backend voice handle is nonnegative.
BOOL rf_music_owned_is_playing()
{
  return rf_music_owned_backend_voice >= 0;
}

