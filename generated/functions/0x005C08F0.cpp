// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C08F0 rf_sound_voice_start_looping
// UNREALRED VERIFIED [mission-mover-effects-20261013] CORRECTION: this wrapper starts LOOPING playback; final argument to0x5905E0 is1. Prior streaming label was incorrect. Resource metadata byte+0x3E selects this wrapper through0x568050.
int __cdecl rf_sound_voice_start_looping(int a1, float a2, float a3, float a4, char a5)
{
  int v6; // [esp+14h] [ebp-8h]
  float v7; // [esp+18h] [ebp-4h]

  if ( !rf_sound_backend_ready )
    return -1;
  if ( a1 == -1 )
    return -1;
  if ( rf_sound_load_entry(a1, 0, 0) == -1 )
    return -1;
  if ( a5 == 1 )
    v7 = a2;
  else
    v7 = rf_sound_compute_scaled_group_gain(a1, a2);
  v6 = -1;
  if ( rf_sound_backend_mode == 1 )
    return rf_dsound_start_buffer_voice(unk_1D85DE8[16 * a1], v7, a3, 1);
  return v6;
}

