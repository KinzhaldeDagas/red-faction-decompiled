// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00489BB0 rf_mover_activate_forward
// UNREALRED VERIFIED [mission-mover-layout-20261013] Forward activation resolves common type8, rejects inactive triggering owner, requires keys and at least two keys unless rotating, and only starts when target index +0x2FC is -1. Rotating target is zero. Linear direction bit 0x2000 selects next/previous index with wrapping; mode1 installs the corresponding terminal index at +0x30C. Starts audio, retains source context +0x314, and wakes intersecting entity/projectile owners. Existing movement is not restarted by repeated activation.
// UNREALRED VERIFIED [mission-mover-activation-20261013] Retains argument2 at mover+0x314 only when starting an idle target. This is the originating trigger UID propagated through event dispatch; repeated activation while moving does not replace it. Argument3 is the activating common object and is checked for respawn-inactive state before motion admission.
// UNREALRED VERIFIED [mission-unhide-20261020] Forward mover activation resolves its activating object from arg3 and rejects an inactive activator. This is not a test of the mover common object itself. Child entity occupancy/attachment collection also excludes inactive entities. UnrealRed checks current mission activation context before beginning the mover.
char __cdecl rf_mover_activate_forward(int a1, int a2, int a3)
{
  int first_dword; // eax
  int *v4; // eax
  float v6[3]; // [esp+Ch] [ebp-348h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-33Ch] BYREF
  char v8; // [esp+27h] [ebp-32Dh]
  int k; // [esp+28h] [ebp-32Ch]
  int v10; // [esp+2Ch] [ebp-328h]
  int j; // [esp+30h] [ebp-324h]
  int m; // [esp+34h] [ebp-320h]
  int i; // [esp+38h] [ebp-31Ch]
  float destination[194]; // [esp+3Ch] [ebp-318h] BYREF
  int v15; // [esp+344h] [ebp-10h]
  int v16; // [esp+348h] [ebp-Ch]
  int v17; // [esp+34Ch] [ebp-8h]
  float *v18; // [esp+350h] [ebp-4h]

  first_dword = rf_mover_resolve_handle(a1);
  v18 = (float *)first_dword;
  if ( first_dword )
  {
    v15 = rf_object_resolve_handle(a3);
    LOBYTE(first_dword) = rf_object_has_respawn_inactive_flag(v15);
    if ( !(_BYTE)first_dword )
    {
      first_dword = rf_receiver_get_first_dword(v18 + 167);
      if ( first_dword > 0 )
      {
        if ( rf_mover_is_rotating((int)v18) || (first_dword = rf_receiver_get_first_dword(v18 + 167), first_dword > 1) )
        {
          first_dword = rf_entity_resolve_handle(a3);
          v17 = first_dword;
          if ( first_dword )
          {
            LOBYTE(first_dword) = rf_object_has_player_flag(v17);
            if ( !(_BYTE)first_dword )
            {
              LOBYTE(first_dword) = rf_mover_key1_gate_is_satisfied(v18);
              if ( !(_BYTE)first_dword )
              {
                LOBYTE(first_dword) = a1;
                *(_DWORD *)(v17 + 1740) = a1;
              }
            }
          }
          if ( *((_DWORD *)v18 + 191) == -1 )
          {
            if ( rf_mover_is_rotating((int)v18) )
            {
              v18[191] = 0.0;
              if ( ((_DWORD)v18[198] & 0x40) != 0 )
              {
                *((_DWORD *)v18 + 198) &= ~0x20u;
                *((_DWORD *)v18 + 198) |= 0x10u;
                v18[192] = 0.0;
              }
            }
            else
            {
              LODWORD(destination[193]) = rf_object_resolve_handle(a3);
              if ( ((_DWORD)v18[198] & 0x2000) != 0 )
              {
                *((_DWORD *)v18 + 191) = *((_DWORD *)v18 + 190) + 1;
                if ( *((_DWORD *)v18 + 191) >= rf_receiver_get_first_dword(v18 + 167) )
                  v18[191] = 0.0;
                *((_DWORD *)v18 + 195) = *((_DWORD *)v18 + 186) == 1 ? rf_receiver_get_first_dword(v18 + 167) - 1 : -1;
              }
              else
              {
                *((_DWORD *)v18 + 191) = *((_DWORD *)v18 + 190) - 1;
                if ( *((int *)v18 + 191) < 0 )
                  *((_DWORD *)v18 + 191) = rf_receiver_get_first_dword(v18 + 167) - 1;
                *((_DWORD *)v18 + 195) = *((_DWORD *)v18 + 186) == 1 ? 0 : -1;
              }
            }
            *((_DWORD *)v18 + 198) |= 8u;
            if ( *((_DWORD *)v18 + 186) == 1 )
              *((_DWORD *)v18 + 198) &= ~1u;
            rf_mover_start_sounds((int)v18);
            if ( rf_object_handle_has_direct_player_flag(a3) )
            {
              LODWORD(destination[192]) = rf_entity_resolve_handle(a3);
              if ( !rf_entity_weapon_is_holstered_for_actions(dword_681E38)
                || !sub_4EF770()
                || rf_alarm_get_shared_active() == 1 )
              {
                rf_ai_propagate_stimulus_to_nearby_entities(a3, v18 + 15, 10.0, 0);
              }
            }
            *((_DWORD *)v18 + 197) = a2;
            first_dword = rf_receiver_get_first_dword(v18 + 179);
            v16 = first_dword;
            if ( first_dword > 0 )
            {
              if ( v16 > 32 )
                v16 = 32;
              rf_vector_construct_no_unwind(
                (char *)destination,
                0x18u,
                32,
                (void *(__thiscall *)(void *))rf_force_sample44_construct_vectors_noop);
              for ( i = 0; ; ++i )
              {
                LOBYTE(first_dword) = i;
                if ( i >= v16 )
                  break;
                v4 = (int *)sub_552200((_DWORD *)v18 + 179, i);
                v10 = rf_moving_solid_resolve_handle(*v4);
                if ( v10 )
                {
                  rf_vector_copy(&destination[6 * i], copy_result, (const float *)(v10 + 400));
                  rf_vector_copy(&destination[6 * i + 3], v6, (const float *)(v10 + 412));
                }
                else
                {
                  rf_vector3_zero_return_destination(&destination[6 * i]);
                  rf_vector3_zero_return_destination(&destination[6 * i + 3]);
                }
              }
              for ( j = unk_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
              {
                for ( i = 0; i < v16; ++i )
                {
                  if ( !rf_object_has_respawn_inactive_flag(j)
                    && rf_pointer_array_find_index((_DWORD *)v18 + 176, *(_DWORD *)(j + 44)) < 0
                    && rf_aabb_overlap_strict_ordered(
                         (float *)(j + 400),
                         (float *)(j + 412),
                         &destination[6 * i],
                         &destination[6 * i + 3]) )
                  {
                    v8 = 1;
                    for ( k = unk_70489C; (_UNKNOWN *)k != &unk_704610; k = *(_DWORD *)(k + 652) )
                    {
                      if ( *(_DWORD *)(j + 48) == *(_DWORD *)(k + 44) )
                      {
                        v8 = 0;
                        break;
                      }
                    }
                    if ( rf_entity_class_has_contact_geomod_flag400(j) )
                      v8 = 0;
                    if ( v8 )
                      rf_object_request_physics_reactivation_flags(j);
                  }
                }
                LOBYTE(first_dword) = j;
              }
              for ( m = dword_911F74; (_UNKNOWN *)m != &unk_911CE8; m = first_dword )
              {
                for ( i = 0; i < v16; ++i )
                {
                  if ( rf_aabb_overlap_strict_ordered(
                         (float *)(m + 400),
                         (float *)(m + 412),
                         &destination[6 * i],
                         &destination[6 * i + 3]) )
                  {
                    rf_object_request_physics_reactivation_flags(m);
                  }
                }
                first_dword = *(_DWORD *)(m + 652);
              }
            }
          }
        }
      }
    }
  }
  return first_dword;
}

