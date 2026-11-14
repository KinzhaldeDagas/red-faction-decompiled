// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BAD10 rf_damage_apply_radial_to_target
// UNREALRED VERIFIED [weapon-impact-decode]: Applies per-target radial damage with the linear factor 1 - distance / radius.
// UNREALRED VERIFIED [combat-pool-and-radius-20260923]: Ordinary non-special-target branch computes the length of (target common +0xE4 minus explosion origin), stores float distance and float alpha=1-distance/radius, and dispatches only positive alpha. The LOS query also uses target +0xE4. This annotation does not assign unverified source-to-UE center mapping or change the separate special-target branch.
// UNREALRED VERIFIED [radial-geometry-occlusion-20260924]: Radial LOS and distance/falloff read current physics position common+0xE4 (0x4BAD39 and 0x4BAD63); the separate response direction reads published position +0x3C at 0x4BAE9C. Setter 0x4BC330 copies the same input point to +0x3C/+0xE4/+0xF0, while physics commit 0x4D52B0 copies predicted +0xF0 to +0xE4. This is not a visual-bounds midpoint field. Obstruction call 0x4D0220 with mask 5 queries serialized type-9 solids and world faces, not intervening character/clutter/projectile objects.
void __cdecl rf_damage_apply_radial_to_target(int a1, float *center_a, float a3, float radius_a, int a5, int a6)
{
  int first_dword; // eax
  char v7; // al
  char v8; // al
  float v9; // [esp+1Ch] [ebp-40h]
  int local_player_entry_or_related_owner; // [esp+20h] [ebp-3Ch]
  int v11[2]; // [esp+24h] [ebp-38h] BYREF
  float v12[3]; // [esp+2Ch] [ebp-30h] BYREF
  float v13; // [esp+38h] [ebp-24h]
  int v14; // [esp+3Ch] [ebp-20h]
  int v15; // [esp+40h] [ebp-1Ch]
  int v16; // [esp+44h] [ebp-18h]
  float v17; // [esp+48h] [ebp-14h]
  float out_vector[3]; // [esp+4Ch] [ebp-10h] BYREF
  float v19; // [esp+58h] [ebp-4h]

  if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority)
    && !rf_geometry_segment_is_obstructed((int)center_a, a1 + 228, 5, 0) )
  {
    rf_vector_subtract((const float *)(a1 + 228), out_vector, center_a);
    v16 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 44));
    if ( v16 && rf_entity_class_flag2000000_positive_scalar56(v16) )
    {
      if ( rf_spheres_overlap_strict(center_a, (const float *)(v16 + 60), radius_a, 1.0) == 1 )
      {
        if ( (*(_DWORD *)(v16 + 124) & 4) == 0 )
        {
          v17 = rf_vector3_length(out_vector);
          v19 = 1.0 - v17 / radius_a;
          *(float *)(v16 + 56) = *(float *)(v16 + 56) - v19 * a3;
          if ( *(float *)(v16 + 56) <= 0.0 )
            rf_entity_restore_saved_class_motion_and_clear_source(v16, 1);
        }
        first_dword = rf_receiver_get_first_dword((void *)v16);
        rf_vclip_spawn_runtime_effect(unk_681E74, first_dword, v16 + 60, v16 + 60, 1.0, -1, (int)out_vector, 1);
      }
    }
    else
    {
      v17 = rf_vector3_length(out_vector);
      v19 = 1.0 - v17 / radius_a;
      if ( v19 > 0.0 )
      {
        v13 = a3 * v19;
        rf_vector_subtract((const float *)(a1 + 60), v12, center_a);
        if ( rf_entity_has_player_pointer_if_type0(a1) )
        {
          v7 = rf_player_direction_to_local_quadrant_mask(*(_DWORD *)(a1 + 5168), v12);
          rf_player_or_direction_nibble_into_flags(*(_DWORD *)(a1 + 5168), v7);
          v11[1] = a1;
          *(float *)v11 = v13 / 50.0;
          rf_float_clamp_in_place((float *)v11, 0.0, 1.0);
        }
        else if ( rf_entity_matches_local_player_or_related_handle(a1) )
        {
          local_player_entry_or_related_owner = rf_object_find_local_player_entry_or_related_owner(a1);
          v8 = rf_player_direction_to_local_quadrant_mask(local_player_entry_or_related_owner, v12);
          rf_player_or_direction_nibble_into_flags(local_player_entry_or_related_owner, v8);
        }
        v14 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 44));
        if ( v14 && *(float *)(v14 + 52) > 0.0 && rf_entity_admits_speech_body_actions(v14) )
        {
          if ( rf_vector_dot(out_vector, (float *)(v14 + 276)) <= 0.0 )
            *(_DWORD *)(v14 + 2084) = 7;
          else
            *(_DWORD *)(v14 + 2084) = 6;
        }
        v15 = rf_entity_resolve_handle(a5);
        if ( rf_multiplayer_runtime_mode == 1
          && rf_multiplayer_server_authority == 1
          && v15
          && (*(_DWORD *)(v15 + 2068) & 0x20000) != 0 )
        {
          v9 = v13 * flt_662DC0;
          rf_damage_dispatch(*(_DWORD *)(a1 + 44), v9, a5, -1, a6, 0, -1, 0);
        }
        else
        {
          rf_damage_dispatch(*(_DWORD *)(a1 + 44), v13, a5, -1, a6, 0, -1, 0);
        }
      }
    }
  }
}

