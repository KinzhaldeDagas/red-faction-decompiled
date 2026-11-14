// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D850 rf_ai_mode2_speech_action_update
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] Mode2 AI speech/action branch: refresh owner idle deadline, return while owner speech handle is playing. Branches select sounds through 0x441370/0x4413A0/0x441340 from descriptor+0x6F4. The middle branch can enter mode14, set target, clear scripted animation context, and request action43 even when chosen sound id is -1. Action43 deadline at AI+0x4C4 is trunc(float(max(clip_duration(owner+0xD04),sound_duration(selected_id)))*1000+0.5)+750ms. Assembly 0x40DA3E-0x40DA6C stores and uses the maximum; stale/inferred pseudocode can incorrectly appear to discard it.
void __cdecl rf_ai_mode2_speech_action_update(int *a1, int a2)
{
  float duration; // [esp+Ch] [ebp-14h]
  int v3; // [esp+10h] [ebp-10h]
  int v4; // [esp+10h] [ebp-10h]
  int v5; // [esp+10h] [ebp-10h]
  float v6; // [esp+18h] [ebp-8h]
  float v7; // [esp+1Ch] [ebp-4h]

  if ( a1[160] == 2 )
  {
    rf_entity_refresh_idle_animation_deadline(*a1);
    if ( !rf_entity_speech_voice_is_playing(*a1) )
    {
      if ( *((float *)a1 + 304) <= 0.0 || *(_DWORD *)(*a1 + 5216) == -1 )
      {
        v3 = rf_registry56_choose_sound_at_6E674C(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
        if ( v3 != -1 )
          rf_entity_replace_speech_voice(*a1, v3, 0);
      }
      else if ( *(float *)(*(_DWORD *)(a2 + 660) + 68) > (double)*(float *)(a2 + 52) )
      {
        v5 = rf_foley_registry_choose_sound_by_index(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
        if ( v5 != -1 )
          rf_entity_replace_speech_voice(*a1, v5, 0);
        rf_ai_numeric_mode_write(a1, 14, -1, -1);
        sub_40BA80(a1, *(_DWORD *)(a2 + 44));
        rf_ai_clear_scripted_animation_context(a1);
        rf_entity_request_body_action(*a1, 0x2Bu, 1.0, 0, 1);
        v7 = rf_model_animation_duration_seconds((unsigned int *)*(_DWORD *)(*a1 + 128), *(_DWORD *)(*a1 + 3332));
        duration = rf_sound_query_duration(v5);
        v6 = rf_float_maximum_two_values(v7, duration);
        rf_replicator_arm_milliseconds(a1 + 305, (int)(v6 * 1000.0 + 0.5) + 750);
      }
      else
      {
        v4 = rf_registry56_choose_sound_at_6E6750(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
        if ( v4 != -1 )
          rf_entity_replace_speech_voice(*a1, v4, 0);
      }
    }
  }
}

