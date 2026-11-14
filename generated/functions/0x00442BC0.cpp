// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442BC0 rf_player_render_view
// VERIFIED CORRECTION: Player-view frame renderer fog selection. An eligible liquid room uses its RGB, zero start, and room end. Outside that branch, enabled global fog first applies fixed RGB (92,61,27), then eligible level-custom RGB/start/end can override it in the same frame. Selected RGB also becomes clear color. Fog is disabled before later presentation overlays.
// UNREALRED VERIFIED [authored-sky-renderer] Player rendering passes no sky transform while angular speed is nonpositive and passes the current axis-rotation matrix while speed is positive.
// UNREALRED VERIFIED [correction-pass-20260903]: Root player-view frame renderer for one player/view; owns camera and FOV setup, world and authored-sky presentation, first-person weapon work, and ordered gameplay HUD/overlay dispatch.
void __cdecl rf_player_render_view(int a1, int a2)
{
  int physical_screen_height; // eax
  float *v3; // eax
  const float *v4; // eax
  float *v5; // eax
  int viewport_width; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int first_dword; // eax
  _DWORD *v12; // eax
  int v13; // eax
  int v14; // eax
  _DWORD *v15; // eax
  _DWORD *v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  double v23; // st7
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // [esp-14h] [ebp-1F8h]
  int v30; // [esp-8h] [ebp-1ECh]
  int v31; // [esp-4h] [ebp-1E8h]
  int v32; // [esp+0h] [ebp-1E4h]
  int v33; // [esp+0h] [ebp-1E4h]
  int v34; // [esp+0h] [ebp-1E4h]
  int v35; // [esp+0h] [ebp-1E4h]
  int physical_screen_width; // [esp+4h] [ebp-1E0h]
  int v37; // [esp+4h] [ebp-1E0h]
  int viewport_height; // [esp+4h] [ebp-1E0h]
  int v39; // [esp+4h] [ebp-1E0h]
  int v40; // [esp+4h] [ebp-1E0h]
  int v41; // [esp+4h] [ebp-1E0h]
  int v42; // [esp+4h] [ebp-1E0h]
  float v43; // [esp+4h] [ebp-1E0h]
  int v44; // [esp+4h] [ebp-1E0h]
  float *v45; // [esp+4h] [ebp-1E0h]
  int v46; // [esp+4h] [ebp-1E0h]
  int v47; // [esp+4h] [ebp-1E0h]
  int v48; // [esp+4h] [ebp-1E0h]
  int v49; // [esp+4h] [ebp-1E0h]
  int v50; // [esp+4h] [ebp-1E0h]
  int v51; // [esp+4h] [ebp-1E0h]
  int v52; // [esp+4h] [ebp-1E0h]
  int v53; // [esp+4h] [ebp-1E0h]
  int v54; // [esp+8h] [ebp-1DCh]
  int v55; // [esp+8h] [ebp-1DCh]
  int v56; // [esp+8h] [ebp-1DCh]
  int v57; // [esp+8h] [ebp-1DCh]
  int v58; // [esp+8h] [ebp-1DCh]
  int v59; // [esp+8h] [ebp-1DCh]
  int v60; // [esp+8h] [ebp-1DCh]
  int v61; // [esp+8h] [ebp-1DCh]
  int v62; // [esp+8h] [ebp-1DCh]
  int v63; // [esp+8h] [ebp-1DCh]
  int v64; // [esp+8h] [ebp-1DCh]
  int v65; // [esp+8h] [ebp-1DCh]
  int v66; // [esp+8h] [ebp-1DCh]
  int v67; // [esp+8h] [ebp-1DCh]
  int v68; // [esp+8h] [ebp-1DCh]
  int v69; // [esp+8h] [ebp-1DCh]
  int v70; // [esp+8h] [ebp-1DCh]
  int v71; // [esp+8h] [ebp-1DCh]
  int v72; // [esp+8h] [ebp-1DCh]
  float v73[3]; // [esp+38h] [ebp-1ACh] BYREF
  int v74[3]; // [esp+44h] [ebp-1A0h] BYREF
  _BYTE v75[36]; // [esp+50h] [ebp-194h] BYREF
  float copy_result[3]; // [esp+74h] [ebp-170h] BYREF
  float v77[3]; // [esp+80h] [ebp-164h] BYREF
  _DWORD *v78; // [esp+8Ch] [ebp-158h]
  int v79; // [esp+90h] [ebp-154h] BYREF
  int v80; // [esp+94h] [ebp-150h] BYREF
  int v81; // [esp+98h] [ebp-14Ch]
  int v82; // [esp+9Ch] [ebp-148h]
  _DWORD v83[3]; // [esp+A0h] [ebp-144h] BYREF
  _DWORD v84[3]; // [esp+ACh] [ebp-138h] BYREF
  int v85; // [esp+B8h] [ebp-12Ch]
  int v86; // [esp+BCh] [ebp-128h]
  int v87; // [esp+C0h] [ebp-124h]
  int v88; // [esp+C4h] [ebp-120h]
  int v89; // [esp+C8h] [ebp-11Ch]
  int v90; // [esp+CCh] [ebp-118h]
  int v91; // [esp+D0h] [ebp-114h]
  int v92; // [esp+D4h] [ebp-110h]
  int v93; // [esp+D8h] [ebp-10Ch]
  int v94; // [esp+DCh] [ebp-108h]
  int v95; // [esp+E0h] [ebp-104h] BYREF
  int v96; // [esp+E4h] [ebp-100h]
  int v97; // [esp+E8h] [ebp-FCh] BYREF
  int v98; // [esp+ECh] [ebp-F8h]
  int v99; // [esp+F0h] [ebp-F4h]
  int v100; // [esp+F4h] [ebp-F0h]
  int v101; // [esp+F8h] [ebp-ECh]
  int v102; // [esp+FCh] [ebp-E8h] BYREF
  int v103; // [esp+100h] [ebp-E4h] BYREF
  int v104; // [esp+104h] [ebp-E0h] BYREF
  int v105; // [esp+108h] [ebp-DCh] BYREF
  int v106; // [esp+10Ch] [ebp-D8h] BYREF
  int v107; // [esp+110h] [ebp-D4h]
  int v108; // [esp+114h] [ebp-D0h] BYREF
  int v109; // [esp+118h] [ebp-CCh]
  int v110; // [esp+11Ch] [ebp-C8h] BYREF
  int j; // [esp+120h] [ebp-C4h]
  int v112[3]; // [esp+130h] [ebp-B4h] BYREF
  int v113; // [esp+13Ch] [ebp-A8h] BYREF
  float v114; // [esp+140h] [ebp-A4h] BYREF
  char v115; // [esp+147h] [ebp-9Dh] BYREF
  float v116; // [esp+148h] [ebp-9Ch] BYREF
  _BYTE v117[4]; // [esp+14Ch] [ebp-98h] BYREF
  int v118; // [esp+150h] [ebp-94h] BYREF
  int i; // [esp+154h] [ebp-90h]
  char Buffer[64]; // [esp+158h] [ebp-8Ch] BYREF
  int active_world_count; // [esp+19Ch] [ebp-48h]
  int v122; // [esp+1A0h] [ebp-44h]
  int v123; // [esp+1A4h] [ebp-40h]
  int v124; // [esp+1A8h] [ebp-3Ch]
  int v125; // [esp+1ACh] [ebp-38h]
  int v126; // [esp+1B0h] [ebp-34h]
  int v127; // [esp+1B4h] [ebp-30h]
  int v128; // [esp+1B8h] [ebp-2Ch]
  int room; // [esp+1BCh] [ebp-28h]
  float alt_zoom_factor; // [esp+1C0h] [ebp-24h]
  int v131; // [esp+1C4h] [ebp-20h]
  int *v132; // [esp+1C8h] [ebp-1Ch]
  float out_vector[3]; // [esp+1CCh] [ebp-18h] BYREF
  int v134; // [esp+1E0h] [ebp-4h]

  unk_87C640 = a1;
  if ( (dword_6E6B88[0] & 1) == 0 )
  {
    dword_6E6B88[0] |= 1u;
    rf_vector3_default_construct_noop(&flt_6E6B7C);
    v134 = -1;
  }
  if ( (dword_6E6B88[0] & 2) == 0 )
  {
    dword_6E6B88[0] |= 2u;
    rf_matrix3_construct((char *)flt_6E6B58);
    v134 = -1;
  }
  room = 0;
  if ( (dword_6E6B88[0] & 4) == 0 )
  {
    dword_6E6B88[0] |= 4u;
    rf_vector3_default_construct_noop(&unk_6E6B4C);
    v134 = -1;
  }
  if ( (dword_6E6B88[0] & 8) == 0 )
  {
    dword_6E6B88[0] |= 8u;
    rf_vector3_default_construct_noop(&unk_6E6B40);
    v134 = -1;
  }
  if ( (dword_6E6B88[0] & 0x10) == 0 )
  {
    dword_6E6B88[0] |= 0x10u;
    rf_vector3_default_construct_noop(&unk_6E6B34);
    v134 = -1;
  }
  rf_renderer_set_far_clip_distance(flt_661580);
  v132 = (int *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( rf_splitscreen_runtime_active || !rf_unhide_global_owner_present() )
  {
    rf_renderer_set_viewport_and_relative_clip(
      *(_DWORD *)(a1 + 200),
      *(_DWORD *)(a1 + 204),
      *(_DWORD *)(a1 + 208),
      *(_DWORD *)(a1 + 212));
  }
  else
  {
    v128 = 9 * rf_renderer_get_physical_screen_width() / 16;
    physical_screen_width = rf_renderer_get_physical_screen_width();
    physical_screen_height = rf_renderer_get_physical_screen_height();
    rf_renderer_set_viewport_and_relative_clip(0, (physical_screen_height - v128) / 2, physical_screen_width, v128);
  }
  alt_zoom_factor = rf_player_query_alt_zoom_factor(a1);
  if ( alt_zoom_factor <= 0.0 )
    flt_66157C = *(float *)(a1 + 216);
  else
    flt_66157C = *(float *)(a1 + 216) / alt_zoom_factor;
  v3 = rf_entity_view_copy_referenced_position(v77, *(_DWORD *)(a1 + 196));
  rf_vector_copy(&flt_6E6B7C, copy_result, v3);
  v4 = (const float *)rf_entity_view_copy_referenced_matrix_2016((int)v75, *(_DWORD **)(a1 + 196));
  rf_matrix3_copy(flt_6E6B58, v4);
  room = rf_camera_slot_get_room(*(void ***)(a1 + 196));
  if ( !rf_view_wrapper_get_dword8(*(_DWORD *)(a1 + 196)) )
  {
    if ( rf_entity_has_attached_use_vehicle((int)v132) )
    {
      v127 = rf_entity_resolve_handle(v132[128]);
      if ( rf_entity_class_flag1000(v127) )
        rf_player_apply_vehicle_camera_node_and_cache_transform(a1, v127, &flt_6E6B7C, (int)flt_6E6B58);
    }
    if ( v132 )
    {
      v126 = rf_clutter_find_by_uid(v132[1300]);
      if ( v126 )
      {
        if ( v132[169] == unk_911C80 )
          rf_object_mark_hidden_inactive(v126);
      }
    }
  }
  v5 = rf_vector_scale((float *)v74, 0.14, flt_6E6B70);
  rf_vector_subtract(&flt_6E6B7C, out_vector, v5);
  if ( v132 )
  {
    v125 = rf_entity_resolve_handle(v132[128]);
    if ( rf_entity_class_flag1000(v125) )
      rf_vector_copy(out_vector, v73, &flt_6E6B7C);
  }
  if ( *(_BYTE *)(a1 + 4016) == 1 )
  {
    rf_renderer_set_camera_projection_dispatch((int)flt_6E6B58, (int)out_vector, 30.0, 1, 1);
    a2 |= 2u;
  }
  else
  {
    rf_renderer_set_camera_projection_dispatch((int)flt_6E6B58, (int)out_vector, flt_66157C, 1, 1);
  }
  if ( room && rf_liquid_room_contains_point(room, (int)&flt_6E6B7C) )
  {
    rf_renderer_set_far_clip_distance(*(float *)(room + 400));
    rf_renderer_set_vertex_fog(
      1,
      *(_BYTE *)(room + 396),
      *(_BYTE *)(room + 397),
      *(_BYTE *)(room + 398),
      0.0,
      *(float *)(room + 400));
    rf_render_color_set_rgba8(
      *(unsigned __int8 *)(room + 396),
      *(unsigned __int8 *)(room + 397),
      *(unsigned __int8 *)(room + 398),
      255);
    if ( rf_renderer_get_backend_selector() == 102 )
    {
      v54 = dword_182ABB8;
      v37 = rf_renderer_get_viewport_height() - 1;
      viewport_width = rf_renderer_get_viewport_width();
      rf_renderer_fill_rectangle_clipped(0, 0, viewport_width - 1, v37, v54);
    }
    else
    {
      v55 = dword_182ABB8;
      viewport_height = rf_renderer_get_viewport_height();
      v7 = rf_renderer_get_viewport_width();
      rf_renderer_fill_rectangle_clipped(0, 0, v7, viewport_height, v55);
    }
    if ( dword_66158C == -1 )
    {
      if ( !rf_entity_has_attached_use_vehicle((int)v132) )
      {
        dword_66158C = rf_gamesound_play_event(16, 0, 0.0, 1.0);
        rf_audio_set_environment_if_property_extension_enabled("underwater");
      }
    }
    else if ( rf_entity_has_attached_use_vehicle((int)v132) )
    {
      rf_gamesound_stop_voice_handle(dword_66158C);
      dword_66158C = -1;
      rf_audio_set_environment_if_property_extension_enabled("generic");
    }
  }
  else
  {
    if ( unk_6EDD44 )
    {
      rf_renderer_set_far_clip_distance(flt_661588);
      rf_renderer_set_vertex_fog(1, 92, 61, 27, unk_6E6AD0, flt_661588);
      rf_render_color_set_rgba8(92, 61, 27, 255);
      v56 = dword_182ABB8;
      v39 = rf_renderer_get_physical_screen_height();
      v8 = rf_renderer_get_physical_screen_width();
      rf_renderer_fill_rectangle_clipped(0, 0, v8, v39, v56);
    }
    if ( dword_66158C != -1 )
    {
      rf_gamesound_stop_voice_handle(dword_66158C);
      dword_66158C = -1;
      if ( room )
      {
        if ( rf_local_fpgun_player )
          rf_audio_set_environment_if_property_extension_enabled((char *)(room + 74));
      }
    }
    if ( byte_661584 == 1 && unk_6FC34C > 0.0 )
    {
      v122 = unk_6FC344;
      v123 = unk_6FC345;
      v124 = unk_6FC346;
      if ( !unk_6FC355 )
      {
        rf_renderer_set_far_clip_distance(unk_6FC34C);
        rf_renderer_set_vertex_fog(1, v122, v123, v124, unk_6FC348, unk_6FC34C);
      }
      rf_render_color_set_rgba8(v122, v123, v124, 255);
      if ( rf_renderer_get_backend_selector() == 102 )
      {
        v57 = dword_182ABB8;
        v40 = rf_renderer_get_viewport_height() - 1;
        v9 = rf_renderer_get_viewport_width();
        rf_renderer_fill_rectangle_clipped(0, 0, v9 - 1, v40, v57);
      }
      else
      {
        v58 = dword_182ABB8;
        v41 = rf_renderer_get_viewport_height();
        v10 = rf_renderer_get_viewport_width();
        rf_renderer_fill_rectangle_clipped(0, 0, v10, v41, v58);
      }
    }
  }
  rf_renderer_reserved_noop_5260d0();
  rf_world_decal_advance_fade_and_expiry();
  rf_volume_prepare_visible_for_view();
  rf_object_clear_rendered_and_physics_skip_flags();
  if ( rf_skybox_rotation_degrees_per_second <= 0.0 )
    rf_world_render_rooms_with_authored_sky(rf_world_solid, room, a2, 0);
  else
    rf_world_render_rooms_with_authored_sky(rf_world_solid, room, a2, (int)&rf_skybox_rotation_matrix);
  rf_render_color_set_rgba8(255, 255, 255, 255);
  rf_debug_draw_georegion_registry_shapes();
  rf_projected_shadows_dispatch_frame();
  if ( unk_6E6ABE )
  {
    active_world_count = rf_light_get_active_world_count();
    for ( i = 0; i < active_world_count; ++i )
    {
      rf_vector3_default_construct_noop(v112);
      rf_light_get_active_entry_position_range_rgb_category(
        i,
        (float *)v112,
        (int)v117,
        &v116,
        (float *)&v118,
        &v114,
        (float *)&v113,
        &v115);
      if ( !v115 )
      {
        rf_float_clamp_in_place((float *)&v118, 0.0, 1.0);
        rf_float_clamp_in_place(&v114, 0.0, 1.0);
        rf_float_clamp_in_place((float *)&v113, 0.0, 1.0);
        rf_render_color_set_rgba8(
          (unsigned __int8)(int)(*(float *)&v118 * 255.0),
          (unsigned __int8)(int)(v114 * 255.0),
          (unsigned __int8)(int)(*(float *)&v113 * 255.0),
          255);
        rf_debug_draw_wire_sphere_backend_dispatch((int)v112, 1.0, dword_187CC5C);
      }
    }
    sprintf(Buffer, "%d lights in level", active_world_count);
    rf_font_draw_text_screen(20, 10, (unsigned __int8 *)Buffer, -1, unk_182ABBC);
  }
  if ( unk_6E6ABF )
  {
    rf_render_color_set_rgba8(128, 128, 0, 255);
    for ( j = 0; ; ++j )
    {
      first_dword = rf_receiver_get_first_dword(unk_6FC3E8);
      if ( j >= first_dword )
        break;
      v59 = dword_182ABA0;
      v42 = *(_DWORD *)sub_552200(unk_6FC3E8, j) + 52;
      v32 = *(_DWORD *)sub_552200(unk_6FC3E8, j) + 16;
      v12 = (_DWORD *)sub_552200(unk_6FC3E8, j);
      rf_debug_draw_oriented_wire_box(*v12 + 4, v32, v42, v59);
    }
    rf_render_color_set_rgba8(64, 64, 0, 255);
    for ( j = 0; ; ++j )
    {
      v13 = rf_receiver_get_first_dword(rf_push_region_registry);
      if ( j >= v13 )
        break;
      if ( **(_DWORD **)sub_552200(rf_push_region_registry, j) == 1 )
      {
        v60 = dword_187CC5C;
        v14 = sub_552200(rf_push_region_registry, j);
        v43 = rf_sqrt_float(*(float *)(*(_DWORD *)v14 + 60));
        v15 = (_DWORD *)sub_552200(rf_push_region_registry, j);
        rf_debug_draw_wire_sphere_backend_dispatch(*v15 + 12, v43, v60);
      }
      else if ( **(_DWORD **)sub_552200(rf_push_region_registry, j) == 3 )
      {
        v61 = dword_182ABA0;
        v44 = *(_DWORD *)sub_552200(rf_push_region_registry, j) + 88;
        v33 = *(_DWORD *)sub_552200(rf_push_region_registry, j) + 24;
        v16 = (_DWORD *)sub_552200(rf_push_region_registry, j);
        rf_debug_draw_oriented_wire_box(*v16 + 12, v33, v44, v61);
      }
      v62 = dword_182ABA0;
      v45 = (float *)(*(_DWORD *)sub_552200(rf_push_region_registry, j) + 76);
      v17 = sub_552200(rf_push_region_registry, j);
      rf_renderer_draw_world_aabb_wire_edges((float *)(*(_DWORD *)v17 + 64), v45, v62);
    }
  }
  if ( unk_6E6AC8 && dword_681E38 )
    rf_font_draw_text_screen(
      10,
      10,
      (unsigned __int8 *)(&off_661598)[*(_DWORD *)(*(_DWORD *)(dword_681E38 + 2136) + 4)],
      -1,
      unk_182ABBC);
  rf_clutter_render_registered_clocks();
  rf_mission_events_render_debug_icons();
  rf_trigger_debug_draw_registry();
  if ( unk_6FC354 && byte_661585 )
    rf_glare_process_current_local_player_pass(1);
  else
    rf_glare_process_current_local_player_pass(0);
  if ( unk_6E6AC5 )
    rf_glass_debug_draw_last_tessellation_grid();
  if ( unk_6E6AC6 )
    rf_mover_debug_draw_all();
  if ( unk_6E6AC7 )
    rf_burn_effect_debug_draw_attachment_nodes();
  rf_rail_trail_render_crossed_triangles();
  rf_renderer_reserved_noop_5738C0();
  if ( *(_BYTE *)(a1 + 4016) == 1 )
  {
    rf_render_state_pack(&v110, 0, 0, 0, 1, 0, 3);
    rf_render_color_set_rgba8(0, 128, 0, 255);
    v63 = v110;
    v46 = rf_renderer_get_viewport_height();
    v18 = rf_renderer_get_viewport_width();
    rf_renderer_fill_rectangle_clipped(0, 0, v18, v46, v63);
    if ( dword_661594 == -1 )
    {
      dword_661594 = rf_bitmap_load_with_optional_mipmap_generation("gogglemask.tga", (void *)0xFFFFFFFF, 0);
      rf_bitmap_get_resolved_dimensions(dword_661594, &dword_6E6B2C, &dword_6E6B30);
    }
    if ( dword_661594 > -1 )
    {
      rf_render_state_pack(&v108, 2, 1, 2, 3, 0, 3);
      v109 = rf_renderer_get_viewport_width() / 2;
      v107 = rf_renderer_get_viewport_height() / 2;
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_661594,
        0,
        0,
        v109,
        v107,
        0,
        0,
        dword_6E6B2C,
        dword_6E6B30,
        0,
        0,
        v108);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_661594,
        v109,
        0,
        v109,
        v107,
        0,
        0,
        dword_6E6B2C,
        dword_6E6B30,
        1,
        0,
        v108);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_661594,
        0,
        v107,
        v109,
        v107,
        0,
        0,
        dword_6E6B2C,
        dword_6E6B30,
        0,
        1,
        v108);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_661594,
        v109,
        v107,
        v109,
        v107,
        0,
        0,
        dword_6E6B2C,
        dword_6E6B30,
        1,
        1,
        v108);
    }
  }
  if ( *(_BYTE *)(a1 + 4016) == 1 && *(int *)(a1 + 4232) >= 0 )
  {
    rf_renderer_get_viewport_rectangle(&v106, &v103, &v104, &v105);
    v106 = 0;
    v103 = 0;
    if ( rf_splitscreen_runtime_active || rf_multiplayer_runtime_mode )
      v105 = (int)((double)v105 * 0.8999999761581421);
    else
      v105 /= 2;
    v104 = v105;
    v103 += rf_renderer_get_viewport_height() / 2 - v105 / 2;
    v106 += rf_renderer_get_viewport_width() / 2 - v104 / 2;
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_render_state_pack(&v102, 2, 1, 2, 1, 0, 3);
    rf_bitmap_blit_subrectangle_backend_dispatch(
      *(_DWORD *)(a1 + 4232),
      v106,
      v103,
      v104,
      v105,
      0,
      0,
      64,
      64,
      0,
      0,
      v102);
  }
  if ( *(_BYTE *)(a1 + 4016) == 1 )
  {
    v96 = rf_renderer_get_viewport_width() / 2;
    v93 = rf_renderer_get_viewport_height() / 2;
    if ( dword_661590 == -1 )
    {
      dword_661590 = rf_bitmap_load_with_optional_mipmap_generation("railgun_text.vbm", (void *)0xFFFFFFFF, 1);
      rf_bitmap_get_resolved_dimensions(dword_661590, &dword_6E6B24, &dword_6E6B28);
    }
    rf_render_color_set_rgba8(0, 0, 0, 255);
    v98 = v96 + 10;
    v94 = rf_renderer_get_viewport_width() / 3;
    v92 = v96 - 10 - v94;
    v87 = v93 + 10;
    v89 = rf_renderer_get_viewport_height() / 4;
    v88 = v93 - 10 - v89;
    v90 = rf_renderer_get_viewport_width() / 5;
    rf_render_state_pack(&v97, 0, 0, 0, 3, 0, 3);
    rf_renderer_fill_rectangle_clipped(v98, v93, v94, 1, v97);
    rf_renderer_fill_rectangle_clipped(v92, v93, v94, 1, v97);
    rf_renderer_fill_rectangle_clipped(v96, v87, 1, v89, v97);
    rf_renderer_fill_rectangle_clipped(v96, v88, 1, v89, v97);
    rf_renderer_fill_rectangle_clipped(v94 + v98 - v90, v93 - 1, v90, 3, v97);
    rf_renderer_fill_rectangle_clipped(v92, v93 - 1, v90, 3, v97);
    rf_render_state_pack(&v95, 2, 1, 2, 3, 0, 3);
    rf_bitmap_draw_unscaled_clipped(dword_661590, v94 + v98 - v90, v93 + 5, v95);
    rf_render_color_set_rgba8(0, 0, 0, 65);
    v101 = rf_renderer_get_viewport_width() / 6;
    v99 = rf_renderer_get_viewport_height() / 14;
    v100 = v101 / 2;
    v91 = v99 / 2;
    rf_renderer_fill_rectangle_clipped(v96 - v101 / 2, v93 - v99 / 2, v101, 1, v97);
    rf_renderer_fill_rectangle_clipped(v100 + v96, v93 - v91, 1, v99, v97);
    rf_renderer_fill_rectangle_clipped(v96 - v100, v91 + v93, v101, 1, v97);
    rf_renderer_fill_rectangle_clipped(v96 - v100, v93 - v91, 1, v99, v97);
  }
  rf_hud_reticle_render(a1);
  rf_player_render_fpgun_or_carried_corpse(a1);
  rf_renderer_reserved_noop_5738C0();
  rf_renderer_set_vertex_fog(0, 0, 0, 0, -1.0, -1.0);
  if ( room && rf_liquid_room_contains_point(room, (int)&flt_6E6B7C) )
  {
    rf_render_color_set_rgba8(
      *(unsigned __int8 *)(room + 396),
      *(unsigned __int8 *)(room + 397),
      *(unsigned __int8 *)(room + 398),
      *(_DWORD *)(room + 424));
    if ( rf_renderer_get_backend_selector() == 102 )
    {
      v64 = dword_182ABB8;
      v47 = rf_renderer_get_viewport_height() - 1;
      v19 = rf_renderer_get_viewport_width();
      rf_renderer_fill_rectangle_clipped(0, 0, v19 - 1, v47, v64);
    }
    else
    {
      v65 = dword_182ABB8;
      v48 = rf_renderer_get_viewport_height();
      v20 = rf_renderer_get_viewport_width();
      rf_renderer_fill_rectangle_clipped(0, 0, v20, v48, v65);
    }
    rf_render_color_set_rgba8(255, 255, 255, 255);
    if ( *(_BYTE *)(room + 428) )
      rf_underwater_particles_update_and_render();
  }
  rf_renderer_reserved_noop_5738C0();
  rf_renderer_set_camera_projection_dispatch((int)flt_6E6B58, (int)&flt_6E6B7C, flt_66157C, 1, 1);
  if ( dword_681E38
    && rf_entity_has_attached_use_vehicle(dword_681E38)
    && !rf_entity_is_parent_jeep_relation1((int)v132) )
  {
    rf_player_render_attached_vehicle_cockpit(a1);
  }
  rf_renderer_reserved_noop_5738C0();
  rf_render_color_set_rgba8(0, 0, 0, 255);
  v66 = dword_182ABB8;
  v49 = rf_renderer_get_viewport_height();
  v21 = rf_renderer_get_viewport_width();
  rf_renderer_fill_rectangle_clipped(v21 - 1, 0, 1, v49, v66);
  v67 = dword_182ABB8;
  v34 = rf_renderer_get_viewport_width();
  v22 = rf_renderer_get_viewport_height();
  rf_renderer_fill_rectangle_clipped(0, v22 - 1, v34, 1, v67);
  if ( rf_ui_panel_stack_current_id() == 18 )
  {
    if ( (a1 == rf_local_player_entries[0] || !rf_object_resolve_handle(dword_87C31C)) && !*(_BYTE *)(a1 + 4016) )
      rf_player_hud_render_ordinary(a1);
  }
  else if ( !*(_BYTE *)(a1 + 4016) )
  {
    rf_player_hud_render_ordinary(a1);
  }
  if ( rf_player_has_no_resolved_entity(a1) || rf_player_resolved_entity_is_dead(a1) )
  {
    rf_weapon_selector_is_open = 0;
  }
  else if ( rf_weapon_selector_is_open )
  {
    rf_weapon_selector_draw();
  }
  if ( rf_player_has_no_resolved_entity(a1) || rf_player_resolved_entity_is_dead(a1) )
  {
    v86 = 9 * rf_renderer_get_physical_screen_width() / 16;
    v85 = (rf_renderer_get_physical_screen_height() - v86) / 2;
    if ( rf_replicator_has_elapsed(&unk_6E6AF8) )
    {
      rf_replicator_reset(&unk_6E6AF8);
    }
    else if ( rf_replicator_is_armed(&unk_6E6AF8) )
    {
      v23 = (double)rf_replicator_signed_remaining_milliseconds(&unk_6E6AF8) * 255.0 / 750.0;
      rf_render_color_set_rgba8(170, 21, 0, (int)v23);
      v68 = dword_182ABB8;
      v50 = v86;
      v24 = rf_renderer_get_physical_screen_width();
      rf_renderer_fill_rectangle_clipped(0, v85, v24, v50, v68);
    }
    if ( !rf_multiplayer_runtime_mode )
    {
      if ( rf_replicator_has_elapsed(&unk_6E6B08) )
      {
        rf_replicator_reset(&unk_6E6B08);
      }
      else if ( !rf_replicator_is_armed(&unk_6E6B08) )
      {
        v84[0] = unk_88E114;
        v84[1] = unk_88E120;
        v84[2] = unk_88D460;
        v83[0] = rf_request_panel2_unforced;
        v83[1] = rf_prepare_start_level_and_request_panel5;
        v83[2] = rf_prepare_savegame_level_and_request_panel5;
        if ( rf_savegame_validate_headers_and_read_info(&unk_890400, nullptr, nullptr, nullptr) )
          rf_ui_show_choice_modal(unk_88E118, unk_88E11C, 3, (int)v84, (int)v83, 0, 0);
        else
          rf_ui_show_choice_modal(unk_88E118, unk_88E11C, 2, (int)v84, (int)v83, 0, 0);
        rf_replicator_reset(&unk_6E6AF8);
      }
    }
    rf_render_color_set_rgba8(170, 21, 0, 255);
    v69 = dword_182ABB8;
    v51 = v85;
    v25 = rf_renderer_get_physical_screen_width();
    rf_renderer_fill_rectangle_clipped(0, 0, v25, v51, v69);
    v70 = dword_182ABB8;
    v52 = v85;
    v35 = rf_renderer_get_physical_screen_width();
    v26 = rf_renderer_get_physical_screen_height();
    rf_renderer_fill_rectangle_clipped(0, v26 - v85, v35, v52, v70);
  }
  if ( rf_multiplayer_runtime_mode == 1 )
    rf_multiplayer_hud_render();
  rf_corpse_flag10_when_common_collision_flag_clear();
  if ( !rf_splitscreen_runtime_active && rf_game_pause_gate_query() == 1 )
    rf_pause_overlay_render();
  if ( unk_6E6AC9 == 1 )
  {
    v81 = rf_renderer_get_physical_screen_width();
    v82 = rf_renderer_get_physical_screen_height();
    if ( rf_splitscreen_runtime_active )
      rf_debug_draw_frame_timing_text_and_history(v81 - 120, v82 / 2 - 10);
    else
      rf_debug_draw_frame_timing_text_and_history(v81 - 120, v82 - 10);
  }
  rf_network_bandwidth_overlay_render();
  rf_player_hud_screen_tint_render_decay(a1);
  if ( dword_663290 != -1 )
  {
    rf_bitmap_get_resolved_dimensions(dword_663290, &v79, &v80);
    v71 = unk_187CC7C;
    v31 = v80;
    v30 = v79;
    v29 = rf_renderer_get_physical_screen_height();
    v27 = rf_renderer_get_physical_screen_width();
    rf_bitmap_blit_subrectangle_backend_dispatch(dword_663290, 0, 0, v27, v29, 0, 0, v30, v31, 0, 0, v71);
  }
  v131 = rf_ui_pending_panel_id_get();
  if ( v131 == 8 )
    rf_ui_draw_saving_overlay();
  if ( v132 )
  {
    v78 = (_DWORD *)rf_clutter_find_by_uid(v132[1300]);
    if ( v78 )
    {
      if ( v132[169] == unk_911C80 )
        rf_object_reactivate_from_respawn(v78);
    }
  }
  if ( !rf_splitscreen_runtime_active && !rf_multiplayer_runtime_mode )
  {
    if ( *(float *)(a1 + 4564) > 0.0 )
    {
      if ( rf_player_resolved_entity_is_dead(a1) || rf_player_has_no_resolved_entity(a1) )
        *(_DWORD *)(a1 + 16) &= ~0x100u;
      if ( (*(_DWORD *)(a1 + 16) & 0x100) != 0 )
      {
        *(float *)(a1 + 4564) = *(float *)(a1 + 4564) - rf_frame_delta_seconds * 255.0 / *(float *)(a1 + 4568);
        if ( *(float *)(a1 + 4564) <= 0.0 )
        {
          *(float *)(a1 + 4564) = 0.0;
          *(_DWORD *)(a1 + 16) &= ~0x100u;
        }
      }
      else
      {
        *(float *)(a1 + 4564) = rf_frame_delta_seconds * 255.0 / *(float *)(a1 + 4568) + *(float *)(a1 + 4564);
      }
      if ( *(float *)(a1 + 4564) <= 255.0 )
      {
        rf_render_color_set_rgba8(0, 0, 0, (int)*(float *)(a1 + 4564));
      }
      else if ( rf_ui_top_panel_is11_or18() )
      {
        if ( rf_player_has_no_resolved_entity(a1) || rf_player_resolved_entity_is_dead(a1) )
          rf_player_request_panel13_and_stop_voices();
        if ( (*(_DWORD *)(a1 + 16) & 0x80) == 0 )
          *(float *)(a1 + 4564) = 0.0;
        if ( (*(_DWORD *)(a1 + 16) & 0x200) != 0 )
        {
          if ( dword_681E38 )
            rf_object_mark_for_deferred_delete(dword_681E38);
          rf_player_request_panel13_and_stop_voices();
        }
        if ( (*(_DWORD *)(a1 + 16) & 0x1000) != 0 )
          rf_ui_request_panel_immediate(13, 0);
        rf_render_color_set_rgba8(0, 0, 0, 255);
        if ( *(_DWORD *)(a1 + 4572) )
        {
          if ( rf_player_has_no_resolved_entity(a1) )
          {
            *(_DWORD *)(rf_local_fpgun_player + 16) &= ~0x80u;
            (*(void (__cdecl **)(int))(a1 + 4572))(a1);
          }
          else
          {
            (*(void (__cdecl **)(int))(a1 + 4572))(a1);
          }
        }
      }
      else
      {
        *(float *)(a1 + 4564) = 255.0;
        rf_render_color_set_rgba8(0, 0, 0, (int)*(float *)(a1 + 4564));
      }
      v72 = dword_182ABB8;
      v53 = rf_renderer_get_physical_screen_height();
      v28 = rf_renderer_get_physical_screen_width();
      rf_renderer_fill_rectangle_clipped(0, 0, v28, v53, v72);
      rf_render_color_set_rgba8(255, 255, 255, 255);
    }
    if ( rf_replicator_is_armed(&unk_6E6AF8) && rf_replicator_has_elapsed(&unk_6E6AF8) )
    {
      rf_replicator_reset(&unk_6E6AF8);
      if ( rf_player_has_no_resolved_entity(a1) || rf_player_resolved_entity_is_dead(a1) )
        rf_player_request_panel13_and_stop_voices();
    }
  }
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    rf_multiplayer_draw_stalled_connection_icon();
  unk_87C640 = 0;
}

