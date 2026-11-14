// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040C7F0 rf_ai_try_drop_carried_corpse
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): Cdecl(required AI block,LOWBYTE force). Resolves carried handle+1212 type7; miss clears handle=-1 and returnsAL0. Valid corpse with force byte0
// requires40CBF0(block) nonzero AL; failure returns0 preserving carry state. Any nonzero force bypasses ONLY this clearance predicate. Builds orientation from NEGATED source common
// forward row+96; copies matrix to corpse+252/+72, not+288. Drop position uses source PHYSICS position+228 +1.5*physics forward row+276, then raises Y byDOUBLE0.5 with float32 store,
// and publishes corpse position/bounds. If corpse DWORD+668 mask0x20 clear: only when sphere-array count at+388==EXACT3, computes running minimum radius starting99 (ordered strict
// decreases only), writes each24-byte entry radius+12 to minimum; centers become(0,0,min-1),(0,0,0),(0,0,1-min); corpse radius+384 and FLOAT+120 become float32(min+1). Sets mask0x20
// even when count!=3; publication happened BEFORE radius changes, with no second bounds rebuild here. Requests flag-only reactivation, sets corpse velocity+324=(0,1,0). If corpse
// track DWORD+700!=-1, resets model cyclic/actions, starts VFX(model,track,1.0,1), then copies raw track DWORD+700 to+696. Room query uses ECX=world,
// stack(NULL,corpse+60,corpse+60,0); null room falls back to source cached room getter; sets corpse room/cache. Clears corpse inactive common mask0x4000, clears carried handle,
// selects source speed request1. If no player pointer OR player flags+16 mask0x40 clear: source==global681E38 arms entity+1300 with500ms, otherwise calls436750 unholster helper.
// Player-flag sources additionally arm block+1208 with550ms. Returns explicitAL1. No own multiplayer gate, force-mode extra validation, corpse destruction or full-body collision
// sweep.
char __cdecl rf_ai_try_drop_carried_corpse(int *a1, char a2)
{
  float *v3; // eax
  float *v4; // eax
  int first_dword; // eax
  int element_address_unchecked; // eax
  int v7; // eax
  float *v8; // eax
  int v9; // eax
  float *v10; // eax
  int v11; // eax
  float *v12; // eax
  float v13; // [esp+Ch] [ebp-64h]
  float v14; // [esp+10h] [ebp-60h]
  float scaled_result[3]; // [esp+14h] [ebp-5Ch] BYREF
  float v16[3]; // [esp+20h] [ebp-50h] BYREF
  float v17; // [esp+2Ch] [ebp-44h]
  void *v18; // [esp+30h] [ebp-40h]
  bool v19; // [esp+37h] [ebp-39h]
  float v20[9]; // [esp+38h] [ebp-38h] BYREF
  int i; // [esp+5Ch] [ebp-14h]
  float *v22; // [esp+60h] [ebp-10h]
  float sum_result; // [esp+64h] [ebp-Ch] BYREF
  float v24; // [esp+68h] [ebp-8h]

  v22 = (float *)rf_corpse_resolve_handle_type7(a1[303]);
  if ( v22 )
  {
    if ( a2 || rf_ai_carried_corpse_drop_clearance(a1) )
    {
      rf_matrix3_construct((char *)v20);
      v3 = rf_vector_negate((float *)(*a1 + 96), v16);
      rf_orientation_matrix_from_normalized_direction(v20, v3);
      rf_matrix3_copy(v22 + 63, v20);
      rf_matrix3_copy(v22 + 18, v20);
      v4 = rf_vector_multiply_scalar((const float *)(*a1 + 276), scaled_result, 1.5);
      rf_vector_add((const float *)(*a1 + 228), &sum_result, v4);
      v24 = v24 + 0.5;
      rf_object_publish_position_and_bounds((int)v22, &sum_result);
      if ( ((_DWORD)v22[167] & 0x20) == 0 )
      {
        if ( rf_receiver_get_first_dword(v22 + 97) == 3 )
        {
          v17 = 99.0;
          for ( i = 0; ; ++i )
          {
            first_dword = rf_receiver_get_first_dword(v22 + 97);
            if ( i >= first_dword )
              break;
            element_address_unchecked = rf_array24_get_element_address_unchecked((_DWORD *)v22 + 97, i);
            if ( v17 > (double)*(float *)(element_address_unchecked + 12) )
              v17 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)v22 + 97, i) + 12);
          }
          v7 = rf_array24_get_element_address_unchecked((_DWORD *)v22 + 97, 0);
          *(float *)(v7 + 12) = v17;
          v14 = v17 + -1.0;
          v8 = (float *)rf_array24_get_element_address_unchecked((_DWORD *)v22 + 97, 0);
          rf_vector3_set_components_thiscall(v8, 0.0, 0.0, v14);
          v9 = rf_array24_get_element_address_unchecked((_DWORD *)v22 + 97, 1);
          *(float *)(v9 + 12) = v17;
          v10 = (float *)rf_array24_get_element_address_unchecked((_DWORD *)v22 + 97, 1);
          rf_vector3_zero_return_destination(v10);
          v11 = rf_array24_get_element_address_unchecked((_DWORD *)v22 + 97, 2);
          *(float *)(v11 + 12) = v17;
          v13 = 1.0 - v17;
          v12 = (float *)rf_array24_get_element_address_unchecked((_DWORD *)v22 + 97, 2);
          rf_vector3_set_components_thiscall(v12, 0.0, 0.0, v13);
          v22[96] = v17 + 1.0;
          v22[30] = v22[96];
        }
        *((_DWORD *)v22 + 167) |= 0x20u;
      }
      rf_object_request_physics_reactivation_flags((int)v22);
      rf_vector3_set_components_thiscall(v22 + 81, 0.0, 1.0, 0.0);
      if ( *((_DWORD *)v22 + 175) != -1 )
      {
        rf_model_handle_reset_cyclic_adapter(*((_DWORD *)v22 + 32));
        rf_model_handle_reset_actions_adapter(*((_DWORD *)v22 + 32));
        rf_vfx_start_instance(*((int **)v22 + 32), *((_DWORD *)v22 + 175), 1.0, 1);
        v22[174] = v22[175];
      }
      v18 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v22 + 15, v22 + 15, 0);
      if ( !v18 )
        v18 = (void *)rf_receiver_get_first_dword((void *)*a1);
      rf_object_set_room_and_cache_position(v22, (int)v18);
      *((_DWORD *)v22 + 31) &= ~0x4000u;
      a1[303] = -1;
      sub_4344D0(*a1, 1);
      v19 = 1;
      if ( *(_DWORD *)(*a1 + 5168) )
        v19 = (*(_DWORD *)(*(_DWORD *)(*a1 + 5168) + 16) & 0x40) == 0;
      if ( v19 )
      {
        if ( *a1 == dword_681E38 )
          rf_replicator_arm_milliseconds((int *)(dword_681E38 + 1300), 500);
        else
          rf_entity_clear_holster_if_mapped_weapon_owned((_DWORD *)*a1);
      }
      if ( rf_object_has_player_flag(*a1) )
        rf_replicator_arm_milliseconds(a1 + 302, 550);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    a1[303] = -1;
    return 0;
  }
}

