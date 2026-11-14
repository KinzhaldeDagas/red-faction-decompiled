// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005684D0 rf_positioned_voice_update
// UNREALRED VERIFIED [ambient-audio]: Validates a generation-tagged common voice handle, stores source gain and position, recomputes positional gain/pan, applies channel-group gain, and updates its live backend voice.
void __cdecl rf_positioned_voice_update(int a1, float *source, int a3, float a4)
{
  float copy_result[3]; // [esp+4h] [ebp-1Ch] BYREF
  int v5; // [esp+10h] [ebp-10h] BYREF
  int v6; // [esp+14h] [ebp-Ch] BYREF
  int v7; // [esp+18h] [ebp-8h]
  int *v8; // [esp+1Ch] [ebp-4h]

  v7 = a1 >> 8;
  if ( (unsigned __int8)a1 < 0x1Eu )
  {
    v8 = &rf_gamesound_voice_pool[11 * (unsigned __int8)a1];
    if ( v8[3] == v7 )
    {
      if ( *((_BYTE *)v8 + 40) )
      {
        *((float *)v8 + 9) = a4;
        rf_vector_copy((float *)v8 + 6, copy_result, source);
        rf_gamesound_spatialize_event(v8[1], source, (float *)&v5, (float *)&v6, a4);
        *(float *)&v6 = *(float *)&v6 * rf_sound_channel_group_gains[v8[2]];
        rf_sound_backend_voice_set_gain(*v8, *(float *)&v6);
        rf_sound_backend_voice_set_pan(*v8, *(float *)&v5);
      }
    }
  }
}

