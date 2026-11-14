// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D59C0 rf_entity_resolve_contact_velocity_and_impact_damage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl entity; resolves other object UID484,initial impact scalar0. If liquid492 nonzero: clears flags428 bit0x1000,clears492,scales velocity324 by0.85000002,impact=scaledY,then goes to damage tail. Else reciprocal468 ORDERED>0 OR UNORDERED takes other-body branch: requires resolved other and rejects other-player/nonplayer-self pair. If current descriptor2136 DWORD4==1 and normalY452 ordered nonzero strictly between-0.949999988079071 and+0.949999988079071,sets normalY0 and unchecked-normalizes448. impact=max(0,dot(otherVector472-extraVector2208,normal))-min(0,dot(velocity324,normal));adds normal*(impact*1.049999952316284) to velocity. Other branch (reciprocal<=0 ordered) first checks descriptor1 plus
// resolved other radius384>1,normalY<-0.5,otherVectorY476<0,and squared length(otherVector-extraVector)>0.1000000014901161,all ORDERED. If predicates4354D0 true and40CED0 false,performs436100/4344D0(0),requests body state9 for0.25,sets byte177 on player found by own UID;otherwise damage-dispatch9999,zero velocity,and RETURN without fall-damage tail. Then flags424 bit0x80 selects sliding-style response: decomposes old velocity into normal/tangent,impact=dot(otherVector,N)-dot(oldVelocity+extra,N); positive ordered other normal speed with exactly-zero extra replaces velocity by1.1*otherNormal*N,otherwise retains positive ordered old normal speed*N or zero. Ordered old normal speed<0 applies angle-dependent normal correction oldNormal*1.5*(dot(normalizedCopyOrUnitX(oldV),N)+1). Adds nonzero tangent unconditionally if437F00 predicate,otherwise only ordered tangent-unit dot
// rotated1812>=0;descriptor1 clamps tangentY>=0 on this latter path. Without bit0x80, computes point velocity from oldV+extra,or vehicle branch also cross(rotated angular336 with X negated,contactPoint436-currentPos228);impact=dot(otherVector,N)-dot(pointVelocity,N),adds1.1*impact*N only if its dotN ORDERED>0. Accepted nonvehicle impulse zeroes angular336;vehicle halves336 only if sphere count388>1. Damage tail always calls fall-damage helper in singleplayer;multiplayer skips it when other UID resolves entity OR projectile. No own NULL/class/normal/finite checks; may mutate normal,velocity,flags,liquid,entity state or deal fatal damage.
void __cdecl rf_entity_resolve_contact_velocity_and_impact_damage(int a1)
{
  float *v1; // eax
  double v2; // st7
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float v13; // [esp+18h] [ebp-174h]
  float v14; // [esp+18h] [ebp-174h]
  float v15; // [esp+18h] [ebp-174h]
  float v16; // [esp+1Ch] [ebp-170h]
  float v17; // [esp+20h] [ebp-16Ch]
  double v18; // [esp+24h] [ebp-168h]
  float v19; // [esp+2Ch] [ebp-160h]
  float v20; // [esp+30h] [ebp-15Ch]
  int v21[3]; // [esp+34h] [ebp-158h] BYREF
  float v22[3]; // [esp+40h] [ebp-14Ch] BYREF
  float v23[3]; // [esp+4Ch] [ebp-140h] BYREF
  float v24[3]; // [esp+58h] [ebp-134h] BYREF
  float v25[3]; // [esp+64h] [ebp-128h] BYREF
  float v26[3]; // [esp+70h] [ebp-11Ch] BYREF
  float v27[3]; // [esp+7Ch] [ebp-110h] BYREF
  float v28[3]; // [esp+88h] [ebp-104h] BYREF
  float v29[3]; // [esp+94h] [ebp-F8h] BYREF
  int v30[3]; // [esp+A0h] [ebp-ECh] BYREF
  _BYTE v31[12]; // [esp+ACh] [ebp-E0h] BYREF
  float v32[3]; // [esp+B8h] [ebp-D4h] BYREF
  int v33[3]; // [esp+C4h] [ebp-C8h] BYREF
  float copy_result[3]; // [esp+D0h] [ebp-BCh] BYREF
  int v35[3]; // [esp+DCh] [ebp-B0h] BYREF
  int v36[3]; // [esp+E8h] [ebp-A4h] BYREF
  int v37; // [esp+F4h] [ebp-98h]
  int v38; // [esp+F8h] [ebp-94h]
  float v39; // [esp+FCh] [ebp-90h]
  float v40; // [esp+100h] [ebp-8Ch]
  float v41[3]; // [esp+104h] [ebp-88h] BYREF
  float destination[3]; // [esp+110h] [ebp-7Ch] BYREF
  int v43[3]; // [esp+11Ch] [ebp-70h] BYREF
  float v44[3]; // [esp+128h] [ebp-64h] BYREF
  int v45[3]; // [esp+134h] [ebp-58h] BYREF
  float v46; // [esp+140h] [ebp-4Ch]
  float v47; // [esp+144h] [ebp-48h]
  float v48; // [esp+148h] [ebp-44h]
  float sum_result[3]; // [esp+14Ch] [ebp-40h] BYREF
  float v50; // [esp+158h] [ebp-34h] BYREF
  float v51; // [esp+15Ch] [ebp-30h]
  float lhs[3]; // [esp+164h] [ebp-28h] BYREF
  float v53; // [esp+170h] [ebp-1Ch]
  _DWORD *v54; // [esp+174h] [ebp-18h]
  float out_vector[3]; // [esp+178h] [ebp-14h] BYREF
  float v56; // [esp+184h] [ebp-8h]
  int v57; // [esp+188h] [ebp-4h]

  v56 = 0.0;
  v57 = rf_object_resolve_handle(*(_DWORD *)(a1 + 484));
  if ( *(_DWORD *)(a1 + 492) )
  {
    *(_DWORD *)(a1 + 428) &= ~0x1000u;
    *(_DWORD *)(a1 + 492) = 0;
    rf_vector3_scale_in_place_return_self((float *)(a1 + 324), 0.85000002);
    v56 = *(float *)(a1 + 328);
  }
  else if ( *(float *)(a1 + 468) > 0.0 )
  {
    if ( v57 && (!rf_object_has_player_flag(v57) || rf_object_has_player_flag(a1)) )
    {
      if ( *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 1
        && *(float *)(a1 + 452) != 0.0
        && *(float *)(a1 + 452) < 0.949999988079071
        && *(float *)(a1 + 452) > -0.949999988079071 )
      {
        *(float *)(a1 + 452) = 0.0;
        rf_vector_normalize((float *)(a1 + 448));
      }
      v14 = rf_vector_dot((float *)(a1 + 324), (float *)(a1 + 448));
      v39 = rf_float_minimum_two_values(0.0, v14);
      v11 = rf_vector_subtract((const float *)(a1 + 472), v22, (const float *)(a1 + 2208));
      v15 = rf_vector_dot(v11, (float *)(a1 + 448));
      v40 = rf_float_maximum_two_values(0.0, v15);
      v56 = v40 - v39;
      v16 = v56 * 1.049999952316284;
      v12 = rf_vector_scale((float *)v21, v16, (float *)(a1 + 448));
      rf_vector_accumulate((float *)(a1 + 324), v12);
    }
  }
  else
  {
    if ( *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 1 )
    {
      if ( v57 )
      {
        if ( *(float *)(v57 + 384) > 1.0 && *(float *)(a1 + 452) < -0.5 && *(float *)(a1 + 476) < 0.0 )
        {
          rf_vector_subtract((const float *)(a1 + 472), out_vector, (const float *)(a1 + 2208));
          if ( rf_vector_length_squared(out_vector) > 0.1000000014901161 )
          {
            if ( !rf_entity_has_record_at974_or964(a1) || rf_entity_is_crouched_state810(a1) )
            {
              rf_damage_dispatch(*(_DWORD *)(a1 + 44), 9999.0, *(_DWORD *)(a1 + 484), -1, 0, 0, -1, 0);
              rf_vector3_zero_return_destination((float *)(a1 + 324));
              return;
            }
            rf_entity_apply_crouch_shape_centers(a1);
            sub_4344D0(a1, 0);
            rf_entity_request_body_state(a1, 9u, 0.25);
            v54 = sub_4DD720(*(_DWORD *)(a1 + 44));
            if ( v54 )
              *((_BYTE *)v54 + 177) = 1;
          }
        }
      }
    }
    if ( (*(_DWORD *)(a1 + 424) & 0x80) != 0 )
    {
      rf_vector_add((const float *)(a1 + 324), sum_result, (const float *)(a1 + 2208));
      rf_vector3_copy_return_destination(lhs, (float *)(a1 + 324));
      v48 = rf_vector_dot(lhs, (float *)(a1 + 448));
      v1 = rf_vector_scale((float *)v36, v48, (float *)(a1 + 448));
      rf_vector_subtract(lhs, &v50, v1);
      v53 = rf_vector_dot((float *)(a1 + 472), (float *)(a1 + 448));
      v2 = rf_vector_dot(sum_result, (float *)(a1 + 448));
      v56 = v53 - v2;
      if ( v53 > 0.0 && rf_vector3_is_exact_zero((float *)(a1 + 2208)) )
      {
        v20 = rf_vector_dot((float *)(a1 + 472), (float *)(a1 + 448)) * 1.100000023841858;
        v3 = rf_vector_scale((float *)v35, v20, (float *)(a1 + 448));
        rf_vector_copy((float *)(a1 + 324), copy_result, v3);
      }
      else if ( v48 <= 0.0 )
      {
        rf_vector3_zero_return_destination((float *)(a1 + 324));
      }
      else
      {
        v4 = rf_vector_scale((float *)v33, v48, (float *)(a1 + 448));
        rf_vector_copy((float *)(a1 + 324), v32, v4);
      }
      if ( v48 < 0.0 )
      {
        v5 = (float *)rf_vector3_normalized_copy_or_unit_x(lhs, (int)v31);
        v47 = rf_vector_dot(v5, (float *)(a1 + 448));
        v46 = (v47 + 1.0) * 1.5;
        v19 = v48 * v46;
        v6 = rf_vector_scale((float *)v30, v19, (float *)(a1 + 448));
        rf_vector_subtract_in_place((float *)(a1 + 324), v6);
      }
      if ( !rf_vector3_is_exact_zero(&v50) )
      {
        if ( rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)a1) )
        {
          rf_vector_accumulate((float *)(a1 + 324), &v50);
        }
        else
        {
          rf_matrix3_rotate_vector((float *)(a1 + 1812), v44, (float *)(a1 + 252));
          v13 = rf_vector3_length(&v50);
          rf_vector_divide(&v50, (float *)v45, v13);
          if ( rf_vector_dot((float *)v45, v44) >= 0.0 )
          {
            if ( *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 1 )
              v51 = rf_float_maximum_two_values(v51, 0.0);
            rf_vector_accumulate((float *)(a1 + 324), &v50);
          }
        }
      }
    }
    else
    {
      rf_vector_subtract((const float *)(a1 + 436), v41, (const float *)(a1 + 228));
      rf_vector3_default_construct_noop(destination);
      if ( rf_object_is_use_vehicle((_DWORD *)a1) )
      {
        rf_vector_copy(destination, v29, (const float *)(a1 + 336));
        destination[0] = destination[0] * -1.0;
        rf_vector_rotate_by_matrix3(destination, (float *)(a1 + 252));
        v7 = rf_vector_cross(destination, v28, v41);
        v8 = rf_vector_add(v7, v27, (const float *)(a1 + 324));
        v9 = rf_vector_add(v8, v26, (const float *)(a1 + 2208));
        rf_vector_copy(destination, v25, v9);
      }
      else
      {
        v10 = rf_vector_add((const float *)(a1 + 324), v24, (const float *)(a1 + 2208));
        rf_vector_copy(destination, v23, v10);
      }
      v18 = rf_vector_dot((float *)(a1 + 472), (float *)(a1 + 448));
      v56 = v18 - rf_vector_dot(destination, (float *)(a1 + 448));
      v17 = v56 * 1.100000023841858;
      rf_vector_scale((float *)v43, v17, (float *)(a1 + 448));
      if ( rf_vector_dot((float *)v43, (float *)(a1 + 448)) > 0.0 )
      {
        rf_vector_accumulate((float *)(a1 + 324), (float *)v43);
        if ( rf_object_is_use_vehicle((_DWORD *)a1) )
        {
          if ( rf_receiver_get_first_dword((void *)(a1 + 388)) > 1 )
            rf_vector3_scale_in_place_return_self((float *)(a1 + 336), 0.5);
        }
        else
        {
          rf_vector3_zero_return_destination((float *)(a1 + 336));
        }
      }
    }
  }
  if ( rf_multiplayer_runtime_mode )
  {
    v37 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 484));
    v38 = rf_projectile_resolve_uid_type2(*(_DWORD *)(a1 + 484));
    if ( !v37 && !v38 )
      rf_fall_damage_apply_from_contact_speed(a1, v56);
  }
  else
  {
    rf_fall_damage_apply_from_contact_speed(a1, v56);
  }
}

