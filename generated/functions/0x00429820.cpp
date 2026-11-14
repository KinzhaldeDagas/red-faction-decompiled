// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00429820 rf_entity_handle_death_admission
// UNREALRED VERIFIED [local-multiplayer-score-20261028] Death admission is guarded by Entity+0x810 mask0x1, set before later death work. Victim player resolves from the dead entity handle; attacker player resolves from Entity+0x270 network ID. In multiplayer, victim==attacker calls0x4E26A0(attacker,-1) at0x42A760. A distinct resolved attacker adds+1 at0x42AC36 except same-team kills in modes1/2. A resolved victim with no resolved attacker only enqueues the mysterious-death message: no frag penalty. Server-owned death events are broadcast; clients also reproduce presentation/arithmetic through this guarded routine.
// UNREALRED VERIFIED [lan-killfeed-20261028] The guarded multiplayer death admission formats one notification for this local viewer after victim lookup by current entity handle and attacker lookup by Entity+0x270 network ID. Resolved self kill: local "You killed yourself!" style4; remote name+gendered own-hand text style5. Distinct killer: local victim gets "You were killed by "+killer style4, or "You just got beat down by "+killer+"!" when killer current entity+0x2A4 equals valid riot-stick id. Local killer gets "You killed "+victim style4 before the observer riot branch. Observer ordinary victim+" was killed by "+killer uses style5; observer riot victim+" got beat down by "+killer+"!" uses style4. Resolved victim/unresolved killer always victim+" was killed mysteriously" style5, including local victim; unresolved victim emits none. Complete text is the message argument with empty player-prefix. English source literals remain in executable; runtime localized-pointer initialization is outside this slice.
// UNREALRED VERIFIED [combat-burn-owner-erratum-20261104]: Native lethal-admission path clears Entity+0x1430 at42ADC3. This ends the retained local player-record association independently of the common player flag; do not retain it for the dead body merely because the Unreal PlayerController/PlayerState survives.
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Death admission calls437820 at42AD45 to stop the shared entity speech voice. Thus no speculative voice transfer into a corpse is needed for this path.437820 leaves speech duration/action deadline/action-handle fields unchanged; native death action ownership is separately retained.
int __cdecl rf_entity_handle_death_admission(int a1)
{
  int result; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  int v9; // eax
  float *v10; // eax
  char *v11; // eax
  int v12; // [esp+4h] [ebp-3C4h]
  int v13; // [esp+8h] [ebp-3C0h]
  float *v14; // [esp+Ch] [ebp-3BCh] BYREF
  float *v15; // [esp+10h] [ebp-3B8h]
  int v16; // [esp+14h] [ebp-3B4h]
  _DWORD *v17; // [esp+18h] [ebp-3B0h] BYREF
  int scalar; // [esp+1Ch] [ebp-3ACh]
  void *v19; // [esp+28h] [ebp-3A0h]
  _DWORD *v20; // [esp+2Ch] [ebp-39Ch]
  _DWORD *v21; // [esp+30h] [ebp-398h]
  const char *v22; // [esp+34h] [ebp-394h]
  void *v23; // [esp+38h] [ebp-390h]
  int *v24; // [esp+3Ch] [ebp-38Ch]
  int *v25; // [esp+40h] [ebp-388h]
  _DWORD *v26; // [esp+44h] [ebp-384h]
  _DWORD *v27; // [esp+48h] [ebp-380h]
  const char *v28; // [esp+4Ch] [ebp-37Ch]
  void *v29; // [esp+50h] [ebp-378h]
  _DWORD *v30; // [esp+54h] [ebp-374h]
  _DWORD *v31; // [esp+58h] [ebp-370h]
  int *v32; // [esp+5Ch] [ebp-36Ch]
  int *v33; // [esp+60h] [ebp-368h]
  _DWORD *v34; // [esp+64h] [ebp-364h]
  _DWORD *v35; // [esp+68h] [ebp-360h]
  const char *v36; // [esp+6Ch] [ebp-35Ch]
  void *v37; // [esp+70h] [ebp-358h]
  _DWORD *v38; // [esp+74h] [ebp-354h]
  _DWORD *v39; // [esp+78h] [ebp-350h]
  const char *v40; // [esp+7Ch] [ebp-34Ch]
  void *v41; // [esp+80h] [ebp-348h]
  _DWORD *v42; // [esp+84h] [ebp-344h]
  _DWORD *v43; // [esp+88h] [ebp-340h]
  const char *v44; // [esp+8Ch] [ebp-33Ch]
  void *v45; // [esp+90h] [ebp-338h]
  _DWORD *v46; // [esp+94h] [ebp-334h]
  _DWORD *v47; // [esp+98h] [ebp-330h]
  _DWORD *v48; // [esp+9Ch] [ebp-32Ch]
  _DWORD *v49; // [esp+A0h] [ebp-328h]
  const char *v50; // [esp+A4h] [ebp-324h]
  void *v51; // [esp+A8h] [ebp-320h]
  _DWORD *v52; // [esp+ACh] [ebp-31Ch]
  _DWORD *v53; // [esp+B0h] [ebp-318h]
  const char *v54; // [esp+B4h] [ebp-314h]
  void *v55; // [esp+B8h] [ebp-310h]
  _DWORD *v56; // [esp+BCh] [ebp-30Ch]
  _DWORD *v57; // [esp+C0h] [ebp-308h]
  const char *v58; // [esp+C4h] [ebp-304h]
  _DWORD *v59; // [esp+C8h] [ebp-300h]
  _DWORD *v60; // [esp+CCh] [ebp-2FCh]
  _DWORD *v61; // [esp+D0h] [ebp-2F8h]
  char *Source; // [esp+D4h] [ebp-2F4h]
  float v63; // [esp+D8h] [ebp-2F0h]
  float v64; // [esp+DCh] [ebp-2ECh]
  float **v65; // [esp+E0h] [ebp-2E8h]
  void *v66; // [esp+E4h] [ebp-2E4h]
  _BYTE v67[8]; // [esp+E8h] [ebp-2E0h] BYREF
  float **v68; // [esp+F0h] [ebp-2D8h]
  void *v69; // [esp+F4h] [ebp-2D4h]
  _BYTE v70[8]; // [esp+F8h] [ebp-2D0h] BYREF
  _BYTE v71[8]; // [esp+100h] [ebp-2C8h] BYREF
  float **v72; // [esp+108h] [ebp-2C0h]
  void *v73; // [esp+10Ch] [ebp-2BCh]
  float **v74; // [esp+110h] [ebp-2B8h]
  void *v75; // [esp+114h] [ebp-2B4h]
  float **v76; // [esp+118h] [ebp-2B0h]
  void *v77; // [esp+11Ch] [ebp-2ACh]
  _BYTE v78[8]; // [esp+120h] [ebp-2A8h] BYREF
  float **v79; // [esp+128h] [ebp-2A0h]
  void *v80; // [esp+12Ch] [ebp-29Ch]
  float **v81; // [esp+130h] [ebp-298h]
  void *v82; // [esp+134h] [ebp-294h]
  float **v83; // [esp+138h] [ebp-290h]
  void *v84; // [esp+13Ch] [ebp-28Ch]
  float **v85; // [esp+140h] [ebp-288h]
  void *v86; // [esp+144h] [ebp-284h]
  float v87[3]; // [esp+148h] [ebp-280h] BYREF
  float v88[3]; // [esp+154h] [ebp-274h] BYREF
  float v89[3]; // [esp+160h] [ebp-268h] BYREF
  float v90[3]; // [esp+16Ch] [ebp-25Ch] BYREF
  float scaled_result[3]; // [esp+178h] [ebp-250h] BYREF
  float v92[3]; // [esp+184h] [ebp-244h] BYREF
  float v93[3]; // [esp+190h] [ebp-238h] BYREF
  float v94[3]; // [esp+19Ch] [ebp-22Ch] BYREF
  _BYTE v95[36]; // [esp+1A8h] [ebp-220h] BYREF
  float v96[3]; // [esp+1CCh] [ebp-1FCh] BYREF
  char v97[12]; // [esp+1D8h] [ebp-1F0h] BYREF
  float v98[3]; // [esp+1E4h] [ebp-1E4h] BYREF
  char v99[12]; // [esp+1F0h] [ebp-1D8h] BYREF
  float v100[3]; // [esp+1FCh] [ebp-1CCh] BYREF
  char v101[12]; // [esp+208h] [ebp-1C0h] BYREF
  float v102[3]; // [esp+214h] [ebp-1B4h] BYREF
  char v103[12]; // [esp+220h] [ebp-1A8h] BYREF
  float v104[3]; // [esp+22Ch] [ebp-19Ch] BYREF
  char v105[12]; // [esp+238h] [ebp-190h] BYREF
  float v106[3]; // [esp+244h] [ebp-184h] BYREF
  float v107[3]; // [esp+250h] [ebp-178h] BYREF
  float out_vector[3]; // [esp+25Ch] [ebp-16Ch] BYREF
  float v109[3]; // [esp+268h] [ebp-160h] BYREF
  float copy_result[3]; // [esp+274h] [ebp-154h] BYREF
  char v111; // [esp+283h] [ebp-145h]
  int v112; // [esp+284h] [ebp-144h]
  int v113; // [esp+288h] [ebp-140h]
  const void **v114; // [esp+28Ch] [ebp-13Ch]
  const void **v115; // [esp+290h] [ebp-138h]
  _DWORD *v116; // [esp+294h] [ebp-134h]
  _DWORD *v117; // [esp+298h] [ebp-130h]
  int v118; // [esp+29Ch] [ebp-12Ch]
  int j; // [esp+2A0h] [ebp-128h]
  _DWORD *v121; // [esp+2A8h] [ebp-120h]
  int i; // [esp+2ACh] [ebp-11Ch]
  char v123; // [esp+2B3h] [ebp-115h]
  char v124[4]; // [esp+2B4h] [ebp-114h] BYREF
  char v125[12]; // [esp+2B8h] [ebp-110h] BYREF
  char v126[36]; // [esp+2C4h] [ebp-104h] BYREF
  float v127[3]; // [esp+2E8h] [ebp-E0h] BYREF
  float v128[13]; // [esp+2F4h] [ebp-D4h] BYREF
  int v129; // [esp+328h] [ebp-A0h]
  _DWORD v130[2]; // [esp+32Ch] [ebp-9Ch] BYREF
  float source[3]; // [esp+334h] [ebp-94h] BYREF
  float vector[5]; // [esp+340h] [ebp-88h] BYREF
  float destination; // [esp+354h] [ebp-74h] BYREF
  float v134; // [esp+358h] [ebp-70h]
  float v135; // [esp+35Ch] [ebp-6Ch]
  float rhs[3]; // [esp+360h] [ebp-68h] BYREF
  float lhs[3]; // [esp+36Ch] [ebp-5Ch] BYREF
  float v138[3]; // [esp+378h] [ebp-50h] BYREF
  float v139[3]; // [esp+384h] [ebp-44h] BYREF
  float v140[3]; // [esp+390h] [ebp-38h] BYREF
  int v141; // [esp+39Ch] [ebp-2Ch]
  char v142; // [esp+3A3h] [ebp-25h]
  int runtime_pointer; // [esp+3A4h] [ebp-24h]
  int v144; // [esp+3A8h] [ebp-20h]
  _DWORD *v145; // [esp+3ACh] [ebp-1Ch]
  char v146; // [esp+3B1h] [ebp-17h]
  bool v147; // [esp+3B2h] [ebp-16h]
  char v148; // [esp+3B3h] [ebp-15h]
  int v149; // [esp+3B4h] [ebp-14h]
  int v150; // [esp+3B8h] [ebp-10h]
  int v151; // [esp+3C4h] [ebp-4h]

  v147 = 1;
  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    result = *(_DWORD *)(a1 + 124) & 0x40;
    v147 = result != 0;
  }
  if ( v147 )
  {
    result = *(_DWORD *)(a1 + 2064) & 1;
    if ( !result )
    {
      rf_vector3_zero_return_destination((float *)(a1 + 1812));
      if ( !rf_entity_uses_fall_or_airborne_vehicle_motion(a1) )
        rf_vector3_zero_return_destination((float *)(a1 + 324));
      rf_vector3_zero_return_destination((float *)(a1 + 336));
      *(_DWORD *)(a1 + 2064) |= 1u;
      *(_DWORD *)(a1 + 424) &= ~0x8000u;
      rf_collision_remove_pairs_for_object(a1);
      if ( a1 == dword_681E38 && rf_local_fpgun_player && rf_player_get_alt_zoom_in_flag_byte(rf_local_fpgun_player) )
        rf_player_reset_alt_zoom_state(rf_local_fpgun_player);
      if ( a1 == dword_681E38 && rf_local_fpgun_player )
        *(_BYTE *)(rf_local_fpgun_player + 4016) = 0;
      if ( rf_multiplayer_runtime_mode )
      {
        v145 = sub_4DD720(*(_DWORD *)(a1 + 44));
        if ( v145 && v145 == (_DWORD *)rf_local_fpgun_player )
          rf_replicator_arm_milliseconds(&unk_6E6AF8, 750);
      }
      else
      {
        rf_replicator_arm_milliseconds(&unk_6E6B08, 1500);
        rf_replicator_arm_milliseconds(&unk_6E6AF8, 750);
      }
      v146 = 0;
      if ( !rf_splitscreen_runtime_active && !rf_multiplayer_runtime_mode && rf_object_has_player_flag(a1) )
      {
        v146 = 1;
        *(_DWORD *)(a1 + 2084) = -1;
      }
      if ( (*(_DWORD *)(a1 + 2064) & 0x80) == 0 && !v146 )
      {
        v144 = -1;
        if ( *(_DWORD *)(a1 + 2108) == -1 )
          v144 = rf_entity_select_contextual_death_action(a1);
        else
          v144 = *(_DWORD *)(a1 + 2108);
        if ( rf_entity_admits_speech_body_actions(a1) )
        {
          rf_model_handle_reset_actions_adapter(*(_DWORD *)(a1 + 128));
          runtime_pointer = rf_model_handle_get_runtime_pointer(*(int **)(a1 + 128));
          if ( *(int *)(*(_DWORD *)(a1 + 660) + 5080) > -1 )
          {
            *(_BYTE *)(runtime_pointer + 48 * *(_DWORD *)(*(_DWORD *)(a1 + 660) + 5080) + 5052) = 0;
            *(float *)(a1 + 5220) = 0.0;
          }
          if ( *(int *)(*(_DWORD *)(a1 + 660) + 5084) > -1 )
          {
            *(_BYTE *)(runtime_pointer + 48 * *(_DWORD *)(*(_DWORD *)(a1 + 660) + 5084) + 5052) = 0;
            *(float *)(a1 + 5220) = 0.0;
          }
          if ( *(int *)(*(_DWORD *)(a1 + 660) + 5088) > -1 )
          {
            *(_BYTE *)(runtime_pointer + 48 * *(_DWORD *)(*(_DWORD *)(a1 + 660) + 5088) + 5052) = 0;
            *(float *)(a1 + 5224) = 0.0;
          }
        }
        if ( v144 == -1 )
        {
          *(_DWORD *)(a1 + 2084) = -1;
        }
        else if ( *(_DWORD *)(a1 + 16 * v144 + 2644) == -1 )
        {
          *(_DWORD *)(a1 + 2084) = -1;
        }
        else
        {
          if ( *(_DWORD *)(a1 + 128) )
          {
            v141 = rf_model_handle_get_runtime_pointer(*(int **)(a1 + 128));
            if ( v141 )
            {
              *(_BYTE *)(v141 + 48 * *(_DWORD *)(*(_DWORD *)(a1 + 668) + 5080) + 5052) = 0;
              *(_BYTE *)(v141 + 48 * *(_DWORD *)(*(_DWORD *)(a1 + 668) + 5084) + 5052) = 0;
            }
          }
          *(_DWORD *)(a1 + 2084) = v144;
          v142 = 1;
          if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x200000) != 0 )
          {
            *(_DWORD *)(a1 + 2064) |= (unsigned int)&unk_2000000;
            v142 = 0;
          }
          rf_entity_request_body_action(a1, v144, 1.0, v142, 1);
          if ( v142 == 1 )
            *(_DWORD *)(a1 + 2064) |= 8u;
        }
      }
      if ( rf_splitscreen_runtime_active && sub_438AC0(a1) )
        *(float *)(*(_DWORD *)(a1 + 5168) + 4596) = 0.0;
      v149 = 0;
      v150 = 0;
      if ( *(_DWORD *)(a1 + 2092) != -1 )
      {
        rf_matrix3_construct((char *)v138);
        rf_vector3_default_construct_noop(&destination);
        rf_vector3_default_construct_noop(rhs);
        rf_vector3_default_construct_noop(lhs);
        rf_vector_copy(&destination, copy_result, (const float *)(a1 + 60));
        rf_matrix3_copy(v138, (const float *)(a1 + 72));
        v64 = v134 + 0.5;
        rf_vector3_set_components_thiscall(rhs, destination, v64, v135);
        *(float *)&scalar = v135;
        v63 = v134 - *(float *)(a1 + 1988);
        rf_vector3_set_components_thiscall(lhs, destination, v63, v135);
        rf_solid_collision_query_construct_clear_face_hint(v124);
        rf_solid_collision_result_construct_noop((int)v130);
        rf_vector_copy(v127, v109, rhs);
        v2 = rf_vector_subtract(lhs, out_vector, rhs);
        rf_vector_copy(v128, v107, v2);
        v128[3] = 0.15000001;
        LODWORD(v128[4]) = 0x2000;
        rf_vector3_zero_return_destination((float *)v125);
        rf_identity_orientation_matrix((float *)v126);
        *(float *)&v130[1] = 3.4028235e38;
        rf_world_collision_sweep((char *)rf_world_solid, (int)v124, (int)v130, 1);
        v129 = 0;
        if ( v130[0] > 0 )
        {
          rf_vector_copy(&destination, v106, source);
          if ( rf_vector_dot(v138, vector) <= 0.0 )
          {
            v5 = rf_vector_cross(vector, (float *)v101, v140);
            rf_vector_copy(v139, v100, v5);
            rf_vector_normalize(v139);
            v6 = rf_vector_cross(v139, (float *)v99, vector);
            rf_vector_copy(v140, v98, v6);
          }
          else
          {
            v3 = rf_vector_cross(v140, (float *)v105, vector);
            rf_vector_copy(v139, v104, v3);
            rf_vector_normalize(v139);
            v4 = rf_vector_cross(vector, (float *)v103, v139);
            rf_vector_copy(v140, v102, v4);
          }
          v7 = rf_vector_cross(v139, (float *)v97, v140);
          rf_vector_copy(v138, v96, v7);
          v123 = 0;
          for ( i = 0; i < 64; ++i )
          {
            if ( *(_BYTE *)(i + a1 + 1068) )
            {
              v123 = 1;
              break;
            }
          }
          if ( v123 )
          {
            v15 = rf_vector3_set_components_return_destination(v94, 0.0, 0.0, 1.0);
            v14 = rf_vector3_set_components_return_destination(v93, 0.0, 1.0, 0.0);
            v8 = rf_vector3_set_components_return_destination(v92, 1.0, 0.0, 0.0);
            v9 = rf_matrix3_construct_from_three_rows((int)v95, v8, v14, v15);
            v129 = rf_item_instance_spawn(
                     *(_DWORD *)(a1 + 2092),
                     (char *)&byte_631A4F,
                     unk_6F915C[20 * *(_DWORD *)(a1 + 2092)],
                     *(_DWORD *)(a1 + 44),
                     (int)&destination,
                     v9,
                     -1,
                     1,
                     0);
          }
        }
        if ( v129 )
        {
          *(_DWORD *)(v129 + 700) |= 8u;
          if ( v130[0] > 0
            && rf_rf_string_not_equals_cstring_case_insensitive(*(_DWORD *)(v129 + 660), "medical kit")
            && rf_rf_string_not_equals_cstring_case_insensitive(*(_DWORD *)(v129 + 660), "riot_stick_battery") )
          {
            rf_model_handle_bounds_aabb_adapter(*(_DWORD *)(v129 + 128), (int)rhs, (int)lhs);
            v10 = rf_vector_multiply_scalar(vector, scaled_result, lhs[0]);
            rf_vector_accumulate((float *)(v129 + 228), v10);
            rf_vector_copy((float *)(v129 + 60), v90, (const float *)(v129 + 228));
          }
          if ( rf_string_equals_case_insensitive(*(_DWORD *)(v129 + 660), "medical kit")
            || rf_string_equals_case_insensitive(*(_DWORD *)(v129 + 660), "riot_stick_battery") )
          {
            *(float *)(v129 + 232) = *(float *)(v129 + 232) + 0.05000000074505806;
            rf_vector_copy((float *)(v129 + 60), v89, (const float *)(v129 + 228));
          }
        }
        v149 = v129;
      }
      if ( *(_DWORD *)(a1 + 5228) != -1 )
      {
        v121 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 5228));
        if ( v121 )
        {
          if ( !sub_438B00((int)v121) )
          {
            rf_vector_copy((float *)v121 + 57, v88, (const float *)(a1 + 60));
            rf_matrix3_copy((float *)v121 + 63, (const float *)(a1 + 72));
            rf_vector_copy((float *)v121 + 15, v87, (const float *)(a1 + 60));
            rf_matrix3_copy((float *)v121 + 18, (const float *)(a1 + 72));
            rf_object_reactivate_from_respawn(v121);
            scalar = 1;
            v17 = v121 + 424;
            v16 = (int)(v121 + 423);
            v15 = nullptr;
            v14 = (float *)(v121 + 424);
            sub_40FD80((float *)v121 + 15, *((float *)v121 + 496), *((float *)v121 + 497), 0, v121 + 423, v121 + 424, 1);
            sub_4BBF50((int)v121, 0);
            if ( dword_681E38 )
            {
              sub_40BA80(v121 + 168, *(_DWORD *)(dword_681E38 + 44));
              sub_40B2D0(v121 + 168);
            }
            if ( rf_entity_has_attached_use_vehicle(dword_681E38) )
            {
              v118 = rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
              if ( v118 )
              {
                *(_DWORD *)(v118 + 2068) |= 0x800u;
                rf_entity_try_detach_with_safe_exit(dword_681E38);
                *(float *)(v118 + 52) = 0.0;
              }
            }
            for ( j = unk_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
            {
              if ( rf_entity_class_flags724_has_mask800(j) )
                *(float *)(j + 52) = 0.0;
            }
          }
        }
      }
      rf_entity_stop_weapon_firing(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 676));
      v150 = rf_character_drop_selected_weapon_item(a1, 0);
      v148 = 0;
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        v117 = sub_4DD720(*(_DWORD *)(a1 + 44));
        if ( v117 )
        {
          if ( rf_multiplayer_game_mode_get() == 1 )
          {
            v116 = rf_player_find_by_network_id(*(_BYTE *)(a1 + 624));
            if ( v116
              && (!*((_BYTE *)v117 + 48) && v117 == (_DWORD *)rf_ctf_blue_carrier_get() && *((_BYTE *)v116 + 48) == 1
               || *((_BYTE *)v117 + 48) == 1 && v117 == (_DWORD *)rf_ctf_red_carrier_get() && !*((_BYTE *)v116 + 48)) )
            {
              rf_multiplayer_player_add_frags((int)v116, 1);
            }
            rf_ctf_drop_player_carried_flag((int)v117);
          }
          rf_network_remove_player_flag_nodes((int)v117);
        }
        ++unk_704EE0;
        sub_4A9F70(a1, v149, v150);
      }
      if ( rf_multiplayer_runtime_mode == 1 && rf_entity_has_live_designated_projectile(a1) )
        rf_mark_owned_class_flag40_objects_for_delete(a1);
      if ( rf_multiplayer_runtime_mode )
      {
        v114 = (const void **)sub_4DD720(*(_DWORD *)(a1 + 44));
        v115 = (const void **)rf_player_find_by_network_id(*(_BYTE *)(a1 + 624));
        if ( v114 && v115 )
        {
          if ( v114 == v115 )
          {
            if ( rf_local_fpgun_player && (const void **)rf_local_fpgun_player == v114 )
            {
              Source = (char *)unk_88E2F0;
              v86 = &v17;
              v61 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A5A);
              v60 = v61;
              v151 = 0;
              v16 = 4;
              v85 = &v14;
              v59 = rf_string_construct_from_cstr(&v14, Source);
              v151 = -1;
              rf_multiplayer_notification_enqueue((int)v14, (int)v15, v16, (int)v17);
            }
            else
            {
              if ( sub_49BBF0((int)v114[983]) )
              {
                v58 = (const char *)unk_88DF08;
                v84 = &v17;
                v57 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A5B);
                v56 = v57;
                v151 = 1;
                v16 = 5;
                v83 = &v14;
                v55 = rf_string_concat_object_cstr(&v14, v114 + 2, v58);
              }
              else
              {
                v54 = (const char *)unk_88DF0C;
                v82 = &v17;
                v53 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A6A);
                v52 = v53;
                v151 = 2;
                v16 = 5;
                v81 = &v14;
                v51 = rf_string_concat_object_cstr(&v14, v114 + 2, v54);
              }
              v151 = -1;
              rf_multiplayer_notification_enqueue((int)v14, (int)v15, v16, (int)v17);
            }
            rf_multiplayer_player_add_frags((int)v115, -1);
          }
          else
          {
            v113 = rf_entity_resolve_handle((int)v115[5]);
            if ( rf_local_fpgun_player && (const void **)rf_local_fpgun_player == v114 )
            {
              if ( v113 && *(_DWORD *)(v113 + 676) == rf_weapon_id_riot_stick && rf_weapon_id_riot_stick != -1 )
              {
                v50 = (const char *)unk_88E2F4;
                v80 = &v17;
                v49 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A6B);
                v48 = v49;
                v151 = 3;
                v16 = 4;
                v79 = &v14;
                v47 = rf_string_concat_cstr_object(v78, v50, v115 + 2);
                v46 = v47;
                LOBYTE(v151) = 4;
                v45 = rf_string_concat_object_cstr(&v14, v47, "!");
                LOBYTE(v151) = 5;
                rf_multiplayer_notification_enqueue((int)v14, (int)v15, v16, (int)v17);
                v151 = -1;
                rf_string_destroy_buffer(v78);
              }
              else
              {
                v44 = (const char *)unk_88E2F8;
                v77 = &v17;
                v43 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A71);
                v42 = v43;
                v151 = 6;
                v16 = 4;
                v76 = &v14;
                v41 = rf_string_concat_cstr_object(&v14, v44, v115 + 2);
                v151 = -1;
                rf_multiplayer_notification_enqueue((int)v14, (int)v15, v16, (int)v17);
              }
            }
            else if ( rf_local_fpgun_player && (const void **)rf_local_fpgun_player == v115 )
            {
              v40 = (const char *)unk_88E2FC;
              v75 = &v17;
              v39 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A72);
              v38 = v39;
              v151 = 7;
              v16 = 4;
              v74 = &v14;
              v37 = rf_string_concat_cstr_object(&v14, v40, v114 + 2);
              v151 = -1;
              rf_multiplayer_notification_enqueue((int)v14, (int)v15, v16, (int)v17);
            }
            else if ( v113 && *(_DWORD *)(v113 + 676) == rf_weapon_id_riot_stick && rf_weapon_id_riot_stick != -1 )
            {
              v36 = (const char *)unk_88E300;
              v73 = &v17;
              v35 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A73);
              v34 = v35;
              v151 = 8;
              v16 = 4;
              v72 = &v14;
              v12 = (int)(v115 + 2);
              v33 = (int *)rf_string_concat_object_cstr(v71, v114 + 2, v36);
              v32 = v33;
              LOBYTE(v151) = 9;
              v31 = rf_string_concat_two_objects(v70, v33, v12);
              v30 = v31;
              LOBYTE(v151) = 10;
              v29 = rf_string_concat_object_cstr(&v14, v31, "!");
              LOBYTE(v151) = 12;
              rf_multiplayer_notification_enqueue((int)v14, (int)v15, v16, (int)v17);
              LOBYTE(v151) = 11;
              rf_string_destroy_buffer(v70);
              v151 = -1;
              rf_string_destroy_buffer(v71);
            }
            else
            {
              v28 = (const char *)unk_88DF10;
              v69 = &v17;
              v27 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A87);
              v26 = v27;
              v151 = 13;
              v16 = 5;
              v68 = &v14;
              v13 = (int)(v115 + 2);
              v25 = (int *)rf_string_concat_object_cstr(v67, v114 + 2, v28);
              v24 = v25;
              LOBYTE(v151) = 14;
              v23 = rf_string_concat_two_objects(&v14, v25, v13);
              LOBYTE(v151) = 15;
              rf_multiplayer_notification_enqueue((int)v14, (int)v15, v16, (int)v17);
              v151 = -1;
              rf_string_destroy_buffer(v67);
            }
            v111 = 1;
            v112 = rf_multiplayer_game_mode_get();
            if ( (v112 == 2 || v112 == 1) && *((unsigned __int8 *)v115 + 48) == *((unsigned __int8 *)v114 + 48) )
              v111 = 0;
            if ( v111 )
              rf_multiplayer_player_add_frags((int)v115, 1);
          }
        }
        else if ( v114 )
        {
          v22 = (const char *)unk_88DF14;
          v66 = &v17;
          v21 = rf_string_construct_from_cstr(&v17, (char *)&byte_631A9D);
          v20 = v21;
          v151 = 16;
          v16 = 5;
          v65 = &v14;
          v19 = rf_string_concat_object_cstr(&v14, v114 + 2, v22);
          v151 = -1;
          rf_multiplayer_notification_enqueue((int)v14, (int)v15, v16, (int)v17);
        }
      }
      if ( *(_DWORD *)(a1 + 1312) == 13 )
        sub_40C340((int *)(a1 + 672));
      if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 0x20) != 0 )
      {
        if ( *(float *)(a1 + 120) <= 6.0 )
          rf_replicator_arm_milliseconds((int *)(a1 + 1208), 1600);
        else
          rf_replicator_arm_milliseconds((int *)(a1 + 1208), 2000);
      }
      rf_entity_stop_speech_voice(a1);
      result = a1;
      if ( (*(_DWORD *)(a1 + 2064) & 0x400000) != 0 )
      {
        v11 = (char *)rf_string_object_c_str_or_empty((const void *)(a1 + 24));
        result = rf_frontend_request_credits_or_endgame_blackout(v11);
      }
      if ( rf_multiplayer_runtime_mode == 1 )
      {
        result = (unsigned __int8)byte_704E83;
        if ( !byte_704E83 && *(_DWORD *)(a1 + 5168) == rf_local_fpgun_player && rf_local_fpgun_player )
        {
          rf_player_set_flags16_bit8(rf_local_fpgun_player);
          result = rf_replicator_arm_milliseconds(&rf_manual_respawn_gate_event, 1000);
        }
        *(_DWORD *)(a1 + 5168) = 0;
      }
      if ( *(_DWORD *)(a1 + 5260) )
      {
        result = rf_model_handle_destroy_cdecl_adapter(*(_DWORD **)(a1 + 5260));
        *(_DWORD *)(a1 + 5260) = 0;
      }
    }
  }
  return result;
}

