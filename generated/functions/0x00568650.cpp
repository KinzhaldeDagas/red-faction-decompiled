// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568650 rf_gamesound_stop_all_voice_slots
// UNREALRED VERIFIED [sound-spatialization]: Stops every live backend voice and releases all 30 gamesound voice slots.
void __cdecl rf_gamesound_stop_all_voice_slots()
{
  int j; // [esp+0h] [ebp-10h]
  int *v1; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]
  int paused_slot_handle; // [esp+Ch] [ebp-4h]

  v1 = nullptr;
  for ( i = 0; i < 30; ++i )
  {
    paused_slot_handle = rf_sound_backend_get_paused_slot_handle(i);
    if ( paused_slot_handle != -1 )
    {
      for ( j = 0; j < 30; ++j )
      {
        if ( rf_gamesound_voice_pool[11 * j] == paused_slot_handle )
          v1 = &rf_gamesound_voice_pool[11 * j];
      }
      rf_sound_backend_voice_stop(paused_slot_handle);
      if ( v1 )
      {
        if ( *v1 >= 0 )
          rf_gamesound_release_voice_slot((int)v1);
      }
    }
  }
}

