// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C75C0 rf_positional_sound_is_playing
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Returns false for signed index outside [0,127]; otherwise calls backend_voice_is_playing with slot voice handle +12 and returns its byte result. No subsystem-initialized or allocation test here; backend wrapper provides its own ready check.
unsigned __int8 __cdecl rf_positional_sound_is_playing(int instance_index)
{
  return (unsigned int)instance_index < 0x80 && rf_sound_backend_voice_is_playing(dword_1DAEE64[27 * instance_index]);
}

