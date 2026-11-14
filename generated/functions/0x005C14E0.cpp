// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C14E0 rf_sound_backend_voice_set_frequency
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready, clamps the frequency argument in place using UNSIGNED comparisons to [100,100000], then mode 1 calls rf_dsound_set_frequency_if_playing(handle,frequency). Negative signed input therefore clamps to 100000 rather than 100. Return EAX is incidental outside the backend call.
int __cdecl rf_sound_backend_voice_set_frequency(int a1, int a2)
{
  int result; // eax

  result = rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    result = (int)rf_uint32_clamp_in_place((unsigned int *)&a2, 0x64u, 0x186A0u);
    if ( rf_sound_backend_mode == 1 )
      return rf_dsound_set_frequency_if_playing(a1, a2);
  }
  return result;
}

