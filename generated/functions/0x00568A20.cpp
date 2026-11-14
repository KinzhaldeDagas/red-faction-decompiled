// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568A20 rf_music_play_owned_filename
// Resolves and loads a supplied music filename, starts playback, and stores the active playback handle.
// UNREALRED VERIFIED [sound-backend]: Registers and lazy-loads one filename as music, multiplies caller gain by the configured music channel-group gain, selects resident or streaming start from resource byte +0x3E, and stores the owned resource and backend voice handles.
int __cdecl rf_music_play_owned_filename(char *a1, float a2)
{
  char *v3; // [esp+10h] [ebp-4h]
  float v4; // [esp+20h] [ebp+Ch]

  if ( !rf_sound_system_ready[0] )
    return -1;
  rf_music_owned_sound_handle = rf_sound_find_or_register(a1, 5.0, 1.0, 1.0, 0);
  if ( rf_music_owned_sound_handle < 0 || rf_sound_load_entry(rf_music_owned_sound_handle, 1, 0) < 0 )
    return -1;
  v3 = &rf_sound_resource_registry[64 * rf_music_owned_sound_handle];
  v4 = a2 * rf_sound_channel_group_gains[rf_music_channel_group_index];
  if ( v3[62] )
    rf_music_owned_backend_voice = rf_music_voice_start_streaming(rf_music_owned_sound_handle, v4, 0.0);
  else
    rf_music_owned_backend_voice = rf_music_voice_start_resident(rf_music_owned_sound_handle, v4, 0.0);
  if ( rf_music_owned_backend_voice < 0 )
    return -1;
  v3[60] = 1;
  return 0;
}

