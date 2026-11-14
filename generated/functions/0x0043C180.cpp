// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C180 rf_character_classify_weapon_hit_region
// UNREALRED VERIFIED [combat-named-sphere-binding-20261112]: Consumed hit-region selector reads standing modelclass+CEC40-byte record radius+0 for distance/radius and activefactor+4 for returned damage. BothSP andMP branches query LIVE named model center through modelhandle128 plus physicalpositionE4/matrixFC; MPbboxmetric doesnot read radius. Name-aware class override binding therefore affects actual combat damage, not merely physics metadata. Render/bind/UEframe host adapters remain separate parity gaps.
double __cdecl rf_character_classify_weapon_hit_region(int a1, int a2, float *a3, int *a4)
{
  int first_dword; // eax
  int v6; // eax
  float v7; // [esp+0h] [ebp-2Ch]
  float v8; // [esp+4h] [ebp-28h]
  float v9; // [esp+8h] [ebp-24h]
  float v10; // [esp+8h] [ebp-24h]
  float v11; // [esp+Ch] [ebp-20h]
  float v12; // [esp+10h] [ebp-1Ch]
  float v13; // [esp+14h] [ebp-18h]
  float v14[3]; // [esp+18h] [ebp-14h] BYREF
  bool v15; // [esp+27h] [ebp-5h]
  int i; // [esp+28h] [ebp-4h]

  if ( !rf_entity_has_humanoid_flag(a1)
    || rf_object_has_player_flag(a1) && !rf_object_handle_has_direct_player_flag(*(_DWORD *)(a2 + 48)) )
  {
    return 1.0;
  }
  v13 = 1.0;
  rf_vector3_default_construct_noop(v14);
  v15 = (*(_DWORD *)(*(_DWORD *)(a2 + 660) + 616) & 0x400) != 0;
  if ( rf_multiplayer_runtime_mode && rf_multiplayer_bbox_hit_regions_enabled && !v15 )
  {
    v11 = 3.4028235e38;
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)(a1 + 668) + 3308));
      if ( i >= first_dword )
        break;
      if ( i || !rf_entity_is_crouched_state810(a1) )
      {
        rf_model_handle_get_named_sphere_world_center(*(_DWORD *)(a1 + 128), i, v14, a1 + 228, (float *)(a1 + 252));
        v7 = fabs(v14[1] - a3[1]);
        v12 = v7;
        if ( i == 2 )
          v12 = v7 * 4.5;
        if ( v11 > (double)v12 )
        {
          v13 = *(float *)(rf_inline_array40_get_element_address((void *)(*(_DWORD *)(a1 + 668) + 3308), i) + 4);
          *a4 = i;
          v11 = v12;
        }
      }
    }
  }
  else
  {
    *a4 = -1;
    v8 = 3.4028235e38;
    for ( i = 0; ; ++i )
    {
      v6 = rf_receiver_get_first_dword((void *)(*(_DWORD *)(a1 + 668) + 3308));
      if ( i >= v6 )
        break;
      rf_model_handle_get_named_sphere_world_center(*(_DWORD *)(a1 + 128), i, v14, a1 + 228, (float *)(a1 + 252));
      v9 = rf_vector_distance(v14, a3);
      v10 = v9 / *(float *)rf_inline_array40_get_element_address((void *)(*(_DWORD *)(a1 + 668) + 3308), i);
      if ( v8 > (double)v10 )
      {
        v13 = *(float *)(rf_inline_array40_get_element_address((void *)(*(_DWORD *)(a1 + 668) + 3308), i) + 4);
        *a4 = i;
        v8 = v10;
      }
    }
  }
  return v13;
}

