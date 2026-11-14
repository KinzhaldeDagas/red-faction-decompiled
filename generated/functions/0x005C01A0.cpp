// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C01A0 rf_sound_backend_resume_all
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready and mode==1, delegates to rf_dsound_resume_all_paused_slots. Other paths perform no resume operation.
int rf_sound_backend_resume_all()
{
  int result; // eax

  result = rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    if ( rf_sound_backend_mode == 1 )
      return rf_dsound_resume_all_paused_slots();
  }
  return result;
}

