// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568410 rf_sound_channel_group_set_gain
// UNREALRED VERIFIED [sound-backend]: Accepts channel-group indices 0..3, stores the gain, and immediately reapplies gain/pan to all 30 active common voices in that group. Group index 1 also propagates to the separate streamed-instance set.
int __cdecl rf_sound_channel_group_set_gain(unsigned int a1, float a2)
{
  int result; // eax
  int v3; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  result = rf_sound_system_ready[0];
  if ( rf_sound_system_ready[0] && a1 < 4 )
  {
    rf_sound_channel_group_gains[a1] = a2;
    for ( i = 0; i < 30; ++i )
    {
      result = (int)&rf_gamesound_voice_pool[11 * i];
      v3 = result;
      if ( *(int *)result >= 0 )
      {
        result = a1;
        if ( a1 == *(_DWORD *)(v3 + 8) )
          result = rf_gamesound_voice_set_gain_and_pan(
                     i | (*(_DWORD *)(v3 + 12) << 8),
                     *(float *)(v3 + 16),
                     *(float *)(v3 + 20));
      }
    }
    if ( a1 == 1 )
      return rf_streamed_group_one_set_gain(a2);
  }
  return result;
}

