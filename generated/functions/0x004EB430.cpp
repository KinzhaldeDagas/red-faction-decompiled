// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EB430 rf_player_update_alt_zoom_factor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Unequal local-global pointer no-op. Equal NULL path calls reset(NULL), which dereferences; not NULL-safe. Missing own entity, dead AL==1, monitor AL==1 or absent alt-zoom weapon flag(nonzero admission) resets flags/factor0 then exits, without stopping sound. Otherwise flags:3988 EXACT1 has priority; options member(player228) action1 held query441F40 EXACT1 adds dt*DOUBLE15 into F32 factor3992, else stops nonnegative global voice662FB0 and sets-1. Only when3988!=1 and3989==1 subtract dt*DOUBLE80 intoF32; ORDERED factor<=1 clears out flag and stops nonnegative voice. NaN does not clear flag. Finally native float clamp to[1,12], preserving NaN. Even no exact-active flags still clamps on valid admission; no factor wrap/finite
// check.
void __cdecl rf_player_update_alt_zoom_factor(int a1)
{
  unsigned int selected_weapon_and_resolve_mesh; // [esp+8h] [ebp-Ch]
  int v2; // [esp+10h] [ebp-4h]

  if ( a1 == rf_local_fpgun_player )
  {
    if ( a1 )
    {
      v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
      if ( v2
        && !rf_entity_is_dead(v2)
        && !rf_player_view_target_is_monitor(a1)
        && (selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1),
            rf_weapon_has_alt_zoom_flag(selected_weapon_and_resolve_mesh)) )
      {
        if ( *(_BYTE *)(a1 + 3988) == 1 )
        {
          if ( rf_input_action_any_bound_key_or_mouse_held(a1 + 228, 1) == 1 )
          {
            *(float *)(a1 + 3992) = rf_frame_delta_seconds * 15.0 + *(float *)(a1 + 3992);
          }
          else if ( dword_662FB0 >= 0 )
          {
            rf_gamesound_stop_voice_handle(dword_662FB0);
            dword_662FB0 = -1;
          }
        }
        else if ( *(_BYTE *)(a1 + 3989) == 1 )
        {
          *(float *)(a1 + 3992) = *(float *)(a1 + 3992) - rf_frame_delta_seconds * 80.0;
          if ( *(float *)(a1 + 3992) <= 1.0 )
          {
            *(_BYTE *)(a1 + 3989) = 0;
            if ( dword_662FB0 >= 0 )
            {
              rf_gamesound_stop_voice_handle(dword_662FB0);
              dword_662FB0 = -1;
            }
          }
        }
        rf_float_clamp_in_place((float *)(a1 + 3992), 1.0, 12.0);
      }
      else
      {
        rf_player_reset_alt_zoom_state(a1);
      }
    }
    else
    {
      rf_player_reset_alt_zoom_state(0);
    }
  }
}

