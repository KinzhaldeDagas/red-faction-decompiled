// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487F90 rf_mover_update_motion
// UNREALRED VERIFIED [mission-mover-layout-20261013] Nonrotating motion update delegates rotating movers to 0x489010 and respects pause bit0x80. Key floats +0x34,+0x38,+0x3C,+0x40,+0x44 are wait, forward/back travel parameters, acceleration and deceleration. Runtime flag0x400 makes travel parameter speed; otherwise nominal speed is distance/parameter. Direction chooses current forward versus destination backward parameter. Arrival tests previous traveled distance before snapping, emits key-owned activation, then advances according to mode1..5 and direction. This is not constant-duration lerp; acceleration, wait, obstruction/door reversal, event and audio owners matter.
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Linear timing details: speed/elapsed/travelled bookkeeping advances BEFORE the wait-deadline gate. Arrival compares PREVIOUS travelled distance, so snapping this frame can precede next-frame arrival effects. Forward and reverse deceleration boundary guards differ (forward additionally requires boundary>0). 0x40D620 uses ordered lower-then-upper branches, not a generic min/max clamp. Positive waits quantize (seconds*1000+0.5) to integer milliseconds; the Waiting bit forces arrival processing again on expiry, including key-event dispatch. One transition per frame; do not consume leftover time across multiple segments.
unsigned int __cdecl rf_mover_update_motion(int a1)
{
  unsigned int result; // eax
  double v2; // st7
  double v3; // st7
  int v4; // eax
  int v5; // eax
  int v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  int v10; // eax
  float v11; // [esp+8h] [ebp-DCh]
  float v12[3]; // [esp+14h] [ebp-D0h] BYREF
  float v13[3]; // [esp+20h] [ebp-C4h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-B8h] BYREF
  float v15[3]; // [esp+38h] [ebp-ACh] BYREF
  float scaled_result[3]; // [esp+44h] [ebp-A0h] BYREF
  float v17[3]; // [esp+50h] [ebp-94h] BYREF
  float v18[3]; // [esp+5Ch] [ebp-88h] BYREF
  float copy_result[3]; // [esp+68h] [ebp-7Ch] BYREF
  float v20; // [esp+74h] [ebp-70h]
  int v21; // [esp+78h] [ebp-6Ch]
  float out_vector[3]; // [esp+7Ch] [ebp-68h] BYREF
  float rhs[3]; // [esp+88h] [ebp-5Ch] BYREF
  float lhs[3]; // [esp+94h] [ebp-50h] BYREF
  _BYTE v25[12]; // [esp+A0h] [ebp-44h] BYREF
  float v26; // [esp+ACh] [ebp-38h]
  float v27; // [esp+B0h] [ebp-34h]
  float v28; // [esp+B4h] [ebp-30h]
  float v29; // [esp+B8h] [ebp-2Ch]
  float v30; // [esp+BCh] [ebp-28h]
  int v31; // [esp+C0h] [ebp-24h]
  float v32; // [esp+C4h] [ebp-20h]
  float v33; // [esp+C8h] [ebp-1Ch]
  int v34; // [esp+CCh] [ebp-18h]
  float v35; // [esp+D0h] [ebp-14h]
  char v36; // [esp+D7h] [ebp-Dh]
  float v37; // [esp+D8h] [ebp-Ch]
  float v38; // [esp+DCh] [ebp-8h]
  int v39; // [esp+E0h] [ebp-4h]

  rf_vector3_zero_return_destination((float *)(a1 + 324));
  if ( rf_mover_is_rotating(a1) )
    return rf_mover_update_rotation(a1);
  result = a1;
  if ( *(_DWORD *)(a1 + 748) )
  {
    *(_BYTE *)(*(_DWORD *)(a1 + 748) + 64) = 0;
    result = a1;
    if ( !*(_DWORD *)(a1 + 760) && *(_DWORD *)(a1 + 764) == -1 )
    {
      result = *(_DWORD *)(a1 + 748);
      *(_BYTE *)(result + 64) = 1;
    }
  }
  if ( (*(_DWORD *)(a1 + 792) & 0x80) == 0 )
  {
    result = a1;
    if ( *(_DWORD *)(a1 + 764) != -1 )
    {
      *(_DWORD *)(a1 + 124) |= 0x4000000u;
      *(_DWORD *)(a1 + 792) |= 0x4008u;
      if ( *(_DWORD *)(a1 + 800) != -1 )
        rf_positioned_voice_update(*(_DWORD *)(a1 + 800), (float *)(a1 + 60), (int)&unk_17F10B0, 1.0);
      v39 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 760));
      v34 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 764));
      v32 = 0.0;
      if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
      {
        v37 = *(float *)(v39 + 56);
        v35 = rf_vector_distance((const float *)(v39 + 4), (const float *)(v34 + 4));
        v33 = v35 / v37;
        if ( (*(_DWORD *)(a1 + 792) & 0x400) != 0 )
          v33 = v37;
        if ( *(float *)(v39 + 64) > 0.0 )
        {
          v30 = v33 / *(float *)(v39 + 64);
          if ( *(float *)(v39 + 64) >= (double)*(float *)(a1 + 768) )
            v32 = v30;
        }
        if ( *(float *)(v39 + 68) > 0.0 )
        {
          v29 = v33 / *(float *)(v39 + 68);
          v28 = v35 - v29 * 0.5 * *(float *)(v39 + 68) * *(float *)(v39 + 68);
          if ( v28 > 0.0 && v28 <= (double)*(float *)(a1 + 772) )
            v32 = -v29;
        }
        v31 = v39;
      }
      else
      {
        v37 = *(float *)(v34 + 60);
        v35 = rf_vector_distance((const float *)(v39 + 4), (const float *)(v34 + 4));
        v33 = v35 / v37;
        if ( (*(_DWORD *)(a1 + 792) & 0x400) != 0 )
          v33 = v37;
        if ( *(float *)(v39 + 64) > 0.0 )
        {
          v27 = v33 / *(float *)(v39 + 64);
          if ( *(float *)(v39 + 64) >= (double)*(float *)(a1 + 768) )
            v32 = v27;
        }
        if ( *(float *)(v39 + 68) > 0.0 )
        {
          v26 = v33 / *(float *)(v39 + 68);
          if ( *(float *)(a1 + 772) >= v35 - v26 * 0.5 * *(float *)(v39 + 68) * *(float *)(v39 + 68) )
            v32 = -v26;
        }
        v31 = v34;
      }
      if ( v32 == 0.0 && *(float *)(a1 + 768) == 0.0 )
      {
        *(float *)(a1 + 756) = v33;
      }
      else
      {
        *(float *)(a1 + 756) = v32 * rf_frame_delta_seconds + *(float *)(a1 + 756);
        rf_float_clamp_in_place((float *)(a1 + 756), 0.40000001, v33);
      }
      *(float *)(a1 + 768) = *(float *)(a1 + 768) + rf_frame_delta_seconds;
      v38 = *(float *)(a1 + 772);
      v2 = *(float *)(a1 + 756) * rf_frame_delta_seconds + *(float *)(a1 + 772);
      *(float *)(a1 + 772) = v2;
      result = rf_replicator_has_elapsed((int *)(a1 + 784));
      if ( (_BYTE)result )
      {
        if ( rf_mover_hold_open_for_trigger(v2, (_DWORD *)a1) == 1 )
        {
          return rf_replicator_arm_milliseconds((int *)(a1 + 784), (int)(*(float *)(v34 + 52) * 1000.0 + 0.5));
        }
        else
        {
          v36 = 0;
          v3 = v37;
          if ( v37 == 0.0 || (*(_DWORD *)(a1 + 792) & 1) != 0 || (v3 = v38, v35 <= (double)v38) )
            v36 = 1;
          if ( v36 )
          {
            v10 = sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 764));
            rf_vector_copy((float *)(a1 + 240), v12, (const float *)(*(_DWORD *)v10 + 4));
            *(float *)(a1 + 756) = 0.0;
            *(float *)(a1 + 772) = 0.0;
            *(_DWORD *)(a1 + 760) = *(_DWORD *)(a1 + 764);
            if ( *(_DWORD *)(v34 + 72) != -1 )
            {
              v21 = rf_mission_event_registry_find_by_saved_uid(*(_DWORD *)(v34 + 72));
              if ( v21 )
                rf_mission_event_activate_by_uid(*(_DWORD *)(v21 + 48), *(_DWORD *)(a1 + 44), -1);
            }
            rf_mover_update_linked_pickups(a1);
            if ( (*(_DWORD *)(a1 + 792) & 1) != 0 || (v20 = *(float *)(v34 + 52), v20 <= 0.0) )
            {
              if ( *(_DWORD *)(a1 + 780) == *(_DWORD *)(a1 + 764) )
              {
                *(_DWORD *)(a1 + 760) = *(_DWORD *)(a1 + 764);
                *(_DWORD *)(a1 + 764) = -1;
                *(float *)(a1 + 768) = 0.0;
                if ( (*(_DWORD *)(a1 + 792) & 1) == 0 )
                  rf_mover_stop_sounds(a1);
                if ( *(_DWORD *)(a1 + 760) == rf_receiver_get_first_dword((void *)(a1 + 668)) - 1 )
                {
                  result = *(_DWORD *)(a1 + 792) & 0xFFFFDFFF;
                  *(_DWORD *)(a1 + 792) = result;
                }
                else
                {
                  result = a1;
                  if ( !*(_DWORD *)(a1 + 760) )
                  {
                    result = a1;
                    *(_DWORD *)(a1 + 792) |= 0x2000u;
                  }
                }
              }
              else
              {
                if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
                {
                  ++*(_DWORD *)(a1 + 764);
                  if ( *(_DWORD *)(a1 + 764) >= rf_receiver_get_first_dword((void *)(a1 + 668)) )
                  {
                    switch ( *(_DWORD *)(a1 + 744) )
                    {
                      case 1:
                        *(_DWORD *)(a1 + 760) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                        *(_DWORD *)(a1 + 764) = -1;
                        *(_DWORD *)(a1 + 792) &= ~0x2000u;
                        break;
                      case 2:
                        *(_DWORD *)(a1 + 792) &= ~0x2000u;
                        *(_DWORD *)(a1 + 760) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                        *(_DWORD *)(a1 + 764) = *(_DWORD *)(a1 + 760) - 1;
                        *(_DWORD *)(a1 + 780) = 0;
                        break;
                      case 3:
                        *(_DWORD *)(a1 + 792) &= ~0x2000u;
                        *(_DWORD *)(a1 + 760) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                        *(_DWORD *)(a1 + 764) = *(_DWORD *)(a1 + 760) - 1;
                        break;
                      case 4:
                        *(_DWORD *)(a1 + 760) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                        *(_DWORD *)(a1 + 764) = 0;
                        *(_DWORD *)(a1 + 780) = 0;
                        break;
                      case 5:
                        *(_DWORD *)(a1 + 760) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                        *(_DWORD *)(a1 + 764) = 0;
                        *(_DWORD *)(a1 + 780) = -1;
                        break;
                      default:
                        break;
                    }
                  }
                }
                else if ( (int)--*(_DWORD *)(a1 + 764) < 0 )
                {
                  switch ( *(_DWORD *)(a1 + 744) )
                  {
                    case 1:
                      *(_DWORD *)(a1 + 760) = 0;
                      *(_DWORD *)(a1 + 764) = -1;
                      *(_DWORD *)(a1 + 792) |= 0x2000u;
                      break;
                    case 2:
                      *(_DWORD *)(a1 + 792) |= 0x2000u;
                      *(_DWORD *)(a1 + 760) = 0;
                      *(_DWORD *)(a1 + 764) = 1;
                      *(_DWORD *)(a1 + 780) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                      break;
                    case 3:
                      *(_DWORD *)(a1 + 792) |= 0x2000u;
                      *(_DWORD *)(a1 + 760) = 0;
                      *(_DWORD *)(a1 + 764) = 1;
                      break;
                    case 4:
                      *(_DWORD *)(a1 + 760) = 0;
                      *(_DWORD *)(a1 + 764) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                      *(_DWORD *)(a1 + 780) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                      break;
                    case 5:
                      *(_DWORD *)(a1 + 760) = 0;
                      *(_DWORD *)(a1 + 764) = rf_receiver_get_first_dword((void *)(a1 + 668)) - 1;
                      *(_DWORD *)(a1 + 780) = -1;
                      break;
                    default:
                      break;
                  }
                }
                if ( (*(_DWORD *)(a1 + 792) & 1) != 0 )
                {
                  rf_mover_start_sounds(a1);
                  *(_DWORD *)(a1 + 792) &= ~1u;
                }
                *(float *)(a1 + 768) = 0.0;
                return a1;
              }
            }
            else
            {
              rf_replicator_arm_milliseconds((int *)(a1 + 784), (int)(v20 * 1000.0 + 0.5));
              *(_DWORD *)(a1 + 792) |= 1u;
              return rf_mover_stop_sounds(a1);
            }
          }
          else if ( !rf_mover_flag2_is_set(a1)
                 || *(_DWORD *)(a1 + 764)
                 || *(_DWORD *)(a1 + 744) == 1
                 || rf_mover_trigger_has_active_entity(v3, a1) != 1 )
          {
            if ( v35 > (double)*(float *)(a1 + 772) )
            {
              rf_vector3_default_construct_noop(rhs);
              rf_vector3_default_construct_noop(lhs);
              rf_vector3_default_construct_noop(v25);
              v5 = sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 760));
              rf_vector_copy(rhs, v18, (const float *)(*(_DWORD *)v5 + 4));
              v6 = sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 764));
              rf_vector_copy(lhs, v17, (const float *)(*(_DWORD *)v6 + 4));
              rf_vector_subtract(lhs, out_vector, rhs);
              rf_vector_normalize_reciprocal_sqrt(out_vector);
              v11 = rf_frame_delta_seconds;
              v7 = rf_vector_multiply_scalar(out_vector, scaled_result, *(float *)(a1 + 756));
              v8 = rf_vector_multiply_scalar(v7, v15, v11);
              v9 = rf_vector_add((const float *)(a1 + 228), sum_result, v8);
              return (unsigned int)rf_vector_copy((float *)(a1 + 240), v13, v9);
            }
            else
            {
              v4 = sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 764));
              return (unsigned int)rf_vector_copy((float *)(a1 + 240), copy_result, (const float *)(*(_DWORD *)v4 + 4));
            }
          }
          else
          {
            return rf_mover_reverse_linear_segment(a1);
          }
        }
      }
    }
  }
  return result;
}

