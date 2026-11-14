// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0140 rf_sound_backend_service_fades
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready and mode==1, delegates to rf_dsound_service_all_fades. Other paths do no fade processing; inferred EAX is incidental.
int rf_sound_backend_service_fades()
{
  int result; // eax

  result = rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    if ( rf_sound_backend_mode == 1 )
      return rf_dsound_service_all_fades();
  }
  return result;
}

