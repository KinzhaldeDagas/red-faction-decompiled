// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ECD10 rf_fpgun_initialize_cycle_slot_model_cache
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): No arguments. Skips any nonzero ready byte87C6E6 or dedicated byte704E83 exactly1. For multiplayer and signed local-player character index3932>=0, resets index to0 when >=character count, then scans all32 cycle slots (16-byte stride), considering signed weapon IDs>=0. Character records320 bytes, type index at64+4*weapon. Nonnegative type index loads52-byte custom type; game types1/2 select player byte48, other types999. Stores model in main slot, clears weapon+1304=-1; remote-charge slot additionally loads mapped detonator type when its index>=0. Any valid custom TYPE INDEX sets customFound even if returned model is NULL; this suppresses the ENTIRE default pass, not just that slot. If none found, loads defaults for all valid
// slots and remote-charge detonator; cache character/team becomes current character/999 in multiplayer or-1/-1 in single player. Afterwards loads three state/twelve action entries per valid main slot; machine pistol also loads special machine-pistol entries using same model, remote charge uses secondary model for detonator entries. Ignores asset/animation failures and sets ready=1 regardless. Cache globals662F6C/70 record selected character/team; no own model NULL or weapon/type upper-bound checks, no player+52 assignment.
int rf_fpgun_initialize_cycle_slot_model_cache()
{
  int result; // eax
  int type_model_with_team_materials; // eax
  char *v2; // [esp+0h] [ebp-34h]
  int v3; // [esp+4h] [ebp-30h]
  int v4; // [esp+8h] [ebp-2Ch]
  int v5; // [esp+Ch] [ebp-28h]
  char *v6; // [esp+14h] [ebp-20h]
  int v7; // [esp+18h] [ebp-1Ch]
  int *v8; // [esp+1Ch] [ebp-18h]
  int m; // [esp+20h] [ebp-14h]
  int n; // [esp+20h] [ebp-14h]
  int ii; // [esp+20h] [ebp-14h]
  int jj; // [esp+20h] [ebp-14h]
  int kk; // [esp+20h] [ebp-14h]
  int mm; // [esp+20h] [ebp-14h]
  int i; // [esp+2Ch] [ebp-8h]
  int j; // [esp+2Ch] [ebp-8h]
  int k; // [esp+2Ch] [ebp-8h]
  char v18; // [esp+33h] [ebp-1h]

  result = byte_87C6E6[0];
  if ( !byte_87C6E6[0] && byte_704E83 != 1 )
  {
    rf_performance_clock_elapsed_scaled(1000);
    v18 = 0;
    if ( rf_multiplayer_runtime_mode && *(int *)(rf_local_fpgun_player + 3932) > -1 )
    {
      if ( *(_DWORD *)(rf_local_fpgun_player + 3932) >= rf_multiplayer_character_count )
        *(_DWORD *)(rf_local_fpgun_player + 3932) = 0;
      v8 = &rf_multiplayer_character_table[80 * *(_DWORD *)(rf_local_fpgun_player + 3932)];
      for ( i = 0; i < 32; ++i )
      {
        if ( rf_weapon_cycle_slots_weapon_index[4 * i] > -1 )
        {
          v7 = v8[rf_weapon_cycle_slots_weapon_index[4 * i] + 16];
          if ( v7 > -1 )
          {
            v6 = &byte_87C798[52 * v7];
            v4 = rf_multiplayer_game_mode_get();
            if ( v4 == 1 || v4 == 2 )
            {
              v5 = *(unsigned __int8 *)(rf_local_fpgun_player + 48);
              type_model_with_team_materials = rf_fpgun_load_type_model_with_team_materials(v6, v5);
            }
            else
            {
              v5 = 999;
              type_model_with_team_materials = rf_fpgun_load_type_model_with_team_materials(v6, 999);
            }
            rf_weapon_cycle_slots_runtime_icon[4 * i] = type_model_with_team_materials;
            *((_DWORD *)&rf_weapon_records + 340 * rf_weapon_cycle_slots_weapon_index[4 * i] + 326) = -1;
            if ( rf_weapon_cycle_slots_weapon_index[4 * i] == dword_911C78 )
            {
              v3 = v8[unk_911C88 + 16];
              if ( v3 > -1 )
                unk_87C118[4 * i] = rf_fpgun_load_type_model_with_team_materials(&byte_87C798[52 * v3], v5);
            }
            dword_662F6C = *(_DWORD *)(rf_local_fpgun_player + 3932);
            dword_662F70 = v5;
            v18 = 1;
          }
        }
      }
    }
    if ( !v18 )
    {
      for ( j = 0; j < 32; ++j )
      {
        if ( rf_weapon_cycle_slots_weapon_index[4 * j] > -1 )
        {
          v2 = (char *)&rf_weapon_records + 1360 * rf_weapon_cycle_slots_weapon_index[4 * j];
          rf_weapon_cycle_slots_runtime_icon[4 * j] = rf_fpgun_load_default_weapon_model_and_warm_materials((int)v2);
          *((_DWORD *)v2 + 326) = -1;
          if ( rf_weapon_cycle_slots_weapon_index[4 * j] == dword_911C78 )
            unk_87C118[4 * j] = rf_fpgun_load_default_weapon_model_and_warm_materials((int)&rf_weapon_records + 1360 * unk_911C88);
        }
      }
      if ( rf_multiplayer_runtime_mode )
      {
        dword_662F6C = *(_DWORD *)(rf_local_fpgun_player + 3932);
        dword_662F70 = 999;
      }
      else
      {
        dword_662F6C = -1;
        dword_662F70 = -1;
      }
    }
    for ( k = 0; k < 32; ++k )
    {
      if ( rf_weapon_cycle_slots_weapon_index[4 * k] > -1 )
      {
        for ( m = 0; m < 3; ++m )
          rf_weapon_load_named_animation_entry(
            rf_weapon_cycle_slots_runtime_icon[4 * k],
            rf_weapon_cycle_slots_weapon_index[4 * k],
            (char *)rf_fpgun_state_names[m],
            1);
        for ( n = 0; n < 12; ++n )
          rf_weapon_load_named_animation_entry(
            rf_weapon_cycle_slots_runtime_icon[4 * k],
            rf_weapon_cycle_slots_weapon_index[4 * k],
            (char *)rf_fpgun_action_names[n],
            0);
        if ( rf_weapon_cycle_slots_weapon_index[4 * k] == dword_911CC4 )
        {
          for ( ii = 0; ii < 3; ++ii )
            rf_weapon_load_named_animation_entry(
              rf_weapon_cycle_slots_runtime_icon[4 * k],
              unk_911C98,
              (char *)rf_fpgun_state_names[ii],
              1);
          for ( jj = 0; jj < 12; ++jj )
            rf_weapon_load_named_animation_entry(
              rf_weapon_cycle_slots_runtime_icon[4 * k],
              unk_911C98,
              (char *)rf_fpgun_action_names[jj],
              0);
        }
        if ( rf_weapon_cycle_slots_weapon_index[4 * k] == dword_911C78 )
        {
          for ( kk = 0; kk < 3; ++kk )
            rf_weapon_load_named_animation_entry(unk_87C118[4 * k], unk_911C88, (char *)rf_fpgun_state_names[kk], 1);
          for ( mm = 0; mm < 12; ++mm )
            rf_weapon_load_named_animation_entry(unk_87C118[4 * k], unk_911C88, (char *)rf_fpgun_action_names[mm], 0);
        }
      }
    }
    result = rf_performance_clock_elapsed_scaled(1000);
    byte_87C6E6[0] = 1;
  }
  return result;
}

