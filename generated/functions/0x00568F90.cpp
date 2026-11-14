// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568F90 rf_sound_frontend_update
// UNREALRED VERIFIED [sound-backend]: Ages referenced nonpersistent sound resources across all 2600 registry records, then invokes the lower backend update.
void rf_sound_frontend_update()
{
  int i; // [esp+0h] [ebp-4h]

  if ( rf_sound_system_ready[0] )
  {
    for ( i = 0; i < 2600; ++i )
    {
      if ( unk_1D85DF0[16 * i] > 0 && !unk_1D85DF4[64 * i] )
        ++unk_1D85DF0[16 * i];
    }
    rf_sound_backend_tick();
  }
}

