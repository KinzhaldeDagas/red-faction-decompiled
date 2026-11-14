// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E8A70 rf_player_render_fpgun
// UNREALRED VERIFIED [weapon-holding-variants] Renders the local first-person gun. Foreground projection selects WeaponInfo+0x78 under the same split-screen-active and nonzero Player+0xDC gate, otherwise WeaponInfo+0x74, then restores the ordinary camera projection after rendering.
char __cdecl rf_player_render_fpgun(_DWORD *player)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  int viewport_width; // eax
  double v9; // st7
  float *v10; // eax
  float *v11; // eax
  int v12; // eax
  int v13; // eax
  float *v14; // [esp+Ch] [ebp-6A4h]
  float v15; // [esp+Ch] [ebp-6A4h]
  int v16; // [esp+Ch] [ebp-6A4h]
  int viewport_height; // [esp+10h] [ebp-6A0h]
  float v18; // [esp+10h] [ebp-6A0h]
  float *scalar; // [esp+14h] [ebp-69Ch]
  int scalara; // [esp+14h] [ebp-69Ch]
  float scalarb; // [esp+14h] [ebp-69Ch]
  float v22; // [esp+1Ch] [ebp-694h]
  float v23; // [esp+20h] [ebp-690h]
  float v24[3]; // [esp+24h] [ebp-68Ch] BYREF
  float v25[3]; // [esp+30h] [ebp-680h] BYREF
  float v26[3]; // [esp+3Ch] [ebp-674h] BYREF
  int v27[3]; // [esp+48h] [ebp-668h] BYREF
  float v28[3]; // [esp+54h] [ebp-65Ch] BYREF
  int v29[3]; // [esp+60h] [ebp-650h] BYREF
  float sum_result[3]; // [esp+6Ch] [ebp-644h] BYREF
  int v31[3]; // [esp+78h] [ebp-638h] BYREF
  float v32[3]; // [esp+84h] [ebp-62Ch] BYREF
  float v33[3]; // [esp+90h] [ebp-620h] BYREF
  float scaled_result[3]; // [esp+9Ch] [ebp-614h] BYREF
  float v35[3]; // [esp+A8h] [ebp-608h] BYREF
  float copy_result[3]; // [esp+B4h] [ebp-5FCh] BYREF
  int v37; // [esp+C0h] [ebp-5F0h]
  float v38[3]; // [esp+C4h] [ebp-5ECh] BYREF
  char v39[36]; // [esp+D0h] [ebp-5E0h] BYREF
  char v40[80]; // [esp+F4h] [ebp-5BCh] BYREF
  int thruster_1_node_index; // [esp+144h] [ebp-56Ch]
  float v42[3]; // [esp+148h] [ebp-568h] BYREF
  char v43[80]; // [esp+154h] [ebp-55Ch] BYREF
  char v44[36]; // [esp+1A4h] [ebp-50Ch] BYREF
  float lhs[3]; // [esp+1C8h] [ebp-4E8h] BYREF
  char v46[36]; // [esp+1D4h] [ebp-4DCh] BYREF
  float v47; // [esp+1F8h] [ebp-4B8h]
  float v48; // [esp+1FCh] [ebp-4B4h]
  int v49; // [esp+200h] [ebp-4B0h]
  char v50[12]; // [esp+204h] [ebp-4ACh] BYREF
  _BYTE v51[72]; // [esp+210h] [ebp-4A0h] BYREF
  int runtime_pointer; // [esp+258h] [ebp-458h]
  int v53[3]; // [esp+25Ch] [ebp-454h] BYREF
  char v54[36]; // [esp+268h] [ebp-448h] BYREF
  int *v55; // [esp+28Ch] [ebp-424h]
  char v56[36]; // [esp+290h] [ebp-420h] BYREF
  char v57[80]; // [esp+2B4h] [ebp-3FCh] BYREF
  float v58[3]; // [esp+304h] [ebp-3ACh] BYREF
  int weapon_node_index; // [esp+310h] [ebp-3A0h]
  char v60[36]; // [esp+314h] [ebp-39Ch] BYREF
  int v61; // [esp+338h] [ebp-378h]
  unsigned int v62; // [esp+33Ch] [ebp-374h]
  int v63[3]; // [esp+340h] [ebp-370h] BYREF
  char v64[32]; // [esp+34Ch] [ebp-364h] BYREF
  int v65; // [esp+36Ch] [ebp-344h]
  int v66; // [esp+370h] [ebp-340h]
  int v67; // [esp+374h] [ebp-33Ch]
  float v68[9]; // [esp+378h] [ebp-338h] BYREF
  float v69[3]; // [esp+39Ch] [ebp-314h] BYREF
  char v70[36]; // [esp+3A8h] [ebp-308h] BYREF
  int v71; // [esp+3CCh] [ebp-2E4h]
  float v72; // [esp+3D0h] [ebp-2E0h]
  char v73[80]; // [esp+3D4h] [ebp-2DCh] BYREF
  int room; // [esp+424h] [ebp-28Ch]
  char v75[36]; // [esp+428h] [ebp-288h] BYREF
  float v76[3]; // [esp+44Ch] [ebp-264h] BYREF
  float v77; // [esp+458h] [ebp-258h]
  int v78[3]; // [esp+45Ch] [ebp-254h] BYREF
  int v79; // [esp+468h] [ebp-248h] BYREF
  float v80; // [esp+46Ch] [ebp-244h] BYREF
  float muzzle_position[3]; // [esp+470h] [ebp-240h] BYREF
  int v82; // [esp+47Ch] [ebp-234h]
  float v83; // [esp+480h] [ebp-230h]
  unsigned int usable_preferred_weapon; // [esp+484h] [ebp-22Ch]
  float v85[3]; // [esp+488h] [ebp-228h] BYREF
  char v86[84]; // [esp+494h] [ebp-21Ch] BYREF
  float v87[3]; // [esp+4E8h] [ebp-1C8h] BYREF
  float v88[3]; // [esp+4F4h] [ebp-1BCh] BYREF
  int v89; // [esp+500h] [ebp-1B0h]
  float v90[33]; // [esp+504h] [ebp-1ACh] BYREF
  int v91; // [esp+588h] [ebp-128h] BYREF
  float destination[48]; // [esp+58Ch] [ebp-124h] BYREF
  int j; // [esp+64Ch] [ebp-64h]
  float *source; // [esp+650h] [ebp-60h]
  float v95[9]; // [esp+654h] [ebp-5Ch] BYREF
  int i; // [esp+678h] [ebp-38h]
  char v97[4]; // [esp+67Ch] [ebp-34h] BYREF
  int node_adapter; // [esp+680h] [ebp-30h]
  int first_dword; // [esp+684h] [ebp-2Ch]
  int owned_riotshield_clutter; // [esp+688h] [ebp-28h]
  unsigned int selected_weapon_and_resolve_mesh; // [esp+68Ch] [ebp-24h]
  char *v102; // [esp+690h] [ebp-20h]
  bool v103; // [esp+697h] [ebp-19h]
  int v104; // [esp+698h] [ebp-18h]
  int silencer_node_index; // [esp+69Ch] [ebp-14h]
  void *v106; // [esp+6A0h] [ebp-10h]
  int v107; // [esp+6ACh] [ebp-4h]

  if ( player != (_DWORD *)rf_local_fpgun_player )
    return 0;
  v106 = (void *)rf_entity_resolve_handle(player[5]);
  if ( !v106 )
    return 0;
  if ( (void *)rf_player_resolve_view_entity_with_monitor_fallback((int)player) != v106 )
    return 0;
  if ( unk_87C6E5 == 1 )
  {
    sprintf(&unk_18CD828, "weapon state: %s", rf_fpgun_state_names[unk_87C6EC]);
    rf_font_draw_text_screen(0, 250, (unsigned __int8 *)&unk_18CD828, -1, dword_182ABBC);
    sprintf(&unk_18CD828, "weapon action: %s", rf_fpgun_action_names[unk_87C6E8]);
    rf_font_draw_text_screen(0, 260, (unsigned __int8 *)&unk_18CD828, -1, dword_182ABBC);
  }
  if ( *((_BYTE *)player + 3894) )
  {
    if ( *((_BYTE *)player + 4016) == 1 )
    {
      return 0;
    }
    else if ( rf_entity_is_dead((int)v106) )
    {
      return 0;
    }
    else if ( *((_BYTE *)player + 3980) == 1 )
    {
      *((_BYTE *)player + 3980) = 0;
      return 0;
    }
    else if ( !rf_view_wrapper_get_dword8(player[49]) && player[13] )
    {
      v104 = rf_entity_resolve_handle(*((_DWORD *)v106 + 128));
      if ( rf_entity_class_use_is4(v104) )
      {
        return 0;
      }
      else if ( rf_fpgun_action_is_active((int)player, 7u)
             || rf_entity_is_parent_jeep_relation1((int)v106)
             || !rf_entity_weapon_is_holstered_for_actions((int)v106) && player[992] == -1 )
      {
        if ( rf_player_query_alt_zoom_factor((int)player) <= 0.0 )
        {
          selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(player);
          if ( selected_weapon_and_resolve_mesh == -1 )
          {
            return 0;
          }
          else
          {
            v102 = (char *)&rf_weapon_records + 1360 * selected_weapon_and_resolve_mesh;
            if ( rf_splitscreen_runtime_active && player[55] )
              rf_renderer_set_camera_projection_dispatch(
                (int)v106 + 2016,
                (int)v106 + 2004,
                *((float *)v102 + 30),
                1,
                1);
            else
              rf_renderer_set_camera_projection_dispatch(
                (int)v106 + 2016,
                (int)v106 + 2004,
                *((float *)v102 + 29),
                1,
                1);
            owned_riotshield_clutter = rf_player_find_owned_riotshield_clutter((int)player);
            if ( owned_riotshield_clutter && !unk_87C6E4 )
            {
              rf_vector_construct_no_unwind((char *)destination, 0xCu, 16, rf_vector3_default_construct_noop);
              rf_vector_construct_no_unwind((char *)v90, 8u, 16, rf_vector3_default_construct_noop);
              rf_vector3_default_construct_noop(v87);
              rf_render_state_pack(&v91, 2, 2, 3, 2, 0, 3);
              node_adapter = rf_model_handle_find_node_adapter(player[13], "fk-shield");
              rf_vector3_default_construct_noop(v88);
              rf_matrix3_construct((char *)v95);
              v97[0] = -1;
              v97[1] = -1;
              v97[2] = -1;
              v97[3] = 64;
              for ( i = 0; i < 25; ++i )
              {
                if ( player[i + 1082] )
                {
                  for ( j = *(_DWORD *)(player[i + 1082] + 32); j != player[i + 1082] + 4; j = *(_DWORD *)(j + 28) )
                  {
                    v89 = 0;
                    for ( source = *(float **)(j + 20); source != (float *)j; source = *((float **)source + 5) )
                    {
                      rf_vector_copy(&destination[3 * v89], copy_result, source);
                      rf_vector_copy(v87, v35, (const float *)player + 1030);
                      v2 = rf_vector_multiply_scalar((const float *)player + 1024, scaled_result, flt_662FF4);
                      rf_vector_accumulate(v87, v2);
                      v3 = rf_vector_multiply_scalar((const float *)player + 1027, v33, flt_662FF8);
                      rf_vector_accumulate(v87, v3);
                      v4 = rf_vector_multiply_scalar((const float *)player + 1021, v32, flt_662FFC);
                      rf_vector_accumulate(v87, v4);
                      rf_vmesh_compose_prop_world_transform(
                        player[13],
                        node_adapter,
                        (float *)player + 1021,
                        (int)v87,
                        (int)v95,
                        v88);
                      rf_vector_rotate_by_matrix3(&destination[3 * v89], v95);
                      rf_vector_accumulate(&destination[3 * v89], v88);
                      v90[2 * v89] = source[3];
                      v90[2 * v89++ + 1] = source[4];
                    }
                    rf_renderer_submit_textured_world_polygon_color4_dispatch(
                      *(_DWORD *)player[i + 1082],
                      v89,
                      (int)destination,
                      (int)v90,
                      v91,
                      v97);
                  }
                }
              }
            }
            rf_render_color_set_rgba8(255, 255, 255, 255);
            if ( selected_weapon_and_resolve_mesh == dword_911C80 && unk_87C6E4 )
            {
              rf_vfx_update_instance((int *)dword_87C6E0, rf_frame_delta_seconds, 0, 0, 0, 1);
              if ( rf_vfx_get_remaining_time((const void *)dword_87C6E0, 0) <= 0.0 )
              {
                sub_403C20((int)v106 + 672, dword_911C80);
                *((_DWORD *)v106 + 169) = -1;
                *((_DWORD *)v106 + 1300) = -1;
                usable_preferred_weapon = rf_player_find_usable_preferred_weapon((int)player);
                rf_player_request_weapon_switch((int)player, usable_preferred_weapon, 1, 0);
                unk_87C6E4 = 0;
              }
              else
              {
                rf_model_render_options_construct(v86);
                scalar = rf_vector_scale((float *)v27, flt_663008, (float *)player + 1027);
                v14 = rf_vector_scale((float *)v29, flt_663004, (float *)player + 1024);
                v5 = rf_vector_scale((float *)v31, flt_663000, (float *)player + 1021);
                v6 = rf_vector_add((const float *)player + 1030, sum_result, v5);
                v7 = rf_vector_add(v6, v28, v14);
                rf_vector_add(v7, v85, scalar);
                rf_model_handle_render_all_adapter(dword_87C6E0, (int)v85, (int)(player + 1021), (int)v86);
              }
              rf_renderer_set_camera_projection_dispatch((int)v106 + 2016, (int)v106 + 2004, flt_66157C, 1, 1);
              return 1;
            }
            else
            {
              first_dword = rf_receiver_get_first_dword(v106);
              v23 = *((float *)v106 + 30) + 1.0;
              rf_light_build_active_list_for_sphere_query(first_dword, (int)v106 + 60, v23, 1, 0);
              if ( rf_weapon_is_riot_stick(selected_weapon_and_resolve_mesh) )
              {
                if ( rf_fpgun_state_is_resident((int)player, 2) )
                {
                  rf_vector3_default_construct_noop(muzzle_position);
                  rf_player_compose_fpgun_muzzle_world_transform(player, muzzle_position, nullptr);
                  if ( rf_replicator_is_armed((_DWORD *)v106 + 1243) && !rf_replicator_has_elapsed((int *)v106 + 1243) )
                  {
                    rf_renderer_set_pending_texture_handles(*((_DWORD *)v102 + 27), -1);
                    rf_renderer_world_billboard_rectangle_backend_wrapper(
                      (int)muzzle_position,
                      0.0,
                      *((float *)v102 + 28),
                      *((float *)v102 + 28),
                      SLODWORD(rf_particle_glow_billboard_render_state));
                  }
                  v83 = *((float *)v102 + 26);
                  if ( rf_entity_runtime_flags810_has_mask2000((int)v106) )
                    v83 = v83 * 1.5;
                  rf_renderer_set_pending_texture_handles(*((_DWORD *)v102 + 25), -1);
                  rf_renderer_world_billboard_rectangle_backend_wrapper(
                    (int)muzzle_position,
                    0.0,
                    v83,
                    v83,
                    SLODWORD(rf_particle_glow_billboard_render_state));
                  v82 = (int)rf_random_float_range(1000.0, 3000.0);
                  rf_replicator_arm_milliseconds(player + 994, v82);
                }
              }
              else
              {
                rf_vector3_default_construct_noop(v78);
                if ( rf_player_get_visible_muzzle_flash_parameters((int)player, (int)v78, &v79, &v80) )
                {
                  rf_renderer_set_pending_texture_handles(v79, -1);
                  v77 = rf_random_float_range(0.0, 6.2831855);
                  if ( rf_game_pause_gate_query() == 1 || (*((_DWORD *)v102 + 153) & 0x2000) != 0 )
                    v77 = 0.0;
                  rf_renderer_world_billboard_rectangle_backend_wrapper(
                    (int)v78,
                    v77,
                    v80,
                    v80,
                    SLODWORD(rf_particle_glow_billboard_render_state));
                }
              }
              if ( rf_weapon_has_pilot_flame(selected_weapon_and_resolve_mesh) )
              {
                if ( dword_662FD4 == -1 )
                  dword_662FD4 = rf_model_handle_find_node_adapter(player[13], "pilot_light_1");
                if ( dword_87C6F4 )
                {
                  if ( dword_662FD4 != -1 )
                  {
                    rf_vector3_default_construct_noop(v76);
                    rf_matrix3_construct(v75);
                    rf_vmesh_compose_prop_world_transform(
                      player[13],
                      dword_662FD4,
                      (float *)player + 1021,
                      (int)(player + 1030),
                      (int)v75,
                      v76);
                    room = rf_camera_slot_get_room((void **)player[49]);
                    if ( room )
                    {
                      if ( !rf_liquid_room_contains_point(room, (int)v76) )
                      {
                        rf_model_render_options_construct(v73);
                        rf_model_handle_render_all_adapter(dword_87C6F4, (int)v76, (int)v75, (int)v73);
                      }
                    }
                  }
                }
              }
              if ( selected_weapon_and_resolve_mesh == rf_weapon_id_shoulder_cannon
                && dword_662FE0 > -1
                && flt_87C6D4 > (double)*((float *)player + 1008) )
              {
                rf_vector3_default_construct_noop(v69);
                rf_matrix3_construct(v70);
                v72 = *((float *)&unk_912068 + 340 * selected_weapon_and_resolve_mesh);
                v71 = (int)(*((float *)player + 1008) / flt_87C6D4 * (double)unk_87C6D0);
                if ( rf_player_compose_fpgun_muzzle_world_transform(player, v69, nullptr) )
                {
                  rf_renderer_set_pending_texture_handles(dword_662FE0 + v71 + 1, -1);
                  rf_renderer_world_billboard_rectangle_backend_wrapper(
                    (int)v69,
                    0.0,
                    v72,
                    v72,
                    SLODWORD(rf_particle_glow_billboard_render_state));
                }
              }
              if ( player[13] )
              {
                rf_model_render_options_construct(v64);
                *(_DWORD *)v64 |= 0x100u;
                *(_DWORD *)v64 |= 0x480u;
                v67 = *((_DWORD *)v106 + 1309);
                rf_matrix3_copy(v68, (const float *)v106 + 18);
                if ( dword_681E38 )
                {
                  if ( (*(_DWORD *)(dword_681E38 + 2068) & 0x20000) != 0 )
                  {
                    v65 = dword_66130C;
                    if ( (*(_DWORD *)(dword_681E38 + 2068) & 0x40000) != 0 )
                      v66 = dword_661308;
                  }
                  else if ( (*(_DWORD *)(dword_681E38 + 2068) & 0x40000) != 0 )
                  {
                    v65 = dword_661308;
                  }
                }
                rf_model_handle_render_all_adapter(player[13], (int)(player + 1030), (int)(player + 1021), (int)v64);
              }
              if ( player[18] != -1 && player[19] != -1 )
              {
                v62 = rf_player_get_selected_weapon_and_resolve_mesh(player);
                v61 = *((_DWORD *)v106 + v62 + 203);
                rf_render_color_set_rgba8(255, 0, 0, 255);
                rf_matrix3_construct(v60);
                rf_vector3_default_construct_noop(v63);
                if ( rf_bitmap_animation_metadata_query(dword_662FC8, nullptr) > 9 )
                {
                  rf_vmesh_compose_prop_world_transform(
                    player[13],
                    player[19],
                    (float *)player + 1021,
                    (int)(player + 1030),
                    (int)v60,
                    (float *)v63);
                  rf_renderer_set_pending_texture_handles(dword_662FC8 + v61 % 10 + 1, -1);
                  rf_renderer_oriented_billboard_backend_wrapper(
                    (int)v63,
                    (int)v60,
                    0.013,
                    SLODWORD(rf_particle_glow_billboard_render_state));
                  rf_vmesh_compose_prop_world_transform(
                    player[13],
                    player[18],
                    (float *)player + 1021,
                    (int)(player + 1030),
                    (int)v60,
                    (float *)v63);
                  rf_renderer_set_pending_texture_handles(dword_662FC8 + v61 / 10 % 10 + 1, -1);
                  rf_renderer_oriented_billboard_backend_wrapper(
                    (int)v63,
                    (int)v60,
                    0.013,
                    SLODWORD(rf_particle_glow_billboard_render_state));
                }
              }
              if ( rf_weapon_has_remote_charge_flag(selected_weapon_and_resolve_mesh) )
              {
                weapon_node_index = rf_weapon_get_weapon_node_index((int)player, selected_weapon_and_resolve_mesh);
                if ( weapon_node_index != -1 )
                {
                  if ( *((_BYTE *)player + 4164) )
                  {
                    rf_vector3_default_construct_noop(v58);
                    rf_matrix3_construct(v56);
                    rf_vmesh_compose_prop_world_transform(
                      player[13],
                      weapon_node_index,
                      (float *)player + 1021,
                      (int)(player + 1030),
                      (int)v56,
                      v58);
                    rf_model_render_options_construct(v57);
                    rf_model_handle_render_all_adapter(unk_87C6F0, (int)v58, (int)v56, (int)v57);
                  }
                }
              }
              if ( selected_weapon_and_resolve_mesh == dword_911CE0 )
              {
                rf_vector3_default_construct_noop(v53);
                rf_matrix3_construct(v54);
                v55 = (int *)rf_fpgun_selected_mesh_resolve(player, dword_911CE0);
                if ( player[1006] == -1
                  || player[1007] == -1
                  || dword_662FD8 == -1
                  || dword_662FDC == -1
                  || !dword_87C6DC )
                {
                  runtime_pointer = rf_model_handle_get_runtime_pointer(v55);
                  player[1006] = rf_character_find_named_node_index(*(const char **)(runtime_pointer + 7504), "fork_1");
                  player[1007] = rf_character_find_named_node_index(*(const char **)(runtime_pointer + 7504), "cart_1");
                  rf_vfx_start_instance((int *)dword_87C6DC, 0, 1.0, 0);
                }
                rf_vmesh_compose_prop_world_transform(
                  (int)v55,
                  player[1006],
                  (float *)player + 1021,
                  (int)(player + 1030),
                  (int)v54,
                  (float *)v53);
                if ( dword_87C6DC )
                {
                  if ( rf_vfx_get_remaining_time((const void *)dword_87C6DC, 0) <= 0.0 )
                    rf_vfx_start_instance((int *)dword_87C6DC, 0, 1.0, 0);
                  rf_vfx_update_instance((int *)dword_87C6DC, rf_frame_delta_seconds, 0, (int)v53, (int)v54, 1);
                  rf_model_render_options_construct(v50);
                  *(_DWORD *)v50 = 2;
                  rf_color4_set_bytes_return_destination(v51, 127, 127, 127, 32);
                  rf_model_handle_render_all_adapter(dword_87C6DC, (int)v53, (int)v54, (int)v50);
                }
                if ( rf_fpgun_has_reload_fire_or_riotstick_state2(player) )
                {
                  if ( *((float *)player + 1008) < 0.4000000059604645 )
                  {
                    if ( (dword_87FBA0 & 1) == 0 )
                    {
                      dword_87FBA0 |= 1u;
                      v107 = 0;
                      rf_render_state_pack(&unk_87FB9C, 2, 2, 3, 1, 1, 0);
                      v107 = -1;
                    }
                    if ( (dword_87FBA0 & 2) == 0 )
                    {
                      dword_87FBA0 |= 2u;
                      v107 = 1;
                      rf_render_state_pack(&dword_87FB98, 0, 0, 0, 3, 0, 3);
                      v107 = -1;
                    }
                    if ( *((float *)player + 1008) >= 0.2000000029802322 )
                    {
                      v48 = (0.4000000059604645 - *((float *)player + 1008)) * 5.0;
                      v48 = v48 * v48;
                    }
                    else
                    {
                      v22 = *((float *)player + 1008) * 5.0;
                      v48 = rf_sqrt_float(v22);
                    }
                    v49 = (int)(v48 * 64.0);
                    v48 = v48 * 1.0;
                    rf_renderer_set_pending_texture_handles(dword_662FD8, -1);
                    rf_render_color_set_rgba8(128, 255, 255, 255);
                    rf_renderer_world_billboard_aspect_backend_dispatch((int)v53, 0.0, v48, unk_87FB9C);
                    rf_render_color_set_rgba8(128, 255, 255, v49);
                    scalara = dword_87FB98;
                    viewport_height = rf_renderer_get_viewport_height();
                    viewport_width = rf_renderer_get_viewport_width();
                    rf_renderer_fill_rectangle_clipped(0, 0, viewport_width, viewport_height, scalara);
                  }
                  if ( *((float *)player + 1008) > 0.8500000238418579 && *((float *)player + 1008) < 3.5 )
                  {
                    v47 = 1.0 - (*((float *)player + 1008) - 0.8500000238418579) * 0.377358466386795;
                    v9 = rf_random_float_range(0.0, 1.0);
                    if ( v47 > v9 )
                    {
                      rf_vector3_default_construct_noop(lhs);
                      rf_matrix3_construct(v46);
                      rf_vmesh_compose_prop_world_transform(
                        (int)v55,
                        player[1007],
                        (float *)player + 1021,
                        (int)(player + 1030),
                        (int)v46,
                        lhs);
                      scalarb = rf_random_float_range(0.0, 0.1);
                      v18 = rf_random_float_range(0.0, 0.1);
                      v15 = rf_random_float_range(0.0, 0.1);
                      v10 = rf_vector3_set_components_return_destination(v26, v15, v18, scalarb);
                      v11 = rf_vector_add(lhs, v25, v10);
                      rf_vector_copy(&flt_87C6F8, v24, v11);
                      unk_87C710 = v47 * 0.2000000029802322;
                      v16 = *((_DWORD *)v106 + 11);
                      v12 = rf_receiver_get_first_dword(v106);
                      rf_particle_allocate_and_initialize(0, &flt_87C6F8, v12, 0, v16, nullptr, 0);
                    }
                  }
                }
              }
              silencer_node_index = rf_weapon_get_silencer_node_index((int)player, selected_weapon_and_resolve_mesh);
              if ( silencer_node_index != -1
                && rf_string_length_from_cstr((const char **)v102 + 314)
                && *((_DWORD *)v102 + 316)
                && *((_BYTE *)player + 4156) == 1 )
              {
                rf_vector3_default_construct_noop(v42);
                rf_matrix3_construct(v44);
                rf_vmesh_compose_prop_world_transform(
                  player[13],
                  silencer_node_index,
                  (float *)player + 1021,
                  (int)(player + 1030),
                  (int)v44,
                  v42);
                rf_model_render_options_construct(v43);
                rf_model_handle_render_all_adapter(*((_DWORD *)v102 + 316), (int)v42, (int)v44, (int)v43);
              }
              if ( rf_weapon_is_riot_stick(selected_weapon_and_resolve_mesh)
                && !rf_entity_runtime_flags810_has_mask2000((int)v106) )
              {
                if ( sub_436310((int)v106) <= 0 )
                  rf_replicator_reset(player + 994);
                thruster_1_node_index = rf_weapon_get_thruster_1_node_index(
                                          (int)player,
                                          selected_weapon_and_resolve_mesh);
                if ( thruster_1_node_index != -1 && *((_DWORD *)v102 + 320) )
                {
                  if ( rf_replicator_has_elapsed(player + 994) )
                  {
                    v13 = rf_foley_choose_random_sound(dword_662FCC);
                    rf_gamesound_play_event(v13, 0, 0.0, 1.0);
                    v37 = (int)rf_random_float_range(6000.0, 8000.0);
                    rf_replicator_arm_milliseconds(player + 994, v37);
                    rf_vfx_start_instance(*((int **)v102 + 320), 0, 1.0, 0);
                  }
                  rf_vector3_default_construct_noop(v38);
                  rf_matrix3_construct(v39);
                  rf_vmesh_compose_prop_world_transform(
                    player[13],
                    thruster_1_node_index,
                    (float *)player + 1021,
                    (int)(player + 1030),
                    (int)v39,
                    v38);
                  rf_model_render_options_construct(v40);
                  rf_model_handle_render_all_adapter(*((_DWORD *)v102 + 320), (int)v38, (int)v39, (int)v40);
                }
              }
              v103 = selected_weapon_and_resolve_mesh != rf_weapon_index_grenade;
              rf_light_clear_active_world_list();
              rf_renderer_set_camera_projection_dispatch((int)v106 + 2016, (int)v106 + 2004, flt_66157C, 1, 1);
              return 1;
            }
          }
        }
        else
        {
          if ( *((_DWORD *)v106 + 169) == unk_911CB4 )
            rf_player_render_red_scope_overlay((int)player);
          else
            rf_player_render_green_scope_overlay((int)player);
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    if ( rf_player_query_alt_zoom_factor((int)player) > 0.0 )
    {
      if ( *((_DWORD *)v106 + 169) == unk_911CB4 )
        rf_player_render_red_scope_overlay((int)player);
      else
        rf_player_render_green_scope_overlay((int)player);
    }
    return 0;
  }
}

