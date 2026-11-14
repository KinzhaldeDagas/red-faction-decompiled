// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1470 rf_sound_backend_voice_set_pan
// UNREALRED VERIFIED [sound-backend]: Updates pan on a valid lower backend voice handle.
void __cdecl rf_sound_backend_voice_set_pan(int a1, float a2)
{
  if ( rf_sound_backend_ready )
  {
    if ( a2 > 1.0 )
      a2 = 1.0;
    if ( a2 < -1.0 )
      a2 = -1.0;
    if ( rf_sound_backend_mode == 1 )
      rf_dsound_set_pan_by_play_handle(a1, a2);
  }
}

