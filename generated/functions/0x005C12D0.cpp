// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C12D0 rf_sound_backend_stop_release_all_voices
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready and mode==1, calls rf_dsound_stop_release_all_slots. Used before releasing unreferenced resources.
int rf_sound_backend_stop_release_all_voices()
{
  int result; // eax

  result = rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    if ( rf_sound_backend_mode == 1 )
      return rf_dsound_stop_release_all_slots();
  }
  return result;
}

