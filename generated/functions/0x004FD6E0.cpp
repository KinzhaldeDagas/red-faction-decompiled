// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD6E0 rf_event_sound_reverse
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] event_sound reverse callback, vtable 0x63DFEC slot +8; not an unconditional stop. Nonempty alternate filename +0x2C0 loads resource into +0x2CC, stops current event voice only if playing, starts alternate sound locally (distance ==0 nonpositional, finite nonzero positional), optionally rearms +0x2E0 from positive duration, and marks +0x2DD=1. That branch ignores entity target +0x2E4 and leaves old voice untouched if alternate load fails. Empty alternate: positive target resolves through 0x4BC680 then rf_entity_resolve_handle and stops entity speech. Without positive target, only non--1 local handle causes optional deadline reset, voice stop, handle=-1 and active=0. An already -1 local handle leaves active/deadline untouched.
void __thiscall rf_event_sound_reverse(int this)
{
  const char *v1; // eax
  float distance; // [esp+0h] [ebp-18h]
  int v4; // [esp+10h] [ebp-8h]
  int v5; // [esp+14h] [ebp-4h]

  if ( (int)rf_string_length_from_cstr((const char **)(this + 704)) <= 0 )
  {
    if ( *(int *)(this + 740) <= 0 )
    {
      if ( *(_DWORD *)(this + 720) != -1 )
      {
        if ( *(float *)(this + 728) > 0.0 )
          rf_replicator_reset((_DWORD *)(this + 736));
        rf_gamesound_stop_voice_handle(*(_DWORD *)(this + 720));
        *(_DWORD *)(this + 720) = -1;
        *(_BYTE *)(this + 733) = 0;
      }
    }
    else
    {
      v5 = rf_object_find_by_saved_identifier(*(_DWORD *)(this + 740));
      if ( v5 )
      {
        v4 = rf_entity_resolve_handle(*(_DWORD *)(v5 + 44));
        if ( v4 )
          rf_entity_stop_speech_voice(v4);
      }
    }
  }
  else
  {
    distance = *(float *)(this + 724);
    v1 = rf_string_object_c_str_or_empty((const void *)(this + 704));
    *(_DWORD *)(this + 716) = rf_sound_resource_load(v1, distance, 1.0, 1.0);
    if ( *(_DWORD *)(this + 716) != -1 )
    {
      if ( rf_gamesound_voice_is_playing(*(_DWORD *)(this + 720)) )
      {
        rf_gamesound_stop_voice_handle(*(_DWORD *)(this + 720));
        *(_DWORD *)(this + 720) = -1;
      }
      if ( *(float *)(this + 724) == 0.0 )
      {
        *(_DWORD *)(this + 720) = rf_gamesound_play_event(*(_DWORD *)(this + 716), 0, 0.0, 1.0);
        if ( *(float *)(this + 728) > 0.0 )
          rf_replicator_arm_milliseconds((int *)(this + 736), (int)(*(float *)(this + 728) * 1000.0));
      }
      else
      {
        *(_DWORD *)(this + 720) = rf_gamesound_play_positional_event(
                                    *(_DWORD *)(this + 716),
                                    (float *)(this + 64),
                                    1.0,
                                    (int)flt_17F10B0,
                                    0);
        if ( *(float *)(this + 728) > 0.0 )
          rf_replicator_arm_milliseconds((int *)(this + 736), (int)(*(float *)(this + 728) * 1000.0));
      }
      *(_BYTE *)(this + 733) = 1;
    }
  }
}

