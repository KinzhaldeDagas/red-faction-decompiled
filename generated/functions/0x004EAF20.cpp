// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EAF20 sub_4EAF20
// UNREALRED VERIFIED [rocket-reacquire-20260930] Local-player alternate hold scans at 75 ms intervals. After 0x4EB210 changes Player+4000 target handle, clears +3997 ready byte; if new target is valid, rearms +4004 duration to 2750 ms and +4012 cue timer to zero. Loss to -1 prevents completion; returning to the same entity after an observed -1 is a handle change and rearms the full duration. Completion sets +3997 and launch occurs on a later update. This local routine does not establish any multiplayer authority-ready acknowledgement protocol.
void __cdecl sub_4EAF20(int a1)
{
  int v1; // [esp+8h] [ebp-14h]
  int v2; // [esp+Ch] [ebp-10h]
  int v3; // [esp+10h] [ebp-Ch] BYREF
  unsigned int selected_weapon_and_resolve_mesh; // [esp+14h] [ebp-8h]
  int v5; // [esp+18h] [ebp-4h]

  if ( a1 == rf_local_fpgun_player )
  {
    if ( a1 )
    {
      v5 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
      if ( v5
        && (selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1),
            rf_weapon_has_alt_lock_flag(selected_weapon_and_resolve_mesh)) )
      {
        if ( rf_input_action_any_bound_key_or_mouse_held(a1 + 228, 1) )
          goto LABEL_15;
        if ( *(_BYTE *)(a1 + 3996) == 1 && !*(_BYTE *)(a1 + 3997) )
        {
          rf_player_handle_weapon_fire_input(a1, 0, 1);
          *(_DWORD *)(a1 + 4000) = -1;
        }
        *(_BYTE *)(a1 + 3996) = 0;
        if ( *(_BYTE *)(a1 + 3997) != 1 )
        {
LABEL_15:
          if ( *(_BYTE *)(a1 + 3996) == 1 )
          {
            v2 = rf_replicator_signed_remaining_milliseconds((int *)(a1 + 4004));
            if ( *(_DWORD *)(a1 + 4000) != -1 && v2 >= 0 && rf_replicator_has_elapsed((int *)(a1 + 4012)) )
            {
              rf_gamesound_play_event(20, 0, 0.0, 1.0);
              rf_replicator_arm_milliseconds((int *)(a1 + 4012), v2 / 5);
            }
            if ( rf_replicator_has_elapsed((int *)(a1 + 4008)) )
            {
              v1 = *(_DWORD *)(a1 + 4000);
              sub_4EB210(a1);
              rf_replicator_arm_milliseconds((int *)(a1 + 4008), 75);
              if ( v1 != *(_DWORD *)(a1 + 4000) )
              {
                *(_BYTE *)(a1 + 3997) = 0;
                if ( *(_DWORD *)(a1 + 4000) != -1 )
                {
                  rf_replicator_arm_milliseconds((int *)(a1 + 4004), 2750);
                  rf_replicator_arm_milliseconds((int *)(a1 + 4012), 0);
                }
              }
            }
            if ( *(_DWORD *)(a1 + 4000) != -1 && rf_replicator_has_elapsed((int *)(a1 + 4004)) )
            {
              rf_gamesound_play_event(21, 0, 0.0, 1.0);
              *(_BYTE *)(a1 + 3997) = 1;
            }
          }
        }
        else
        {
          v3 = 0;
          sub_431FD0(*(float *)&v5, 0, 1, &v3, nullptr, nullptr);
          if ( v3 )
          {
            *(_DWORD *)(v3 + 744) = *(_DWORD *)(a1 + 4000);
            *(float *)(*(_DWORD *)(v3 + 660) + 308) = 45.0;
            *(float *)(*(_DWORD *)(v3 + 660) + 304) = 5.0;
            *(float *)(*(_DWORD *)(v3 + 660) + 312) = 150.0;
            *(float *)(*(_DWORD *)(v3 + 660) + 316) = 0.33333001;
            sub_4E71A0(a1);
          }
        }
      }
      else
      {
        sub_4E71A0(a1);
      }
    }
    else
    {
      sub_4E71A0(0);
    }
  }
}

