// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569010 rf_sound_release_unreferenced
// UNREALRED VERIFIED [sound-backend]: Stops and resets common and ambient frontend voices whose resources are no longer retained, then asks the lower backend to release unreferenced resources.
char *__cdecl rf_sound_release_unreferenced(unsigned __int8 a1)
{
  char *result; // eax
  int *v2; // [esp+0h] [ebp-Ch]
  int *v3; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]
  int j; // [esp+8h] [ebp-4h]

  result = (char *)rf_sound_system_ready[0];
  if ( rf_sound_system_ready[0] )
  {
    for ( i = 0; i < 30; ++i )
    {
      v3 = &rf_gamesound_voice_pool[11 * i];
      if ( v3[1] >= 0 && unk_1D85DF0[16 * v3[1]] <= 1 )
      {
        rf_sound_backend_voice_stop(*v3);
        rf_gamesound_release_voice_slot((int)v3);
      }
    }
    for ( j = 0; j < 25; ++j )
    {
      v2 = &rf_ambient_voice_pool[6 * j];
      if ( *v2 >= 0 && unk_1D85DF0[16 * *v2] <= 1 )
      {
        rf_sound_backend_voice_stop(v2[1]);
        rf_ambient_voice_slot_reset((int)v2);
      }
    }
    return rf_sound_backend_release_unreferenced(a1);
  }
  return result;
}

