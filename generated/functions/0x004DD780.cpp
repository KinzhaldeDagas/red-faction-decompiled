// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DD780 rf_player_cycle_weapon_next
// UNREALRED VERIFIED [weapon-cycle] Advances the selector through Player+0x1154 preference entries within the current weapon category; wrapping preference position advances category modulo four.
// UNREALRED VERIFIED [weapon-selector] Arms the shared selector deadline for 4000 ms, opens at the current weapon, recursively advances without equipping, and plays On or Scroll.
char __cdecl rf_player_cycle_weapon_next(int a1, int a2, char a3)
{
  int v3; // eax
  int v4; // eax
  int v6; // [esp+8h] [ebp-3Ch]
  int v7; // [esp+Ch] [ebp-38h]
  int j; // [esp+10h] [ebp-34h]
  unsigned int v9; // [esp+14h] [ebp-30h]
  int v10; // [esp+18h] [ebp-2Ch]
  int v11; // [esp+20h] [ebp-24h]
  int *v12; // [esp+24h] [ebp-20h]
  int v13; // [esp+28h] [ebp-1Ch]
  int v14; // [esp+2Ch] [ebp-18h]
  int v15; // [esp+30h] [ebp-14h]
  int v16; // [esp+34h] [ebp-10h]
  int i; // [esp+38h] [ebp-Ch]
  int m; // [esp+38h] [ebp-Ch]
  int k; // [esp+38h] [ebp-Ch]
  int n; // [esp+38h] [ebp-Ch]
  int ii; // [esp+38h] [ebp-Ch]
  int jj; // [esp+38h] [ebp-Ch]
  int v23; // [esp+3Ch] [ebp-8h]
  int v24; // [esp+40h] [ebp-4h]

  v12 = (int *)rf_player_resolve_entity_inventory(a1);
  v3 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( v12 && v3 )
  {
    if ( v12[1] < 0 && (*(_DWORD *)(v3 + 2064) & 0x800) != 0 )
    {
      LOBYTE(v3) = rf_player_has_flags16_mask10(a1);
      if ( (_BYTE)v3 )
        LOBYTE(v3) = rf_gamesound_play_event(2, 0, 0.0, 1.0);
    }
    else
    {
      v24 = *v12;
      LOBYTE(v3) = rf_entity_has_attached_use_turret(*v12);
      if ( !(_BYTE)v3 )
      {
        LOBYTE(v3) = rf_entity_has_attached_use_vehicle(v24);
        if ( !(_BYTE)v3 )
        {
          LOBYTE(v3) = rf_entity_is_parent_jeep_relation1(v24);
          if ( !(_BYTE)v3 )
          {
            rf_replicator_arm_milliseconds(&rf_weapon_selector_deadline_event, 4000);
            if ( rf_weapon_selector_is_open )
              v7 = rf_weapon_selector_current_cycle_slot;
            else
              v7 = -1;
            v13 = v7;
            if ( v7 == -1 )
              v6 = v12[1];
            else
              v6 = rf_weapon_cycle_slots_weapon_index[4 * v7];
            v14 = v6;
            if ( a2 != -1 && (!rf_weapon_selector_is_open || a2 != rf_weapon_records_category[340 * v6]) )
            {
              v10 = rf_player_resolve_entity_inventory(a1);
              v13 = -1;
              rf_weapon_selector_is_open = 0;
              for ( i = 0; i < 32; ++i )
              {
                v9 = *(_DWORD *)(rf_local_fpgun_player + 4 * i + 4436);
                for ( j = 0; j < 32; ++j )
                {
                  if ( rf_weapon_cycle_slots_weapon_index[4 * j] == v9
                    && rf_weapon_cycle_slots_category[4 * j] == a2
                    && sub_403D00(v10, v9) )
                  {
                    v14 = v9;
                    v13 = j;
                    break;
                  }
                  if ( rf_weapon_cycle_slots_weapon_index[4 * j] == -1 )
                    break;
                }
                if ( v13 != -1 )
                  break;
              }
            }
            if ( v14 == unk_911C98 )
              v14 = dword_911CC4;
            LOBYTE(v3) = v14;
            if ( v14 == unk_911C88 )
              v14 = dword_911C78;
            if ( v13 != -1 )
              goto LABEL_52;
            if ( v14 == -1 )
            {
              for ( k = 0; k < 32; ++k )
              {
                LOBYTE(v3) = sub_403D00((int)v12, rf_weapon_cycle_slots_weapon_index[4 * k]);
                if ( (_BYTE)v3 )
                {
                  v13 = k;
                  break;
                }
                LOBYTE(v3) = k + 1;
              }
            }
            else
            {
              for ( m = 0; m < 32; ++m )
              {
                LOBYTE(v3) = 16 * m;
                if ( rf_weapon_cycle_slots_weapon_index[4 * m] == v14 )
                {
                  v13 = m;
                  break;
                }
              }
            }
            if ( v13 != -1 )
            {
LABEL_52:
              if ( rf_weapon_selector_is_open )
              {
                v23 = -1;
                v15 = -1;
                v16 = -1;
                if ( rf_local_fpgun_player )
                {
                  for ( n = 0; n < 32; ++n )
                  {
                    if ( v14 == *(_DWORD *)(rf_local_fpgun_player + 4 * n + 4436) )
                    {
                      v15 = (n + 1) % 32;
                      v16 = n;
                      break;
                    }
                  }
                  if ( v15 != -1 )
                  {
                    for ( ii = 0; ii < 32; ++ii )
                    {
                      if ( rf_weapon_cycle_slots_weapon_index[4 * ii] == *(_DWORD *)(rf_local_fpgun_player
                                                                                   + 4 * v15
                                                                                   + 4436) )
                      {
                        v23 = ii;
                        break;
                      }
                    }
                  }
                }
                v11 = rf_weapon_cycle_slots_category[4 * v13];
                do
                {
                  if ( rf_player_cycle_candidate_is_usable(a1, v23, v11, a2) )
                    break;
                  v4 = (v15 + 1) % 32;
                  v15 = v4;
                  if ( a2 == -1 && v4 < v16 )
                    v11 = (v11 + 1) % 4;
                  v16 = v4;
                  for ( jj = 0; jj < 32; ++jj )
                  {
                    if ( rf_weapon_cycle_slots_weapon_index[4 * jj] == *(_DWORD *)(rf_local_fpgun_player + 4 * v4 + 4436) )
                    {
                      v23 = jj;
                      break;
                    }
                  }
                }
                while ( v23 != v13 || v11 != rf_weapon_cycle_slots_category[4 * v23] );
                if ( v23 == -1 || rf_weapon_cycle_slots_weapon_index[4 * v23] == v14 )
                {
                  LOBYTE(v3) = rf_player_has_flags16_mask10(a1);
                  if ( (_BYTE)v3 )
                    LOBYTE(v3) = rf_gamesound_play_event(2, 0, 0.0, 1.0);
                }
                else
                {
                  LOBYTE(v3) = v23;
                  rf_weapon_selector_current_cycle_slot = v23;
                  if ( a3 )
                    LOBYTE(v3) = rf_gamesound_play_event(rf_weapon_selector_scroll_sound_event, 0, 0.0, 1.0);
                }
              }
              else
              {
                rf_weapon_selector_is_open = 1;
                rf_weapon_selector_current_cycle_slot = v13;
                if ( a2 == -1 )
                  rf_player_cycle_weapon_next(a1, -1, 0);
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

