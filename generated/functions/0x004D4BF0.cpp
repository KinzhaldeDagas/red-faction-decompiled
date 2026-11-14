// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D4BF0 rf_fall_damage_apply_from_contact_speed
// UNREALRED VERIFIED [respawn-surrounding]: Converts inward contact speed in RF meters/second to raw fall damage: excess=max(speed-7,0); one material/class branch halves excess; damage=excess^2; vehicle classification doubles damage; results below 10 become zero. Eligible local multiplayer clients send packet 49; authority and standalone dispatch ordinary damage type 9 directly.
void __cdecl rf_fall_damage_apply_from_contact_speed(int a1, float a2)
{
  char v2; // al
  float *v3; // eax
  char v4; // al
  char v5[4]; // [esp+0h] [ebp-44h] BYREF
  int v6; // [esp+4h] [ebp-40h]
  int v7; // [esp+8h] [ebp-3Ch]
  int *p_sound_by_index; // [esp+Ch] [ebp-38h]
  int v9; // [esp+10h] [ebp-34h]
  float v10; // [esp+14h] [ebp-30h]
  float v11; // [esp+18h] [ebp-2Ch]
  float v12; // [esp+1Ch] [ebp-28h]
  float v13[4]; // [esp+20h] [ebp-24h] BYREF
  int v14; // [esp+30h] [ebp-14h] BYREF
  int local_player_entry_or_related_owner; // [esp+34h] [ebp-10h]
  int sound_by_index; // [esp+38h] [ebp-Ch] BYREF
  float v17; // [esp+3Ch] [ebp-8h]
  float v18; // [esp+40h] [ebp-4h]

  v18 = 7.0;
  v12 = a2 - (float)7.0;
  v17 = rf_float_maximum_two_values(v12, 0.0);
  if ( !rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)a1) && *(_DWORD *)(a1 + 464) == 3 )
    v17 = v17 * 0.5;
  v17 = v17 * v17;
  if ( rf_object_is_use_vehicle((_DWORD *)a1) )
    v17 = v17 + v17;
  if ( v17 < 10.0 )
    v17 = 0.0;
  if ( v17 > 0.0 && (*(_DWORD *)(a1 + 124) & 4) == 0 )
  {
    rf_push_region_flag40_contains_point((float *)(a1 + 60));
    if ( !v2 )
    {
      if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority && a1 == dword_681E38 )
        rf_client_send_fall_damage_packet_49(v17);
      else
        rf_damage_dispatch(*(_DWORD *)(a1 + 44), v17, -1, -1, 9, 0, -1, 0);
      if ( *(float *)(a1 + 52) >= 0.0 )
      {
        local_player_entry_or_related_owner = rf_object_find_local_player_entry_or_related_owner(a1);
        if ( local_player_entry_or_related_owner )
        {
          v3 = rf_vector3_set_components_return_destination(v13, 0.0, 0.0, 0.0);
          v4 = rf_player_direction_to_local_quadrant_mask(local_player_entry_or_related_owner, v3);
          rf_player_or_direction_nibble_into_flags(local_player_entry_or_related_owner, v4);
          rf_entity_set_player_linked_perturbation_timer(
            *(_DWORD *)(local_player_entry_or_related_owner + 196),
            0.0049999999,
            0.60000002);
          *(float *)&v14 = v17 / 50.0;
          rf_float_clamp_in_place((float *)&v14, 0.0, 1.0);
        }
      }
      else
      {
        sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 296), 0);
        v11 = 0.0;
        v10 = 1.0;
        v9 = 0;
        p_sound_by_index = &sound_by_index;
        rf_vector3_copy_return_destination((float *)v5, (float *)(a1 + 228));
        rf_sound_list_select_play_return_asset(a1, *(float *)v5, v6, v7, (int)p_sound_by_index, v9, v10, v11);
      }
    }
  }
}

