// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568050 rf_gamesound_play_event
// UNREALRED VERIFIED [mission-mover-effects-20261013] CORRECTION: resource byte+0x3E selects LOOPING0x5C08F0 versus NONLOOPING0x5C07F0, not a streaming/resident distinction. Both ultimately call0x5905E0 with the final argument1/0. The fifth argument passed to the wrapper here is gain-normalization control, not loop selection. The common pool still admits at most30 simultaneous voices without live eviction.
int __cdecl rf_gamesound_play_event(int a1, int a2, float a3, float a4)
{
  float v5; // [esp+10h] [ebp-18h]
  float v6; // [esp+14h] [ebp-14h]
  int *v7; // [esp+18h] [ebp-10h]
  int v8; // [esp+1Ch] [ebp-Ch]
  int i; // [esp+24h] [ebp-4h]
  int j; // [esp+24h] [ebp-4h]

  if ( !rf_sound_system_ready )
    return -1;
  v7 = nullptr;
  v8 = -1;
  if ( rf_gamesound_resolve_and_load(a1) == -1 )
    return -1;
  for ( i = 0; i < 30; ++i )
  {
    v7 = &rf_gamesound_voice_pool[11 * i];
    if ( !rf_sound_backend_voice_is_playing(*v7) )
    {
      rf_sound_backend_voice_stop(*v7);
      rf_gamesound_release_voice_slot((int)v7);
    }
  }
  for ( j = 0; j < 30; ++j )
  {
    v7 = &rf_gamesound_voice_pool[11 * j];
    if ( v7[1] < 0 )
    {
      v8 = j;
      break;
    }
  }
  if ( v8 < 0 )
    return -1;
  if ( rf_sound_resource_registry[64 * a1 + 62] )
  {
    v6 = a4 * rf_sound_channel_group_gains[a2];
    *v7 = rf_sound_voice_start_looping(a1, v6, a3, 0.0, 0);
  }
  else
  {
    v5 = a4 * rf_sound_channel_group_gains[a2];
    *v7 = rf_sound_voice_start_nonlooping(a1, v5, a3, 0.0, 0);
  }
  if ( *v7 < 0 )
    return -1;
  v7[1] = a1;
  v7[2] = a2;
  *((float *)v7 + 4) = a4;
  *((float *)v7 + 5) = a3;
  *((_BYTE *)v7 + 40) = 0;
  return v8 | (++v7[3] << 8);
}

