// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435D80 rf_character_try_damage_flinch
// UNREALRED VERIFIED [damage-flinch-decode]: Timestamp-gated flinch owner; body fire actions 2 and 3 block it, and success arms an independent inclusive 1000-2000 ms cooldown.
char __cdecl rf_character_try_damage_flinch(_DWORD *a1)
{
  int dword8; // eax
  float v3; // [esp+Ch] [ebp-8h]
  unsigned int v4; // [esp+10h] [ebp-4h]

  if ( !sub_438AC0((int)a1) || (dword8 = rf_view_wrapper_get_dword8(*(_DWORD *)(a1[1292] + 196))) != 0 )
  {
    LOBYTE(dword8) = rf_replicator_has_elapsed(a1 + 524);
    if ( (_BYTE)dword8 )
    {
      LOBYTE(dword8) = rf_entity_is_dead((int)a1);
      if ( (unsigned __int8)dword8 != 1 )
      {
        LOBYTE(dword8) = rf_ai_is_ready_flag_set((int)(a1 + 168));
        if ( (_BYTE)dword8 || a1[773] == -1 )
        {
          LOBYTE(dword8) = rf_ai_unholster_pending_flag_set((int)(a1 + 168));
          if ( (unsigned __int8)dword8 != 1 )
          {
            LOBYTE(dword8) = rf_ai_unholster_animation_deadline_active((int)(a1 + 168));
            if ( (unsigned __int8)dword8 != 1 )
            {
              LOBYTE(dword8) = rf_entity_body_action_is_active((int)a1, 2u);
              if ( (unsigned __int8)dword8 != 1 )
              {
                LOBYTE(dword8) = rf_entity_body_action_is_active((int)a1, 3u);
                if ( (unsigned __int8)dword8 != 1 )
                {
                  v4 = a1[522];
                  if ( v4 == -1 )
                  {
                    if ( rf_entity_selected_weapon_ready_admit(a1) )
                      v4 = 23;
                    else
                      v4 = 22;
                  }
                  LOBYTE(dword8) = (_BYTE)a1;
                  if ( a1[4 * v4 + 661] != -1 )
                  {
                    rf_entity_stop_weapon_firing(a1[11], a1[169]);
                    a1[522] = v4;
                    rf_entity_request_body_action((int)a1, v4, 1.0, 0, 1);
                    rf_timestamp_arm_random_inclusive_milliseconds(a1 + 524, 1000, 2000);
                    v3 = rf_model_animation_duration_seconds((unsigned int *)a1[32], a1[4 * v4 + 661]);
                    LOBYTE(dword8) = rf_replicator_arm_milliseconds(a1 + 465, (int)(v3 * 1000.0 + 0.5) + 250);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return dword8;
}

