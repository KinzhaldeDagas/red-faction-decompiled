// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568970 rf_gamesound_voice_is_playing
// UNREALRED VERIFIED [sound-backend]: Validates a generation-tagged common voice handle and asks the backend whether that slot's live voice is still playing.
BOOL __cdecl rf_gamesound_voice_is_playing(int a1)
{
  int *v2; // [esp+4h] [ebp-4h]

  if ( !rf_sound_system_ready[0] )
    return 0;
  if ( a1 == -1 )
    return 0;
  v2 = &rf_gamesound_voice_pool[11 * (unsigned __int8)a1];
  if ( (unsigned __int8)a1 < 0x1Eu && *v2 >= 0 && v2[3] == a1 >> 8 )
    return rf_sound_backend_voice_is_playing(*v2);
  else
    return rf_sound_backend_voice_is_playing(*v2);
}

