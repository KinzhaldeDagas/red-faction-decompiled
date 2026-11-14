// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569140 rf_gamesound_initialize_level_state
// UNREALRED VERIFIED [sound-spatialization]: Resets listener/channel groups and the 30-slot voice pool, initializes the backend, and clears transient state on all 2600 possible 64-byte sound records.
// UNREALRED VERIFIED [ambient-audio]: Initializes listener/channel state, resets 30 generation-tagged common voices, resets all 25 fixed frontend ambient slots, initializes the backend, and clears transient fields on 2600 sound resources.
int __cdecl rf_gamesound_initialize_level_state(
        int a1,
        int a2,
        unsigned __int16 a3,
        __int16 a4,
        char a5,
        char a6,
        char a7,
        char a8)
{
  char *v9; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  int j; // [esp+10h] [ebp-4h]
  int k; // [esp+10h] [ebp-4h]
  int m; // [esp+10h] [ebp-4h]

  rf_vector3_set_components_thiscall(unk_1808BC0, 0.0, 0.0, 0.0);
  rf_vector3_set_components_thiscall(unk_18090F8, -1.0, 0.0, 0.0);
  for ( i = 0; i < 4; ++i )
    rf_sound_channel_group_gains[i] = 1.0;
  for ( j = 0; j < 30; ++j )
  {
    rf_gamesound_release_voice_slot((int)&rf_gamesound_voice_pool[11 * j]);
    unk_1808BDC[11 * j] = 0;
  }
  for ( k = 0; k < 25; ++k )
    rf_ambient_voice_slot_reset((int)&rf_ambient_voice_pool[6 * k]);
  if ( rf_sound_backend_initialize(a1, a2, a3, a4, a5, a6, a7, a8) )
    return -1;
  for ( m = 0; m < 2600; ++m )
  {
    v9 = &rf_sound_resource_registry[64 * m];
    *((_DWORD *)v9 + 14) = 0;
    v9[60] = 0;
    v9[61] = 0;
    v9[62] = 0;
  }
  rf_music_owned_sound_handle = -1;
  rf_music_owned_backend_voice = -1;
  unk_1808940 = 0.0;
  rf_sound_system_ready[0] = 1;
  return 0;
}

