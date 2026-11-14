// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568A00 rf_sound_backend_set_paused
// UNREALRED VERIFIED [sound-backend]: Selects one of the lower backend pause/resume operations from a boolean argument while the sound system is ready.
void __cdecl rf_sound_backend_set_paused(char a1)
{
  if ( a1 )
    rf_sound_backend_pause_all();
  else
    rf_sound_backend_resume_all();
}

