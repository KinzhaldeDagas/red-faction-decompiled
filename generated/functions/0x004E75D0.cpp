// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E75D0 rf_fpgun_select_state
// UNREALRED VERIFIED [fpgun-state-decode]: Selects loop_fire, idle, or run under the recovered priority rules.
char __cdecl rf_fpgun_select_state(_DWORD *a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float v5[3]; // [esp+Ch] [ebp-20h] BYREF
  float v6[3]; // [esp+18h] [ebp-14h] BYREF
  unsigned int selected_weapon_and_resolve_mesh; // [esp+24h] [ebp-8h]
  float *v8; // [esp+28h] [ebp-4h]

  LOBYTE(v1) = (_BYTE)a1;
  if ( a1 == (_DWORD *)rf_local_fpgun_player )
  {
    v1 = (float *)rf_entity_resolve_handle(a1[5]);
    v8 = v1;
    if ( v1 )
    {
      selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(a1);
      if ( rf_entity_weapon_firing_byte_is_set(*((_DWORD *)v8 + 11), selected_weapon_and_resolve_mesh) )
      {
        LOBYTE(v1) = rf_fpgun_state_is_resident((int)a1, 2);
        if ( !(_BYTE)v1 )
          LOBYTE(v1) = rf_fpgun_request_state((int)a1, 2);
      }
      else
      {
        if ( !rf_fpgun_state_is_resident((int)a1, 0) )
          rf_fpgun_request_state((int)a1, 0);
        if ( (rf_entity_movement_is_index4_or7((int)v8)
           || rf_entity_uses_fall_or_airborne_vehicle_motion(v8)
           || (v2 = rf_vector3_set_components_return_destination(v6, 0.0, 0.0, 0.0),
               rf_vector3_components_equal(v8 + 453, v2))
           || rf_vector3_length(v8 + 81) < 0.2000000029802322)
          && !rf_fpgun_state_is_resident((int)a1, 0) )
        {
          LOBYTE(v1) = rf_fpgun_request_state((int)a1, 0);
        }
        else
        {
          v3 = rf_vector3_set_components_return_destination(v5, 0.0, 0.0, 0.0);
          LOBYTE(v1) = rf_vector3_components_not_equal(v8 + 453, v3);
          if ( (_BYTE)v1 )
          {
            if ( rf_entity_descriptor_mode1_and_speedmode1((int)v8)
              || (LOBYTE(v1) = rf_entity_is_crouched_state810((int)v8), (_BYTE)v1) )
            {
              LOBYTE(v1) = rf_fpgun_state_is_resident((int)a1, 1);
              if ( !(_BYTE)v1 )
              {
                rf_fpgun_cleanup_idle_actions((int)a1);
                if ( v8[453] <= 0.1000000014901161
                  && v8[453] >= -0.1000000014901161
                  && v8[455] <= 0.1000000014901161
                  && v8[455] >= -0.1000000014901161 )
                {
                  LOBYTE(v1) = rf_fpgun_request_state((int)a1, 0);
                }
                else
                {
                  LOBYTE(v1) = rf_fpgun_request_state((int)a1, 1);
                }
              }
            }
          }
        }
      }
    }
  }
  return (char)v1;
}

