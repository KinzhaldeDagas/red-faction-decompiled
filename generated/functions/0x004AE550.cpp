// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE550 rf_splitscreen_update_render_and_check_match_end
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Cdecl BYTE skipUpdate. Always dereference first local player/view wrapper to copy camera position and matrix, zero local velocity; no runtime/count/NULL entry
// guard. If skipUpdate==0: only while pause query AL==0 update audio and ambient sounds. Monitor-view predicate must equal EXACT1 to substitute resolved owned entity pose
// at2004/2016. If second-player pointer87C5B4 nonNULL compute its pose too and push SIX words(pos0,zeroVelocity,mat0,pos1,zeroVelocity,mat1) to568F70, cleanup24; verified wrapper
// consumes ONLY first3, so second pose is ignored by actual audio ABI, not justification to retype wrapper. Without second player call568D20 directly with first3. Then, even when
// paused, call input owner4E0DF0(selected7B25D8), clear other player's control block via442000(entity+1800 or dereferenced view target+1800), and invoke level-update444D30 (delegates
// enforce own gates). Other-player selection is second if selected==first, otherwise first; no NULL second guard on this path. skipUpdate!=0 skips all those update calls, not later
// score-limit checks. Always call442950, draw black separator (0,216,640,16,alpha192) plus opaque(0,214,640,3) and(0,231,640,3) using global clip182ABB8. Render first player with
// arg0 regardless count; for local indices1..<count increment global18092E0 then render. Reset full viewport; draw pause overlay only pause AL EXACT1. If endedBYTE7B25DC already
// nonzero skip remaining limit/end side effects, but preceding rendering/update still runs. Otherwise skipUpdate0 and pause0 subtract frame delta from float7B25C8 EVEN when
// no-time-limit BYTE7B25DD!=0; set ended1 only ordered countdown<0 AND no-time-limit byte0. If no-score-limit BYTE7B25DE==0, check signed16 local score at player.stats44+2 and
// signedDWORD extra16 records757668 stride84 (activeDWORD0,scoreDWORD4) against signed limit7B2574. These score checks run even paused/render-only and can set ended1. Query4AF080
// global score-table maximum, play announcer row8 exactly max==limit-5 and changed from7B25E8; otherwise row9 exactly max==limit-1 and changed; update7B25E8, no crossed-threshold
// detection. On newly ended: query rank4AF030 for first and optional second signed16 score; for each resolved entity only, stop firing if422270 returns EXACT1, clear playerBYTE4016,
// toggle alternate zoom only if incoming zoom flag nonzero. Play announcer row4(stopAll1,onlyIfIdle0). Choose result-pointer7B25E4: without second first-rank1->row5(662CBC),elseNULL;
// with second both-rank1->row10(662CF8),onlyfirst->row6(662CC8),onlysecond->row7(662CD4),elseNULL. Rank helper falls back1 on no match, not guaranteed valid standings. No immediate
// panel transition or permanent update freeze here.
void __cdecl rf_splitscreen_update_render_and_check_match_end(char a1)
{
  float v1[3]; // [esp+Ch] [ebp-B0h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-A4h] BYREF
  int v3; // [esp+24h] [ebp-98h]
  int v4; // [esp+28h] [ebp-94h]
  int score_rank_or_one; // [esp+2Ch] [ebp-90h]
  int v6; // [esp+30h] [ebp-8Ch]
  int *v7; // [esp+34h] [ebp-88h]
  int v8; // [esp+38h] [ebp-84h]
  int v9; // [esp+3Ch] [ebp-80h]
  int v10; // [esp+40h] [ebp-7Ch]
  int v11; // [esp+44h] [ebp-78h]
  float v12[3]; // [esp+48h] [ebp-74h] BYREF
  float v13[9]; // [esp+54h] [ebp-68h] BYREF
  int v14; // [esp+78h] [ebp-44h]
  float destination[3]; // [esp+7Ch] [ebp-40h] BYREF
  float v16[3]; // [esp+88h] [ebp-34h] BYREF
  float v17[9]; // [esp+94h] [ebp-28h] BYREF
  int i; // [esp+B8h] [ebp-4h]

  rf_entity_view_copy_referenced_position(destination, *(_DWORD *)(rf_local_player_entries[0] + 196));
  rf_vector3_set_components_return_destination(v16, 0.0, 0.0, 0.0);
  rf_entity_view_copy_referenced_matrix_2016((int)v17, *(_DWORD **)(rf_local_player_entries[0] + 196));
  if ( !a1 )
  {
    if ( !rf_game_pause_gate_query() )
    {
      if ( rf_player_view_target_is_monitor(rf_local_player_entries[0]) )
      {
        v14 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[0] + 20));
        if ( v14 )
        {
          rf_vector_copy(destination, copy_result, (const float *)(v14 + 2004));
          rf_matrix3_copy(v17, (const float *)(v14 + 2016));
        }
      }
      if ( dword_87C5B4 )
      {
        rf_entity_view_copy_referenced_position(v12, *(_DWORD *)(dword_87C5B4 + 196));
        rf_entity_view_copy_referenced_matrix_2016((int)v13, *(_DWORD **)(dword_87C5B4 + 196));
        if ( rf_player_view_target_is_monitor(dword_87C5B4) )
        {
          v11 = rf_entity_resolve_handle(*(_DWORD *)(dword_87C5B4 + 20));
          if ( v11 )
          {
            rf_vector_copy(v12, v1, (const float *)(v11 + 2004));
            rf_matrix3_copy(v13, (const float *)(v11 + 2016));
          }
        }
        rf_sound_update_listener_and_instances_adapter(destination, (int)v16, v17);
      }
      else
      {
        rf_sound_update_listener_and_instances(destination, (int)v16, v17);
      }
      rf_ambient_sounds_update();
    }
    sub_4E0DF0(dword_7B25D8);
    if ( dword_7B25D8 == rf_local_player_entries[0] )
    {
      v10 = rf_entity_resolve_handle(*(_DWORD *)(dword_87C5B4 + 20));
      if ( v10 )
        rf_player_control_clear_vectors_and_fields1C20((float *)(v10 + 1800));
      else
        rf_player_control_clear_vectors_and_fields1C20((float *)(**(_DWORD **)(dword_87C5B4 + 196) + 1800));
    }
    else
    {
      v9 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[0] + 20));
      if ( v9 )
        rf_player_control_clear_vectors_and_fields1C20((float *)(v9 + 1800));
      else
        rf_player_control_clear_vectors_and_fields1C20((float *)(**(_DWORD **)(rf_local_player_entries[0] + 196) + 1800));
    }
    sub_444D30();
  }
  rf_render_local_player_auxiliary_views_and_visibility_union();
  rf_render_color_set_rgba8(0, 0, 0, 192);
  rf_renderer_fill_rectangle_clipped(0, 216, 640, 16, dword_182ABB8);
  rf_render_color_set_rgba8(0, 0, 0, 255);
  rf_renderer_fill_rectangle_clipped(0, 214, 640, 3, dword_182ABB8);
  rf_renderer_fill_rectangle_clipped(0, 231, 640, 3, dword_182ABB8);
  rf_player_render_view(rf_local_player_entries[0], 0);
  for ( i = 1; i < rf_local_player_entry_count; ++i )
  {
    ++LODWORD(flt_18092A0[16]);
    rf_player_render_view(rf_local_player_entries[i], 0);
  }
  rf_renderer_reset_viewport_full_screen();
  if ( rf_game_pause_gate_query() == 1 )
    rf_pause_overlay_render();
  if ( !unk_7B25DC )
  {
    if ( !a1 && !rf_game_pause_gate_query() )
    {
      unk_7B25C8 = unk_7B25C8 - rf_frame_delta_seconds;
      if ( unk_7B25C8 < 0.0 && !unk_7B25DD )
        unk_7B25DC = 1;
    }
    if ( !unk_7B25DE )
    {
      for ( i = 0; i < rf_local_player_entry_count; ++i )
      {
        if ( *(__int16 *)(*(_DWORD *)(rf_local_player_entries[i] + 44) + 2) >= dword_7B2574 )
          unk_7B25DC = 1;
      }
      for ( i = 0; i < 16; ++i )
      {
        v7 = &unk_757668[21 * i];
        if ( *v7 && v7[1] >= dword_7B2574 )
          unk_7B25DC = 1;
      }
      v8 = rf_splitscreen_score_table_maximum_floor_zero();
      if ( v8 != dword_7B2574 - 5 || v8 == unk_7B25E8 )
      {
        if ( v8 == dword_7B2574 - 1 && v8 != unk_7B25E8 )
          rf_splitscreen_play_announcer_row(9, 0, 0);
      }
      else
      {
        rf_splitscreen_play_announcer_row(8, 0, 0);
      }
      unk_7B25E8 = v8;
    }
    if ( unk_7B25DC )
    {
      score_rank_or_one = rf_splitscreen_find_score_rank_or_one(*(__int16 *)(*(_DWORD *)(rf_local_player_entries[0] + 44)
                                                                           + 2));
      v6 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[0] + 20));
      if ( v6 )
      {
        if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(v6 + 44), *(_DWORD *)(v6 + 676)) )
          rf_entity_stop_weapon_firing(*(_DWORD *)(v6 + 44), *(_DWORD *)(v6 + 676));
        *(_BYTE *)(rf_local_player_entries[0] + 4016) = 0;
        if ( rf_player_get_alt_zoom_in_flag_byte(rf_local_player_entries[0]) )
          rf_player_toggle_alt_zoom(rf_local_player_entries[0]);
      }
      if ( dword_87C5B4 )
      {
        v4 = rf_splitscreen_find_score_rank_or_one(*(__int16 *)(*(_DWORD *)(dword_87C5B4 + 44) + 2));
        v3 = rf_entity_resolve_handle(*(_DWORD *)(dword_87C5B4 + 20));
        if ( v3 )
        {
          if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(v3 + 44), *(_DWORD *)(v3 + 676)) )
            rf_entity_stop_weapon_firing(*(_DWORD *)(v3 + 44), *(_DWORD *)(v3 + 676));
          *(_BYTE *)(dword_87C5B4 + 4016) = 0;
          if ( rf_player_get_alt_zoom_in_flag_byte(dword_87C5B4) )
            rf_player_toggle_alt_zoom(dword_87C5B4);
        }
      }
      rf_splitscreen_play_announcer_row(4, 1, 0);
      if ( dword_87C5B4 )
      {
        if ( score_rank_or_one == 1 && v4 == 1 )
        {
          unk_7B25E4 = &unk_662CF8;
        }
        else if ( score_rank_or_one == 1 )
        {
          unk_7B25E4 = &unk_662CC8;
        }
        else if ( v4 == 1 )
        {
          unk_7B25E4 = &unk_662CD4;
        }
        else
        {
          unk_7B25E4 = 0;
        }
      }
      else if ( score_rank_or_one == 1 )
      {
        unk_7B25E4 = &unk_662CBC;
      }
      else
      {
        unk_7B25E4 = 0;
      }
    }
  }
}

