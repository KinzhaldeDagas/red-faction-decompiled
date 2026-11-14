// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C6370 rf_glass_shard_integrate_collision
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl shard; AL incidental pointer/delegate result, not normalized bool. WorldSolidNULL ->no shard motion. Room104 assumed valid. Predict end=position8+(velocity64*dt)*scale;
// scaleF32.2 only when room BYTE388==1 AND liquid_contains_point(position)==1, else1. This scales DISPLACEMENT, not stored velocity. Calls recursive
// sweep6740(shard,start,end,out20,depth0). False ->copies FULL predicted end into position, even if sweep changed bucket/owner or spawned liquid splash. True assumes nonnull face.
// Face normalY+4 comparison to DOUBLE0.699999988079071: ordered>= decrements signed collision budget96; < OR unordered goes directly to bounce, no decrement. Floor case ordered
// speedSq>4 and (room liquid BYTE0 OR !contains(contact point)) accumulates impact count, OLD shard position, and speed contribution sqrt(speedSq) unless ordered>100 then10. NaN
// speed fails outer>4.
// If floor budget<=0: samples min-dotF32.95 cone around face normal, builds matrix20 from that direction, stores position=contactPoint+F32(normal*F32.001) then adds SECOND separately
// rounded normal*.001. Two offsets preserve binary32 sequence; no single .002 collapse. If face-owner-type1-flag152-clear true,owner100=face DWORD68, otherwise preserves100. Does not
// zero velocity/axis/spin, release/unlink node, arm a lifetime or change damage flag196. Resting records remain allocated/rendered.
// Otherwise bounce: d=F32(-dot(velocity,normal)),gdot=F32(dot(normal,(0,-gravity,0))),r=F32random[.1,.4],q=F32(-(d*r)/(gdot*dt)); only ordered0<q<1 changes r=F32(r/q).
// Magnitude=F32((r+1)*d), random min-dotF32.98 cone normal scaled by magnitude added to velocity64; random unit axis76,spin88=random[pi,2pi]. All solid bounce paths retain OLD
// position: no contact snap/fraction remainder movement. No gravity integration subtraction here (caller does it), zero-divisor/finite/normal validation or guaranteed finite
// response.
unsigned __int8 __cdecl rf_glass_shard_integrate_collision(int a1)
{
  unsigned __int8 result; // al
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float v7; // [esp-4h] [ebp-E4h] BYREF
  float scalar; // [esp+0h] [ebp-E0h]
  float v9; // [esp+4h] [ebp-DCh]
  float v10; // [esp+8h] [ebp-D8h]
  float v11[4]; // [esp+Ch] [ebp-D4h] BYREF
  float v12[3]; // [esp+1Ch] [ebp-C4h] BYREF
  float v13[3]; // [esp+28h] [ebp-B8h] BYREF
  int v14[3]; // [esp+34h] [ebp-ACh] BYREF
  float copy_result[3]; // [esp+40h] [ebp-A0h] BYREF
  float sum_result[3]; // [esp+4Ch] [ebp-94h] BYREF
  int v17[4]; // [esp+58h] [ebp-88h] BYREF
  float scaled_result[3]; // [esp+68h] [ebp-78h] BYREF
  float v19[3]; // [esp+74h] [ebp-6Ch] BYREF
  float v20; // [esp+80h] [ebp-60h]
  float v21; // [esp+84h] [ebp-5Ch]
  float v22; // [esp+88h] [ebp-58h]
  float v23; // [esp+8Ch] [ebp-54h]
  float v24; // [esp+90h] [ebp-50h]
  float v25; // [esp+94h] [ebp-4Ch]
  float v26[3]; // [esp+98h] [ebp-48h] BYREF
  float rhs[3]; // [esp+A4h] [ebp-3Ch] BYREF
  float v28; // [esp+B0h] [ebp-30h]
  float *vector[2]; // [esp+B4h] [ebp-2Ch] BYREF
  float lhs[3]; // [esp+BCh] [ebp-24h] BYREF
  float source[3]; // [esp+C8h] [ebp-18h] BYREF
  float destination[3]; // [esp+D4h] [ebp-Ch] BYREF

  rf_geomod_intersection24_construct_noop((char *)vector);
  result = (unsigned __int8)rf_vector3_default_construct_noop(destination);
  if ( rf_world_solid )
  {
    v28 = 1.0;
    if ( *(_BYTE *)(*(_DWORD *)(a1 + 104) + 388) == 1 && rf_liquid_room_contains_point(*(_DWORD *)(a1 + 104), a1 + 8) )
      v28 = 0.2;
    v10 = v28;
    v2 = rf_vector_multiply_scalar((const float *)(a1 + 64), scaled_result, rf_frame_delta_seconds);
    rf_vector_multiply_scalar(v2, rhs, v10);
    rf_vector_add((const float *)(a1 + 8), source, rhs);
    if ( rf_glass_shard_sweep_world(a1, (float *)(a1 + 8), (int)source, (int)vector, 0) )
    {
      if ( vector[0][1] < 0.699999988079071 )
        goto LABEL_17;
      --*(_DWORD *)(a1 + 96);
      v20 = rf_vector_length_squared((float *)(a1 + 64));
      if ( v20 > 4.0
        && (!*(_BYTE *)(*(_DWORD *)(a1 + 104) + 388) || !rf_liquid_room_contains_point(*(_DWORD *)(a1 + 104), (int)lhs)) )
      {
        ++rf_glass_frame_impact_count;
        rf_vector_accumulate(rf_glass_frame_impact_position_sum, (float *)(a1 + 8));
        if ( v20 <= 100.0 )
          rf_glass_frame_impact_speed_sum = rf_sqrt_float(v20) + rf_glass_frame_impact_speed_sum;
        else
          rf_glass_frame_impact_speed_sum = rf_glass_frame_impact_speed_sum + 10.0;
      }
      if ( *(int *)(a1 + 96) > 0 )
      {
LABEL_17:
        v25 = -rf_vector_dot((float *)(a1 + 64), vector[0]);
        v6 = rf_vector_multiply_scalar(vector[0], v13, v25);
        rf_vector_copy(destination, v12, v6);
        rf_vector3_default_construct_noop(v26);
        v9 = -rf_physics_gravity_acceleration;
        rf_vector3_set_components_thiscall(v26, 0.0, v9, 0.0);
        v21 = rf_vector_dot(vector[0], v26);
        v23 = rf_random_float_range(0.1, 0.40000001);
        v24 = -(v25 * v23) / (v21 * rf_frame_delta_seconds);
        if ( v24 > 0.0 && v24 < 1.0 )
          v23 = v23 / v24;
        v22 = (v23 + 1.0) * v25;
        v10 = 0.98000002;
        rf_vector3_copy_return_destination(&v7, vector[0]);
        rf_random_unit_vector_in_cone(destination, v7, scalar, v9, v10);
        rf_vector3_scale_in_place_return_self(destination, v22);
        rf_random_unit_vector((float *)(a1 + 76));
        *(float *)(a1 + 88) = rf_random_float_range(3.1415927, 6.2831855);
        return (unsigned __int8)rf_vector_accumulate((float *)(a1 + 64), destination);
      }
      else
      {
        rf_vector3_default_construct_noop(v19);
        v10 = 0.94999999;
        rf_vector3_copy_return_destination(&v7, vector[0]);
        rf_random_unit_vector_in_cone(v19, v7, scalar, v9, v10);
        rf_orientation_matrix_from_normalized_direction((float *)(a1 + 20), v19);
        v3 = rf_vector_scale((float *)v17, 0.001, vector[0]);
        v4 = rf_vector_add(lhs, sum_result, v3);
        rf_vector_copy((float *)(a1 + 8), copy_result, v4);
        v5 = rf_vector_scale((float *)v14, 0.001, vector[0]);
        rf_vector_accumulate((float *)(a1 + 8), v5);
        result = rf_geomod_face_owner_type1_flag152_clear((int)vector[0]);
        if ( result )
        {
          result = a1;
          *(_DWORD *)(a1 + 100) = *((_DWORD *)vector[0] + 17);
        }
      }
    }
    else
    {
      return (unsigned __int8)rf_vector_copy((float *)(a1 + 8), v11, source);
    }
  }
  return result;
}

