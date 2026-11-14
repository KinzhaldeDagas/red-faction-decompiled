// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568B20 rf_music_play_unowned_filename
// UNREALRED VERIFIED [sound-backend]: Registers and lazy-loads a one-shot music filename, applies channel-group zero gain, and starts a resident music backend voice without replacing the owned music globals.
int __cdecl rf_music_play_unowned_filename(char *a1, float a2)
{
  int v3; // [esp+14h] [ebp-4h]
  float v4; // [esp+24h] [ebp+Ch]

  if ( !rf_sound_system_ready[0] )
    return -1;
  v3 = rf_sound_find_or_register(a1, 5.0, 1.0, 1.0, 0);
  if ( rf_sound_load_entry(v3, 1, 0) < 0 )
    return -1;
  v4 = a2 * rf_sound_channel_group_gains[0];
  return rf_music_voice_start_resident(v3, v4, 0.0);
}

