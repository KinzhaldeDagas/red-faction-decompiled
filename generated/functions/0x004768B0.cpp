// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004768B0 rf_cutscene_begin_by_identifier
// UNREALRED VERIFIED [mission-visibility-20261020] This owner assigns global pointer0x6FB24C from registry lookup475E80(a1), which is the UnHide global bypass predicate476D00. Entry stops music/voices, configures player presentation, can hide player and attached vehicle, and changes frame timing. Semantic sequence identity has not been fully reconstructed in this pass.
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Selected by generic forward type55 Cutscene. Require non-null living player. Stop owned music, pause sound backend, stop all gamesound slots and run presentation/audio helpers BEFORE registry lookup0x475E80(input). Store global cutscene pointer0x6FB24C; non-null record with nonpositive count+4 returns after those earlier effects. Valid record initializes playback, clears zoom/voices/projectiles/alarm, optionally hides player and associated vehicle, and applies record field+0x85C to player+0xD8. Exact level exceptions include L7S3.rfl association handling and L20S2.rfl fighter01 cleanup. Final reached path calls0x5A4110(1), saves global timing0x661580 to0x6FB254 then sets31.25f; null lookup also reaches that timing path. This contract records entry side effects; full cutscene evaluator/restore lifecycle remains separate.
void __cdecl rf_cutscene_begin_by_identifier(int a1)
{
  int j; // [esp+0h] [ebp-14h]
  int v2; // [esp+4h] [ebp-10h]
  int v3; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]

  if ( dword_681E38 && !rf_entity_is_dead(dword_681E38) )
  {
    rf_music_owned_stop();
    rf_sound_backend_set_paused(1);
    rf_gamesound_stop_all_voice_slots();
    rf_audio_environment_save_room_level_and_mute();
    if ( rf_ui_pending_panel_id_get() == 2 )
      rf_ui_clear_pending_panel_transition();
    sub_43E8A0();
    dword_6FB24C = rf_cutscene_record_find_by_id(a1);
    if ( dword_6FB24C )
    {
      if ( *(int *)(dword_6FB24C + 4) <= 0 )
        return;
      *(_DWORD *)(dword_6FB24C + 2056) = 0;
      rf_cutscene_start_segment(dword_6FB24C, 0);
      rf_cutscene_play_level_audio_mix();
      sub_43C0B0(dword_681E38);
      rf_player_reset_alt_zoom_state(rf_local_fpgun_player);
      *(_BYTE *)(rf_local_fpgun_player + 4016) = 0;
      for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
        rf_object_mark_for_deferred_delete(i);
      rf_alarm_disable_shared();
      if ( dword_681E38 )
      {
        rf_player_control_clear_vectors_and_fields1C20((float *)(dword_681E38 + 1800));
        rf_entity_stop_weapon_firing(*(_DWORD *)(dword_681E38 + 44), *(_DWORD *)(dword_681E38 + 676));
        if ( rf_entity_has_attached_use_vehicle(dword_681E38) )
        {
          v3 = rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
          if ( v3 )
            rf_entity_stop_weapon_firing(*(_DWORD *)(v3 + 44), *(_DWORD *)(v3 + 676));
        }
      }
      if ( *(_BYTE *)(dword_6FB24C + 2137) == 1 )
      {
        rf_object_mark_hidden_inactive(dword_681E38);
        v2 = rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
        if ( v2 )
        {
          if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "L7S3.rfl") )
            rf_entity_try_detach_with_safe_exit(dword_681E38);
          rf_object_mark_hidden_inactive(v2);
        }
      }
      *(float *)(rf_local_fpgun_player + 216) = *(float *)(dword_6FB24C + 2140);
      if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "L6S3.rfl")
        || rf_string_equals_case_insensitive((int)unk_6FC31C, "L8S4.rfl")
        || rf_string_equals_case_insensitive((int)unk_6FC31C, "L11S3.rfl")
        || rf_string_equals_case_insensitive((int)unk_6FC31C, "L14S3.rfl") )
      {
        rf_ai_pause_updates_and_stop_entity_firing();
      }
      if ( rf_string_equals_case_insensitive((int)unk_6FC31C, "L20S2.rfl") )
      {
        for ( j = unk_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
        {
          if ( rf_string_equals_case_insensitive(*(_DWORD *)(j + 660), "fighter01")
            && !rf_entity_runtime_enabled_or_resolved_attachment(j, -1) )
          {
            rf_object_mark_for_deferred_delete(j);
          }
        }
      }
    }
    rf_model_set_special_lod_light_mode(1);
    unk_6FB254 = flt_661580;
    flt_661580 = 31.25;
  }
}

