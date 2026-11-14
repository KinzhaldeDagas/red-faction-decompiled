// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C09B0 rf_music_voice_start_resident
// UNREALRED VERIFIED [sound-backend]: Lazy-loads in music mode, normalizes gain, rejects gain below 0.05, and starts a lower backend music voice with streaming selector zero.
int __cdecl rf_music_voice_start_resident(int a1, float a2, float a3)
{
  int v4; // [esp+14h] [ebp-8h]
  float v5; // [esp+18h] [ebp-4h]

  if ( !rf_sound_backend_ready )
    return -1;
  if ( rf_sound_load_entry(a1, 1, 0) == -1 )
    return -1;
  v5 = rf_sound_compute_scaled_group_gain(a1, a2);
  if ( v5 < 0.05000000074505806 )
    return -1;
  v4 = -1;
  if ( rf_sound_backend_mode == 1 )
    return rf_dsound_play_streaming_sample(unk_1D85DE8[16 * a1], v5, a3, 0);
  return v4;
}

