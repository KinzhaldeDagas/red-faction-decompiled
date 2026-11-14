// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D9960 sub_4D9960
// UNREALRED VERIFIED [combat-selected-drop-item-20261111]: Ground-support contact branch: resolved supportobject sets common+1A8 bit400000 and common+8AC handle; worldsolid/noobject contact clearsboth. Type3 enabledphysics has a separate diversion. Miss/fall paths do not establish a universal clearbit assumption;4356E0 changesfallstate/flag1 rather than clearing400000. Host floor provider must reject unknown/mover/airborne states instead of inventingnativebit0.
// [UnrealRed physical spheres 2026-11-12; verified ASM] Real support/snap owner: lowest physical24 Y record into scratch shape, outerradius abs(lowY)+radius, identity orientation, world/mover4D13C0 sweep plus optional player pair registry; updates support/fall/position. Not a bounds-only routine and no universal clear/support assumption is justified.
unsigned __int8 __cdecl sub_4D9960(int a1)
{
  int first_dword; // eax
  int element_address_unchecked; // eax
  float *v3; // eax
  double v4; // st7
  unsigned __int8 result; // al
  int v6; // ecx
  float *v7; // eax
  int v8; // ecx
  float *v9; // eax
  int v10; // edx
  float v11[4]; // [esp-10h] [ebp-124h] BYREF
  int v12; // [esp+0h] [ebp-114h]
  int v13; // [esp+4h] [ebp-110h]
  float v14; // [esp+Ch] [ebp-108h]
  float v15; // [esp+10h] [ebp-104h]
  float v16; // [esp+14h] [ebp-100h]
  int v17; // [esp+18h] [ebp-FCh] BYREF
  float v18[3]; // [esp+1Ch] [ebp-F8h] BYREF
  int v19[3]; // [esp+28h] [ebp-ECh] BYREF
  float v20[3]; // [esp+34h] [ebp-E0h] BYREF
  int v21[3]; // [esp+40h] [ebp-D4h] BYREF
  float v22[3]; // [esp+4Ch] [ebp-C8h] BYREF
  float v23[3]; // [esp+58h] [ebp-BCh] BYREF
  float v24[3]; // [esp+64h] [ebp-B0h] BYREF
  float copy_result[4]; // [esp+70h] [ebp-A4h] BYREF
  int v26; // [esp+80h] [ebp-94h]
  float v27; // [esp+84h] [ebp-90h]
  float v28[3]; // [esp+88h] [ebp-8Ch] BYREF
  float v29[3]; // [esp+94h] [ebp-80h] BYREF
  float v30; // [esp+A0h] [ebp-74h]
  int v31; // [esp+A4h] [ebp-70h]
  float v32; // [esp+B0h] [ebp-64h]
  int v33; // [esp+B8h] [ebp-5Ch]
  int v34; // [esp+C0h] [ebp-54h]
  int v35; // [esp+C4h] [ebp-50h]
  float v36; // [esp+D4h] [ebp-40h] BYREF
  float v37; // [esp+D8h] [ebp-3Ch]
  float v38; // [esp+E0h] [ebp-34h]
  float destination; // [esp+ECh] [ebp-28h] BYREF
  float v40; // [esp+F0h] [ebp-24h]
  int i; // [esp+F8h] [ebp-1Ch]
  float v42; // [esp+FCh] [ebp-18h] BYREF
  float v43; // [esp+100h] [ebp-14h]
  int v44; // [esp+110h] [ebp-4h]

  rf_vector3_default_construct_noop(&destination);
  rf_vector3_default_construct_noop(&v42);
  rf_physics_hit_record_construct_noop((char *)v28);
  if ( (dword_87C0F8[0] & 1) == 0 )
  {
    dword_87C0F8[0] |= 1u;
    v44 = 0;
    rf_physics_state_construct_empty_sphere_collection(byte_87BF88);
    atexit(rf_static_cleanup_0087bf88);
    v44 = -1;
  }
  rf_vector_prefix_construct_noop(&v36);
  rf_pointer_array_clear_count_keep_storage(dword_87C084);
  v37 = 3.4028235e38;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a1 + 388));
    if ( i >= first_dword )
      break;
    element_address_unchecked = rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
    if ( v37 > (double)*(float *)(element_address_unchecked + 4) )
    {
      v3 = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
      rf_record24_copy_six_floats(&v36, v3);
    }
  }
  LODWORD(copy_result[3]) = v11;
  rf_record24_copy_construct_six_floats(v11, &v36);
  rf_array24_append_record_by_value(
    dword_87C084,
    v11[0],
    SLODWORD(v11[1]),
    SLODWORD(v11[2]),
    SLODWORD(v11[3]),
    v12,
    v13);
  v16 = fabs(v37);
  unk_87C080 = v16 + v38;
  rf_identity_orientation_matrix(flt_87BFFC);
  unk_87C0AC = *(_DWORD *)(a1 + 428);
  unk_87C0AC &= ~0x1000u;
  rf_vector_copy(&destination, copy_result, (const float *)(a1 + 240));
  v40 = v40 + 0.05000000074505806;
  if ( *(float *)(a1 + 2212) > 0.0 )
    v40 = *(float *)(a1 + 2212) * rf_frame_delta_seconds + v40;
  rf_vector_copy(&v42, v24, (const float *)(a1 + 240));
  if ( rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)a1) )
    v4 = v43 - 0.1000000014901161;
  else
    v4 = v43 - (*(float *)(*(_DWORD *)(a1 + 660) + 80) * rf_frame_delta_seconds + 0.05000000074505806);
  v43 = v4;
  rf_segment_bounds_build(flt_87C090, flt_87C09C, &destination, &v42);
  rf_vector3_subtract_scalar_in_place(flt_87C090, unk_87C080);
  rf_vector3_add_scalar_in_place(flt_87C09C, unk_87C080);
  v30 = 1.0;
  v34 = 0;
  if ( rf_object_has_player_flag(a1) )
    rf_physics_pair_registry_sweep_subject_segment(a1, &destination, &v42, (int)v28, 0);
  rf_physics_shape_sweep_movers_and_static_world(&destination, &v42, (int)byte_87BF88, v28);
  if ( v30 >= 1.0 )
  {
    result = rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)a1);
    if ( !result )
      return (unsigned __int8)rf_entity_select_fall_movement_descriptor((_DWORD *)a1);
  }
  else
  {
    v27 = rf_vector_dot(v29, &flt_87BF48);
    if ( v27 < 0.5 )
    {
      result = rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)a1);
      if ( !result )
        return (unsigned __int8)rf_entity_select_fall_movement_descriptor((_DWORD *)a1);
    }
    else
    {
      v26 = rf_object_resolve_handle(v33);
      if ( v26 )
      {
        if ( *(_DWORD *)(v26 + 36) == 3 && rf_physics_state_is_enabled(v26 + 136) )
        {
          result = rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)a1);
          if ( !result )
            return (unsigned __int8)rf_entity_select_fall_movement_descriptor((_DWORD *)a1);
          return result;
        }
        *(_DWORD *)(a1 + 424) |= 0x400000u;
        *(_DWORD *)(a1 + 2220) = *(_DWORD *)(v26 + 44);
        if ( v32 <= 0.0 )
        {
          v15 = (v43 - v40) * v30 + v40 + 0.05000000074505806;
          v12 = a1;
          *(float *)(a1 + 244) = rf_float_minimum_two_values(*(float *)(a1 + 244), v15);
        }
        else
        {
          *(float *)(a1 + 244) = (v43 - v40) * v30 + v40 + 0.05000000074505806;
        }
      }
      else
      {
        *(_DWORD *)(a1 + 424) &= ~0x400000u;
        *(_DWORD *)(a1 + 2220) = 0;
        v14 = (v43 - v40) * v30 + v40 + 0.05000000074505806;
        v12 = a1;
        *(float *)(a1 + 244) = rf_float_minimum_two_values(*(float *)(a1 + 244), v14);
      }
      rf_physics_hit_record68_copy_fields((float *)(a1 + 436), v28);
      rf_vector_copy((float *)(a1 + 228), v23, (const float *)(a1 + 240));
      rf_vector_copy((float *)(a1 + 60), v22, (const float *)(a1 + 228));
      v13 = v6;
      v7 = rf_vector3_subtract_scalar_from_components((float *)(a1 + 228), (float *)v21, *(float *)(a1 + 384));
      rf_vector_copy((float *)(a1 + 400), v20, v7);
      v13 = v8;
      v9 = rf_vector3_add_scalar_to_components((float *)(a1 + 228), (float *)v19, *(float *)(a1 + 384));
      rf_vector_copy((float *)(a1 + 412), v18, v9);
      *(_DWORD *)(a1 + 4992) = v31;
      result = rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)a1);
      if ( result )
      {
        *(float *)&v13 = -rf_vector_dot((float *)(a1 + 324), v29);
        rf_fall_damage_apply_from_contact_speed(a1, *(float *)&v13);
        v13 = a1 + 240;
        result = rf_entity_apply_landing_sound_and_motion_reset(a1);
      }
      if ( v35 && v33 <= -1 )
      {
        v10 = *rf_world_face_sample_lightmap_rgb555((_DWORD *)rf_world_solid, &v17, v35, (int)v28);
        result = a1;
        *(_DWORD *)(a1 + 5236) = v10;
      }
    }
  }
  return result;
}

