// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476BF0 rf_cutscene_end_restore_player_state
// UNREALRED VERIFIED [mission-visibility-20261020] Exits owner referenced by UnHide bypass pointer0x6FB24C. Reactivates player and (except L7S3) attached vehicle, resets player-related state, then clears pointer and restores timing. UnHide global bypass tests pointer presence, not an inferred world-pause flag.
// UNREALRED VERIFIED [cutscene-ui-20261028]: Only when active pointer0x6FB24C is nonnull: resets local-player view owner through0x4120D0 and sets player+216=90; reactivates entity0x681E38, reactivates attached vehicle except when current logical level equals L7S3.rfl (case-insensitive), resets entity-related values through0x442000/+1800 and zero-vector helpers+324/+336. Clears active pointer, calls0x40CDE0/0x5987D0/0x5A4110(0), restores float0x661580 from0x6FB254. No registry destruction here; called by level reset.
void rf_cutscene_end_restore_player_state()
{
  _DWORD *v0; // [esp+0h] [ebp-4h]

  if ( dword_6FB24C )
  {
    if ( rf_local_fpgun_player )
    {
      rf_camera_slot_enter_first_person(*(float ***)(rf_local_fpgun_player + 196));
      *(float *)(rf_local_fpgun_player + 216) = 90.0;
    }
    if ( dword_681E38 )
    {
      rf_object_reactivate_from_respawn((_DWORD *)dword_681E38);
      if ( rf_rf_string_not_equals_cstring_case_insensitive((int)unk_6FC31C, "L7S3.rfl") )
      {
        v0 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
        if ( v0 )
          rf_object_reactivate_from_respawn(v0);
      }
      rf_player_control_clear_vectors_and_fields1C20((float *)(dword_681E38 + 1800));
      rf_vector3_zero_return_destination((float *)(dword_681E38 + 324));
      rf_vector3_zero_return_destination((float *)(dword_681E38 + 336));
    }
    dword_6FB24C = 0;
    rf_ai_resume_updates();
    rf_audio_environment_restore_saved_room_level();
    rf_model_set_special_lod_light_mode(0);
    flt_661580 = unk_6FB254;
  }
}

