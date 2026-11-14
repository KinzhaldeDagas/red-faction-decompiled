// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C01D0 rf_sound_backend_get_paused_slot_handle
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Returns rf_dsound_get_paused_slot_play_handle(slot) only when ready and mode==1, otherwise -1.
int __cdecl rf_sound_backend_get_paused_slot_handle(int a1)
{
  if ( !rf_sound_backend_ready )
    return -1;
  if ( rf_sound_backend_mode == 1 )
    return rf_dsound_get_paused_slot_play_handle(a1);
  return -1;
}

