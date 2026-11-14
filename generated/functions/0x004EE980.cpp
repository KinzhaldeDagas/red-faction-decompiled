// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EE980 rf_fplegs_select_movement_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Uses global entity681E38 and player87C640 without own NULL checks. Falling predicate AL exactly1 chooses5; otherwise player byte177 exactly1 chooses3 for exact-zero motion1812 or4 for nonzero. Otherwise exact-zero motion chooses0; nonzero motion plus walking predicate AL exactly1 chooses1, else running predicate AL exactly1 chooses2. If no predicate matches leaves state untouched. Requests selected state with float0.25 only when neither current nor pending already equals it. Vector tests are exact component comparisons, not length/tolerance.
void rf_fplegs_select_movement_state()
{
  float *v0; // eax
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float v4[3]; // [esp+Ch] [ebp-30h] BYREF
  float v5[3]; // [esp+18h] [ebp-24h] BYREF
  float v6[3]; // [esp+24h] [ebp-18h] BYREF
  float v7[3]; // [esp+30h] [ebp-Ch] BYREF

  if ( rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)dword_681E38) )
  {
    if ( !rf_fplegs_state_is_resident(5) )
      rf_fplegs_request_state_transition(5u, 0.25);
  }
  else if ( *(_BYTE *)(rf_local_fpgun_player + 177) == 1 )
  {
    v0 = rf_vector3_set_components_return_destination(v7, 0.0, 0.0, 0.0);
    if ( rf_vector3_components_equal((float *)(dword_681E38 + 1812), v0) )
    {
      if ( !rf_fplegs_state_is_resident(3) )
        rf_fplegs_request_state_transition(3u, 0.25);
    }
    else if ( !rf_fplegs_state_is_resident(4) )
    {
      rf_fplegs_request_state_transition(4u, 0.25);
    }
  }
  else
  {
    v1 = rf_vector3_set_components_return_destination(v6, 0.0, 0.0, 0.0);
    if ( rf_vector3_components_equal((float *)(dword_681E38 + 1812), v1) )
    {
      if ( !rf_fplegs_state_is_resident(0) )
        rf_fplegs_request_state_transition(0, 0.25);
    }
    else
    {
      v2 = rf_vector3_set_components_return_destination(v5, 0.0, 0.0, 0.0);
      if ( rf_vector3_components_not_equal((float *)(dword_681E38 + 1812), v2) && sub_437E80(dword_681E38) )
      {
        if ( !rf_fplegs_state_is_resident(1) )
          rf_fplegs_request_state_transition(1u, 0.25);
      }
      else
      {
        v3 = rf_vector3_set_components_return_destination(v4, 0.0, 0.0, 0.0);
        if ( rf_vector3_components_not_equal((float *)(dword_681E38 + 1812), v3)
          && rf_entity_descriptor_mode1_and_speedmode1(dword_681E38)
          && !rf_fplegs_state_is_resident(2) )
        {
          rf_fplegs_request_state_transition(2u, 0.25);
        }
      }
    }
  }
}

