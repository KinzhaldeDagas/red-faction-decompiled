// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0170 rf_sound_backend_pause_all
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready and mode==1, delegates to rf_dsound_pause_all_playing_slots.
void rf_sound_backend_pause_all()
{
  if ( rf_sound_backend_ready )
  {
    if ( rf_sound_backend_mode == 1 )
      rf_dsound_pause_all_playing_slots();
  }
}

