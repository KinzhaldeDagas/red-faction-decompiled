// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7710 rf_object_apply_containing_push_region
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, push-region/GeoMod/use-selector/physics batch chains, original float constants and field widths and native
// signed/x87/stack/callback ABI): Cdecl one required common-object pointer. Physics flags DWORD+424 bit8 gates lookup of FIRST enabled containing push region using published
// position+60; no region or player-associated object with region flags+8 bit0x20 returns without applying. Resolves entity by full object handle+44. Region bit2 requires entity
// grounded descriptor predicate438010 (current index1 or5); nonentity instead requires object physics mask0x18000000. Direction is unchecked-normalized (physics position+228 minus
// region origin+12) when bit0x10, otherwise region vector+48. Strength starts FLOAT region+100; bit8 multiplies by squared radial distance/region FLOAT+60; ELSE bit4 multiplies
// by1-that ratio. Neither path takes square root, clamps falloff or checks zero divisor. Unless region bits1/2, multiply by float32 radius(+384)^2/mass(+152) only if that rounded
// factor is ordered<1. All strength assignments round to float32. Jitter nibble bits16..19 nonzero: perturb=float32(abs(float(nibble)/(150.0/frameDelta)*strength)); cone
// minimum-dot=float32(1-perturb) clamped[-1,1]; calls random-cone helper with direction BY VALUE12 bytes, not an incoming ST0 argument. Player-pointer association additionally
// forwards perturb and FLOAT0.05 via4123F0 using *(*(object+5168)+196). Region bit0x40 plus resolved entity overwrites entity velocity+324 with direction*strength and calls4356E0; if
// entity physics bit0x200000 was clear, plays event83 at entity physics position+228 using BY VALUE vector and eight four-byte stack slots total (entity,x,y,z,&83,0,1.0,0.0).
// Horizontal speed copies velocity and zeroes Y, then entity+5256 receives class FLOAT(+660)->+80 unless that class value is ordered strictly less than rounded horizontal length, in
// which case length+1; UNORDERED chooses class value. Sets entity physics bit0x200000. Otherwise resolved entity zeroes direction.Y for movement indices1/2, adds direction*strength
// to entity vector+2208, then fall/airborne predicate limits magnitude only on ordered strength<length, scaling by strength/length. Nonentity instead adds
// direction*strength*frameDelta to velocity+324, with separate float vector multiplies. Finally ORs original object physics bit0x80000000. No damage call, room-liquid test, role gate
// or independently constructed success return. Native body and corrected477D30 prototype require one stack argument, no incoming x87 value.
int __cdecl rf_object_apply_containing_push_region(int a1)
{
  int result; // eax
  const float *v2; // eax
  double v3; // st7
  double v4; // st7
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v9[3]; // [esp-10h] [ebp-DCh] BYREF
  int *v10; // [esp-4h] [ebp-D0h] BYREF
  int v11; // [esp+0h] [ebp-CCh]
  float v12; // [esp+4h] [ebp-C8h]
  float scalar; // [esp+8h] [ebp-C4h]
  float v14; // [esp+Ch] [ebp-C0h]
  __int64 v15; // [esp+10h] [ebp-BCh]
  float v16[3]; // [esp+18h] [ebp-B4h] BYREF
  float v17[3]; // [esp+24h] [ebp-A8h] BYREF
  float v18[4]; // [esp+30h] [ebp-9Ch] BYREF
  float v19[3]; // [esp+40h] [ebp-8Ch] BYREF
  float scaled_result[4]; // [esp+4Ch] [ebp-80h] BYREF
  float v21[3]; // [esp+5Ch] [ebp-70h] BYREF
  float copy_result[3]; // [esp+68h] [ebp-64h] BYREF
  _BYTE v23[12]; // [esp+74h] [ebp-58h] BYREF
  float v24; // [esp+80h] [ebp-4Ch]
  int v25; // [esp+84h] [ebp-48h] BYREF
  float v26; // [esp+88h] [ebp-44h]
  float v27[3]; // [esp+8Ch] [ebp-40h] BYREF
  float v28; // [esp+98h] [ebp-34h]
  float v29; // [esp+9Ch] [ebp-30h] BYREF
  float v30; // [esp+A0h] [ebp-2Ch]
  float v31; // [esp+A4h] [ebp-28h]
  float destination[3]; // [esp+A8h] [ebp-24h] BYREF
  int v33; // [esp+B4h] [ebp-18h]
  float out_vector[3]; // [esp+B8h] [ebp-14h] BYREF
  int v35; // [esp+C4h] [ebp-8h]
  float v36; // [esp+C8h] [ebp-4h]

  result = a1;
  if ( (*(_DWORD *)(a1 + 424) & 8) != 0 )
  {
    result = rf_push_region_find_containing_point((const float *)(a1 + 60));
    v35 = result;
    if ( result )
    {
      if ( !rf_object_is_player_associated(a1) || (result = *(_DWORD *)(v35 + 8) & 0x20) == 0 )
      {
        v33 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 44));
        result = v35;
        if ( (*(_DWORD *)(v35 + 8) & 2) != 0 )
        {
          if ( v33 )
          {
            result = sub_438010(v33);
            if ( !(_BYTE)result )
              return result;
          }
          else if ( (*(_DWORD *)(a1 + 424) & 0x18000000) == 0 )
          {
            return result;
          }
        }
        rf_vector3_default_construct_noop(destination);
        v36 = *(float *)(v35 + 100);
        rf_vector_subtract((const float *)(a1 + 228), out_vector, (const float *)(v35 + 12));
        if ( (*(_DWORD *)(v35 + 8) & 0x10) != 0 )
        {
          v2 = (const float *)rf_vector3_normalized_copy_unchecked(out_vector, (int)v23);
          rf_vector_copy(destination, copy_result, v2);
        }
        else
        {
          rf_vector_copy(destination, v21, (const float *)(v35 + 48));
        }
        if ( (*(_DWORD *)(v35 + 8) & 8) != 0 )
        {
          v3 = rf_vector_length_squared(out_vector);
          v36 = v3 / *(float *)(v35 + 60) * v36;
        }
        else if ( (*(_DWORD *)(v35 + 8) & 4) != 0 )
        {
          v4 = rf_vector_length_squared(out_vector);
          v36 = (1.0 - v4 / *(float *)(v35 + 60)) * v36;
        }
        if ( (*(_DWORD *)(v35 + 8) & 1) == 0 && (*(_DWORD *)(v35 + 8) & 2) == 0 )
        {
          v31 = *(float *)(a1 + 384) * *(float *)(a1 + 384) / *(float *)(a1 + 152);
          if ( v31 < 1.0 )
            v36 = v36 * v31;
        }
        if ( (*(_DWORD *)(v35 + 8) & 0xF0000) != 0 )
        {
          v15 = (*(_DWORD *)(v35 + 8) & 0xF0000u) >> 16;
          v28 = (float)v15;
          v14 = fabs(v28 / (150.0 / rf_frame_delta_seconds) * v36);
          v30 = v14;
          v29 = 1.0 - v14;
          rf_float_clamp_in_place(&v29, -1.0, 1.0);
          scalar = v29;
          rf_vector3_copy_return_destination((float *)&v10, destination);
          rf_random_unit_vector_in_cone(destination, *(float *)&v10, *(float *)&v11, v12, scalar);
          if ( rf_entity_has_player_pointer_if_type0(a1) )
          {
            scalar = 0.050000001;
            rf_entity_set_player_linked_perturbation_timer(*(_DWORD *)(*(_DWORD *)(a1 + 5168) + 196), v30, 0.050000001);
          }
        }
        if ( (*(_DWORD *)(v35 + 8) & 0x40) != 0 && v33 )
        {
          v5 = rf_vector_multiply_scalar(destination, scaled_result, v36);
          rf_vector_copy((float *)(v33 + 324), v19, v5);
          rf_entity_select_fall_movement_descriptor((_DWORD *)v33);
          if ( (*(_DWORD *)(v33 + 424) & 0x200000) == 0 )
          {
            v25 = 83;
            scalar = 0.0;
            v12 = 1.0;
            v11 = 0;
            v10 = &v25;
            rf_vector3_copy_return_destination(v9, (float *)(v33 + 228));
            rf_sound_list_select_play_return_asset(
              v33,
              v9[0],
              SLODWORD(v9[1]),
              SLODWORD(v9[2]),
              (int)v10,
              v11,
              v12,
              scalar);
          }
          rf_vector3_copy_return_destination(v27, (float *)(v33 + 324));
          v27[1] = 0.0;
          v26 = rf_vector3_length(v27);
          if ( *(float *)(*(_DWORD *)(v33 + 660) + 80) >= (double)v26 )
            *(float *)(v33 + 5256) = *(float *)(*(_DWORD *)(v33 + 660) + 80);
          else
            *(float *)(v33 + 5256) = v26 + 1.0;
          *(_DWORD *)(v33 + 424) |= 0x200000u;
        }
        else if ( v33 )
        {
          if ( rf_entity_movement_is_index1_or2(v33) )
            destination[1] = 0.0;
          v6 = rf_vector_multiply_scalar(destination, v18, v36);
          rf_vector_accumulate((float *)(v33 + 2208), v6);
          if ( rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)v33) )
          {
            v24 = rf_vector3_length((float *)(v33 + 2208));
            if ( v36 < (double)v24 )
            {
              v24 = v36 / v24;
              rf_vector3_scale_in_place_return_self((float *)(v33 + 2208), v24);
            }
          }
        }
        else
        {
          scalar = rf_frame_delta_seconds;
          v12 = COERCE_FLOAT(v16);
          v7 = rf_vector_multiply_scalar(destination, v17, v36);
          v8 = rf_vector_multiply_scalar(v7, (float *)LODWORD(v12), scalar);
          rf_vector_accumulate((float *)(a1 + 324), v8);
        }
        *(_DWORD *)(a1 + 424) |= 0x80000000;
        return a1;
      }
    }
  }
  return result;
}

