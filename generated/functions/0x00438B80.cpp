// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438B80 rf_entity_try_idle_body_variation
// UNREALRED VERIFIED [ai-script-animation-release-20261013] Idle variation launcher chooses among available canonical action slots 30..33, invokes ordinary body request at mix 1 / hold 0 / sound 1, then stores the chosen canonical slot at Entity+0x1364. This is distinct from filename registry index +0x1368. Generic canonical Play_Animation does not write either owner. Existing mode/residency/cutscene/deadline gates remain significant.
char __cdecl rf_entity_try_idle_body_variation(int *a1)
{
  int v1; // eax
  unsigned int v3; // [esp+Ch] [ebp-20h]
  int v4; // [esp+10h] [ebp-1Ch]
  _DWORD v5[4]; // [esp+14h] [ebp-18h]
  int first_dword; // [esp+24h] [ebp-8h]
  int i; // [esp+28h] [ebp-4h]

  LOBYTE(v1) = (_BYTE)a1;
  if ( a1[328] == 2 || a1[328] == 1 )
  {
    LOBYTE(v1) = rf_entity_is_crouched_state810((int)a1);
    if ( !(_BYTE)v1 )
    {
      LOBYTE(v1) = rf_object_has_player_flag((int)a1);
      if ( (unsigned __int8)v1 != 1 )
      {
        if ( rf_entity_speech_voice_is_playing((int)a1)
          || !rf_entity_body_state_is_resident((int)a1, 0)
          || rf_unhide_global_owner_present() )
        {
          LOBYTE(v1) = rf_entity_refresh_idle_animation_deadline((int)a1);
        }
        else
        {
          LOBYTE(v1) = rf_replicator_has_elapsed(a1 + 1244);
          if ( (unsigned __int8)v1 == 1 )
          {
            rf_timestamp_arm_random_inclusive_milliseconds(a1 + 1244, 30000, 60000);
            first_dword = rf_receiver_get_first_dword(a1);
            if ( !first_dword || *(_BYTE *)(first_dword + 352) || (v1 = a1[516] & 0x40000000) != 0 )
            {
              v4 = 0;
              for ( i = 0; i < 4; ++i )
              {
                if ( a1[4 * i + 781] != -1 )
                  v5[v4++] = i + 30;
              }
              if ( v4 > 0 )
              {
                v3 = v5[rand() % v4];
                rf_entity_request_body_action((int)a1, v3, 1.0, 0, 1);
                a1[1241] = v3;
              }
              a1[516] &= ~0x40000000u;
              LOBYTE(v1) = (_BYTE)a1;
            }
          }
        }
      }
    }
  }
  return v1;
}

