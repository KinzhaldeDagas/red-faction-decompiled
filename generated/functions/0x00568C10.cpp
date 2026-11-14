// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568C10 rf_music_owned_reset_and_stop
// UNREALRED VERIFIED [sound-backend]: Requests a lower backend music reset for a live owned voice, then follows the common owned-music stop and clear path.
int *rf_music_owned_reset_and_stop()
{
  if ( rf_music_owned_backend_voice >= 0 )
    rf_music_backend_reset(rf_music_owned_backend_voice);
  return rf_music_owned_stop();
}

