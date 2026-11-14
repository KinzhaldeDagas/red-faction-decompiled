// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047C6C0 rf_rfl_level_load
// UNREALRED VERIFIED [trigger-attachment-20261020] Attachment fixup at47D68A..47D6EE looks up trigger+0x300 as an authored UID through4BC680 once, immediately copies owner common position+0x3C and orientation+0x48 into the trigger, then replaces the field with owner runtime handle+0x2C. No relative offset is retained. Missing lookup leaves the field unchanged; the later lifecycle uses full-handle resolution, not repeated UID lookup. UnrealRed captures the live owner identity at entity-initialization completion and keeps a separate runtime trigger pose.
// UNREALRED VERIFIED [trigger-use-20261021] Postload trigger link pass at47D5AA..47D628 resolves saved UIDs to live common handles, stores those handles, then records trigger handle on linked entity+0x838. UnrealRed captures weak target identities once after entity initialization; later replacement or late-spawn actor sharing a UID is not adopted.
// UNREALRED VERIFIED [ai-navigation-import-20261028] RFL dispatch selects named waypoint-list loader0x486EA0 for section0x00010000 and point-pool loader0x480E80 for section0x00020000 when fileversion>=71. Named lists are indices into world-solid point storage, not direct point UID references.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] After finishing RFL reads,47D4C4 tests saved-state flag: nonempty second FileName parameter sets flag and preserves6FC428; ordinary no-saved-state load resets float seconds to0 at47D4CE before queued model/event work. Host normal-import publication can own reset under an explicit source/World lease; restore/client clock synchronization remains separate, not a guessed reset.
// UNREALRED VERIFIED [combat-ai-birth-phase-20261111]47D2E5 dispatches entity section4811C0; reached entity construction42CB80 invokes4033C0 before the section loop ends. After fileclose47D4B9, var_D is tested47D4C8 and only zero performs fldz47D4CC/store6FC428 at47D4CE. Native authored AI288 therefore samples PRE-reset seconds, while subsequent startup/runtime mode writes sample their then-current clock. Retained pre-reset source provenance or explicitly unavailable is required; post-publication0 is not an equivalent constructor timestamp.
int __cdecl rf_rfl_level_load(char *String1, char *FileName, char *Buffer)
{
  const char *v4; // eax
  char *v5; // eax
  const char *v6; // eax
  char *v7; // eax
  const char *v8; // eax
  int slot_version; // eax
  int v10; // eax
  int first_dword; // eax
  int *v12; // eax
  _DWORD *v13; // eax
  int *v14; // eax
  _DWORD *v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // esi
  _DWORD *v19; // eax
  int v20; // eax
  int *v21; // eax
  _DWORD *v22; // eax
  int *v23; // eax
  _DWORD *v24; // eax
  int v25; // eax
  int v26; // eax
  int *v27; // eax
  _DWORD *v28; // eax
  int v29; // eax
  float copy_result[3]; // [esp+1Ch] [ebp-4F4h] BYREF
  int *v31; // [esp+34h] [ebp-4DCh]
  int v32; // [esp+38h] [ebp-4D8h]
  int i4; // [esp+3Ch] [ebp-4D4h]
  int v34; // [esp+40h] [ebp-4D0h]
  int i3; // [esp+44h] [ebp-4CCh]
  int i2; // [esp+48h] [ebp-4C8h]
  char v37; // [esp+4Fh] [ebp-4C1h]
  int i1; // [esp+50h] [ebp-4C0h]
  int v39; // [esp+54h] [ebp-4BCh]
  int v40; // [esp+58h] [ebp-4B8h]
  int v41; // [esp+5Ch] [ebp-4B4h]
  char v42; // [esp+63h] [ebp-4ADh]
  _DWORD v43[22]; // [esp+64h] [ebp-4ACh] BYREF
  void *v44; // [esp+BCh] [ebp-454h]
  int open_slot_offset; // [esp+C0h] [ebp-450h]
  _DWORD v46[22]; // [esp+C4h] [ebp-44Ch] BYREF
  void *Block; // [esp+11Ch] [ebp-3F4h]
  int kk; // [esp+120h] [ebp-3F0h]
  char v49[256]; // [esp+124h] [ebp-3ECh] BYREF
  int jj; // [esp+228h] [ebp-2E8h]
  int v52[2]; // [esp+22Ch] [ebp-2E4h] BYREF
  int v53; // [esp+234h] [ebp-2DCh]
  int ii; // [esp+238h] [ebp-2D8h]
  char v55[260]; // [esp+23Ch] [ebp-2D4h] BYREF
  int n; // [esp+344h] [ebp-1CCh]
  int v58[2]; // [esp+348h] [ebp-1C8h] BYREF
  int v59; // [esp+350h] [ebp-1C0h]
  int m; // [esp+354h] [ebp-1BCh]
  int k; // [esp+358h] [ebp-1B8h]
  int v62[2]; // [esp+35Ch] [ebp-1B4h] BYREF
  int v63; // [esp+364h] [ebp-1ACh]
  int j; // [esp+368h] [ebp-1A8h]
  char *first_character; // [esp+36Ch] [ebp-1A4h]
  int i; // [esp+370h] [ebp-1A0h]
  char Str[68]; // [esp+374h] [ebp-19Ch] BYREF
  int int32_versioned; // [esp+3B8h] [ebp-158h]
  int mm; // [esp+3BCh] [ebp-154h]
  int v70; // [esp+3C0h] [ebp-150h] BYREF
  size_t Size; // [esp+3C4h] [ebp-14Ch] BYREF
  char v72; // [esp+3CBh] [ebp-145h]
  int v73; // [esp+3CCh] [ebp-144h]
  _DWORD *v74; // [esp+3D0h] [ebp-140h]
  int v75; // [esp+3D4h] [ebp-13Ch]
  char v76; // [esp+3DBh] [ebp-135h]
  int self[71]; // [esp+3DCh] [ebp-134h] BYREF
  int nn; // [esp+4FCh] [ebp-14h]
  char v79; // [esp+503h] [ebp-Dh]
  int v80; // [esp+50Ch] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v80 = 0;
  v76 = 1;
  v79 = 0;
  rf_level_set_logical_name(String1);
  if ( rf_vfile_open_with_extension_cache_control_paths(self, String1, 1, byte_98967F) )
  {
    sprintf(Buffer, "Couldn't open level file");
    rf_level_reset_auxiliary_name_string();
    v80 = -1;
    rf_vfile_destruct_close_if_open(self);
    return -1;
  }
  if ( !rf_rfl_validate_header_and_read_prelude(self, Buffer) )
  {
    rf_level_reset_auxiliary_name_string();
    v80 = -1;
    rf_vfile_destruct_close_if_open(self);
    return -1;
  }
  v72 = 0;
  while ( !v72 && rf_rfl_read_section_header(self, &v70, (int *)&Size) )
  {
    if ( v70 > 28672 )
    {
      switch ( v70 )
      {
        case 28673:
          int32_versioned = rf_binary_stream_read_int32_versioned(self, 0, 0);
          for ( i = 0; i < int32_versioned; ++i )
          {
            rf_binary_stream_read_u16_string_to_buffer(self, Str, 64, 0, nullptr);
            first_character = rf_cstring_find_first_character(Str, 46);
            if ( first_character )
              *first_character = 0;
            rf_progress_update_poll_network_and_callback(0, 0);
            rf_character_cache_lookup_adapter(Str, 0);
          }
          for ( j = 0; j < int32_versioned; ++j )
            rf_binary_stream_read_int32_versioned(self, 0, 0);
          break;
        case 28674:
          rf_string_construct_empty(v62);
          LOBYTE(v80) = 1;
          v63 = rf_binary_stream_read_int32_versioned(self, 0, 0);
          for ( k = 0; k < v63; ++k )
          {
            rf_binary_stream_read_string_object_versioned(self, v62, 0, nullptr);
            v4 = rf_string_object_c_str_or_empty(v62);
            rf_rfa_load_raw_file(v4, nullptr);
            rf_progress_update_poll_network_and_callback(0, 0);
          }
          for ( m = 0; m < v63; ++m )
            rf_binary_stream_read_int32_versioned(self, 0, 0);
          LOBYTE(v80) = 0;
          rf_string_destroy_buffer(v62);
          break;
        case 28675:
          rf_string_construct_empty(v58);
          LOBYTE(v80) = 2;
          v59 = rf_binary_stream_read_int32_versioned(self, 0, 0);
          for ( n = 0; n < v59; ++n )
          {
            rf_binary_stream_read_string_object_versioned(self, v58, 0, nullptr);
            v5 = (char *)rf_string_object_c_str_or_empty(v58);
            if ( !sub_5B7F80(v5, 1u, (int)byte_98967F) )
            {
              v6 = rf_string_object_c_str_or_empty(v58);
              sprintf(v55, "Failed to load a V3D specified in the level resource! (%s)", v6);
              rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\level\\level_load.cpp", 4131, v55);
            }
            rf_progress_update_poll_network_and_callback(0, 0);
          }
          for ( ii = 0; ii < v59; ++ii )
            rf_binary_stream_read_int32_versioned(self, 0, 0);
          LOBYTE(v80) = 0;
          rf_string_destroy_buffer(v58);
          break;
        case 28676:
          rf_string_construct_empty(v52);
          LOBYTE(v80) = 3;
          v53 = rf_binary_stream_read_int32_versioned(self, 0, 0);
          for ( jj = 0; jj < v53; ++jj )
          {
            rf_binary_stream_read_string_object_versioned(self, v52, 0, nullptr);
            v7 = (char *)rf_string_object_c_str_or_empty(v52);
            if ( !rf_scene_definition_get_or_load_cached_vsfx(v7, (int)byte_98967F) )
            {
              v8 = rf_string_object_c_str_or_empty(v52);
              sprintf(v49, "Failed to load a VFX specified in the level resource! (%s)", v8);
              rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\level\\level_load.cpp", 4154, v49);
            }
            rf_progress_update_poll_network_and_callback(0, 0);
          }
          for ( kk = 0; kk < v53; ++kk )
            rf_binary_stream_read_int32_versioned(self, 0, 0);
          LOBYTE(v80) = 0;
          rf_string_destroy_buffer(v52);
          break;
        default:
          goto LABEL_15;
      }
    }
    else
    {
      switch ( v70 )
      {
        case 28672:
          goto LABEL_15;
        case 256:
          open_slot_offset = rf_vfile_get_open_slot_offset(self);
          rf_stream_adapter_construct_unbound(v46);
          Block = malloc(Size);
          rf_vfile_read_buffered_bytes_versioned(self, (char *)Block, Size, 0, 0);
          rf_stream_adapter_bind_memory(v46, (int)Block, Size, nullptr);
          slot_version = rf_vfile_get_slot_version(self);
          rf_stream_adapter_set_version(v46, slot_version);
          if ( !rf_rfl_world_geometry_read_and_seed_mp_rooms((int)v46) )
          {
            sprintf(Buffer, "Error loading geometry");
            v80 = -1;
            rf_vfile_destruct_close_if_open(self);
            return -1;
          }
          free(Block);
          rf_progress_update_poll_network_and_callback(0, 0);
          rf_vfile_seek(self, Size + open_slot_offset, 0);
          sub_4CAF00(rf_world_solid);
          v72 = 1;
          break;
        case 2304:
          rf_rfl_level_environment_read();
          rf_progress_update_poll_network_and_callback(0, 0);
          break;
        case 4608:
          rf_lightmap_atlas_destroy_all_registered_pages();
          rf_rfl_lightmaps_section_load((int)self);
          break;
        default:
LABEL_15:
          rf_vfile_seek(self, Size, 1);
          break;
      }
    }
  }
  v72 = 0;
  if ( FileName && *FileName )
    v79 = 1;
  else
    FileName = "auto.svl";
  while ( !v72 && rf_rfl_read_section_header(self, &v70, (int *)&Size) )
  {
    if ( v70 > 0x2000 )
    {
      if ( v70 > 0x40000 )
      {
        if ( v70 > 0x80000 )
        {
          if ( v70 != 0x4000000 )
            goto LABEL_120;
          rf_rfl_lights_section_load((int)self, 1);
        }
        else
        {
          switch ( v70 )
          {
            case 0x80000:
              goto LABEL_120;
            case 0x50000:
              rf_rfl_clutter_section_load((int)self);
              continue;
            case 0x60000:
              rf_rfl_triggers_section_load((int)self);
              continue;
          }
          if ( v70 != 458752 )
            goto LABEL_120;
          rf_rfl_player_start_section_load();
        }
      }
      else
      {
        if ( v70 == 0x40000 )
        {
          if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
          {
            rf_rfl_items_section_load((int)self);
            continue;
          }
          goto LABEL_120;
        }
        if ( v70 <= 24576 )
        {
          switch ( v70 )
          {
            case 24576:
              rf_rfl_cutscene_bezier_paths_load(self);
              continue;
            case 12288:
              rf_rfl_moving_groups_section_load((int)self);
              continue;
            case 16384:
              rf_rfl_cutscene_sequences_load(self);
              continue;
            case 20480:
              rf_rfl_cutscene_aux_points_load(self);
              continue;
          }
          goto LABEL_120;
        }
        if ( v70 != 0x10000 )
        {
          if ( v70 == 0x20000 )
          {
            if ( rf_vfile_get_slot_version(self) >= 71 )
            {
              sub_480E80((int)self);
              continue;
            }
          }
          else if ( v70 == 196608 && (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority) )
          {
            rf_rfl_entities_section_load((int)self);
            continue;
          }
          goto LABEL_120;
        }
        sub_486EA0((int)self);
      }
    }
    else
    {
      if ( v70 == 0x2000 )
      {
        v44 = malloc(Size);
        rf_stream_adapter_construct_unbound(v43);
        rf_vfile_read_buffered_bytes_versioned(self, (char *)v44, Size, 0, 0);
        rf_stream_adapter_bind_memory(v43, (int)v44, Size, nullptr);
        v10 = rf_vfile_get_slot_version(self);
        rf_stream_adapter_set_version(v43, v10);
        rf_rfl_moving_solids_section_load((int)v43);
        free(v44);
        continue;
      }
      if ( v70 > 2816 )
      {
        if ( v70 > 3840 )
        {
          if ( v70 == 4096 )
          {
            rf_rfl_decals_read(self);
          }
          else
          {
            if ( v70 != 4352 )
              goto LABEL_120;
            rf_rfl_push_regions_section_load();
          }
        }
        else
        {
          switch ( v70 )
          {
            case 3840:
              rf_rfl_target_markers_section_load(self);
              break;
            case 3072:
              goto LABEL_120;
            case 3328:
              rf_rfl_load_obb_region_records((int)self);
              break;
            case 3584:
              rf_rfl_bolt_emitters_section_load(self);
              break;
            default:
              goto LABEL_120;
          }
        }
      }
      else if ( v70 == 2816 )
      {
        rf_rfl_volume_effects_read((int)self);
      }
      else if ( v70 > 1280 )
      {
        switch ( v70 )
        {
          case 1536:
            rf_rfl_events_section_load((int)self);
            break;
          case 1792:
            rf_rfl_multiplayer_respawns_section_load((int)self);
            break;
          case 2560:
            rf_rfl_particle_emitters_section_load(self);
            break;
          default:
            goto LABEL_120;
        }
      }
      else
      {
        switch ( v70 )
        {
          case 1280:
            rf_rfl_ambient_sounds_section_load((int)self);
            break;
          case 512:
            rf_geomod_georegions_load((int)self);
            break;
          case 768:
            rf_rfl_lights_section_load((int)self, 0);
            break;
          case 1024:
            rf_rfl_pose_records_0400_load(self);
            continue;
          default:
LABEL_120:
            rf_vfile_seek(self, Size, 1);
            continue;
        }
      }
    }
  }
  rf_vfile_close_stdio_or_vpp(self);
  if ( !v79 )
    *(float *)&dword_6FC428 = 0.0;
  v73 = rf_ui_panel_stack_current_id();
  if ( v73 != 10 && v73 != 9 && !v79 )
  {
    unk_6FC42C = 0.0;
    rf_mission_countdown_remaining_seconds = 0.0;
  }
  rf_object_apply_queued_model_rebuilds();
  rf_mission_preload_file_animation_events();
  if ( v76 )
    v42 = rf_savegame_restore_level_state(FileName, rf_local_fpgun_player);
  for ( mm = rf_trigger_runtime_list_head; (_UNKNOWN *)mm != &unk_90B510; mm = *(_DWORD *)(mm + 652) )
  {
    for ( nn = 0; ; ++nn )
    {
      first_dword = rf_receiver_get_first_dword((void *)(mm + 724));
      if ( nn >= first_dword )
        break;
      v12 = (int *)sub_552200((_DWORD *)(mm + 724), nn);
      v75 = rf_object_find_by_saved_identifier(*v12);
      if ( v75 )
      {
        v13 = (_DWORD *)sub_552200((_DWORD *)(mm + 724), nn);
        *v13 = *(_DWORD *)(v75 + 44);
        if ( rf_trigger_is_auto(mm) )
        {
          v40 = rf_entity_resolve_handle(*(_DWORD *)(v75 + 44));
          if ( v40 )
            *(_DWORD *)(v40 + 2104) = *(_DWORD *)(mm + 44);
        }
      }
      else
      {
        v14 = (int *)sub_552200((_DWORD *)(mm + 724), nn);
        v39 = rf_mover_find_by_key_uid(*v14);
        if ( v39 )
        {
          v15 = (_DWORD *)sub_552200((_DWORD *)(mm + 724), nn);
          *v15 = *(_DWORD *)(v39 + 44);
        }
      }
    }
    v41 = rf_object_find_by_saved_identifier(*(_DWORD *)(mm + 768));
    if ( v41 )
    {
      rf_vector_copy((float *)(mm + 60), copy_result, (const float *)(v41 + 60));
      rf_matrix3_copy((float *)(mm + 72), (const float *)(v41 + 72));
      *(_DWORD *)(mm + 768) = *(_DWORD *)(v41 + 44);
    }
    v41 = rf_object_find_by_saved_identifier(*(_DWORD *)(mm + 772));
    if ( v41 )
      *(_DWORD *)(mm + 772) = *(_DWORD *)(v41 + 44);
  }
  rf_progress_update_poll_network_and_callback(0, 0);
  for ( nn = 0; ; ++nn )
  {
    v16 = rf_receiver_get_first_dword(unk_90B0E0);
    if ( nn >= v16 )
      break;
    v74 = *(_DWORD **)sub_552200(unk_90B0E0, nn);
    if ( v74[164] == 69 )
    {
      for ( i1 = rf_receiver_get_first_dword(v74 + 167) - 1; i1 >= 0; --i1 )
      {
        v37 = 0;
        for ( i2 = 0; ; ++i2 )
        {
          v17 = rf_receiver_get_first_dword((void *)(rf_world_solid + 768));
          if ( i2 >= v17 )
            break;
          v18 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), i2);
          if ( *(_DWORD *)(v18 + 108) == *(_DWORD *)sub_552200(v74 + 167, i1) )
          {
            v19 = (_DWORD *)sub_552200(v74 + 167, i1);
            *v19 = i2;
            v37 = 1;
            break;
          }
        }
        if ( !v37 )
          rf_pointer_array_erase_index_unchecked(v74 + 167, i1);
      }
    }
    else
    {
      for ( i3 = 0; ; ++i3 )
      {
        v20 = rf_receiver_get_first_dword(v74 + 167);
        if ( i3 >= v20 )
          break;
        v21 = (int *)sub_552200(v74 + 167, i3);
        v75 = rf_object_find_by_saved_identifier(*v21);
        if ( v75 )
        {
          v22 = (_DWORD *)sub_552200(v74 + 167, i3);
          *v22 = *(_DWORD *)(v75 + 44);
        }
        else
        {
          v23 = (int *)sub_552200(v74 + 167, i3);
          v34 = rf_mover_find_by_key_uid(*v23);
          if ( v34 )
          {
            v24 = (_DWORD *)sub_552200(v74 + 167, i3);
            *v24 = *(_DWORD *)(v34 + 44);
          }
        }
      }
    }
  }
  for ( nn = 0; ; ++nn )
  {
    v25 = rf_receiver_get_first_dword((void *)(rf_world_solid + 768));
    if ( nn >= v25 )
      break;
    v32 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), nn);
    for ( i4 = 0; ; ++i4 )
    {
      v26 = rf_receiver_get_first_dword((void *)(v32 + 112));
      if ( i4 >= v26 )
        break;
      v27 = (int *)sub_552200((_DWORD *)(v32 + 112), i4);
      v74 = (_DWORD *)rf_mission_event_registry_find_by_saved_uid(*v27);
      if ( !v74 )
      {
        rf_pointer_array_clear_count_keep_storage((_DWORD *)(v32 + 112));
        break;
      }
      v28 = (_DWORD *)sub_552200((_DWORD *)(v32 + 112), i4);
      *v28 = v74[12];
    }
  }
  for ( nn = 0; ; ++nn )
  {
    v29 = rf_receiver_get_first_dword(rf_bolt_emitter_registry);
    if ( nn >= v29 )
      break;
    v31 = *(int **)sub_552200(rf_bolt_emitter_registry, nn);
    rf_bolt_emitter_refresh_attachment(v31);
  }
  rf_progress_update_poll_network_and_callback(0, 0);
  rf_mission_events_release_type10_effect_handles();
  rf_progress_update_poll_network_and_callback(0, 0);
  v80 = -1;
  rf_vfile_destruct_close_if_open(self);
  return 0;
}

