// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568700 rf_gamesound_stop_voice_handle
// UNREALRED VERIFIED [sound-spatialization]: Validates slot index below 30 and the stored generation before stopping and releasing one voice.
int *__cdecl rf_gamesound_stop_voice_handle(int a1)
{
  int *result; // eax
  int *v2; // [esp+4h] [ebp-4h]

  result = (int *)rf_sound_system_ready[0];
  if ( rf_sound_system_ready[0] )
  {
    if ( (unsigned __int8)a1 < 0x1Eu )
    {
      result = &rf_gamesound_voice_pool[11 * (unsigned __int8)a1];
      v2 = result;
      if ( *result >= 0 )
      {
        result = (int *)(a1 >> 8);
        if ( a1 >> 8 == v2[3] )
        {
          rf_sound_backend_voice_stop(*v2);
          return (int *)rf_gamesound_release_voice_slot((int)v2);
        }
      }
    }
  }
  return result;
}

