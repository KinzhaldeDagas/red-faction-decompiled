// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005685A0 rf_gamesound_voice_set_gain_and_pan
// UNREALRED VERIFIED [sound-backend]: Validates a generation-tagged common voice handle, stores source gain and pan, applies the voice's channel-group multiplier, and updates the live backend voice when nonpositional.
void __cdecl rf_gamesound_voice_set_gain_and_pan(int a1, float a2, float a3)
{
  int *v3; // [esp+8h] [ebp-4h]
  float v4; // [esp+18h] [ebp+Ch]

  if ( rf_sound_system_ready[0] )
  {
    if ( (unsigned __int8)a1 < 0x1Eu )
    {
      v3 = &rf_gamesound_voice_pool[11 * (unsigned __int8)a1];
      if ( v3[3] == a1 >> 8 && !*((_BYTE *)v3 + 40) )
      {
        *((float *)v3 + 4) = a2;
        *((float *)v3 + 5) = a3;
        v4 = a2 * rf_sound_channel_group_gains[v3[2]];
        rf_sound_backend_voice_set_gain(*v3, v4);
        rf_sound_backend_voice_set_pan(*v3, a3);
      }
    }
  }
}

