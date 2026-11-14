// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DDD80 rf_player_cycle_weapon_previous
// UNREALRED VERIFIED [weapon-cycle] Reverses the selector through Player+0x1154 preference entries within the current category; wrapping preference position decrements category modulo four.
// UNREALRED VERIFIED [weapon-selector] Arms the shared selector deadline for 4000 ms, opens at the current weapon, recursively reverses without equipping, and plays On or Scroll.
char __cdecl rf_player_cycle_weapon_previous(int a1, int a2, char a3)
{
  int v3; // eax
  int v4; // ecx
  int v6; // [esp+8h] [ebp-30h]
  int v7; // [esp+Ch] [ebp-2Ch]
  int v8; // [esp+14h] [ebp-24h]
  int v9; // [esp+18h] [ebp-20h]
  int *v10; // [esp+1Ch] [ebp-1Ch]
  int v11; // [esp+20h] [ebp-18h]
  int v12; // [esp+24h] [ebp-14h]
  int v13; // [esp+28h] [ebp-10h]
  int v14; // [esp+2Ch] [ebp-Ch]
  int j; // [esp+30h] [ebp-8h]
  int i; // [esp+30h] [ebp-8h]
  int k; // [esp+30h] [ebp-8h]
  int m; // [esp+30h] [ebp-8h]
  int n; // [esp+30h] [ebp-8h]
  int v20; // [esp+34h] [ebp-4h]

  v10 = (int *)rf_player_resolve_entity_inventory(a1);
  v3 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( v10 && v3 )
  {
    if ( v10[1] < 0 && (*(_DWORD *)(v3 + 2064) & 0x800) != 0 )
    {
      LOBYTE(v3) = rf_player_has_flags16_mask10(a1);
      if ( (_BYTE)v3 )
        LOBYTE(v3) = rf_gamesound_play_event(2, 0, 0.0, 1.0);
    }
    else
    {
      v20 = *v10;
      LOBYTE(v3) = rf_entity_has_attached_use_turret(*v10);
      if ( !(_BYTE)v3 )
      {
        LOBYTE(v3) = rf_entity_has_attached_use_vehicle(v20);
        if ( !(_BYTE)v3 )
        {
          LOBYTE(v3) = rf_entity_is_parent_jeep_relation1(v20);
          if ( !(_BYTE)v3 )
          {
            rf_replicator_arm_milliseconds(&rf_weapon_selector_deadline_event, 4000);
            rf_replicator_arm_milliseconds(&rf_weapon_selector_deadline_event, 4000);
            if ( rf_weapon_selector_is_open )
              v7 = rf_weapon_selector_current_cycle_slot;
            else
              v7 = -1;
            v11 = v7;
            if ( v7 == -1 )
              v6 = v10[1];
            else
              v6 = rf_weapon_cycle_slots_weapon_index[4 * v7];
            v12 = v6;
            LOBYTE(v3) = v6;
            if ( v6 == unk_911C98 )
              v12 = dword_911CC4;
            if ( v12 == unk_911C88 )
            {
              LOBYTE(v3) = dword_911C78;
              v12 = dword_911C78;
            }
            if ( v7 != -1 )
              goto LABEL_37;
            if ( v12 == -1 )
            {
              for ( i = 0; i < 32; ++i )
              {
                LOBYTE(v3) = sub_403D00((int)v10, rf_weapon_cycle_slots_weapon_index[4 * i]);
                if ( (_BYTE)v3 )
                {
                  v11 = i;
                  break;
                }
              }
            }
            else
            {
              for ( j = 0; j < 32; ++j )
              {
                v3 = rf_weapon_cycle_slots_weapon_index[4 * j];
                if ( v3 == v12 )
                {
                  v11 = j;
                  break;
                }
              }
            }
            if ( v11 != -1 )
            {
LABEL_37:
              if ( rf_weapon_selector_is_open )
              {
                v13 = -1;
                v9 = -1;
                v14 = -1;
                if ( rf_local_fpgun_player )
                {
                  for ( k = 0; k < 32; ++k )
                  {
                    if ( v12 == *(_DWORD *)(rf_local_fpgun_player + 4 * k + 4436) )
                    {
                      v9 = (k + 31) % 32;
                      v14 = k;
                      break;
                    }
                  }
                  if ( v9 != -1 )
                  {
                    for ( m = 0; m < 32; ++m )
                    {
                      if ( rf_weapon_cycle_slots_weapon_index[4 * m] == *(_DWORD *)(rf_local_fpgun_player + 4 * v9 + 4436) )
                      {
                        v13 = m;
                        break;
                      }
                    }
                  }
                }
                v8 = rf_weapon_cycle_slots_category[4 * v11];
                while ( !rf_player_cycle_candidate_is_usable(a1, v13, v8, -1) )
                {
                  v4 = (v9 + 31) % 32;
                  v9 = v4;
                  if ( a2 == -1 && v4 > v14 )
                  {
                    v8 = (v8 + 3) % 4;
                    v13 = 31;
                  }
                  v14 = v4;
                  if ( *(_DWORD *)(rf_local_fpgun_player + 4 * v4 + 4436) != -1 || v13 <= 0 )
                  {
                    for ( n = 0; n < 32; ++n )
                    {
                      if ( rf_weapon_cycle_slots_weapon_index[4 * n] == *(_DWORD *)(rf_local_fpgun_player + 4 * v4 + 4436) )
                      {
                        v13 = n;
                        break;
                      }
                    }
                    if ( v13 == v11 && v8 == rf_weapon_cycle_slots_category[4 * v13] )
                      break;
                  }
                }
                if ( v13 == -1 || rf_weapon_cycle_slots_weapon_index[4 * v13] == v12 )
                {
                  LOBYTE(v3) = rf_player_has_flags16_mask10(a1);
                  if ( (_BYTE)v3 )
                    LOBYTE(v3) = rf_gamesound_play_event(2, 0, 0.0, 1.0);
                }
                else
                {
                  LOBYTE(v3) = v13;
                  rf_weapon_selector_current_cycle_slot = v13;
                  if ( a3 )
                    LOBYTE(v3) = rf_gamesound_play_event(rf_weapon_selector_scroll_sound_event, 0, 0.0, 1.0);
                }
              }
              else
              {
                rf_weapon_selector_current_cycle_slot = v11;
                rf_weapon_selector_is_open = 1;
                rf_player_cycle_weapon_previous(a1, a2, 0);
                LOBYTE(v3) = rf_gamesound_play_event(rf_weapon_selector_on_sound_event, 0, 0.0, 1.0);
              }
            }
          }
        }
      }
    }
  }
  return v3;
}

