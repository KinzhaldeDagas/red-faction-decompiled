// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00422A40 rf_entity_stop_weapon_firing
// UNREALRED VERIFIED [mission-visibility-20261020] Stops the specified weapon index for resolved entity UID: clears entity+1132[index], clears entity+2000 mask0x2000, conditionally stops looping weapon voice+2076 and presents stop sound+2080; shuts off flame owner+5076. UnHide hide calls this with the equipped weapon at entity+676.
void __cdecl rf_entity_stop_weapon_firing(int a1, unsigned int a2)
{
  int v2; // eax
  float v3[3]; // [esp-10h] [ebp-38h] BYREF
  int sound_by_index; // [esp-4h] [ebp-2Ch]
  float v5; // [esp+0h] [ebp-28h]
  float v6; // [esp+4h] [ebp-24h]
  int local_player_entry_or_related_owner; // [esp+Ch] [ebp-1Ch]
  float out_position[3]; // [esp+10h] [ebp-18h] BYREF
  char *v9; // [esp+1Ch] [ebp-Ch]
  unsigned int *entity; // [esp+20h] [ebp-8h]
  char v11; // [esp+27h] [ebp-1h]

  if ( a2 < 0x40 )
  {
    entity = (unsigned int *)rf_entity_resolve_handle(a1);
    if ( entity )
    {
      v11 = 0;
      if ( *((_BYTE *)entity + a2 + 1132) )
      {
        v11 = 1;
        if ( byte_704E83 != 1 )
        {
          v9 = (char *)&rf_weapon_records + 1360 * a2;
          if ( (*((_DWORD *)v9 + 153) & 2) != 0 || (*((_DWORD *)v9 + 153) & 4) != 0 )
          {
            if ( entity[519] != -1 )
            {
              rf_gamesound_stop_voice_handle(entity[519]);
              entity[519] = -1;
            }
            if ( *((int *)v9 + 129) > -1 && v11 == 1 )
            {
              rf_vector3_default_construct_noop(out_position);
              rf_entity_primary_tag_position(entity, out_position);
              v6 = 0.0;
              v5 = 1.0;
              sound_by_index = rf_foley_get_sound_by_index(*((_DWORD *)v9 + 129), 0);
              rf_vector3_copy_return_destination(v3, out_position);
              v2 = rf_sound_event_play_for_object_view(
                     (int)entity,
                     v3[0],
                     SLODWORD(v3[1]),
                     SLODWORD(v3[2]),
                     sound_by_index,
                     v5,
                     v6);
              entity[520] = v2;
            }
            if ( rf_entity_admits_speech_body_actions((int)entity) && !rf_entity_is_dead((int)entity) )
              rf_model_handle_reset_actions_adapter(entity[32]);
          }
        }
      }
      *((_BYTE *)entity + a2 + 1132) = 0;
      entity[500] &= ~0x2000u;
      if ( rf_weapon_has_flame_flag(a2) && entity[1269] != -1 )
        rf_firing_effect_slot_set_enabled_for_mode(entity[1269], 0);
      if ( sub_438AC0((int)entity) && v11 )
      {
        rf_weapon_has_flame_flag(a2);
      }
      else if ( rf_entity_matches_local_player_or_related_handle((int)entity)
             && v11
             && (a2 == unk_911CB8 || a2 == unk_911C9C || a2 == unk_911C90 || a2 == unk_911CD0 || a2 == unk_911C8C) )
      {
        local_player_entry_or_related_owner = rf_object_find_local_player_entry_or_related_owner((int)entity);
      }
      if ( sub_438AC0((int)entity) )
        rf_player_autoswitch_exhausted_weapon(entity[1292], 0);
    }
  }
}

