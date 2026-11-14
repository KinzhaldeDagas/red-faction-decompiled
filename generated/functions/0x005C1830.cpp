// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1830 rf_sound_backend_get_3d_mode
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Returns the byte from rf_audio_get_3d_mode_byte. No ready or backend-mode guard in this wrapper.
char rf_sound_backend_get_3d_mode()
{
  return rf_audio_get_3d_mode_byte();
}

