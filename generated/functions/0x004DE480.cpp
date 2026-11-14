// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DE480 rf_multiplayer_player_entity_create
// UNREALRED VERIFIED [early-respawn-20260930] Fresh entity creation writes the new entity handle to Player+0x14. It does not reset the old dying entity in place or call its death finalizer. Old death update 0x4283B0 independently waits for its selected action before 0x420140. The Unreal early manual handoff therefore retains the old ticking body until that finalization, while possession moves to a distinct fresh body.
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: Playerbody+0x1430 is assigned at4DE784 ONLYwhenplayerobjectargumentmatchesanentryinrf_local_player_entries (4DE76F..784). Commonplayerflag at+0x7C bit8 is set forcreatedplayerbodybeforethisloop. Therefore438AC0/no_z_check correspondsboundLOCALplayerrecord, not everyremotePlayerState. Live Unreal adapter mayuse explicit playercontrolled+locallycontrolledsource; vehicleforwarding andunpossessedoldbodyrecordpersistence requireadditionalownershipimplementation.
// UNREALRED VERIFIED [combat-burn-owner-erratum-20261104]: Raw4DE76F..4DE784 compares the supplied player object with each rf_local_player_entries entry and writes Entity+0x1430 only on equality. The common player flag is set before that loop for every created player body. Therefore438AC0 is a retained LOCAL player-record association, not every PlayerState and not IsLocallyControlled() for a bot. A host local PlayerController with an actual LocalPlayer is an explicit association adapter; preserve through unpossession until native death/reset retirement.
int __cdecl rf_multiplayer_player_entity_create(int a1, int a2, float *destination, float *a4, int a5)
{
  char *v6; // eax
  char *v7; // eax
  char *v9; // [esp+8h] [ebp-60h]
  char *v11; // [esp+10h] [ebp-58h]
  char v12; // [esp+17h] [ebp-51h]
  _BYTE *v13; // [esp+1Ch] [ebp-4Ch]
  char *v14; // [esp+20h] [ebp-48h]
  float copy_result[3]; // [esp+24h] [ebp-44h] BYREF
  int v16; // [esp+30h] [ebp-38h]
  int v17; // [esp+34h] [ebp-34h] BYREF
  _DWORD v18[6]; // [esp+38h] [ebp-30h] BYREF
  char *v19; // [esp+54h] [ebp-14h]
  int *v20; // [esp+58h] [ebp-10h]
  unsigned int v21; // [esp+5Ch] [ebp-Ch]
  int runtime; // [esp+60h] [ebp-8h]
  int i; // [esp+64h] [ebp-4h]

  if ( !a1 )
    return 0;
  if ( a5 < 0 || a5 >= rf_multiplayer_character_count )
  {
    if ( a1 == rf_local_fpgun_player )
      *(_DWORD *)(a1 + 3932) = 0;
    a5 = 0;
  }
  if ( a1 == rf_local_fpgun_player )
    rf_player_clear_flags16_bit8(a1);
  if ( unk_87C314 == 1 )
  {
    rf_vector_copy(destination, copy_result, &flt_87C698);
    unk_87C314 = 0;
  }
  if ( byte_87C315[0] == 1 )
  {
    rf_orientation_matrix_from_normalized_direction(a4, &flt_87C650);
    byte_87C315[0] = 0;
  }
  v6 = (char *)rf_string_object_c_str_or_empty((const void *)(a1 + 8));
  runtime = rf_entity_create_runtime(a2, v6, -1, destination, a4, 1, a5);
  if ( !runtime )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\player\\player.cpp",
      3243,
      "Failure to create player  entity\n");
  if ( rf_multiplayer_runtime_mode == 1 )
  {
    v20 = nullptr;
    if ( *(int *)(a1 + 3932) > -1 && *(_DWORD *)(a1 + 3932) < rf_multiplayer_character_count )
      v20 = &rf_multiplayer_character_table[80 * *(_DWORD *)(a1 + 3932)];
    if ( v20 )
    {
      if ( rf_multiplayer_game_mode_get() )
      {
        v19 = &rf_entity_info_definitions[5396 * v20[1]];
        if ( rf_multiplayer_character_needs_default_team_skins((int)v20, (int)v19) )
        {
          rf_multiplayer_character_append_default_team_skin_profiles((int)v20, runtime);
          if ( *(_BYTE *)(a1 + 48) )
          {
            strcpy((char *)v18, "default_blue");
          }
          else
          {
            qmemcpy(v18, "default_", 8);
            v18[2] = "jects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d.cpp";
          }
        }
        else
        {
          v14 = (char *)(v20 + 12);
          v13 = v18;
          do
          {
            v12 = *v14;
            *v13++ = *v14++;
          }
          while ( v12 );
          if ( *(_BYTE *)(a1 + 48) )
          {
            v9 = (char *)&v17 + 3;
            while ( *++v9 )
              ;
            strcpy(v9, "_blue");
          }
          else
          {
            v11 = (char *)&v17 + 3;
            while ( *++v11 )
              ;
            strcpy(v11, "_red");
          }
        }
        rf_entity_apply_named_skin_profile(runtime, (char *)v18);
      }
      else
      {
        rf_entity_apply_named_skin_profile(runtime, (char *)v20 + 48);
      }
    }
  }
  *(_DWORD *)(a1 + 20) = *(_DWORD *)(runtime + 44);
  *(_DWORD *)(runtime + 124) |= 8u;
  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    if ( a1 == rf_local_player_entries[i] )
      *(_DWORD *)(runtime + 5168) = a1;
  }
  if ( rf_local_fpgun_player == a1 )
  {
    rf_player_associate_local_runtime_entity(runtime);
    *(_DWORD *)(runtime + 32) = -999;
  }
  else if ( a1 == dword_87C5B4 )
  {
    *(_DWORD *)(runtime + 32) = -998;
  }
  if ( rf_player_has_flags16_mask10(a1) )
    rf_camera_slot_enter_first_person(*(float ***)(a1 + 196));
  if ( rf_player_has_flags16_mask10(a1) )
    rf_entity_clear_weapon_inventory(dword_681E38);
  v7 = (char *)rf_string_object_c_str_or_empty(unk_87C65C);
  v21 = sub_50FB80(v7);
  if ( rf_multiplayer_runtime_mode )
  {
    if ( v21 < 0x20 )
    {
      rf_player_grant_weapon_and_set_reserve_and_clip(a1, v21, 3 * unk_912088[340 * v21]);
      rf_player_select_owned_weapon_if_present(a1, v21);
    }
    rf_player_grant_weapon_and_set_reserve_and_clip(
      a1,
      rf_weapon_id_riot_stick,
      unk_912088[340 * rf_weapon_id_riot_stick]);
  }
  else if ( v21 < 0x20 )
  {
    rf_player_grant_weapon_and_set_reserve_and_clip(a1, v21, unk_912260[340 * v21]);
    rf_player_select_owned_weapon_if_present(a1, v21);
  }
  *(_BYTE *)(a1 + 3988) = 0;
  *(_BYTE *)(a1 + 3989) = 0;
  *(_BYTE *)(runtime + 40) = *(_BYTE *)(a1 + 48);
  *(_DWORD *)(runtime + 124) &= ~0x200u;
  for ( i = 0; i < 96; ++i )
    *(_BYTE *)(i + a1 + 80) = 0;
  rf_replicator_reset((_DWORD *)(runtime + 1300));
  if ( rf_multiplayer_runtime_mode && a1 == rf_local_fpgun_player )
  {
    if ( dword_662F6C != *(_DWORD *)(a1 + 3932) )
    {
      rf_fpgun_release_cycle_slot_model_cache();
      rf_fpgun_initialize_cycle_slot_model_cache();
    }
    v16 = rf_multiplayer_game_mode_get();
    if ( v16 == 1 || v16 == 2 )
      v17 = *(unsigned __int8 *)(rf_local_fpgun_player + 48);
    else
      v17 = 999;
    if ( v17 != dword_662F70 )
    {
      rf_fpgun_release_cycle_slot_model_cache();
      rf_fpgun_initialize_cycle_slot_model_cache();
    }
  }
  else if ( !rf_multiplayer_runtime_mode && dword_662F6C != -1 )
  {
    rf_fpgun_release_cycle_slot_model_cache();
    rf_fpgun_initialize_cycle_slot_model_cache();
  }
  return runtime;
}

