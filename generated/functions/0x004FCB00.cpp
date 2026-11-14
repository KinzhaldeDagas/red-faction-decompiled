// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FCB00 rf_event_fire_weapon_no_anim_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type79 Fire_Weapon_No_Anim. Resolve special record identifier8359 once before target traversal. For each entity target build projectile origin from entity position+0x3C and orientation+0x48; if special record resolves, aim toward its position with Y+0.2. Apply cone sampling based on1.5-degree literal, then directly call rf_projectile_create_runtime(entity weapon+0x2A4,entity id,origin,orientation,0,0). Only nonzero projectile result triggers Foley selection from projectile descriptor+0x160 or conditional+0x168, positional playback, optional elapsed deadline entity+0x136C rearmed50ms, and configured shell ejection. No ammo decrement, body-action request or standard firing-cooldown admission directly in this handler; downstream creation semantics remain separate.
int __cdecl rf_event_fire_weapon_no_anim_apply(int a1)
{
  int result; // eax
  int *v2; // eax
  float v3[3]; // [esp-4h] [ebp-90h] BYREF
  float v4; // [esp+8h] [ebp-84h]
  float v5; // [esp+Ch] [ebp-80h]
  float copy_result[3]; // [esp+14h] [ebp-78h] BYREF
  int v7; // [esp+20h] [ebp-6Ch]
  float v8[3]; // [esp+24h] [ebp-68h] BYREF
  float lhs; // [esp+30h] [ebp-5Ch] BYREF
  float v10; // [esp+34h] [ebp-58h]
  float out_vector[3]; // [esp+3Ch] [ebp-50h] BYREF
  int runtime; // [esp+48h] [ebp-44h]
  float v13; // [esp+4Ch] [ebp-40h]
  float v14[6]; // [esp+50h] [ebp-3Ch] BYREF
  float v15[3]; // [esp+68h] [ebp-24h] BYREF
  float *v16; // [esp+74h] [ebp-18h]
  float rhs[3]; // [esp+78h] [ebp-14h] BYREF
  int v18; // [esp+84h] [ebp-8h]
  int i; // [esp+88h] [ebp-4h]

  rf_vector3_default_construct_noop(rhs);
  rf_matrix3_construct((char *)v14);
  v18 = rf_object_find_by_saved_identifier(8359);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v16 = (float *)rf_entity_resolve_handle(*v2);
    if ( v16 )
    {
      v13 = 1.5;
      rf_vector_copy(rhs, copy_result, v16 + 15);
      rf_matrix3_copy(v14, v16 + 18);
      if ( v18 )
      {
        rf_vector3_copy_return_destination(&lhs, (float *)(v18 + 60));
        v10 = v10 + 0.2000000029802322;
        rf_vector_subtract(&lhs, out_vector, rhs);
        rf_vector_normalize_reciprocal_sqrt(out_vector);
        rf_orientation_matrix_from_normalized_direction(v14, out_vector);
      }
      if ( v13 > 0.0 )
      {
        rf_vector3_default_construct_noop(v8);
        rf_vector_normalize_reciprocal_sqrt(v15);
        v5 = v13 * 3.141592741012573 / 180.0;
        v4 = rf_cos_float(v5);
        rf_vector3_copy_return_destination(v3, v15);
        rf_random_unit_vector_in_cone(v8, v3[0], v3[1], v3[2], v4);
        rf_orientation_matrix_from_normalized_direction(v14, v8);
      }
      runtime = rf_projectile_create_runtime(*((_DWORD *)v16 + 169), *((_DWORD *)v16 + 11), (int)rhs, (int)v14, 0, 0);
      if ( runtime )
      {
        v7 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(runtime + 660) + 352));
        if ( rf_entity_custom_mask142C_has_index((int)v16, *(_DWORD *)(runtime + 664))
          && *(_DWORD *)(*(_DWORD *)(runtime + 660) + 360) != -1 )
        {
          v7 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(runtime + 660) + 360));
        }
        rf_gamesound_play_positional_event(v7, rhs, 1.0, (int)flt_17F10B0, 0);
        if ( rf_replicator_has_elapsed((int *)v16 + 1243) )
          rf_replicator_arm_milliseconds((int *)v16 + 1243, 50);
        if ( rf_rf_string_not_equals_cstring_case_insensitive(*(_DWORD *)(runtime + 660) + 1208, (char *)&byte_63D983) )
          rf_weapon_present_shell_ejection(v16);
      }
    }
  }
  return result;
}

