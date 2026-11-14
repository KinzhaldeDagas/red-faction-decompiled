// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00409C40 sub_409C40
// UNREALRED VERIFIED [ai-authored-startup-20261028] Waypoint arrival consumes last route point when routecount>0: wait from point+0x24; orientation flag point+0x44; activates event UIDs from point+0x70 before cursor advance. Direction AI+0x410 chooses +/-1. Flags AI+0x414 priority1 wraps,4 wraps once and clears4,2 reverses and selects adjacent point. Then arm5000ms deadline, admit next route via0x40DCA0, arm wait on success; failure uses0x40B2D0 in MP/splitscreen else saved-state restore0x40A2A0. Local end flag is not read by emitted control flow, so do not invent an early return from it. Event dispatch can invalidate UE route/lifetime ownership and requires guards in a future owner.
void __cdecl sub_409C40(int *a1)
{
  float *v1; // eax
  float *v2; // eax
  int first_dword; // eax
  int *v4; // eax
  int v5; // edx
  float v6[3]; // [esp+4h] [ebp-58h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-4Ch] BYREF
  float sum_result[3]; // [esp+1Ch] [ebp-40h] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-34h] BYREF
  float v10; // [esp+34h] [ebp-28h]
  int j; // [esp+38h] [ebp-24h]
  float *lhs; // [esp+3Ch] [ebp-20h]
  int i; // [esp+40h] [ebp-1Ch]
  _DWORD *v14; // [esp+44h] [ebp-18h]
  float v15; // [esp+48h] [ebp-14h]
  char v16[14]; // [esp+4Ch] [ebp-10h] BYREF
  char v17; // [esp+5Ah] [ebp-2h]
  char v18; // [esp+5Bh] [ebp-1h]

  rf_entity_refresh_idle_animation_deadline(*a1);
  v17 = 0;
  v15 = 0.0;
  v18 = 0;
  rf_vector3_default_construct_noop(v16);
  if ( a1[186] > 0 )
  {
    lhs = (float *)a1[a1[186] + 186];
    v15 = lhs[9];
    if ( *((_BYTE *)lhs + 68) == 1 )
    {
      v1 = rf_vector_multiply_scalar(lhs + 24, scaled_result, 100.0);
      v2 = rf_vector_add(lhs, sum_result, v1);
      rf_vector_copy((float *)a1 + 264, copy_result, v2);
      rf_vector_copy((float *)a1 + 315, v6, (const float *)a1 + 264);
    }
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword(lhs + 28);
      if ( i >= first_dword )
        break;
      v4 = (int *)sub_552200((_DWORD *)lhs + 28, i);
      rf_mission_event_activate_by_uid(*v4, -1, -1);
    }
  }
  if ( a1[260] )
    v5 = a1[259] - 1;
  else
    v5 = a1[259] + 1;
  a1[259] = v5;
  v14 = &unk_700480[131 * a1[258]];
  if ( a1[259] < v14[2] )
  {
    if ( a1[259] < 0 )
    {
      if ( (a1[261] & 1) != 0 )
      {
        a1[259] = v14[2] - 1;
      }
      else if ( (a1[261] & 4) != 0 )
      {
        a1[259] = v14[2] - 1;
        a1[261] ^= 4u;
      }
      else if ( (a1[261] & 2) != 0 )
      {
        a1[260] = 0;
        a1[259] = 1;
      }
      else
      {
        v17 = 1;
      }
    }
  }
  else if ( (a1[261] & 1) != 0 )
  {
    a1[259] = 0;
  }
  else if ( (a1[261] & 4) != 0 )
  {
    a1[259] = 0;
    a1[261] ^= 4u;
  }
  else if ( (a1[261] & 2) != 0 )
  {
    a1[260] = 1;
    a1[259] = v14[2] - 2;
  }
  else if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode && a1[160] == 4 )
  {
    for ( j = unk_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
    {
      if ( *(_DWORD *)(*a1 + 44) != *(_DWORD *)(j + 44)
        && !rf_entity_is_dead(j)
        && (*(_DWORD *)(j + 124) & 2) == 0
        && !rf_object_has_respawn_inactive_flag(j) )
      {
        v10 = rf_vector_fast_distance((const float *)(*a1 + 60), (const float *)(j + 60));
        if ( v10 < 3.0 )
        {
          a1[259] = 1;
          break;
        }
      }
    }
    v17 = 1;
  }
  rf_replicator_arm_milliseconds(a1 + 314, 5000);
  if ( sub_40DCA0(*(_DWORD *)(*a1 + 44)) == 1 )
  {
    rf_replicator_arm_milliseconds(a1 + 263, (int)(v15 * 1000.0));
  }
  else if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode )
  {
    sub_40B2D0(a1);
  }
  else
  {
    sub_40A2A0(a1);
  }
}

