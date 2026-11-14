// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004905B0 sub_4905B0
// UNREALRED VERIFIED [piercing-contact-decode]: Separate piercing-contact visitor; applies hit factor, damage, death/flinch override, and returns whether traversal continues. Broader function semantics remain unnamed.
int __cdecl sub_4905B0(int a1, float *a2)
{
  char v3; // al
  float v4[3]; // [esp+24h] [ebp-78h] BYREF
  float v5[3]; // [esp+30h] [ebp-6Ch] BYREF
  float v6[3]; // [esp+3Ch] [ebp-60h] BYREF
  float copy_result[3]; // [esp+48h] [ebp-54h] BYREF
  int v9; // [esp+58h] [ebp-44h]
  bool v10; // [esp+5Fh] [ebp-3Dh]
  float v11[2]; // [esp+60h] [ebp-3Ch] BYREF
  float v12; // [esp+68h] [ebp-34h]
  int v13; // [esp+6Ch] [ebp-30h]
  const float *v14; // [esp+70h] [ebp-2Ch]
  float selected_damage_with_owner_scale; // [esp+74h] [ebp-28h] BYREF
  int v16; // [esp+78h] [ebp-24h]
  int v17; // [esp+7Ch] [ebp-20h]
  char v18; // [esp+83h] [ebp-19h] BYREF
  float source[3]; // [esp+84h] [ebp-18h] BYREF
  _DWORD *v20; // [esp+90h] [ebp-Ch]
  int v21; // [esp+94h] [ebp-8h] BYREF
  int v22; // [esp+98h] [ebp-4h]

  v16 = rf_object_resolve_handle(*(_DWORD *)(a1 + 16));
  if ( !v16 )
    return 0;
  v17 = 0;
  v21 = -1;
  selected_damage_with_owner_scale = rf_projectile_get_selected_damage_with_owner_scale((int)a2, 0);
  if ( !*(_DWORD *)(v16 + 36) )
    selected_damage_with_owner_scale = rf_character_classify_weapon_hit_region(v16, (int)a2, (float *)a1, &v21)
                                     * selected_damage_with_owner_scale;
  rf_vector3_copy_return_destination(source, a2 + 15);
  if ( rf_projectile_apply_common_object_penetration((int)a2, (float *)a1, v16, &selected_damage_with_owner_scale, &v18)
    && !v18 )
  {
    v17 = 1;
  }
  rf_vector_copy(a2 + 15, copy_result, source);
  rf_vector_copy(a2 + 57, v6, source);
  rf_vector_copy(a2 + 60, v5, source);
  rf_vector_copy(a2 + 60, v4, source);
  v22 = rf_entity_resolve_handle(*((_DWORD *)a2 + 12));
  if ( v22 && (*(_DWORD *)(v22 + 2068) & 0x20000) != 0 )
    selected_damage_with_owner_scale = selected_damage_with_owner_scale * flt_662DC0;
  rf_damage_dispatch(
    *(_DWORD *)(v16 + 44),
    selected_damage_with_owner_scale,
    *((_DWORD *)a2 + 12),
    *((_DWORD *)a2 + 166),
    *(_DWORD *)(*((_DWORD *)a2 + 165) + 1324),
    a1,
    -1,
    0);
  if ( !*(_DWORD *)(v16 + 36) )
  {
    v14 = (const float *)v16;
    if ( !rf_entity_is_dead(v16) )
    {
      v10 = 0;
      v13 = *((_DWORD *)a2 + 166);
      if ( v13 == rf_weapon_id_rocket_launcher
        || v13 == rf_weapon_id_shoulder_cannon
        || v13 == rf_weapon_id_apc_rocket
        || v13 == rf_weapon_id_fighter_rocket
        || v13 == rf_weapon_id_heap
        || v13 == rf_weapon_id_shotgun )
      {
        if ( v13 == rf_weapon_id_shotgun )
        {
          v9 = rf_object_resolve_handle(*((_DWORD *)a2 + 12));
          if ( v9 && rf_vector_distance_squared((const float *)(v9 + 60), (const float *)(v16 + 60)) < 100.0 )
            v10 = 1;
        }
        else
        {
          v10 = 1;
        }
      }
      else
      {
        v10 = v13 == unk_911CE0;
      }
      rf_vector3_copy_return_destination(v11, (float *)a1);
      rf_vector_inverse_translate_rotate_in_place(v11, (int)(v14 + 15), (int)(v14 + 18));
      if ( v10 )
      {
        if ( rf_vector_dot(a2 + 24, (float *)v14 + 24) < 0.0 )
          *((_DWORD *)v14 + 521) = 7;
        else
          *((_DWORD *)v14 + 521) = 6;
      }
      else if ( v21 )
      {
        if ( v21 == 1 )
        {
          if ( v12 <= 0.0 )
          {
            *((_DWORD *)v14 + 522) = 25;
            *((_DWORD *)v14 + 521) = 11;
          }
          else
          {
            *((_DWORD *)v14 + 522) = 24;
            *((_DWORD *)v14 + 521) = 12;
          }
        }
        else if ( v21 == 2 )
        {
          *((_DWORD *)v14 + 521) = v12 <= 0.0 ? 8 : 9;
          if ( rf_entity_has_model1410_and_runtime_flag200000((int)v14) )
            rf_entity_spawn_class_tag_debris(v14, (int)a2);
        }
      }
      else if ( v11[0] <= 0.0 )
      {
        *((_DWORD *)v14 + 522) = 26;
        *((_DWORD *)v14 + 521) = 14;
      }
      else
      {
        *((_DWORD *)v14 + 522) = 27;
        *((_DWORD *)v14 + 521) = 15;
      }
    }
  }
  v20 = sub_4DD720(*(_DWORD *)(v16 + 44));
  if ( v20 )
  {
    v3 = rf_player_direction_to_local_quadrant_mask((int)v20, a2 + 24);
    *((_BYTE *)v20 + 4604) = v3;
    if ( v20 == (_DWORD *)rf_local_fpgun_player )
      rf_player_or_direction_nibble_into_flags((int)v20, *((_BYTE *)v20 + 4604));
  }
  return v17;
}

