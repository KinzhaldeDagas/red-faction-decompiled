// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044CEE0 rf_hud_persona_admit_message
// UNREALRED VERIFIED [hud-persona-presentation-20261027] Persona activation selects its own active index/record and target opacity, independently of the ordinary message queue rendered by 0x44B360. Only the selected persona record has its previous voice stopped; other persona voices remain owned by the sound pool. Host ordinary and persona presentation must not overwrite one shared message slot. Exact 350ms voice-start/end-cue scheduling remains the separate 0x44D0C0 contract.
char __cdecl rf_hud_persona_admit_message(char *Source, int a2, int a3)
{
  const char *v4; // eax
  char *v5; // eax
  char *v6; // [esp+8h] [ebp-Ch]
  float duration; // [esp+Ch] [ebp-8h]
  char _3d_mode_byte; // [esp+13h] [ebp-1h]

  if ( a2 == -1 )
  {
    rf_hud_message_enqueue_expand_tokens_and_rearm_head(
      "Asked to play message an undefined persona type",
      0,
      0,
      nullptr);
    return 0;
  }
  else
  {
    rf_persona_history_append(Source, a2);
    if ( *(_BYTE *)(rf_local_fpgun_player + 3902)
      || (v4 = rf_string_object_c_str_or_empty(unk_6FC31C), rf_level_name_is_training(v4)) )
    {
      v6 = &rf_hud_persona_records[296 * a2];
      if ( rf_gamesound_voice_is_playing(*((_DWORD *)v6 + 7)) )
      {
        rf_gamesound_stop_voice_handle(*((_DWORD *)v6 + 7));
        *((_DWORD *)v6 + 7) = -1;
      }
      sub_568000(3, 0, 0.0, 1.0);
      rf_replicator_arm_milliseconds(&rf_hud_persona_voice_start_timer, 350);
      _3d_mode_byte = rf_audio_get_3d_mode_byte();
      rf_audio_set_3d_mode_byte_raw(0);
      duration = rf_sound_query_duration(a3);
      rf_replicator_arm_milliseconds(&rf_hud_persona_end_cue_timer, (int)(duration * 1000.0 + 0.5) + 400);
      rf_audio_set_3d_mode_byte_raw(_3d_mode_byte);
      strncpy(v6 + 36, Source, 0x100u);
      v6[291] = 0;
      *((_DWORD *)v6 + 8) = a3;
      if ( *((_DWORD *)v6 + 6) == -1 )
      {
        v5 = (char *)rf_string_object_c_str_or_empty(v6 + 8);
        *((_DWORD *)v6 + 6) = rf_bitmap_load_with_optional_mipmap_generation(v5, (void *)0xFFFFFFFF, 0);
      }
      if ( duration > 2000.0 )
        rf_replicator_arm_milliseconds((int *)v6 + 73, (int)(duration * 1000.0) + 2000);
      else
        rf_replicator_arm_milliseconds((int *)v6 + 73, 6000);
      rf_hud_persona_active_index = a2;
      rf_hud_persona_set_target_opacity255(255.0);
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

