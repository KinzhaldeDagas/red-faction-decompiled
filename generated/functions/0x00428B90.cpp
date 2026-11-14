// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00428B90 sub_428B90
// UNREALRED VERIFIED [mission-play-animation-file-20261013] When no pending state (Entity+0x834==-1), flag0x02000000 selects canonical custom state22 with0.25s transition unless already resident. This persistent filename-loop request differs from type11 canonical state commands, which only write cyclic weights. Bit8 suppression is owned by outer scheduler0x428970.
void __cdecl sub_428B90(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v6[3]; // [esp+Ch] [ebp-50h] BYREF
  float v7[3]; // [esp+18h] [ebp-44h] BYREF
  float v8[3]; // [esp+24h] [ebp-38h] BYREF
  float v9[3]; // [esp+30h] [ebp-2Ch] BYREF
  float v10[3]; // [esp+3Ch] [ebp-20h] BYREF
  char v11; // [esp+4Bh] [ebp-11h]
  int v12; // [esp+4Ch] [ebp-10h] BYREF
  int v13; // [esp+50h] [ebp-Ch] BYREF
  int v14; // [esp+54h] [ebp-8h]
  int v15; // [esp+58h] [ebp-4h]

  if ( *(_DWORD *)(a1 + 2100) == -1 )
  {
    if ( ((unsigned int)&unk_2000000 & *(_DWORD *)(a1 + 2064)) != 0 )
    {
      if ( !rf_entity_body_state_is_resident(a1, 22) )
        rf_entity_request_body_state(a1, 0x16u, 0.25);
    }
    else if ( rf_entity_has_attached_use_turret(a1) )
    {
      if ( !rf_entity_body_state_is_resident(a1, 15) )
        rf_entity_request_body_state(a1, 0xFu, 0.25);
    }
    else if ( rf_entity_is_parent_jeep_relation0(a1) )
    {
      if ( !rf_entity_body_state_is_resident(a1, 20) )
        rf_entity_request_body_state(a1, 0x14u, 0.25);
    }
    else if ( rf_entity_is_parent_jeep_relation0(a1) )
    {
      if ( !rf_entity_body_state_is_resident(a1, 21) )
        rf_entity_request_body_state(a1, 0x15u, 0.25);
    }
    else if ( rf_entity_uses_fall_or_airborne_vehicle_motion(a1) )
    {
      if ( !rf_entity_body_state_is_resident(a1, 14) )
        rf_entity_request_body_state(a1, 0xEu, 0.25);
    }
    else if ( (*(_DWORD *)(a1 + 424) & 0x8000) != 0 && rf_entity_is_crouched_state810(a1) )
    {
      if ( rf_vector3_length((float *)(a1 + 324)) > 0.009999999776482582 )
        rf_entity_request_body_state(a1, 0xAu, 0.25);
      else
        rf_entity_request_body_state(a1, 9u, 0.25);
    }
    else
    {
      v11 = 0;
      if ( (*(_DWORD *)(a1 + 1364) == 1 || *(_DWORD *)(a1 + 1364) == 3)
        && *(_DWORD *)(a1 + 1740) == -1
        && !rf_entity_descriptor_mode_is_12_15_13_11_or9(a1) )
      {
        v11 = 1;
        if ( !(rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode)
          && !rf_weapon_is_melee(*(_DWORD *)(a1 + 676)) )
        {
          rf_replicator_arm_milliseconds((int *)(a1 + 1860), 800);
          rf_entity_stop_weapon_firing(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 676));
        }
      }
      if ( *(_DWORD *)(a1 + 1312) == 17 )
      {
        v15 = 8;
        v14 = 0;
        v12 = 7;
        v13 = 7;
        if ( *(_DWORD *)(a1 + 2388) == -1 )
        {
          v12 = 4;
          v13 = 4;
        }
      }
      else if ( *(_DWORD *)(a1 + 1312) == 7 || *(_DWORD *)(a1 + 1312) == 12 && *(_DWORD *)(a1 + 1364) == 1 )
      {
        v15 = 8;
        v14 = 13;
        v12 = 6;
        v13 = 6;
        if ( *(_DWORD *)(a1 + 2372) == -1 )
          v13 = 4;
      }
      else if ( !rf_entity_selected_weapon_ready_admit((_DWORD *)a1)
             || rf_entity_is_dead(a1)
             || rf_entity_weapon_is_holstered_for_actions(a1) )
      {
        v15 = 8;
        v14 = 0;
        v12 = 2;
        v13 = 4;
      }
      else
      {
        v15 = 9;
        v14 = 1;
        rf_entity_choose_body_actions_and_movement_codes(a1, &v12, &v13);
        if ( !rf_splitscreen_runtime_active )
        {
          if ( *(float *)(a1 + 2240) * 0.300000011920929 >= rf_vector3_length((float *)(a1 + 324))
            || *(_DWORD *)(a1 + 1856) == 2 )
          {
            v14 = 1;
          }
          else
          {
            v14 = v13;
          }
        }
      }
      if ( rf_ai_multiplayer_flag2000000_allows_action(a1) && rf_entity_mode3_or12_action_admitted(a1) )
      {
        if ( rf_entity_body_state_is_resident(a1, v15) )
        {
          if ( !rf_entity_is_crouched_state810(a1) && *(_DWORD *)(a1 + 5004) == v15 && *(float *)(a1 + 5012) == 0.0 )
            rf_entity_apply_crouch_shape_centers(a1);
        }
        else
        {
          rf_entity_request_body_state(a1, v15, 0.25);
        }
      }
      else
      {
        if ( rf_entity_is_crouched_state810(a1) )
          rf_entity_try_apply_standing_shape_centers(a1);
        if ( rf_entity_movement_is_index4_or7(a1) )
        {
          v1 = rf_vector3_set_components_return_destination(v10, 0.0, 0.0, 0.0);
          if ( !rf_vector3_components_equal((float *)(a1 + 1812), v1) || rf_entity_body_state_is_resident(a1, 18) )
          {
            v2 = rf_vector3_set_components_return_destination(v9, 0.0, 0.0, 0.0);
            if ( rf_vector3_components_not_equal((float *)(a1 + 1812), v2) && !rf_entity_body_state_is_resident(a1, 19) )
              rf_entity_request_body_state(a1, 0x13u, 0.25);
          }
          else
          {
            rf_entity_request_body_state(a1, 0x12u, 0.25);
          }
        }
        else
        {
          v3 = rf_vector3_set_components_return_destination(v8, 0.0, 0.0, 0.0);
          if ( !rf_vector3_components_equal((float *)(a1 + 1812), v3) || rf_entity_body_state_is_resident(a1, v14) )
          {
            v4 = rf_vector3_set_components_return_destination(v7, 0.0, 0.0, 0.0);
            if ( rf_vector3_components_not_equal((float *)(a1 + 1812), v4)
              && sub_437E80(a1)
              && !rf_entity_body_state_is_resident(a1, v12) )
            {
              rf_entity_request_body_state(a1, v12, 0.25);
            }
            else
            {
              v5 = rf_vector3_set_components_return_destination(v6, 0.0, 0.0, 0.0);
              if ( rf_vector3_components_not_equal((float *)(a1 + 1812), v5)
                && (rf_entity_descriptor_mode1_and_speedmode1(a1) || rf_entity_descriptor_mode_is_12_15_13_11_or9(a1))
                && !rf_entity_body_state_is_resident(a1, v13) )
              {
                rf_entity_request_body_state(a1, v13, 0.25);
              }
            }
          }
          else
          {
            rf_entity_request_body_state(a1, v14, 0.25);
          }
        }
      }
    }
  }
  else if ( !rf_entity_body_state_is_resident(a1, *(_DWORD *)(a1 + 2100)) )
  {
    rf_entity_request_body_state(a1, *(_DWORD *)(a1 + 2100), 0.25);
  }
}

