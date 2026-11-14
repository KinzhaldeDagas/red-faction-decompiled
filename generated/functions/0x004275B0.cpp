// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004275B0 sub_4275B0
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Within admitted active/model entity update:42BBB0 speech action scheduler precedes retained speech pose5684D0 at427878 (source7D4,velocity144,gain1); later death admission429820 and body-state transition428950 occur. Common inactive branch skips these countdown/pose phases without stopping retained speech. This caller alone does not prove global AI-vs-entity frame ordering.
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Reference retention order: speech action42BBB0 at4276C3; retained voice5684D0 update at427878 uses existing7D4; reference recompute420870 at427890 happens AFTER that voice update. Then later body transition428950. AI executes in prephysics4B9420 type0->426890->403D90->403DE0 before postphysics4B9590 entity update. A current camera/socket query at every speech callback does not preserve this retained reference/order.
char __cdecl sub_4275B0(unsigned int *entity)
{
  _DWORD *v1; // eax
  float *v2; // eax
  int v3; // eax
  double v4; // st7
  float v6[2]; // [esp+8h] [ebp-114h] BYREF
  float *v7; // [esp+10h] [ebp-10Ch]
  float v8; // [esp+14h] [ebp-108h]
  float v9; // [esp+18h] [ebp-104h]
  float v10; // [esp+1Ch] [ebp-100h]
  float v11; // [esp+20h] [ebp-FCh]
  float v12; // [esp+24h] [ebp-F8h]
  float v13; // [esp+28h] [ebp-F4h]
  float v14; // [esp+2Ch] [ebp-F0h]
  float v15; // [esp+30h] [ebp-ECh]
  float v16; // [esp+34h] [ebp-E8h]
  float v17; // [esp+38h] [ebp-E4h]
  float v18; // [esp+3Ch] [ebp-E0h]
  float v19[3]; // [esp+40h] [ebp-DCh] BYREF
  float v20[3]; // [esp+4Ch] [ebp-D0h] BYREF
  float copy_result[3]; // [esp+58h] [ebp-C4h] BYREF
  float v22[4]; // [esp+64h] [ebp-B8h] BYREF
  float v23; // [esp+74h] [ebp-A8h]
  float v24; // [esp+78h] [ebp-A4h]
  int v25; // [esp+7Ch] [ebp-A0h]
  _DWORD *v26; // [esp+80h] [ebp-9Ch]
  float v27; // [esp+84h] [ebp-98h]
  float v28; // [esp+88h] [ebp-94h]
  float out_orientation[9]; // [esp+8Ch] [ebp-90h] BYREF
  float out_attachment_position[3]; // [esp+B0h] [ebp-6Ch] BYREF
  float out_corrected_position[3]; // [esp+BCh] [ebp-60h] BYREF
  float *v32; // [esp+C8h] [ebp-54h]
  char v33[12]; // [esp+CCh] [ebp-50h] BYREF
  float source[6]; // [esp+D8h] [ebp-44h] BYREF
  float *v35; // [esp+F0h] [ebp-2Ch]
  int v36; // [esp+F4h] [ebp-28h]
  _DWORD *v37; // [esp+F8h] [ebp-24h]
  char v38; // [esp+FFh] [ebp-1Dh]
  int v39; // [esp+100h] [ebp-1Ch]
  float out_position[3]; // [esp+104h] [ebp-18h] BYREF
  int v41; // [esp+110h] [ebp-Ch]
  _DWORD *v42; // [esp+114h] [ebp-8h]
  int v43; // [esp+118h] [ebp-4h]

  LOBYTE(v1) = rf_object_has_respawn_inactive_flag((int)entity);
  if ( (unsigned __int8)v1 == 1 )
  {
    if ( entity[513] != -1 )
      LOBYTE(v1) = (unsigned __int8)rf_ambient_voice_set_source_gain(entity[513], 0.0);
  }
  else
  {
    if ( rf_multiplayer_runtime_mode == 1 )
    {
      LOBYTE(v1) = rf_multiplayer_server_authority;
      if ( !rf_multiplayer_server_authority && (entity[31] & 0x40) != 0 )
      {
        LOBYTE(v1) = (_BYTE)entity;
        *((float *)entity + 13) = 0.0;
      }
    }
    if ( rf_multiplayer_runtime_mode != 1
      || rf_multiplayer_server_authority
      || (LOBYTE(v1) = (_BYTE)entity, (entity[31] & 8) == 0)
      || (v1 = sub_4DD720(entity[11]), (v42 = v1) != nullptr) )
    {
      if ( entity[32] && entity != (unsigned int *)unk_666A9C )
      {
        rf_entity_apply_room_kind_frame_damage((int *)entity);
        rf_entity_apply_frame_damage_type10((int)entity);
        rf_entity_update_motion_ambient_voice_gain((int)entity);
        rf_entity_update_motion_scaled_positioned_voice((int)entity);
        rf_entity_update_speech_body_actions((int)entity);
        if ( entity[519] == -1 )
        {
          if ( rf_entity_class_flags724_has_mask800((int)entity) && rf_replicator_has_elapsed((int *)entity + 518) )
          {
            rf_replicator_reset(entity + 518);
            if ( rf_entity_weapon_firing_byte_is_set(entity[11], entity[169]) )
            {
              v39 = rf_foley_choose_random_sound(unk_912160[340 * entity[169]]);
              if ( *(_DWORD *)(entity[165] + 1872) != -1 )
                v39 = rf_foley_choose_random_sound(*(_DWORD *)(entity[165] + 1872));
              entity[519] = rf_gamesound_play_event(v39, 0, 0.0, 1.0);
            }
            else
            {
              v41 = unk_912204[340 * entity[169]];
              if ( v41 > -1 )
              {
                rf_vector3_default_construct_noop(out_position);
                rf_entity_primary_tag_position(entity, out_position);
                v10 = 0.0;
                v9 = 1.0;
                v8 = COERCE_FLOAT(rf_foley_get_sound_by_index(v41, 0));
                rf_vector3_copy_return_destination(v6, out_position);
                entity[520] = rf_sound_event_play_for_object_view(
                                (int)entity,
                                v6[0],
                                SLODWORD(v6[1]),
                                (int)v7,
                                SLODWORD(v8),
                                v9,
                                v10);
              }
            }
          }
        }
        else
        {
          rf_positioned_voice_update(entity[519], (float *)entity + 15, (int)(entity + 81), 1.0);
        }
        if ( entity[1280] != -1 )
          rf_positioned_voice_update(entity[1280], (float *)entity + 501, (int)(entity + 81), 1.0);
        rf_entity_update_directional_motion_sound_latch((unsigned int)entity);
        sub_420870((int)entity);
        if ( rf_object_has_player_flag((int)entity) )
        {
          sub_40BD80((int *)entity + 168);
          rf_ai_spawn_elapsed_projectiles((int *)entity + 168);
        }
        rf_entity_play_footstep_trigger((int)entity);
        if ( rf_entity_weapon_firing_byte_is_set(entity[11], entity[169]) )
        {
          v38 = (entity[500] & 0x2000) != 0;
          sub_431FD0((int)entity, 0, v38, nullptr, 0, 0);
          if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 && !sub_438AC0((int)entity) )
          {
            v37 = sub_4DD720(entity[11]);
            v36 = entity[169];
            if ( v36 >= 0 )
            {
              if ( v37 )
              {
                v35 = (float *)((char *)&rf_weapon_records + 1360 * v36);
                if ( (rf_weapon_is_riot_stick(v36) || rf_weapon_has_flame_flag(v36))
                  && (rf_replicator_has_elapsed(v37 + 996) || !rf_replicator_is_armed(v37 + 996)) )
                {
                  rf_weapon_decrement_clip_or_reserve_ammo((int)entity, v36);
                  rf_replicator_arm_milliseconds(v37 + 996, (int)(v35[36] / (double)*((int *)v35 + 34) * 1000.0));
                }
              }
            }
          }
        }
        rf_entity_update_runtime_vfx(entity);
        rf_entity_weapon_update((int *)entity);
        if ( byte_704E83 != 1 )
        {
          if ( rf_replicator_has_elapsed((int *)entity + 1243) )
          {
            if ( entity[1246] != -1 )
            {
              rf_renderer_light_release(entity[1246], 0);
              entity[1246] = -1;
            }
          }
          else
          {
            rf_entity_ensure_selected_weapon_point_light(entity);
          }
        }
        v43 = rf_entity_resolve_handle(entity[128]);
        if ( v43 && (entity[31] & 0x100) == 0 )
          rf_matrix3_copy((float *)entity + 504, (const float *)(v43 + 2016));
        if ( *((float *)entity + 13) <= 0.0 )
          rf_entity_handle_death_admission((int)entity);
        if ( rf_entity_is_dead((int)entity) )
          rf_entity_update_death_completion((int)entity);
        if ( rf_entity_admits_speech_body_actions((int)entity) )
          sub_428950((int)entity);
        if ( sub_438AC0((int)entity) )
          rf_player_rebuild_forward_point_light(entity[1292]);
        if ( (rf_entity_read_current_room_byte65(entity) == 1 || (*(_DWORD *)(entity[165] + 1832) & 0x20) != 0)
          && entity[1278]
          && (int)entity[1277] > -1
          && !rf_entity_body_state_is_resident((int)entity, 13) )
        {
          rf_matrix3_construct(v33);
          rf_model_handle_get_node_transform_adapter(entity[32], entity[1278] + 8, (int)v33, entity[1277]);
          *(_DWORD *)(entity[1278] + 76) = rf_receiver_get_first_dword(entity);
          if ( (*(_DWORD *)(entity[165] + 1832) & 0x20) != 0 )
          {
            v2 = rf_vector3_set_components_return_destination(v22, 0.0, -1.0, 0.0);
            rf_vector_copy((float *)(entity[1278] + 20), copy_result, v2);
          }
          else
          {
            rf_vector_copy((float *)(entity[1278] + 20), v20, source);
          }
          rf_particle_emitter_process(entity[1278]);
        }
        if ( *(int *)(entity[165] + 316) >= 0 && entity[515] == -1 )
        {
          v10 = 0.0;
          v9 = COERCE_FLOAT(&unk_17F10B0);
          v8 = 1.0;
          v7 = (float *)(entity + 15);
          v3 = rf_foley_choose_random_sound(*(_DWORD *)(entity[165] + 316));
          entity[515] = rf_gamesound_play_positional_event(v3, v7, v8, SLODWORD(v9), SLODWORD(v10));
        }
        if ( rf_entity_class_flag1000((int)entity) )
        {
          entity[517] &= ~0x40u;
          if ( rf_entity_weapon_firing_byte_is_set(entity[11], entity[169]) )
            v4 = rf_frame_delta_seconds / 1.0 * 10.99557495117188 + *((float *)entity + 1266);
          else
            v4 = *((float *)entity + 1266) - rf_frame_delta_seconds / 2.0 * 10.99557495117188;
          *((float *)entity + 1266) = v4;
          rf_float_clamp_in_place((float *)entity + 1266, 0.0, 10.995575);
          *((float *)entity + 1265) = rf_frame_delta_seconds * *((float *)entity + 1266) + *((float *)entity + 1265);
          if ( rf_entity_weapon_firing_byte_is_set(entity[11], entity[169]) )
          {
            rf_driller_contact_geomod_update((int *)entity);
          }
          else
          {
            rf_replicator_reset(entity + 1267);
            if ( entity[1268] != -1 )
            {
              rf_gamesound_stop_voice_handle(entity[1268]);
              entity[1268] = -1;
            }
          }
        }
        if ( rf_gamesound_voice_is_playing(entity[1280]) && dword_681E70 < 10 )
          unk_681E3C[dword_681E70++] = (int)entity;
        if ( entity[1300] != -1 && entity[169] == unk_911C80 )
        {
          v32 = (float *)rf_clutter_find_by_uid(entity[1300]);
          if ( v32 )
          {
            rf_vector3_default_construct_noop(out_attachment_position);
            rf_vector3_default_construct_noop(out_corrected_position);
            rf_matrix3_construct((char *)out_orientation);
            if ( rf_entity_copy_weapon_attachment_transforms(
                   entity,
                   0,
                   out_attachment_position,
                   out_corrected_position,
                   out_orientation) != -1 )
            {
              rf_vector_copy(v32 + 60, v19, out_corrected_position);
              rf_object_publish_position_and_bounds((int)v32, out_corrected_position);
              rf_matrix3_copy(v32 + 18, out_orientation);
              rf_matrix3_copy(v32 + 63, out_orientation);
              rf_matrix3_copy(v32 + 72, out_orientation);
            }
          }
        }
        rf_entity_update_attached_clutter_pose((int)entity, 0);
        rf_entity_update_attached_clutter_pose((int)entity, 1);
        if ( !sub_438AC0((int)entity) )
          entity[516] &= ~2u;
        LOBYTE(v1) = rf_multiplayer_runtime_mode;
        if ( rf_multiplayer_runtime_mode && byte_704E83 != 1 )
        {
          if ( entity[1313] != -1 )
          {
            rf_renderer_light_release(entity[1313], 0);
            entity[1313] = -1;
          }
          if ( (entity[517] & 0x20000) != 0 )
          {
            unk_681E88 = unk_681E88 + rf_frame_delta_seconds;
            if ( flt_661528 < (double)unk_681E88 )
              unk_681E88 = unk_681E88 - flt_661528;
            v18 = 6.283185482025146 / flt_661528 * unk_681E88;
            v28 = rf_sin_float(v18);
            v17 = v28 * flt_66152C + flt_661520;
            v1 = (_DWORD *)rf_renderer_point_light_create(
                             (int)(entity + 15),
                             flt_661524,
                             v17,
                             1.0,
                             0.36078432,
                             0.96078432,
                             1,
                             1,
                             0);
            entity[1313] = (unsigned int)v1;
          }
          else if ( (entity[517] & 0x40000) != 0 )
          {
            unk_681E88 = unk_681E88 + rf_frame_delta_seconds;
            if ( flt_661528 < (double)unk_681E88 )
              unk_681E88 = unk_681E88 - flt_661528;
            v16 = 6.283185482025146 / flt_661528 * unk_681E88;
            v27 = rf_sin_float(v16);
            v15 = v27 * flt_66152C + flt_661520;
            v1 = (_DWORD *)rf_renderer_point_light_create(
                             (int)(entity + 15),
                             flt_661524,
                             v15,
                             0.37254903,
                             0.99215686,
                             1.0,
                             1,
                             1,
                             0);
            entity[1313] = (unsigned int)v1;
          }
          else
          {
            v25 = rf_ctf_blue_carrier_get();
            v1 = (_DWORD *)rf_ctf_red_carrier_get();
            v26 = v1;
            if ( v25 && (LOBYTE(v1) = v25, *(_DWORD *)(v25 + 20) == entity[11]) )
            {
              unk_681E88 = unk_681E88 + rf_frame_delta_seconds;
              if ( flt_661528 < (double)unk_681E88 )
                unk_681E88 = unk_681E88 - flt_661528;
              v14 = 6.283185482025146 / flt_661528 * unk_681E88;
              v24 = rf_sin_float(v14);
              v13 = v24 * flt_66152C + flt_661520;
              v1 = (_DWORD *)rf_renderer_point_light_create(
                               (int)(entity + 15),
                               4.0,
                               v13,
                               0.30000001,
                               0.30000001,
                               1.0,
                               1,
                               1,
                               0);
              entity[1313] = (unsigned int)v1;
            }
            else if ( v26 )
            {
              LOBYTE(v1) = (_BYTE)entity;
              if ( v26[5] == entity[11] )
              {
                unk_681E88 = unk_681E88 + rf_frame_delta_seconds;
                if ( flt_661528 < (double)unk_681E88 )
                  unk_681E88 = unk_681E88 - flt_661528;
                v12 = 6.283185482025146 / flt_661528 * unk_681E88;
                v23 = rf_sin_float(v12);
                v11 = v23 * flt_66152C + flt_661520;
                v1 = (_DWORD *)rf_renderer_point_light_create((int)(entity + 15), 4.0, v11, 1.0, 0.0, 0.0, 1, 1, 0);
                entity[1313] = (unsigned int)v1;
              }
            }
          }
        }
      }
    }
    else
    {
      entity[31] |= 2u;
      LOBYTE(v1) = (_BYTE)entity;
    }
  }
  return (char)v1;
}

