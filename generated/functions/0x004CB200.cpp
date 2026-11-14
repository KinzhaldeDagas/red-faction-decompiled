// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CB200 rf_particle_pool_update
// UNREALRED VERIFIED [burn-motion-20261029]: After movement/contact, nonzero swirl nibble or accelerate flag0x40 invokes5593B0 on CURRENT particle velocity; optionally samples swirl cone, adds acceleration*delta to scalar speed without clamping, rescales direction, then applies gravity. Storing initial launch direction for later acceleration is not equivalent after bounce/gravity/inherited motion. 5593B0 zero/nonpositive-length case sets RF X-axis and returns1 RF unit (Unreal +X and100cm/s; importer mapping is RF(X,Y,Z)->UE(X,-Z,Y)); preserve that explicit branch.
// UNREALRED VERIFIED [combat-particle-contact-20261104]: Saves current next pointer before age/growth/contact processing, not a snapshot of the full list. Collision children append tail: current-tail parent skips its new children until another update, but earlier-parent children can be visited this update when later old nodes save their now-updated next pointer. age=life assigned by contact is not rechecked until a future visit; subsequent swirl/acceleration/gravity/wind/color still run now. Contactbit0x8000 is cleared per admitted particle before contact, set only by response branch.
int __cdecl rf_particle_pool_update(int *a1, float a2)
{
  int result; // eax
  float *v3; // eax
  float *v4; // eax
  double v5; // st7
  const float *v6; // eax
  char v7; // al
  float v8[3]; // [esp+Ch] [ebp-FCh] BYREF
  float scalar; // [esp+18h] [ebp-F0h]
  int v10; // [esp+1Ch] [ebp-ECh]
  int v11; // [esp+20h] [ebp-E8h]
  int v12; // [esp+24h] [ebp-E4h]
  int v13; // [esp+28h] [ebp-E0h]
  int v14; // [esp+2Ch] [ebp-DCh]
  int v15; // [esp+30h] [ebp-D8h]
  int v16; // [esp+34h] [ebp-D4h]
  int v17; // [esp+38h] [ebp-D0h]
  int v18; // [esp+3Ch] [ebp-CCh]
  int v19; // [esp+40h] [ebp-C8h]
  int v20; // [esp+44h] [ebp-C4h]
  int v21; // [esp+48h] [ebp-C0h]
  int v22; // [esp+4Ch] [ebp-BCh]
  int v23; // [esp+50h] [ebp-B8h]
  int v24; // [esp+54h] [ebp-B4h]
  float v25[3]; // [esp+58h] [ebp-B0h] BYREF
  _BYTE v26[16]; // [esp+64h] [ebp-A4h] BYREF
  float out_vector[3]; // [esp+74h] [ebp-94h] BYREF
  float scaled_result[3]; // [esp+80h] [ebp-88h] BYREF
  float copy_result[3]; // [esp+8Ch] [ebp-7Ch] BYREF
  int v30; // [esp+98h] [ebp-70h]
  int v31; // [esp+9Ch] [ebp-6Ch]
  int v32; // [esp+A0h] [ebp-68h]
  float destination[3]; // [esp+A4h] [ebp-64h] BYREF
  float v34[3]; // [esp+B0h] [ebp-58h] BYREF
  int v35; // [esp+BCh] [ebp-4Ch]
  int v36; // [esp+C0h] [ebp-48h]
  int i; // [esp+C4h] [ebp-44h]
  float v38; // [esp+C8h] [ebp-40h]
  int v39; // [esp+CCh] [ebp-3Ch]
  int v40; // [esp+D0h] [ebp-38h]
  int v41; // [esp+D4h] [ebp-34h]
  float v42; // [esp+D8h] [ebp-30h]
  int v43; // [esp+DCh] [ebp-2Ch]
  float v44; // [esp+E0h] [ebp-28h] BYREF
  float length; // [esp+E4h] [ebp-24h]
  float v46; // [esp+E8h] [ebp-20h]
  _DWORD *v47; // [esp+ECh] [ebp-1Ch]
  int v48; // [esp+F0h] [ebp-18h]
  bool v49; // [esp+F4h] [ebp-14h]
  bool v50; // [esp+F5h] [ebp-13h]
  bool v51; // [esp+F6h] [ebp-12h]
  bool v52; // [esp+F7h] [ebp-11h]
  float v53; // [esp+F8h] [ebp-10h]
  int v54; // [esp+FCh] [ebp-Ch]
  int v55; // [esp+100h] [ebp-8h]
  int v56; // [esp+104h] [ebp-4h]

  v56 = 0;
  result = (int)a1;
  v55 = *a1;
  while ( (int *)v55 != a1 )
  {
    v54 = *(_DWORD *)v55;
    rf_vector_copy((float *)(v55 + 108), copy_result, (const float *)(v55 + 12));
    if ( *(int *)(v55 + 8) <= -1
      || ((v48 = rf_object_resolve_handle(*(_DWORD *)(v55 + 8))) != 0 ? (v24 = *(_DWORD *)(v48 + 32)) : (v24 = -1),
          (v47 = (_DWORD *)rf_particle_emitter_find_by_uid(v24)) == nullptr
       || (LOBYTE(result) = rf_particle_emitter_cached_room_visibility_byte(v47), (_BYTE)result)) )
    {
      *(float *)(v55 + 36) = *(float *)(v55 + 36) + a2;
      *(float *)(v55 + 56) = a2 * *(float *)(v55 + 60) + *(float *)(v55 + 56);
      if ( *(float *)(v55 + 52) > (double)*(float *)(v55 + 36) && *(float *)(v55 + 56) > 0.0 )
      {
        ++unk_8377E4;
        *(_DWORD *)(v55 + 88) &= ~0x8000u;
        if ( (*(_DWORD *)(v55 + 88) & 0x10) != 0 )
        {
          rf_particle_move_and_resolve_contact(v55, a2);
        }
        else
        {
          v3 = rf_vector_multiply_scalar((const float *)(v55 + 24), scaled_result, a2);
          rf_vector_accumulate((float *)(v55 + 12), v3);
        }
        if ( *(_DWORD *)(v55 + 104) )
        {
          if ( rf_particle_emitter_has_nonnegative_parent_index(*(_DWORD **)(v55 + 104)) )
          {
            v4 = rf_vector_subtract(
                   (const float *)(*(_DWORD *)(v55 + 104) + 164),
                   out_vector,
                   (const float *)(v55 + 12));
            v46 = rf_vector_length_squared(v4);
            if ( *(float *)(*(_DWORD *)(v55 + 104) + 160) < (double)v46 )
              *(float *)(*(_DWORD *)(v55 + 104) + 160) = v46;
          }
        }
        v50 = (*(_DWORD *)(v55 + 88) & 0xF000000) != 0;
        v52 = (*(_DWORD *)(v55 + 88) & 0x40) != 0;
        if ( v50 || v52 )
        {
          length = rf_vector_normalize_get_length((float *)(v55 + 24));
          if ( v50 )
          {
            v44 = sub_4CBA30(v55);
            if ( length > 0.0 )
            {
              rf_float_clamp_in_place(&v44, -1.0, 1.0);
              scalar = v44;
              rf_vector3_copy_return_destination(v8, (float *)(v55 + 24));
              rf_random_unit_vector_in_cone((float *)(v55 + 24), v8[0], v8[1], v8[2], scalar);
            }
          }
          if ( v52 )
            length = *(float *)(v55 + 64) * a2 + length;
          rf_vector3_scale_in_place_return_self((float *)(v55 + 24), length);
        }
        if ( (*(_DWORD *)(v55 + 88) & 8) != 0 )
          *(float *)(v55 + 28) = *(float *)(v55 + 28) - *(float *)(v55 + 68) * a2;
        if ( (*(_DWORD *)(v55 + 88) & 0xF0000000) != 0 )
          sub_4CBAA0(v55, a2);
        v51 = (*(_DWORD *)(v55 + 88) & 4) != 0;
        v49 = (*(_WORD *)(v55 + 78) & 1) != 0;
        if ( v51 || v49 )
        {
          v53 = *(float *)(v55 + 36) / *(float *)(v55 + 52);
          if ( v51 )
          {
            v42 = v53 * v53;
            v23 = *(unsigned __int8 *)(v55 + 40);
            v22 = *(unsigned __int8 *)(v55 + 44);
            v21 = *(unsigned __int8 *)(v55 + 40);
            v41 = (int)((double)v23 + ((double)v22 - (double)v21) * v42);
            v20 = *(unsigned __int8 *)(v55 + 41);
            v19 = *(unsigned __int8 *)(v55 + 45);
            v18 = *(unsigned __int8 *)(v55 + 41);
            v39 = (int)((double)v20 + ((double)v19 - (double)v18) * v42);
            v17 = *(unsigned __int8 *)(v55 + 42);
            v16 = *(unsigned __int8 *)(v55 + 46);
            v15 = *(unsigned __int8 *)(v55 + 42);
            v40 = (int)((double)v17 + ((double)v16 - (double)v15) * v42);
            v14 = *(unsigned __int8 *)(v55 + 43);
            v13 = *(unsigned __int8 *)(v55 + 47);
            v12 = *(unsigned __int8 *)(v55 + 43);
            v43 = (int)((double)v14 + ((double)v13 - (double)v12) * v42);
            *(_BYTE *)(v55 + 48) = v41;
            *(_BYTE *)(v55 + 49) = v39;
            *(_BYTE *)(v55 + 50) = v40;
            *(_BYTE *)(v55 + 51) = v43;
          }
          if ( v49 && (*(_WORD *)(v55 + 78) & 2) == 0 )
          {
            if ( (v56 & 0xF) == 0 )
            {
              v5 = rf_particle_decode_damage_nibble_half(v55);
              v38 = v5 * (1.0 - v53 * 0.5);
              for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
              {
                if ( !rf_object_has_respawn_inactive_flag(i) )
                {
                  if ( rf_entity_class_flag2000000_positive_scalar56(i) )
                  {
                    if ( (*(_DWORD *)(i + 124) & 4) == 0 )
                    {
                      *(float *)(i + 56) = *(float *)(i + 56) - v38;
                      if ( *(float *)(i + 56) <= 0.0 )
                        rf_entity_restore_saved_class_motion_and_clear_source(i, 1);
                    }
                    rf_vector_subtract((const float *)(v55 + 12), v34, (const float *)(i + 60));
                  }
                  else if ( rf_particle_entity_damage_admitted(v55, v38, i) )
                  {
                    v35 = -1;
                    if ( (*(_WORD *)(v55 + 78) & 8) != 0 )
                      v35 = 4;
                    v36 = rf_object_resolve_handle(*(_DWORD *)(v55 + 8));
                    if ( v36 )
                      v11 = *(_DWORD *)(v36 + 32);
                    else
                      v11 = -1;
                    rf_damage_dispatch(*(_DWORD *)(i + 44), v38, *(_DWORD *)(v55 + 8), -1, v35, 0, v11, 0);
                    *(_WORD *)(v55 + 78) |= 2u;
                    if ( sub_438AC0(i) )
                    {
                      rf_vector3_default_construct_noop(destination);
                      v32 = *(_DWORD *)(i + 5168);
                      v6 = (const float *)rf_vector3_normalized_copy_unchecked((float *)(v55 + 24), (int)v26);
                      rf_vector_copy(destination, v25, v6);
                      rf_matrix3_inverse_rotate_vector(destination, (float *)(i + 72));
                      v7 = rf_player_direction_to_local_quadrant_mask(v32, destination);
                      rf_player_or_direction_nibble_into_flags(v32, v7);
                    }
                    else if ( (*(_WORD *)(v55 + 78) & 8) != 0
                           && (*(_DWORD *)(*(_DWORD *)(i + 660) + 1832) & 0x10) == 0
                           && *(int *)(v55 + 8) > -1 )
                    {
                      v31 = rf_object_resolve_handle(*(_DWORD *)(v55 + 8));
                      v10 = v31 ? *(_DWORD *)(v31 + 32) : -1;
                      v30 = rf_particle_emitter_find_by_uid(v10);
                      if ( v30 )
                      {
                        scalar = rf_random_float_range(1.0, 3.0);
                        sub_40AC80((int *)(i + 672), *(_DWORD *)(v30 + 4), scalar);
                      }
                    }
                  }
                }
              }
            }
            ++v56;
          }
        }
        result = v54;
        v55 = v54;
      }
      else
      {
        *(_DWORD *)(v55 + 88) = 0;
        **(_DWORD **)(v55 + 4) = *(_DWORD *)v55;
        *(_DWORD *)(*(_DWORD *)v55 + 4) = *(_DWORD *)(v55 + 4);
        *(_DWORD *)v55 = 0;
        *(_DWORD *)(v55 + 4) = 0;
        *(_DWORD *)(v55 + 4) = dword_86660C[63 * *(char *)(v55 + 80)];
        *(_DWORD *)v55 = &unk_866608 + 63 * *(char *)(v55 + 80);
        *(_DWORD *)dword_86660C[63 * *(char *)(v55 + 80)] = v55;
        dword_86660C[63 * *(char *)(v55 + 80)] = v55;
        result = 252 * *(char *)(v55 + 80);
        --*(_DWORD *)((char *)&unk_8666F8 + result);
        v55 = v54;
      }
    }
    else
    {
      v55 = v54;
    }
  }
  return result;
}

