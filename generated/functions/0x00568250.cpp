// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568250 rf_gamesound_play_positional_event
// Spatializes a sounds.tbl event from a world position, dispatches it through the common game-sound voice pool, then records source position, source gain, and positional state on the allocated voice. Packet-44 entity creation supplies event 58 (player_respawn.wav).
// UNREALRED VERIFIED [sound-spatialization]: Computes positional pan/gain, allocates a common voice, then stores source position, source gain, and positional state in the selected generation-tagged slot.
int __cdecl rf_gamesound_play_positional_event(int a1, float *source, float a3, int a4, int a5)
{
  float v6; // [esp+8h] [ebp-20h]
  float copy_result[3]; // [esp+Ch] [ebp-1Ch] BYREF
  int v8; // [esp+18h] [ebp-10h] BYREF
  int *v9; // [esp+1Ch] [ebp-Ch]
  int v10; // [esp+20h] [ebp-8h]
  int v11; // [esp+24h] [ebp-4h] BYREF

  if ( !rf_sound_system_ready )
    return -1;
  rf_gamesound_spatialize_event(a1, source, (float *)&v8, (float *)&v11, a3);
  v6 = *(float *)&v11 * a3;
  v10 = rf_gamesound_play_event(a1, a5, *(float *)&v8, v6);
  if ( v10 < 0 )
    return -1;
  v9 = &rf_gamesound_voice_pool[11 * (unsigned __int8)v10];
  *((float *)v9 + 9) = a3;
  rf_vector_copy((float *)v9 + 6, copy_result, source);
  *((_BYTE *)v9 + 40) = 1;
  return v10;
}

