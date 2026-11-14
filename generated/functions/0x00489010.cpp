// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00489010 rf_mover_update_rotation
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Rotating update differs from linear: wait gate precedes timing, elapsed/ramp clocks freeze during waits, completion uses updated elapsed. Mode5 subtracts ONE period only when duration<elapsed, not <= or fmod. Angle integrates scaled rate; ramp factor is elapsed-ramp/accel or 1-elapsed-ramp/decel. Forward and backward periods differ. Uses first key and negative authored degrees in radians. Mode1 stops/toggles, mode2 returns once, mode3 selects backward on each endpoint, mode4 alternates with terminal0, mode5 continues. Linear pause-bit0x80 gate is outside this function and is bypassed by delegation; global game pause remains separate.
// UNREALRED VERIFIED [mission-mover-activation-20261013] Stop interaction: ramp-up bit0x10 is tested before ramp-down bit0x20. A stop requested during ramp-up leaves both bits set; ramp-up therefore runs first until its completion, using the reset ramp clock. Ramp-down reaching zero clears target and ramp clock. No inferred immediate reversal is appropriate.
char __cdecl rf_mover_update_rotation(int a1)
{
  int v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  int v6; // [esp+Ch] [ebp-B0h]
  int v7; // [esp+Ch] [ebp-B0h]
  int v8; // [esp+Ch] [ebp-B0h]
  float v9[3]; // [esp+14h] [ebp-A8h] BYREF
  float v10[3]; // [esp+20h] [ebp-9Ch] BYREF
  float v11[3]; // [esp+2Ch] [ebp-90h] BYREF
  float v12; // [esp+38h] [ebp-84h]
  int v13; // [esp+3Ch] [ebp-80h]
  int v14[3]; // [esp+40h] [ebp-7Ch] BYREF
  int v15[3]; // [esp+4Ch] [ebp-70h] BYREF
  int v16[3]; // [esp+58h] [ebp-64h] BYREF
  int v17[3]; // [esp+64h] [ebp-58h] BYREF
  int v18[3]; // [esp+70h] [ebp-4Ch] BYREF
  float v19; // [esp+7Ch] [ebp-40h]
  int v20[3]; // [esp+80h] [ebp-3Ch] BYREF
  float v21[9]; // [esp+8Ch] [ebp-30h] BYREF
  int v22; // [esp+B0h] [ebp-Ch]
  float v23; // [esp+B4h] [ebp-8h]
  float v24; // [esp+B8h] [ebp-4h]

  LOBYTE(v1) = a1;
  if ( *(_DWORD *)(a1 + 748) )
  {
    *(_BYTE *)(*(_DWORD *)(a1 + 748) + 64) = 0;
    LOBYTE(v1) = a1;
    if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 && *(_DWORD *)(a1 + 764) == -1 )
    {
      LOBYTE(v1) = a1;
      *(_BYTE *)(*(_DWORD *)(a1 + 748) + 64) = 1;
    }
  }
  if ( *(_DWORD *)(a1 + 800) != -1 )
  {
    LOBYTE(v1) = a1;
    if ( *(_DWORD *)(a1 + 764) != -1 )
      LOBYTE(v1) = rf_positioned_voice_update(*(_DWORD *)(a1 + 800), (float *)(a1 + 60), (int)&unk_17F10B0, 1.0);
  }
  if ( *(_DWORD *)(a1 + 764) != -1 )
  {
    LOBYTE(v1) = rf_replicator_has_elapsed((int *)(a1 + 784));
    if ( (_BYTE)v1 )
    {
      *(_DWORD *)(a1 + 792) |= 0x4008u;
      *(_DWORD *)(a1 + 124) |= 0x4000000u;
      v22 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), 0);
      if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
        v23 = *(float *)(v22 + 56);
      else
        v23 = *(float *)(v22 + 60);
      *(float *)(a1 + 768) = *(float *)(a1 + 768) + rf_frame_delta_seconds;
      if ( *(_DWORD *)(a1 + 744) == 5 && v23 < (double)*(float *)(a1 + 768) )
        *(float *)(a1 + 768) = *(float *)(a1 + 768) - v23;
      *(float *)(a1 + 776) = *(float *)(a1 + 776) + rf_frame_delta_seconds;
      v24 = 1.0;
      if ( (*(_DWORD *)(a1 + 792) & 0x10) != 0 )
      {
        v24 = *(float *)(a1 + 776) / *(float *)(v22 + 64);
        if ( v24 >= 1.0 )
        {
          v24 = 1.0;
          *(_DWORD *)(a1 + 792) &= ~0x10u;
        }
      }
      else if ( (*(_DWORD *)(a1 + 792) & 0x20) != 0 )
      {
        v24 = 1.0 - *(float *)(a1 + 776) / *(float *)(v22 + 68);
        if ( v24 <= 0.0 )
        {
          v24 = 0.0;
          *(_DWORD *)(a1 + 792) &= ~0x20u;
          *(_DWORD *)(a1 + 764) = -1;
          *(float *)(a1 + 776) = 0.0;
        }
      }
      if ( v23 <= (double)*(float *)(a1 + 768) )
      {
        rf_mover_stop_loop_voice(a1);
        rf_mover_stop_sounds(a1);
        if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
          *(float *)(a1 + 752) = *(float *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 668), *(_DWORD *)(a1 + 764)) + 84);
        else
          *(float *)(a1 + 752) = 0.0;
        *(_DWORD *)(a1 + 760) = *(_DWORD *)(a1 + 764);
        if ( *(_DWORD *)(v22 + 72) != -1 )
        {
          v13 = rf_mission_event_registry_find_by_saved_uid(*(_DWORD *)(v22 + 72));
          if ( v13 )
            rf_mission_event_activate_by_uid(*(_DWORD *)(v13 + 48), *(_DWORD *)(a1 + 44), -1);
        }
        rf_mover_update_linked_pickups(a1);
        if ( (*(_DWORD *)(a1 + 792) & 1) != 0
          || (*(_DWORD *)(a1 + 792) & 0x2000) == 0
          || (v12 = *(float *)(v22 + 52), v12 <= 0.0) )
        {
          if ( *(_DWORD *)(a1 + 780) == *(_DWORD *)(a1 + 764) )
          {
            *(_DWORD *)(a1 + 764) = -1;
            *(float *)(a1 + 768) = 0.0;
            *(float *)(a1 + 776) = 0.0;
            *(_DWORD *)(a1 + 780) = -1;
            if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
            {
              *(_DWORD *)(a1 + 792) &= ~0x2000u;
              LOBYTE(v1) = a1;
            }
            else
            {
              v1 = *(_DWORD *)(a1 + 792) | 0x2000;
              *(_DWORD *)(a1 + 792) = v1;
            }
          }
          else
          {
            if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
              *(_DWORD *)(a1 + 792) &= ~0x2000u;
            else
              *(_DWORD *)(a1 + 792) |= 0x2000u;
            switch ( *(_DWORD *)(a1 + 744) )
            {
              case 1:
                *(_DWORD *)(a1 + 760) = 0;
                *(_DWORD *)(a1 + 764) = -1;
                break;
              case 2:
                *(_DWORD *)(a1 + 792) &= ~0x2000u;
                *(_DWORD *)(a1 + 760) = 0;
                *(_DWORD *)(a1 + 764) = 0;
                *(_DWORD *)(a1 + 780) = 0;
                break;
              case 3:
                *(_DWORD *)(a1 + 792) &= ~0x2000u;
                *(_DWORD *)(a1 + 760) = 0;
                *(_DWORD *)(a1 + 764) = 0;
                break;
              case 4:
                *(_DWORD *)(a1 + 760) = 0;
                *(_DWORD *)(a1 + 764) = 0;
                *(_DWORD *)(a1 + 780) = 0;
                break;
              case 5:
                *(_DWORD *)(a1 + 760) = 0;
                *(_DWORD *)(a1 + 764) = 0;
                *(_DWORD *)(a1 + 780) = -1;
                break;
              default:
                break;
            }
            if ( (*(_DWORD *)(a1 + 792) & 1) != 0 && *(_DWORD *)(a1 + 764) != -1 )
            {
              rf_mover_start_sounds(a1);
              *(_DWORD *)(a1 + 792) &= ~1u;
            }
            *(float *)(a1 + 768) = 0.0;
            *(float *)(a1 + 776) = 0.0;
            LOBYTE(v1) = a1;
          }
        }
        else
        {
          rf_replicator_arm_milliseconds((int *)(a1 + 784), (int)(v12 * 1000.0 + 0.5));
          *(_DWORD *)(a1 + 792) |= 1u;
          LOBYTE(v1) = a1;
        }
      }
      else
      {
        v19 = v24 * *(float *)(v22 + 84) / v23;
        if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
        {
          *(float *)(a1 + 752) = v19 * rf_frame_delta_seconds + *(float *)(a1 + 752);
          if ( *(float *)(a1 + 752) >= 6.283185482025146 )
            *(float *)(a1 + 752) = *(float *)(a1 + 752) - 6.283185482025146;
        }
        else
        {
          *(float *)(a1 + 752) = *(float *)(a1 + 752) - v19 * rf_frame_delta_seconds;
          if ( *(float *)(a1 + 752) <= -6.283185482025146 )
            *(float *)(a1 + 752) = *(float *)(a1 + 752) + 6.283185482025146;
        }
        rf_matrix3_copy_construct((int)v16, (const void *)(v22 + 16));
        rf_vector3_default_construct_noop(v20);
        rf_vector3_default_construct_noop(v15);
        rf_vector3_default_construct_noop(v14);
        v6 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), 0) + 88;
        v2 = rf_vector3_set_components_return_destination(v11, 0.0, 0.0, 0.0);
        rf_point_rotate_about_axis_pivot((int)v20, (int)v16, *(float *)(a1 + 752), (int)v2, v6);
        v7 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), 0) + 88;
        v3 = rf_vector3_set_components_return_destination(v10, 0.0, 0.0, 0.0);
        rf_point_rotate_about_axis_pivot((int)v15, (int)v17, *(float *)(a1 + 752), (int)v3, v7);
        v8 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 668), 0) + 88;
        v4 = rf_vector3_set_components_return_destination(v9, 0.0, 0.0, 0.0);
        rf_point_rotate_about_axis_pivot((int)v14, (int)v18, *(float *)(a1 + 752), (int)v4, v8);
        rf_matrix3_construct_from_three_rows((int)v21, (float *)v20, (float *)v15, (float *)v14);
        LOBYTE(v1) = rf_matrix3_copy((float *)(a1 + 72), v21);
      }
    }
  }
  return v1;
}

