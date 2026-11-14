// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00431FD0 sub_431FD0
// UNREALRED VERIFIED [combat-fire-exhaustion-20260930] The ammo-check-enabled total<=0 branch stops the current weapon via 0x422A40. For non-player entities, both multiplayer and split-screen inactive call archetype grant/select 0x431DF0; either active calls forced selector 0x4014F0. Empty loaded ammo with positive reserve does not take this recovery. In ordinary single-player non-player use, finite checks include Grenade, shoulder_cannon, Rocket Launcher and HEAP; later flags, association predicates and explicit-shot argument can override admission.
// UNREALRED VERIFIED [weapon-shell-ejection-20261008] At 0x43346x after successful projectile creation/ammo consumption, a nonempty shell model causes ejection. Positive +1220 pause with primary mode arms the single Entity+0x1374 deadline using trunc(pause*1000) milliseconds. Nonpositive delay or alternate mode invokes 0x438170 immediately. No reload-duration 0.6666 factor applies. This is a cosmetic path, not another ammo transaction.
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Finite ammo admission afterOWNED403D00 gate: starttrue; ordinary(nonGrenade/nonshouldercannon/nonRocket/nonHEAP) withMP/splitbothzero sets from4BCF40 playerassociation. Then MELEEflag20 forcesfalse exceptRiotStick uses exactalt selector==1; nonmelee local-related4BCE50 forcestrue. Detonator510FA0 or explicitpositionarg5 nonzero forcesfalse. Enabled test is wrapping436310 TOTAL<=0, not magazine>=cost. NormalSPnonplayer gun canlaunch atzero total; successful ordinarylaunch still invokes431EF0 decrement/floor. Explicit-shotpointer is not merely a host computed muzzle position. Associated/related common handle owners remain distinct source dependencies.
void __cdecl sub_431FD0(float a1, char a2, char a3, _DWORD *a4, float *a5, float *a6)
{
  float *v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  float v10; // [esp-Ch] [ebp-314h] BYREF
  int v11; // [esp-8h] [ebp-310h]
  int v12; // [esp-4h] [ebp-30Ch] BYREF
  int v13; // [esp+0h] [ebp-308h]
  float v14; // [esp+4h] [ebp-304h]
  float v15; // [esp+8h] [ebp-300h]
  float v16; // [esp+Ch] [ebp-2FCh]
  bool v17; // [esp+13h] [ebp-2F5h]
  float v18; // [esp+14h] [ebp-2F4h]
  int v19; // [esp+18h] [ebp-2F0h]
  float v20[3]; // [esp+34h] [ebp-2D4h] BYREF
  float v21[3]; // [esp+40h] [ebp-2C8h] BYREF
  float v22[3]; // [esp+4Ch] [ebp-2BCh] BYREF
  float v23[3]; // [esp+58h] [ebp-2B0h] BYREF
  float v24[7]; // [esp+64h] [ebp-2A4h] BYREF
  float v25[3]; // [esp+80h] [ebp-288h] BYREF
  float out_vector[3]; // [esp+8Ch] [ebp-27Ch] BYREF
  float v27[3]; // [esp+98h] [ebp-270h] BYREF
  float copy_result[6]; // [esp+A4h] [ebp-264h] BYREF
  int v29; // [esp+BCh] [ebp-24Ch]
  _DWORD *v30; // [esp+C0h] [ebp-248h]
  void *player; // [esp+C4h] [ebp-244h]
  float muzzle_position[3]; // [esp+C8h] [ebp-240h] BYREF
  int v33; // [esp+D4h] [ebp-234h]
  int *v34; // [esp+D8h] [ebp-230h]
  float v35[3]; // [esp+DCh] [ebp-22Ch] BYREF
  float v36[6]; // [esp+E8h] [ebp-220h] BYREF
  float v37[3]; // [esp+100h] [ebp-208h] BYREF
  int v38; // [esp+10Ch] [ebp-1FCh]
  float v39[9]; // [esp+110h] [ebp-1F8h] BYREF
  float source[3]; // [esp+134h] [ebp-1D4h] BYREF
  bool is_continuous_exact_selector; // [esp+143h] [ebp-1C5h]
  float v42[3]; // [esp+144h] [ebp-1C4h] BYREF
  float v43[9]; // [esp+150h] [ebp-1B8h] BYREF
  int m; // [esp+174h] [ebp-194h]
  int v45; // [esp+178h] [ebp-190h]
  _DWORD *v46; // [esp+17Ch] [ebp-18Ch]
  int v47; // [esp+180h] [ebp-188h]
  int j; // [esp+184h] [ebp-184h]
  int v49; // [esp+188h] [ebp-180h]
  int v50; // [esp+18Ch] [ebp-17Ch]
  int v51; // [esp+190h] [ebp-178h]
  int v52; // [esp+194h] [ebp-174h]
  int i; // [esp+198h] [ebp-170h]
  int local_player_entry_or_related_owner; // [esp+19Ch] [ebp-16Ch]
  float v55[9]; // [esp+1A0h] [ebp-168h] BYREF
  float v56[3]; // [esp+1C4h] [ebp-144h] BYREF
  char v57[52]; // [esp+1D0h] [ebp-138h] BYREF
  float destination[3]; // [esp+204h] [ebp-104h] BYREF
  float v59[12]; // [esp+210h] [ebp-F8h] BYREF
  _DWORD v60[10]; // [esp+240h] [ebp-C8h] BYREF
  int v61; // [esp+268h] [ebp-A0h]
  int v62; // [esp+26Ch] [ebp-9Ch]
  float lhs[3]; // [esp+270h] [ebp-98h] BYREF
  char v64[36]; // [esp+27Ch] [ebp-8Ch] BYREF
  float v65; // [esp+2A0h] [ebp-68h]
  float v66[9]; // [esp+2A4h] [ebp-64h] BYREF
  int first_dword; // [esp+2C8h] [ebp-40h]
  int v68; // [esp+2CCh] [ebp-3Ch]
  bool v69; // [esp+2D2h] [ebp-36h]
  char v70; // [esp+2D3h] [ebp-35h]
  _DWORD *runtime; // [esp+2D4h] [ebp-34h]
  char *v72; // [esp+2D8h] [ebp-30h]
  bool v73; // [esp+2DFh] [ebp-29h]
  float v74[3]; // [esp+2E0h] [ebp-28h] BYREF
  int v75; // [esp+2ECh] [ebp-1Ch]
  _DWORD *v76; // [esp+2F0h] [ebp-18h]
  int k; // [esp+2F4h] [ebp-14h]
  char v78[4]; // [esp+2F8h] [ebp-10h]
  _DWORD *v79; // [esp+2FCh] [ebp-Ch]
  float v80; // [esp+300h] [ebp-8h]
  bool v81; // [esp+307h] [ebp-1h]

  v81 = a5 != nullptr;
  v79 = (_DWORD *)(LODWORD(a1) + 672);
  if ( !rf_entity_is_dead(SLODWORD(a1)) && !rf_entity_weapon_is_holstered_for_actions(SLODWORD(a1)) )
  {
    *(_DWORD *)v78 = v79[1];
    if ( !v81 && *(int *)v78 < 0 )
    {
      rf_replicator_arm_milliseconds(v79 + 134, 500);
      return;
    }
    if ( (*(_DWORD *)(*(_DWORD *)(LODWORD(a1) + 660) + 1828) & 0x20) != 0 && rf_weapon_has_alt_fire_flag(*(int *)v78) )
      a3 = 1;
    if ( a3 != 1 || rf_weapon_has_alt_fire_flag(*(int *)v78) )
    {
      v72 = (char *)&rf_weapon_records + 1360 * *(_DWORD *)v78;
      if ( !a2 )
      {
        if ( !rf_replicator_has_elapsed(v79 + 134) && !rf_entity_class_flag1000(SLODWORD(a1)) && !v81 )
          return;
        if ( rf_weapon_matches_special_pair(*(int *)v78) )
        {
          v19 = rf_timestamp_signed_elapsed_milliseconds((void *)(LODWORD(a1) + 5116));
          v18 = (double)v19 / 1000.0;
          v65 = v18;
          if ( v18 < 0.300000011920929 && dword_6612A4 )
          {
            *(float *)(LODWORD(a1) + 5044) = v65 * 4.0 + *(float *)(LODWORD(a1) + 5044);
            if ( *(float *)(LODWORD(a1) + 5044) > 5.0 )
              *(float *)(LODWORD(a1) + 5044) = 5.0;
          }
          else
          {
            *(float *)(LODWORD(a1) + 5044) = 1.0;
          }
        }
      }
      v68 = rf_weapon_fire_wait_milliseconds(*(int *)v78, a3);
      if ( !rf_object_is_player_associated(SLODWORD(a1)) )
      {
        if ( rf_weapon_is_continuous_fire(*(int *)v78, a3) )
        {
          v68 *= 2;
        }
        else if ( *(_DWORD *)v78 == rf_weapon_id_shoulder_cannon || *(_DWORD *)v78 == unk_911CE0 )
        {
          v68 = 6000;
        }
        else if ( *(_DWORD *)v78 == rf_weapon_id_rocket_launcher )
        {
          v68 = 4000;
        }
        else if ( *(_DWORD *)v78 == rf_weapon_id_heap )
        {
          v68 = rand() % 2000 + 1500;
        }
        else if ( *(_DWORD *)v78 == unk_911CD4 )
        {
          if ( ((unsigned int)&unk_2000000 & *(_DWORD *)(*(_DWORD *)(LODWORD(a1) + 660) + 1828)) != 0 )
            v68 = rand() % 100 + 60;
          else
            v68 = rand() % 200 + 400;
        }
      }
      if ( !rf_entity_reload_in_progress(SLODWORD(a1))
        || rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        if ( rf_entity_runtime_flags810_has_mask2000(SLODWORD(a1))
          && !rf_weapon_has_underwater_flag(*(int *)v78)
          && rf_object_has_player_flag(SLODWORD(a1)) )
        {
          v15 = 0.0;
          v14 = 1.0;
          v13 = rf_foley_choose_random_sound(*((_DWORD *)v72 + 92));
          rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
          rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
          rf_replicator_arm_milliseconds(v79 + 134, v68);
        }
        else if ( sub_403D00((int)v79, *(unsigned int *)v78) )
        {
          v70 = 0;
          v69 = 1;
          if ( !sub_5119F0(*(int *)v78)
            && *(_DWORD *)v78 != rf_weapon_id_shoulder_cannon
            && *(_DWORD *)v78 != rf_weapon_id_rocket_launcher
            && *(_DWORD *)v78 != rf_weapon_id_heap
            && !rf_multiplayer_runtime_mode
            && !rf_splitscreen_runtime_active )
          {
            v69 = rf_object_is_player_associated(SLODWORD(a1)) != 0;
          }
          if ( (*((_DWORD *)v72 + 153) & 0x20) != 0 )
          {
            v69 = 0;
            if ( rf_weapon_is_riot_stick(*(int *)v78) )
              v69 = a3 == 1;
          }
          else if ( rf_entity_matches_local_player_or_related_handle(SLODWORD(a1)) )
          {
            v69 = 1;
          }
          if ( rf_weapon_has_detonator_flag(*(int *)v78) )
            v69 = 0;
          if ( v81 )
            v69 = 0;
          if ( v69 && sub_436310(SLODWORD(a1)) <= 0 )
            v70 = 1;
          if ( sub_438AC0(SLODWORD(a1))
            && *(_DWORD *)v78 == rf_weapon_id_shotgun
            && *(_DWORD *)(LODWORD(a1) + 4 * *(_DWORD *)(LODWORD(a1) + 676) + 812) == 1 )
          {
            a3 = 1;
          }
          if ( rf_object_is_player_associated(SLODWORD(a1)) && *(_DWORD *)v78 == rf_weapon_id_shotgun && !a3 )
            *(_DWORD *)(LODWORD(a1) + 2068) |= 0x1000u;
          else
            *(_DWORD *)(LODWORD(a1) + 2068) &= ~0x1000u;
          if ( v70 == 1 )
          {
            if ( rf_object_is_player_associated(SLODWORD(a1)) == 1 )
            {
              rf_replicator_arm_milliseconds(v79 + 134, v68);
              if ( rf_weapon_is_riot_stick(*(int *)v78) )
              {
                rf_gamesound_play_event(2, 0, 0.0, 1.0);
              }
              else
              {
                v15 = 0.0;
                v14 = 1.0;
                v13 = rf_foley_choose_random_sound(*((_DWORD *)v72 + 92));
                rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
                rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
              }
            }
            rf_entity_stop_weapon_firing(*(_DWORD *)(LODWORD(a1) + 44), *(unsigned int *)v78);
            if ( !rf_object_has_player_flag(SLODWORD(a1)) )
            {
              if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode )
                sub_4014F0((int *)(LODWORD(a1) + 672), 1);
              else
                rf_ai_switch_to_default_primary_after_launcher_exhaustion((int *)(LODWORD(a1) + 672));
            }
          }
          else if ( !rf_weapon_has_flame_flag(*(int *)v78) || a3 )
          {
            if ( v69
              && rf_weapon_has_positive_clip_size(*(int *)v78)
              && (!rf_weapon_is_riot_stick(*(int *)v78) || a3)
              && *(int *)(LODWORD(a1) + 4 * *(_DWORD *)(LODWORD(a1) + 676) + 812) <= 0 )
            {
              if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(LODWORD(a1) + 44), *(unsigned int *)v78) )
                rf_entity_stop_weapon_firing(*(_DWORD *)(LODWORD(a1) + 44), *(unsigned int *)v78);
            }
            else if ( rf_multiplayer_runtime_mode != 1
                   || !sub_438AC0(SLODWORD(a1))
                   || (v15 = a1, rf_constant_one_4A8380())
                   || rf_weapon_selected_mode_has_high_parameter_flag(*(int *)v78, a3) )
            {
              if ( a2 || !rf_weapon_selected_mode_has_high_parameter_flag(*(int *)v78, a3) )
              {
                if ( (*((_DWORD *)v72 + 153) & 0x20) != 0 )
                {
                  if ( rf_weapon_selected_mode_is_continuous_exact_selector(*(_DWORD *)(LODWORD(a1) + 676), a3) )
                  {
                    rf_entity_begin_weapon_firing_state_and_effects(
                      *(_DWORD *)(LODWORD(a1) + 44),
                      *(_DWORD *)(LODWORD(a1) + 676),
                      a3);
                    if ( rf_entity_class_flag1000(SLODWORD(a1))
                      && rf_entity_matches_local_player_or_related_handle(SLODWORD(a1)) )
                    {
                      local_player_entry_or_related_owner = rf_object_find_local_player_entry_or_related_owner(SLODWORD(a1));
                    }
                  }
                  else
                  {
                    rf_entity_request_forced_body_action_by_handle(*(_DWORD *)(LODWORD(a1) + 44), 2);
                    for ( i = 0; i < 2; ++i )
                    {
                      if ( a3 == 1 )
                        v52 = (int)(*(float *)&v72[4 * i + 344] * 1000.0 + 0.5);
                      else
                        v52 = (int)(*(float *)&v72[4 * i + 336] * 1000.0 + 0.5);
                      if ( v52 > 0 )
                        rf_replicator_arm_milliseconds((int *)(LODWORD(a1) + 4 * i + 1216), v52);
                    }
                    v51 = rf_foley_choose_random_sound(*((_DWORD *)v72 + 88));
                    if ( a3 == 1 && *((_DWORD *)v72 + 88) != -1 )
                      v51 = rf_foley_choose_random_sound(*((_DWORD *)v72 + 89));
                    v15 = 0.0;
                    v14 = 1.0;
                    v13 = v51;
                    rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
                    rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                    if ( rf_multiplayer_runtime_mode && (*(_DWORD *)(LODWORD(a1) + 2068) & 0x20000) != 0 )
                    {
                      v15 = 0.0;
                      v14 = 1.0;
                      v13 = 85;
                      rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
                      rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                    }
                    rf_replicator_arm_milliseconds((int *)(LODWORD(a1) + 1208), v68);
                    if ( sub_438AC0(SLODWORD(a1)) )
                      rf_fpgun_request_fire_action(*(_DWORD *)(LODWORD(a1) + 5168), a3);
                  }
                }
                else
                {
                  rf_entity_request_body_fire_action(SLODWORD(a1), a3);
                  v50 = (int)(*((float *)v72 + 84) * 1000.0 + 0.5);
                  if ( v50 <= 0 )
                  {
                    rf_vector3_default_construct_noop(v74);
                    rf_matrix3_construct((char *)v66);
                    runtime = nullptr;
                    first_dword = 1;
                    if ( (*(_DWORD *)(*(_DWORD *)(LODWORD(a1) + 660) + 1828) & 0x80) != 0 )
                      first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)(LODWORD(a1) + 660) + 444));
                    if ( !first_dword )
                      first_dword = 1;
                    v80 = rf_entity_select_weapon_float_with_context_gates(SLODWORD(a1), *(int *)v78, a2, a3);
                    v76 = nullptr;
                    v75 = rf_projectile_resolve_uid_type2(*(_DWORD *)(LODWORD(a1) + 1376));
                    if ( v75 && *(_DWORD *)(v75 + 664) == dword_911C78 )
                      v80 = 0.0;
                    v17 = rf_multiplayer_runtime_mode == 1
                       && rf_multiplayer_server_authority == 1
                       && (rf_weapon_records_flags2[340 * *(_DWORD *)v78] & 0x800) != 0;
                    v73 = v17;
                    if ( v17 )
                    {
                      rf_lag_compensation_snapshot_count_reset();
                      for ( j = 0; j < *(_DWORD *)(*(_DWORD *)(LODWORD(a1) + 632) + 2300); ++j )
                      {
                        v46 = rf_player_find_by_network_id(*(_BYTE *)(*(_DWORD *)(LODWORD(a1) + 632) + j + 2200));
                        if ( v46 )
                        {
                          v47 = rf_entity_resolve_handle(v46[5]);
                          if ( v47 )
                            rf_lag_compensation_add_entity_sample(
                              v47,
                              *(_WORD *)(*(_DWORD *)(LODWORD(a1) + 632) + 2 * j + 2232));
                        }
                      }
                    }
                    for ( k = 0; k < first_dword; ++k )
                    {
                      ++*(_DWORD *)(LODWORD(a1) + 1296);
                      if ( *(_DWORD *)(LODWORD(a1) + 1296) >= rf_receiver_get_first_dword((void *)(*(_DWORD *)(LODWORD(a1) + 660)
                                                                                                 + 444)) )
                        *(_DWORD *)(LODWORD(a1) + 1296) = 0;
                      if ( v81 )
                      {
                        rf_vector_copy(v74, v20, a5);
                        rf_matrix3_copy(v66, a6);
                      }
                      else
                      {
                        is_continuous_exact_selector = 0;
                        if ( rf_multiplayer_runtime_mode == 1
                          && rf_multiplayer_server_authority == 1
                          && LODWORD(a1) != dword_681E38
                          && !a5 )
                        {
                          is_continuous_exact_selector = rf_weapon_selected_mode_is_continuous_exact_selector(
                                                           *(int *)v78,
                                                           a3);
                        }
                        rf_vector3_default_construct_noop(source);
                        rf_vector3_default_construct_noop(v42);
                        rf_matrix3_construct((char *)v43);
                        rf_matrix3_construct((char *)v39);
                        if ( rf_multiplayer_runtime_mode == 1 && is_continuous_exact_selector )
                        {
                          rf_vector_copy(source, v24, (const float *)(LODWORD(a1) + 60));
                          rf_vector_copy(v42, v23, (const float *)(LODWORD(a1) + 2004));
                          rf_matrix3_copy(v43, (const float *)(LODWORD(a1) + 72));
                          rf_matrix3_copy(v39, (const float *)(LODWORD(a1) + 2016));
                          rf_entity_publish_latest_buffered_pose(SLODWORD(a1));
                        }
                        rf_entity_resolve_firing_transform(
                          (float *)LODWORD(a1),
                          *(int *)v78,
                          v74,
                          v66,
                          *(_DWORD *)(LODWORD(a1) + 1296),
                          1);
                        if ( rf_multiplayer_runtime_mode == 1 && is_continuous_exact_selector )
                        {
                          rf_vector_copy((float *)(LODWORD(a1) + 60), v22, source);
                          rf_vector_copy((float *)(LODWORD(a1) + 2004), v21, v42);
                          rf_matrix3_copy((float *)(LODWORD(a1) + 72), v43);
                          rf_matrix3_copy((float *)(LODWORD(a1) + 2016), v39);
                        }
                      }
                      if ( rf_entity_class_has_contact_geomod_flag400(SLODWORD(a1)) )
                      {
                        v38 = rf_receiver_get_first_dword((void *)LODWORD(a1));
                        if ( !rf_liquid_room_contains_point(v38, (int)v74) )
                        {
                          rf_replicator_arm_milliseconds(v79 + 134, v68);
                          v15 = 0.0;
                          v14 = 1.0;
                          v13 = rf_foley_choose_random_sound(*((_DWORD *)v72 + 92));
                          rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
                          rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                          return;
                        }
                      }
                      v45 = *((_DWORD *)v72 + 31);
                      if ( (*(_DWORD *)(LODWORD(a1) + 2068) & 0x1000) != 0 )
                        v45 *= 2;
                      for ( m = 0; m < v45; ++m )
                      {
                        rf_matrix3_copy_construct((int)v36, v66);
                        if ( v80 > 0.0 )
                        {
                          rf_vector3_default_construct_noop(v35);
                          rf_vector_normalize_reciprocal_sqrt(v37);
                          v16 = v80 * 3.141592741012573 / 180.0;
                          v15 = rf_cos_float(v16);
                          rf_vector3_copy_return_destination((float *)&v12, v37);
                          rf_random_unit_vector_in_cone(v35, *(float *)&v12, *(float *)&v13, v14, v15);
                          rf_orientation_matrix_from_normalized_direction(v36, v35);
                        }
                        runtime = (_DWORD *)rf_projectile_create_runtime(
                                              *(int *)v78,
                                              *(_DWORD *)(LODWORD(a1) + 44),
                                              (int)v74,
                                              (int)v36,
                                              a3,
                                              0);
                        v76 = runtime;
                        if ( !runtime )
                          break;
                        if ( rf_multiplayer_runtime_mode == 1
                          && !rf_multiplayer_server_authority
                          && byte_663A38
                          && LODWORD(a1) != dword_681E38
                          && (*(_DWORD *)(runtime[165] + 616) & 0x800) != 0
                          && runtime[166] != unk_911CE0 )
                        {
                          rf_object_mark_for_deferred_delete((int)runtime);
                        }
                        if ( v73 )
                        {
                          runtime[170] |= 0x80u;
                          v34 = (int *)rf_projectile_create_runtime(
                                         *(int *)v78,
                                         *(_DWORD *)(LODWORD(a1) + 44),
                                         (int)v74,
                                         (int)v36,
                                         a3,
                                         0);
                          if ( v34 )
                          {
                            rf_lag_compensation_trace_with_temporary_poses(SLODWORD(a1), v34);
                            v34[31] |= 2u;
                          }
                        }
                        if ( runtime[166] == rf_weapon_index_grenade && (a3 == 1 || !*(_DWORD *)(LODWORD(a1) + 5168)) )
                          runtime[170] |= 0x10u;
                      }
                      if ( runtime )
                      {
                        if ( rf_replicator_has_elapsed((int *)(LODWORD(a1) + 4972)) )
                          rf_replicator_arm_milliseconds((int *)(LODWORD(a1) + 4972), 50);
                        if ( rf_multiplayer_runtime_mode == 1
                          && !rf_weapon_selected_mode_is_continuous_exact_selector(*(int *)v78, a3)
                          && !rf_weapon_selected_mode_has_high_parameter_flag(*(int *)v78, a3) )
                        {
                          rf_multiplayer_publish_weapon_fire(SLODWORD(a1), v74, v66, *(int *)v78, a3);
                        }
                        rf_weapon_decrement_clip_or_reserve_ammo(SLODWORD(a1), *(unsigned int *)v78);
                        if ( (*(_DWORD *)(LODWORD(a1) + 2068) & 0x1000) != 0 )
                          rf_weapon_decrement_clip_or_reserve_ammo(SLODWORD(a1), *(unsigned int *)v78);
                        if ( rf_rf_string_not_equals_cstring_case_insensitive(runtime[165] + 1208, (char *)&byte_631ADA) )
                        {
                          if ( *(float *)(runtime[165] + 1220) <= 0.0 || a3 )
                            rf_weapon_present_shell_ejection((_DWORD *)LODWORD(a1));
                          else
                            rf_replicator_arm_milliseconds(
                              (int *)(LODWORD(a1) + 4980),
                              (int)(*(float *)(runtime[165] + 1220) * 1000.0));
                        }
                      }
                    }
                    if ( v76 )
                    {
                      v33 = rf_foley_choose_random_sound(*(_DWORD *)(runtime[165] + 352));
                      if ( rf_entity_runtime_flags810_has_mask2000(SLODWORD(a1)) )
                      {
                        v33 = rf_foley_choose_random_sound(*(_DWORD *)(runtime[165] + 364));
                        rf_vector3_default_construct_noop(muzzle_position);
                        if ( sub_438AC0(SLODWORD(a1)) )
                        {
                          player = sub_4DD720(runtime[12]);
                          if ( rf_player_compose_fpgun_muzzle_world_transform(player, muzzle_position, nullptr) )
                          {
                            v7 = rf_receiver_get_first_dword(runtime);
                            rf_emit_thirty_white_particles((int)muzzle_position, v7);
                          }
                        }
                        else
                        {
                          v8 = rf_receiver_get_first_dword(runtime);
                          rf_emit_thirty_white_particles((int)v74, v8);
                        }
                        runtime[190] |= 1u;
                        runtime[190] |= 2u;
                      }
                      else if ( a3 == 1 )
                      {
                        v33 = rf_foley_choose_random_sound(*(_DWORD *)(runtime[165] + 356));
                      }
                      else if ( rf_entity_custom_mask142C_has_index(SLODWORD(a1), runtime[166])
                             && *((_DWORD *)v72 + 90) != -1 )
                      {
                        v33 = rf_foley_choose_random_sound(*((_DWORD *)v72 + 90));
                      }
                      if ( *(_DWORD *)(*(_DWORD *)(LODWORD(a1) + 660) + 1872) != -1 )
                        v33 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(LODWORD(a1) + 660) + 1872));
                      if ( !rf_weapon_selected_mode_is_continuous_exact_selector(runtime[166], a3) || a2 )
                      {
                        if ( a2 != 1 || *((_DWORD *)v72 + 275) == -1 )
                        {
                          v15 = 0.0;
                          v14 = 1.0;
                          v13 = v33;
                          rf_vector3_copy_return_destination(&v10, v74);
                          rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                          if ( rf_multiplayer_runtime_mode && (*(_DWORD *)(LODWORD(a1) + 2068) & 0x20000) != 0 )
                          {
                            v15 = 0.0;
                            v14 = 1.0;
                            v13 = 85;
                            rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
                            rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                          }
                        }
                        else if ( v79[152] == *((_DWORD *)v72 + 273) )
                        {
                          v33 = *(_DWORD *)(runtime[165] + 1100);
                          v15 = 0.0;
                          v14 = 1.0;
                          v13 = v33;
                          rf_vector3_copy_return_destination(&v10, v74);
                          rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                          if ( rf_multiplayer_runtime_mode )
                          {
                            if ( (*(_DWORD *)(LODWORD(a1) + 2068) & 0x20000) != 0 )
                            {
                              v15 = 0.0;
                              v14 = 1.0;
                              v13 = 85;
                              rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
                              rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                            }
                          }
                        }
                      }
                      else
                      {
                        rf_entity_begin_weapon_firing_state_and_effects(*(_DWORD *)(LODWORD(a1) + 44), runtime[166], a3);
                      }
                      if ( !rf_weapon_is_silent(runtime[166])
                        && !rf_entity_custom_mask142C_has_index(SLODWORD(a1), *(_DWORD *)(LODWORD(a1) + 676)) )
                      {
                        LODWORD(v15) = runtime[166] == unk_911CE0;
                        rf_ai_propagate_stimulus_to_nearby_entities(*(_DWORD *)(LODWORD(a1) + 44), v74, 40.0, 1);
                      }
                      if ( !a2 )
                      {
                        if ( rf_object_is_player_associated(SLODWORD(a1)) == 1
                          || rf_weapon_selected_mode_is_continuous_exact_selector(runtime[166], a3)
                          || (*(_DWORD *)(runtime[165] + 612) & 0x20) != 0 )
                        {
                          rf_replicator_arm_milliseconds(v79 + 134, v68);
                        }
                        else
                        {
                          rf_timestamp_arm_random_inclusive_milliseconds(v79 + 134, v68, v68 + 200);
                        }
                      }
                      *(float *)(LODWORD(a1) + 1976) = *(float *)&dword_6FC428;
                      if ( a4 )
                        *a4 = runtime;
                      rf_replicator_arm_milliseconds((int *)(LODWORD(a1) + 5116), 0);
                    }
                    if ( sub_438AC0(SLODWORD(a1)) || rf_entity_jeep_second_relation_resolves_object(SLODWORD(a1)) )
                    {
                      v30 = *(_DWORD **)(LODWORD(a1) + 5168);
                      if ( rf_entity_jeep_second_relation_resolves_object(SLODWORD(a1)) )
                      {
                        v9 = sub_552200((_DWORD *)(LODWORD(a1) + 2252), 1);
                        v30 = sub_4DD720(*(_DWORD *)(*(_DWORD *)v9 + 4));
                      }
                      rf_fpgun_request_fire_action((int)v30, a3);
                    }
                    if ( sub_438AC0(SLODWORD(a1)) )
                      rf_player_autoswitch_exhausted_weapon(*(_DWORD *)(LODWORD(a1) + 5168), 0);
                    if ( rf_entity_matches_local_player_or_related_handle(SLODWORD(a1)) == 1 )
                    {
                      v29 = rf_object_find_local_player_entry_or_related_owner(SLODWORD(a1));
                      if ( v29 )
                      {
                        if ( (*((_DWORD *)v72 + 153) & 0x20000000) != 0 )
                        {
                          v15 = *(float *)&v72;
                          v15 = *((float *)v72 + 313);
                          v14 = *(float *)&v72;
                          rf_entity_set_player_linked_perturbation_timer(
                            *(_DWORD *)(v29 + 196),
                            *((float *)v72 + 312),
                            v15);
                        }
                        if ( runtime )
                          copy_result[5] = *(float *)(LODWORD(a1) + 676);
                      }
                    }
                    rf_entity_refresh_idle_animation_deadline(SLODWORD(a1));
                  }
                  else
                  {
                    rf_replicator_arm_milliseconds((int *)(LODWORD(a1) + 1208), v68);
                    rf_replicator_arm_milliseconds((int *)(LODWORD(a1) + 1216), v50);
                    v49 = rf_foley_choose_random_sound(*((_DWORD *)v72 + 88));
                    if ( *(_DWORD *)(*(_DWORD *)(LODWORD(a1) + 660) + 1872) != -1 )
                      v49 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(LODWORD(a1) + 660) + 1872));
                    v15 = 0.0;
                    v14 = 1.0;
                    v13 = v49;
                    rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
                    rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                    if ( rf_multiplayer_runtime_mode && (*(_DWORD *)(LODWORD(a1) + 2068) & 0x20000) != 0 )
                    {
                      v15 = 0.0;
                      v14 = 1.0;
                      v13 = 85;
                      rf_vector3_copy_return_destination(&v10, (float *)(LODWORD(a1) + 60));
                      rf_sound_event_play_for_object_view(SLODWORD(a1), v10, v11, v12, v13, v14, v15);
                    }
                    rf_weapon_decrement_clip_or_reserve_ammo(SLODWORD(a1), *(unsigned int *)v78);
                  }
                }
              }
              else
              {
                rf_replicator_arm_milliseconds((int *)(LODWORD(a1) + 1276), 0);
                *(_DWORD *)(LODWORD(a1) + 1280) = *((_DWORD *)v72 + 273);
                rf_replicator_arm_milliseconds(v79 + 134, v68);
                if ( rf_multiplayer_runtime_mode == 1 )
                {
                  rf_vector3_default_construct_noop(v56);
                  rf_matrix3_construct((char *)v55);
                  rf_entity_resolve_firing_transform(
                    (float *)LODWORD(a1),
                    *(int *)v78,
                    v56,
                    v55,
                    *(_DWORD *)(LODWORD(a1) + 1296),
                    1);
                  if ( sub_438AC0(SLODWORD(a1)) )
                    rf_multiplayer_publish_weapon_fire(SLODWORD(a1), v56, v55, *(int *)v78, a3);
                }
              }
            }
          }
          else
          {
            rf_vector3_default_construct_noop(lhs);
            rf_matrix3_construct(v64);
            if ( !sub_438AC0(SLODWORD(a1)) )
              goto LABEL_92;
            v61 = *(_DWORD *)(LODWORD(a1) + 5168);
            v62 = *(_DWORD *)(v61 + 64);
            if ( v62 == -1 )
              goto LABEL_92;
            if ( !*(_DWORD *)(v61 + 52) )
              goto LABEL_92;
            rf_vmesh_compose_prop_world_transform(
              *(_DWORD *)(v61 + 52),
              v62,
              (float *)(v61 + 4084),
              v61 + 4120,
              (int)v64,
              lhs);
            rf_solid_collision_query_construct_clear_face_hint(v57);
            rf_solid_collision_result_construct_noop((int)v60);
            rf_vector_copy(destination, copy_result, (const float *)(LODWORD(a1) + 2004));
            rf_vector_copy(v59, v27, lhs);
            v6 = rf_vector_subtract(lhs, out_vector, (const float *)(LODWORD(a1) + 2004));
            rf_vector_copy(v59, v25, v6);
            v59[3] = 0.0;
            LODWORD(v59[4]) = 5;
            rf_world_collision_sweep((char *)rf_world_solid, (int)v57, (int)v60, 1);
            if ( v60[0] <= 0 )
            {
LABEL_92:
              sub_438AC0(SLODWORD(a1));
              rf_entity_begin_weapon_firing_state_and_effects(*(_DWORD *)(LODWORD(a1) + 44), *(unsigned int *)v78, 0);
            }
          }
        }
      }
      else if ( !rf_object_has_player_flag(SLODWORD(a1)) )
      {
        rf_replicator_arm_milliseconds(v79 + 134, v68);
      }
    }
  }
}

