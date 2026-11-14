// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C07F0 rf_sound_voice_start_nonlooping
// UNREALRED VERIFIED [mission-mover-effects-20261013] CORRECTION: this wrapper starts NONLOOPING playback; final argument to0x5905E0 is0. Prior resident/streaming labels obscured the loop choice. Its own argument5 controls gain normalization. Both wrappers use the same resource loader.
int __cdecl rf_sound_voice_start_nonlooping(int a1, float a2, float a3, float a4, char a5)
{
  int v6; // [esp+14h] [ebp-8h]
  float v7; // [esp+18h] [ebp-4h]

  if ( !rf_sound_backend_ready )
    return -1;
  if ( a1 == -1 )
    return -1;
  if ( rf_sound_load_entry(a1, 0, 0) == -1 )
    return -1;
  if ( a5 )
    v7 = a2;
  else
    v7 = rf_sound_compute_scaled_group_gain(a1, a2);
  v6 = -1;
  if ( rf_sound_backend_mode == 1 )
    return rf_dsound_start_buffer_voice(unk_1D85DE8[16 * a1], v7, a3, 0);
  return v6;
}

