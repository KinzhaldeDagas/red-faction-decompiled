// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C40D0 rf_geomod_impact_chunk_move_and_bounce
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl chunk pointer; AL incidental, not normalized success. If worldSolidNULL no movement. Otherwise room108 is assumed valid; end=position8+(velocity72*dt)*scale, scaleF32.2 iff
// room BYTE388==1 AND contains(position)==1, else1. Calls4C4460(start,end,&chunk.room108,outHit,0): native FIVE cdecl args/pop20; callee fifth unused. Does not use collision fraction
// to integrate remainder. Miss copies FULL end to position; liquid hit(faceNULL) spawns VClip global90B824 at returned point,sizeF32.2 then copies FULL end.
// Solid face: compare face normalY+4 with DOUBLE0.699999988079071. ORDERED >=threshold decrements remaining-bounces100 and sets flags120|2; < OR unordered takes bounce directly
// without decrement/bit. On floor case only ordered speedSquared>4 can aggregate audio; additionally room liquid BYTE==0 OR !contains(returnedHitPoint). Adds1 count814FA8, OLD chunk
// position (not contact) to81523C, and min-like speed contribution: ordered speedSquared>100 adds10, else sqrt(speedSquared); NaN speed fails outer>4.
// If floor exhausted signed bounceCount<=0, stores age112=lifetime116; if face-owner-type1-flag152-clear predicate true stores face DWORD68 into chunk104, otherwise preserves104.
// Returns without position/velocity response. Else bounce (also side/NaN normalY): d=F32(-dot(velocity,faceNormal)); constructs gravity vector(0,-gravity,0),
// gdot=F32(dot(normal,gravityVector)); restitution r=F32random[.1,.4]; q=F32(-(d*r)/(gdot*dt)); only ordered0<q<1 replaces r=F32(r/q). Magnitude=F32((r+1)*d); samples random cone
// around faceNormal with minimum-dot F32.98, scales by magnitude and adds to velocity. Randomizes axis84 as unit vector and spin96=random[pi,2pi]. Old position8 is retained on ALL
// solid-hit paths: no contact snap, remaining-time movement or penetration offset. No zero-dt/gravity/normal/divisor guards, clamp or guaranteed finite response; no room-pointer
// update in helper.
unsigned __int8 __cdecl rf_geomod_impact_chunk_move_and_bounce(int a1)
{
  unsigned __int8 result; // al
  float *v2; // eax
  float *v3; // eax
  float v4[2]; // [esp+0h] [ebp-B0h] BYREF
  float v5; // [esp+8h] [ebp-A8h]
  float v6; // [esp+Ch] [ebp-A4h]
  float v7[4]; // [esp+10h] [ebp-A0h] BYREF
  float v8[3]; // [esp+20h] [ebp-90h] BYREF
  float v9[3]; // [esp+2Ch] [ebp-84h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-78h] BYREF
  float scaled_result[3]; // [esp+44h] [ebp-6Ch] BYREF
  float v12; // [esp+50h] [ebp-60h]
  float v13; // [esp+54h] [ebp-5Ch]
  float v14; // [esp+58h] [ebp-58h]
  float v15; // [esp+5Ch] [ebp-54h]
  float v16; // [esp+60h] [ebp-50h]
  float v17; // [esp+64h] [ebp-4Ch]
  float v18[3]; // [esp+68h] [ebp-48h] BYREF
  float rhs[3]; // [esp+74h] [ebp-3Ch] BYREF
  float v20; // [esp+80h] [ebp-30h]
  float *vector[2]; // [esp+84h] [ebp-2Ch] BYREF
  char v22[12]; // [esp+8Ch] [ebp-24h] BYREF
  float source[3]; // [esp+98h] [ebp-18h] BYREF
  float destination[3]; // [esp+A4h] [ebp-Ch] BYREF

  rf_geomod_intersection24_construct_noop((char *)vector);
  result = (unsigned __int8)rf_vector3_default_construct_noop(destination);
  if ( rf_world_solid )
  {
    v20 = 1.0;
    if ( *(_BYTE *)(*(_DWORD *)(a1 + 108) + 388) == 1 && rf_liquid_room_contains_point(*(_DWORD *)(a1 + 108), a1 + 8) )
      v20 = 0.2;
    v6 = v20;
    v2 = rf_vector_multiply_scalar((const float *)(a1 + 72), scaled_result, rf_frame_delta_seconds);
    rf_vector_multiply_scalar(v2, rhs, v6);
    rf_vector_add((const float *)(a1 + 8), source, rhs);
    if ( rf_geomod_segment_hit_or_liquid_crossing((float *)(a1 + 8), source, a1 + 108, (float *)vector, 0) )
    {
      if ( vector[0] )
      {
        if ( vector[0][1] < 0.699999988079071 )
          goto LABEL_19;
        --*(_DWORD *)(a1 + 100);
        *(_DWORD *)(a1 + 120) |= 2u;
        v12 = rf_vector_length_squared((float *)(a1 + 72));
        if ( v12 > 4.0
          && (!*(_BYTE *)(*(_DWORD *)(a1 + 108) + 388) || !rf_liquid_room_contains_point(
                                                             *(_DWORD *)(a1 + 108),
                                                             (int)v22)) )
        {
          ++dword_814FA8;
          rf_vector_accumulate(flt_81523C, (float *)(a1 + 8));
          if ( v12 <= 100.0 )
            unk_814FA0 = rf_sqrt_float(v12) + unk_814FA0;
          else
            unk_814FA0 = unk_814FA0 + 10.0;
        }
        if ( *(int *)(a1 + 100) > 0 )
        {
LABEL_19:
          v17 = -rf_vector_dot((float *)(a1 + 72), vector[0]);
          v3 = rf_vector_multiply_scalar(vector[0], v9, v17);
          rf_vector_copy(destination, v8, v3);
          rf_vector3_default_construct_noop(v18);
          v5 = -rf_physics_gravity_acceleration;
          rf_vector3_set_components_thiscall(v18, 0.0, v5, 0.0);
          v13 = rf_vector_dot(vector[0], v18);
          v15 = rf_random_float_range(0.1, 0.40000001);
          v16 = -(v17 * v15) / (v13 * rf_frame_delta_seconds);
          if ( v16 > 0.0 && v16 < 1.0 )
            v15 = v15 / v16;
          v14 = (v15 + 1.0) * v17;
          v6 = 0.98000002;
          rf_vector3_copy_return_destination(v4, vector[0]);
          rf_random_unit_vector_in_cone(destination, v4[0], v4[1], v5, v6);
          rf_vector3_scale_in_place_return_self(destination, v14);
          rf_random_unit_vector((float *)(a1 + 84));
          *(float *)(a1 + 96) = rf_random_float_range(3.1415927, 6.2831855);
          return (unsigned __int8)rf_vector_accumulate((float *)(a1 + 72), destination);
        }
        else
        {
          *(float *)(a1 + 112) = *(float *)(a1 + 116);
          result = rf_geomod_face_owner_type1_flag152_clear((int)vector[0]);
          if ( result )
          {
            result = (unsigned __int8)vector[0];
            *(_DWORD *)(a1 + 104) = *((_DWORD *)vector[0] + 17);
          }
        }
      }
      else
      {
        rf_vclip_spawn_runtime_effect(unk_90B824, *(_DWORD *)(a1 + 108), 0, (int)v22, 0.2, -1, 0, 1);
        return (unsigned __int8)rf_vector_copy((float *)(a1 + 8), copy_result, source);
      }
    }
    else
    {
      return (unsigned __int8)rf_vector_copy((float *)(a1 + 8), v7, source);
    }
  }
  return result;
}

