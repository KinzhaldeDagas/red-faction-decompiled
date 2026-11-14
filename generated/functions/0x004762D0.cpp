// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004762D0 rf_cutscene_update_and_render_frame
// UNREALRED VERIFIED [cutscene-playback-20261028]: Requires local player/view state and active cutscene record0x6FB24C on timer path; no null guards. Ensures view mode2 through0x412280 if not already2. When byte argument==0 polls UI callback0x4766B0 and updates mode2 player view, advances segment index+2056 when timer+2064 elapsed. Reaching count+4 ends/restores cutscene, activates all subtype83 completion events, requests immediate panel11 and calls0x4478C0. Otherwise starts next segment. Before segment end, named curve+2080 begins when delay timer+2068 elapses: reset delay timer, zero elapsed+2132, set curve-active byte+2136, restore camera position and arm movement timer+2072 using current segment+8 duration/1.017579913*1000,+0.5,trunc. While curve active, elapsed += frame_delta/1.017579913, evaluate cubic Bezier into camera+2084 with t=elapsed/duration; no t clamp or zero-duration
// guard. Elapsed movement timer clears active byte AFTER evaluation. Optional segment ID+16 resolves look-at object, adjusts target via0x4BD150 and entity height+2008, normalizes direction and rebuilds camera matrix+2096. Nonzero argument skips cutscene input/timer/aiming updates but STILL calls main level update0x444D30,0x442950 and player-view render. Tail computes h=trunc(9*helper570F60()/16), y=h+trunc((helper570F70()-h)/2), sets black render color and emits rectangle call0x572CD0(0,y,helper570F60(),2,state). Return is that drawing helper result, not playback status.
int __cdecl rf_cutscene_update_and_render_frame(char a1)
{
  int v1; // eax
  float copy_result[3]; // [esp+4h] [ebp-44h] BYREF
  float lhs[3]; // [esp+10h] [ebp-38h] BYREF
  int v5; // [esp+1Ch] [ebp-2Ch]
  float out_vector[3]; // [esp+20h] [ebp-28h] BYREF
  int v7; // [esp+2Ch] [ebp-1Ch]
  float v8; // [esp+30h] [ebp-18h]
  int v9; // [esp+34h] [ebp-14h]
  int v10; // [esp+38h] [ebp-10h]
  int v11; // [esp+3Ch] [ebp-Ch]
  int v12; // [esp+40h] [ebp-8h]
  int physical_screen_width; // [esp+44h] [ebp-4h]

  if ( rf_view_wrapper_get_dword8(*(_DWORD *)(rf_local_fpgun_player + 196)) != 2 )
    rf_camera_slot_set_state5(*(_DWORD *)(rf_local_fpgun_player + 196));
  if ( !a1 )
  {
    rf_ui_poll_and_dispatch_event((int (__cdecl *)(int))rf_cutscene_ui_event_callback);
    if ( rf_view_wrapper_get_dword8(*(_DWORD *)(rf_local_fpgun_player + 196)) == 2 )
    {
      rf_player_build_referenced_object_controls(rf_local_fpgun_player);
      v10 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_fpgun_player + 20));
      if ( v10 )
      {
        v9 = v10 + 1800;
        rf_player_apply_input_stance_dispatch_and_fire_release(rf_local_fpgun_player, (float *)(v10 + 1800));
      }
    }
    if ( rf_replicator_has_elapsed((int *)(dword_6FB24C + 2064)) )
    {
      if ( ++*(_DWORD *)(dword_6FB24C + 2056) < *(_DWORD *)(dword_6FB24C + 4) )
      {
        rf_cutscene_start_segment(dword_6FB24C, *(_DWORD *)(dword_6FB24C + 2056));
      }
      else
      {
        rf_cutscene_end_restore_player_state();
        rf_cutscene_activate_completion_events();
        rf_ui_request_panel_immediate(11, 0);
        rf_ui_reset_keyboard_and_mouse_input();
      }
    }
    else
    {
      if ( *(_DWORD *)(dword_6FB24C + 2080) && rf_replicator_has_elapsed((int *)(dword_6FB24C + 2068)) )
      {
        rf_replicator_reset((_DWORD *)(dword_6FB24C + 2068));
        *(float *)(dword_6FB24C + 2132) = 0.0;
        *(_BYTE *)(dword_6FB24C + 2136) = 1;
        v1 = sub_552200(unk_6FB258, *(_DWORD *)(dword_6FB24C + 2060));
        rf_vector_copy((float *)(dword_6FB24C + 2084), copy_result, (const float *)(*(_DWORD *)v1 + 4));
        rf_replicator_arm_milliseconds(
          (int *)(dword_6FB24C + 2072),
          (int)(*(float *)(*(_DWORD *)(dword_6FB24C + 2076) + 8) / 1.017579913139343 * 1000.0 + 0.5));
      }
      if ( *(_BYTE *)(dword_6FB24C + 2136) == 1 )
      {
        *(float *)(dword_6FB24C + 2132) = rf_frame_delta_seconds / 1.017579913139343 + *(float *)(dword_6FB24C + 2132);
        v8 = *(float *)(dword_6FB24C + 2132) / *(float *)(*(_DWORD *)(dword_6FB24C + 2076) + 8);
        rf_cubic_bezier_evaluate_position(
          (float **)(*(_DWORD *)(dword_6FB24C + 2080) + 8),
          (float *)(dword_6FB24C + 2084),
          v8);
      }
      if ( rf_replicator_has_elapsed((int *)(dword_6FB24C + 2072)) )
      {
        *(_BYTE *)(dword_6FB24C + 2136) = 0;
        rf_replicator_reset((_DWORD *)(dword_6FB24C + 2072));
      }
      if ( *(_DWORD *)(*(_DWORD *)(dword_6FB24C + 2076) + 16) != -1 )
      {
        v7 = rf_object_find_by_saved_identifier(*(_DWORD *)(*(_DWORD *)(dword_6FB24C + 2076) + 16));
        if ( v7 )
        {
          rf_vector3_copy_return_destination(lhs, (float *)(v7 + 60));
          rf_object_copy_node_or_common_world_position(v7, (int)lhs);
          v5 = rf_entity_resolve_handle(*(_DWORD *)(v7 + 44));
          if ( v5 )
            lhs[1] = *(float *)(v5 + 2008);
          rf_vector_subtract(lhs, out_vector, (const float *)(dword_6FB24C + 2084));
          rf_vector_normalize_reciprocal_sqrt(out_vector);
          rf_orientation_matrix_from_normalized_direction((float *)(dword_6FB24C + 2096), out_vector);
        }
      }
    }
  }
  sub_444D30();
  rf_render_local_player_auxiliary_views_and_visibility_union();
  rf_player_render_view(rf_local_fpgun_player, 0);
  v11 = 9 * rf_renderer_get_physical_screen_width() / 16;
  v12 = v11 + (rf_renderer_get_physical_screen_height() - v11) / 2;
  physical_screen_width = rf_renderer_get_physical_screen_width();
  rf_renderer_reset_viewport_full_screen();
  rf_render_color_set_rgba8(0, 0, 0, 255);
  return rf_renderer_fill_rectangle_clipped(0, v12, physical_screen_width, 2, dword_182ABB8);
}

