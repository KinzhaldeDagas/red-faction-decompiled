// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D7E90 rf_entity_predict_motion_by_current_descriptor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl entity. Two independent native admission tests choose buffered vs local rotation and translation: flags424 bit0x8000 AND entity!=global681E38 uses4B4210 for orientation and4B4360 for position. Missing buffer632 is silently left unchanged by those delegates. Local rotation priority: bit0x4000 ->axis-angle angular-state predictor;else descriptor2136 DWORD4==15 ->free-Euler input;else byte1824 nonzero OR bit0x80 ->pitch-heading helper only if bit0x01000000 clear;else generic Euler branch. Generic branch bit0x01000000 skips integration only: otherwise singleplayer local/related OR multiplayer player-flag entities use gain1-exp(float(dt/float((class96/class100)/log(0.05)))) to approach
// angular336=input1800*class96,others damp336 by1-dt*0.8999999761581421;then divides torque372 IN PLACE by scalar152 and adds it to336 WITHOUT multiplying bydt. Always forms D=336*dt,selector helper445AF0 retains axes whose descriptor20/24/28 are neither0 nor1,stores2160;helper4D7D70 adds2148+2160 with pitch clamp/one-step wrap to local predicted Euler (does NOT store2148 here). Builds current252 from old2148 and predicted288 from local predicted Euler;selector445BC0 copies D axes with selector exactly1 into2184. Local translation priority: bit0x4000 ->traction/drag/gravity predictor;else descriptor1/2/15/11 ->exponential velocity control;else predicate437F00 ->horizontal acceleration/gravity;else bit0x1000 skips prediction entirely;otherwise generic force/drag. Generic branch bit0x01000000 only zeroes initial input A;it DOES NOT bypass drag/force integration. Otherwise A is selected-row
// transform of1812*class92,capped only on ORDERED class92<length. Drag for descriptor4/7 is2*140/152,additionally min(1/dt,drag) for player-flag;other descriptors max(global662E20,140/152). A-=velocity324*drag;A+=force360/scalar152;velocity+=A*dt;predicted240=current228+(UPDATED velocity+extra2208)*dt+ A*(0.5*dt*dt),with PLUS correction (unlike neighboring subtracting predictors),no explicit gravity on this generic branch. All paths finally build swept bounds400/412 over228..240 expanded radius384,set fraction460=1,UID484=-1,clear force360/torque372 vectors,OR physics424 bit0x01000000 and return resulting flags. Other contact metadata retained. No NULL,class,scalar,dt,finite or damping-factor guard.
// UNREALRED VERIFIED [combat-steering-signature-20261112]: Generic NPC orientation consumes queued angular336; it is not automatically input1800 branch6250. Rotation order:buffer8000 non-global-player;else4000 axis-angle;else descriptor index15 free-Euler;else byte720 nonzero ORflags424mask80 selects6250 only ifbit1000000 clear;else generic Euler. Generic non-player damping of336 usesfloat(1-residual432*0.8999999761581421),then torque372/scalar152 without multiplying torque bydt. D=336*432 is split by descriptorselectors into2160 body and2184 view components. Native rendering/common/view updates belong to later commit, not immediate AI query.
unsigned int __cdecl rf_entity_predict_motion_by_current_descriptor(int entity)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  const float *v7; // eax
  const float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  unsigned int result; // eax
  float *scalar; // [esp+8h] [ebp-1D0h]
  float v19; // [esp+Ch] [ebp-1CCh]
  float v20; // [esp+10h] [ebp-1C8h]
  float v21; // [esp+14h] [ebp-1C4h]
  float v22; // [esp+18h] [ebp-1C0h]
  float v23; // [esp+1Ch] [ebp-1BCh]
  float v24; // [esp+20h] [ebp-1B8h]
  float v25; // [esp+24h] [ebp-1B4h]
  float v26[3]; // [esp+30h] [ebp-1A8h] BYREF
  float v27[3]; // [esp+3Ch] [ebp-19Ch] BYREF
  float v28[3]; // [esp+48h] [ebp-190h] BYREF
  float v29[3]; // [esp+54h] [ebp-184h] BYREF
  float v30[3]; // [esp+60h] [ebp-178h] BYREF
  float v31[3]; // [esp+6Ch] [ebp-16Ch] BYREF
  int v32[3]; // [esp+78h] [ebp-160h] BYREF
  int v33[3]; // [esp+84h] [ebp-154h] BYREF
  float v34[3]; // [esp+90h] [ebp-148h] BYREF
  float v35[3]; // [esp+9Ch] [ebp-13Ch] BYREF
  float v36[3]; // [esp+A8h] [ebp-130h] BYREF
  float v37[3]; // [esp+B4h] [ebp-124h] BYREF
  float v38[3]; // [esp+C0h] [ebp-118h] BYREF
  _BYTE v39[36]; // [esp+CCh] [ebp-10Ch] BYREF
  _BYTE v40[36]; // [esp+F0h] [ebp-E8h] BYREF
  float v41[3]; // [esp+114h] [ebp-C4h] BYREF
  float v42[3]; // [esp+120h] [ebp-B8h] BYREF
  float v43[3]; // [esp+12Ch] [ebp-ACh] BYREF
  float v44[3]; // [esp+138h] [ebp-A0h] BYREF
  float v45[3]; // [esp+144h] [ebp-94h] BYREF
  float v46[3]; // [esp+150h] [ebp-88h] BYREF
  float v47[3]; // [esp+15Ch] [ebp-7Ch] BYREF
  float v48[3]; // [esp+168h] [ebp-70h] BYREF
  float out_vector[3]; // [esp+174h] [ebp-64h] BYREF
  float copy_result[3]; // [esp+180h] [ebp-58h] BYREF
  float scaled_result[3]; // [esp+18Ch] [ebp-4Ch] BYREF
  float sum_result[3]; // [esp+198h] [ebp-40h] BYREF
  float v53; // [esp+1A4h] [ebp-34h]
  float v54; // [esp+1A8h] [ebp-30h]
  float v55; // [esp+1ACh] [ebp-2Ch]
  float vector[3]; // [esp+1B0h] [ebp-28h] BYREF
  float destination[3]; // [esp+1BCh] [ebp-1Ch] BYREF
  float v58; // [esp+1C8h] [ebp-10h]
  float lhs[3]; // [esp+1CCh] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(lhs);
  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(destination);
  if ( (*(_DWORD *)(entity + 424) & 0x8000) == 0 || entity == dword_681E38 )
  {
    if ( (*(_DWORD *)(entity + 424) & 0x4000) != 0 )
    {
      rf_entity_predict_axis_angle_from_angular_state(entity);
    }
    else if ( *(_DWORD *)(*(_DWORD *)(entity + 2136) + 4) == 15 )
    {
      rf_entity_apply_free_euler_rotation_input(entity);
    }
    else if ( *(_BYTE *)(entity + 1824) || (*(_DWORD *)(entity + 424) & 0x80) != 0 )
    {
      if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(entity + 424)) == 0 )
        rf_entity_apply_pitch_heading_rotation_input(entity);
    }
    else
    {
      if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(entity + 424)) == 0 )
      {
        if ( !rf_multiplayer_runtime_mode && rf_entity_matches_local_player_or_related_handle(entity)
          || rf_multiplayer_runtime_mode && rf_object_has_player_flag(entity) )
        {
          v54 = *(float *)(*(_DWORD *)(entity + 660) + 96) / *(float *)(*(_DWORD *)(entity + 660) + 100) / log(0.05);
          v25 = *(float *)(entity + 432) / v54;
          v53 = 1.0 - rf_exp_float(v25);
          v1 = rf_vector_multiply_scalar(
                 (const float *)(entity + 1800),
                 scaled_result,
                 *(float *)(*(_DWORD *)(entity + 660) + 96));
          rf_vector_copy(lhs, copy_result, v1);
          v2 = rf_vector_subtract(lhs, out_vector, (const float *)(entity + 336));
          rf_vector_copy(destination, v48, v2);
          v3 = rf_vector_multiply_scalar(destination, v47, v53);
          rf_vector_accumulate((float *)(entity + 336), v3);
        }
        else
        {
          v24 = 1.0 - *(float *)(entity + 432) * 0.8999999761581421;
          rf_vector3_scale_in_place_return_self((float *)(entity + 336), v24);
        }
        rf_vector3_divide_in_place_reciprocal((float *)(entity + 372), *(float *)(entity + 152));
        rf_vector_accumulate((float *)(entity + 336), (float *)(entity + 372));
      }
      v4 = rf_vector_multiply_scalar((const float *)(entity + 336), v46, *(float *)(entity + 432));
      rf_vector_copy(destination, v45, v4);
      v5 = rf_entity_filter_rotation_axes_for_body(v44, entity, destination);
      rf_vector_copy((float *)(entity + 2160), v43, v5);
      v6 = rf_euler_angles_add_clamp_pitch_wrap_once(v42, (float *)(entity + 2148), (float *)(entity + 2160), 0);
      rf_vector_copy(vector, v41, v6);
      v7 = (const float *)rf_matrix3_build_pitch_heading_linear_horizontal_basis((int)v40, (float *)(entity + 2148));
      rf_matrix3_copy((float *)(entity + 252), v7);
      v8 = (const float *)rf_matrix3_build_pitch_heading_linear_horizontal_basis((int)v39, vector);
      rf_matrix3_copy((float *)(entity + 288), v8);
      v9 = rf_entity_filter_rotation_axes_for_view_offset(v38, entity, destination);
      rf_vector_copy((float *)(entity + 2184), v37, v9);
    }
  }
  else
  {
    rf_entity_apply_buffered_orientation_sample(entity);
  }
  if ( (*(_DWORD *)(entity + 424) & 0x8000) == 0 || entity == dword_681E38 )
  {
    if ( (*(_DWORD *)(entity + 424) & 0x4000) != 0 )
    {
      rf_entity_predict_traction_drag_and_gravity(entity);
    }
    else if ( rf_entity_movement_is_index1_or2(entity)
           || *(_DWORD *)(*(_DWORD *)(entity + 2136) + 4) == 15
           || *(_DWORD *)(*(_DWORD *)(entity + 2136) + 4) == 11 )
    {
      rf_entity_predict_velocity_with_exponential_control(entity);
    }
    else if ( rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)entity) )
    {
      rf_entity_predict_horizontal_acceleration_and_gravity(entity);
    }
    else if ( (*(_DWORD *)(entity + 424) & 0x1000) == 0 )
    {
      if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(entity + 424)) != 0 )
      {
        rf_vector3_zero_return_destination(vector);
      }
      else
      {
        rf_vector_copy(lhs, v36, (const float *)(entity + 1812));
        rf_vector3_scale_in_place_return_self(lhs, *(float *)(*(_DWORD *)(entity + 660) + 92));
        v10 = rf_entity_transform_motion_vector_by_selected_rows(v35, entity, lhs);
        rf_vector_copy(vector, v34, v10);
        v55 = rf_vector3_length(vector);
        if ( *(float *)(*(_DWORD *)(entity + 660) + 92) < (double)v55 )
        {
          v23 = *(float *)(*(_DWORD *)(entity + 660) + 92) / v55;
          rf_vector3_scale_in_place_return_self(vector, v23);
        }
      }
      if ( rf_entity_movement_is_index4_or7(entity) )
      {
        if ( rf_object_has_player_flag(entity) )
        {
          v22 = 2.0 * *(float *)(entity + 140) / *(float *)(entity + 152);
          v21 = 1.0 / *(float *)(entity + 432);
          v58 = rf_float_minimum_two_values(v21, v22);
        }
        else
        {
          v58 = 2.0 * *(float *)(entity + 140) / *(float *)(entity + 152);
        }
      }
      else
      {
        v20 = 1.0 * *(float *)(entity + 140) / *(float *)(entity + 152);
        v58 = rf_float_maximum_two_values(flt_662E20, v20);
      }
      v11 = rf_vector_scale((float *)v33, v58, (float *)(entity + 324));
      rf_vector_subtract_in_place(vector, v11);
      v12 = rf_vector_divide((float *)(entity + 360), (float *)v32, *(float *)(entity + 152));
      rf_vector_accumulate(vector, v12);
      v13 = rf_vector_multiply_scalar(vector, v31, *(float *)(entity + 432));
      rf_vector_accumulate((float *)(entity + 324), v13);
      rf_vector_add((const float *)(entity + 324), sum_result, (const float *)(entity + 2208));
      v19 = *(float *)(entity + 432) * 0.5 * *(float *)(entity + 432);
      scalar = rf_vector_multiply_scalar(vector, v28, v19);
      v14 = rf_vector_multiply_scalar(sum_result, v30, *(float *)(entity + 432));
      v15 = rf_vector_add((const float *)(entity + 228), v29, v14);
      v16 = rf_vector_add(v15, v27, scalar);
      rf_vector_copy((float *)(entity + 240), v26, v16);
    }
  }
  else
  {
    rf_entity_apply_buffered_position_sample(entity);
  }
  rf_segment_bounds_build(
    (float *)(entity + 400),
    (float *)(entity + 412),
    (float *)(entity + 228),
    (float *)(entity + 240));
  rf_vector3_subtract_scalar_in_place((float *)(entity + 400), *(float *)(entity + 384));
  rf_vector3_add_scalar_in_place((float *)(entity + 412), *(float *)(entity + 384));
  *(float *)(entity + 460) = 1.0;
  *(_DWORD *)(entity + 484) = -1;
  rf_vector3_zero_return_destination((float *)(entity + 360));
  rf_vector3_zero_return_destination((float *)(entity + 372));
  result = (unsigned int)&unk_1000000 | *(_DWORD *)(entity + 424);
  *(_DWORD *)(entity + 424) = result;
  return result;
}

