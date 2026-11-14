// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FF1A0 rf_event_load_level_apply_forward
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Destination gate detail: reject unavailable-session helper, absent player, or player common pending-delete mask2 before transition work. Same-level comparison uses string substrings length-4 on current and destination names, not extension validation. Successful VFile destination resolution precedes carryover publication and immediate panel10 request; failure instead requests panel13. Raw event byte+0x2C0 uses NONZERO admission for its cleanup branch, not equality1; this differs from Goal_Create shared flag and is not normalized by Load_Level creation0x4FA510. Broader carryover serialization semantics remain outside this added contract.
int __thiscall rf_event_load_level_apply_forward(char *this)
{
  unsigned int v2; // eax
  unsigned int v3; // eax
  char *v4; // eax
  int v5; // eax
  float *v6; // eax
  float *v7; // eax
  int v8; // eax
  const char *v9; // eax
  const char *v10; // eax
  const char *v11; // eax
  float *v12; // eax
  int v13; // eax
  float *v14; // eax
  char v15[4]; // [esp+Ch] [ebp-260h] BYREF
  char *v16; // [esp+10h] [ebp-25Ch]
  int v17; // [esp+14h] [ebp-258h] BYREF
  char *v18; // [esp+18h] [ebp-254h]
  char v19; // [esp+23h] [ebp-249h]
  char *v20; // [esp+24h] [ebp-248h]
  char *v21; // [esp+28h] [ebp-244h]
  char *v22; // [esp+2Ch] [ebp-240h]
  int v23; // [esp+30h] [ebp-23Ch]
  int v24; // [esp+34h] [ebp-238h]
  _DWORD *v25; // [esp+38h] [ebp-234h]
  _DWORD *v26; // [esp+3Ch] [ebp-230h]
  char *v27; // [esp+40h] [ebp-22Ch]
  float v28[3]; // [esp+44h] [ebp-228h] BYREF
  float v29[3]; // [esp+50h] [ebp-21Ch] BYREF
  float v30[3]; // [esp+5Ch] [ebp-210h] BYREF
  float v31[3]; // [esp+68h] [ebp-204h] BYREF
  float v32[3]; // [esp+74h] [ebp-1F8h] BYREF
  float v33[3]; // [esp+80h] [ebp-1ECh] BYREF
  float v34[3]; // [esp+8Ch] [ebp-1E0h] BYREF
  float copy_result[3]; // [esp+98h] [ebp-1D4h] BYREF
  float out_vector[5]; // [esp+A4h] [ebp-1C8h] BYREF
  int v37; // [esp+B8h] [ebp-1B4h]
  int source_record_name_pointer; // [esp+BCh] [ebp-1B0h]
  int k; // [esp+C0h] [ebp-1ACh]
  int v40; // [esp+C4h] [ebp-1A8h]
  float *lhs; // [esp+C8h] [ebp-1A4h]
  char *v42; // [esp+CCh] [ebp-1A0h]
  char *v43; // [esp+D0h] [ebp-19Ch]
  char *v44; // [esp+D4h] [ebp-198h]
  char *v45; // [esp+D8h] [ebp-194h]
  char *i; // [esp+DCh] [ebp-190h]
  int m; // [esp+E0h] [ebp-18Ch]
  int j; // [esp+E4h] [ebp-188h]
  float *v49; // [esp+E8h] [ebp-184h]
  float out_orientation[9]; // [esp+ECh] [ebp-180h] BYREF
  float out_attachment_position[3]; // [esp+110h] [ebp-15Ch] BYREF
  float source[3]; // [esp+11Ch] [ebp-150h] BYREF
  void *v53; // [esp+128h] [ebp-144h]
  _BYTE v54[8]; // [esp+12Ch] [ebp-140h] BYREF
  int first_dword; // [esp+134h] [ebp-138h]
  int self[71]; // [esp+138h] [ebp-134h] BYREF
  _BYTE v57[8]; // [esp+258h] [ebp-14h] BYREF
  int v58; // [esp+268h] [ebp-4h]

  v27 = this;
  rf_vfile_construct_unopened(self);
  v58 = 0;
  if ( rf_extras_panel_false_hook() || !dword_681E38 || (*(_DWORD *)(dword_681E38 + 124) & 2) != 0 )
  {
    v58 = -1;
    return rf_vfile_destruct_close_if_open(self);
  }
  else
  {
    v2 = rf_string_length_from_cstr((const char **)unk_6FC31C);
    rf_string_left_count((char **)unk_6FC31C, v57, v2 - 4);
    LOBYTE(v58) = 1;
    v3 = rf_string_length_from_cstr((const char **)v27 + 174);
    rf_string_left_count((char **)v27 + 174, v54, v3 - 4);
    LOBYTE(v58) = 2;
    if ( rf_string_object_equals_case_insensitive((int)v57, (int)v54) )
    {
      LOBYTE(v58) = 1;
      rf_string_destroy_buffer(v54);
      LOBYTE(v58) = 0;
      rf_string_destroy_buffer(v57);
      v58 = -1;
      return rf_vfile_destruct_close_if_open(self);
    }
    else
    {
      v4 = (char *)rf_string_object_c_str_or_empty(v27 + 696);
      if ( rf_vfile_resolve_open_source((int)self, v4, (int)byte_98967F) )
      {
        LODWORD(out_vector[4]) = &v17;
        v26 = rf_string_construct_from_cstr(&v17, (char *)&byte_63D99F);
        v25 = v26;
        LOBYTE(v58) = 3;
        LODWORD(out_vector[3]) = v15;
        rf_string_copy_construct_from_object(v15, (char **)v27 + 174);
        v24 = v5;
        LOBYTE(v58) = 2;
        rf_level_transition_assign_level_and_save_strings(*(int *)v15, v16, v17, v18);
        rf_string_assign_from_object(unk_6FC478, (int)(v27 + 28));
        rf_object_refresh_room_cache_and_audio((void *)dword_681E38);
        first_dword = rf_receiver_get_first_dword((void *)dword_681E38);
        *(_DWORD *)(dword_681E38 + 124) |= 0x800u;
        v6 = rf_vector_subtract((const float *)(dword_681E38 + 60), out_vector, (const float *)v27 + 16);
        rf_vector_copy((float *)(dword_681E38 + 640), copy_result, v6);
        if ( *(_DWORD *)(dword_681E38 + 5200) != -1 )
        {
          v53 = (void *)rf_clutter_find_by_uid(*(_DWORD *)(dword_681E38 + 5200));
          if ( v53 )
          {
            rf_vector3_default_construct_noop(out_attachment_position);
            rf_vector3_default_construct_noop(source);
            rf_matrix3_construct((char *)out_orientation);
            if ( rf_entity_copy_weapon_attachment_transforms(
                   (const unsigned int *)dword_681E38,
                   0,
                   out_attachment_position,
                   source,
                   out_orientation) != -1 )
            {
              rf_vector_copy((float *)v53 + 60, v34, source);
              rf_object_publish_position_and_bounds((int)v53, source);
              rf_matrix3_copy((float *)v53 + 18, out_orientation);
              rf_matrix3_copy((float *)v53 + 63, out_orientation);
              rf_matrix3_copy((float *)v53 + 72, out_orientation);
              rf_object_refresh_room_cache_and_audio(v53);
            }
          }
        }
        if ( v27[704] )
        {
          unk_6FC3B4 = 1;
          if ( dword_681E38 )
          {
            *(_DWORD *)(dword_681E38 + 124) |= 0x800u;
            rf_object_queue_model_rebuild(dword_681E38);
          }
          rf_object_set_room_and_cache_position((float *)dword_681E38, 0);
          *(_DWORD *)(dword_681E38 + 1884) = -1;
        }
        else
        {
          unk_6FC3B4 = 0;
          sub_43C0B0(dword_681E38);
          v49 = (float *)rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
          if ( v49 )
          {
            *((_DWORD *)v49 + 31) |= 0x800u;
            v7 = rf_vector_subtract(v49 + 15, v33, (const float *)v27 + 16);
            rf_vector_copy(v49 + 160, v32, v7);
            *((_DWORD *)v49 + 517) |= 0x400u;
            rf_object_set_room_and_cache_position(v49, 0);
            rf_object_queue_model_rebuild((int)v49);
          }
          for ( i = (char *)unk_7D0C90; i != (char *)&unk_7D0C80; i = *((char **)i + 4) )
          {
            v8 = rf_receiver_get_first_dword(i);
            if ( v8 == first_dword || *(_DWORD *)(dword_681E38 + 1884) == *((_DWORD *)i + 11) )
            {
              v23 = *((_DWORD *)i + 9);
              switch ( v23 )
              {
                case 0:
                  v18 = "Hendrix_L19S3";
                  v9 = rf_string_object_c_str_or_empty(i + 24);
                  if ( _stricmp(v9, v18) )
                  {
                    v18 = (char *)off_63DF40;
                    v10 = rf_string_object_c_str_or_empty(i + 24);
                    if ( _stricmp(v10, v18) )
                    {
                      v18 = "gryphon";
                      v11 = rf_string_object_c_str_or_empty(i + 24);
                      if ( _stricmp(v11, v18) )
                      {
                        if ( (*((_DWORD *)i + 31) & 0x4000) == 0 && (*((_DWORD *)i + 31) & 2) == 0 )
                        {
                          if ( *((_DWORD *)i + 8) != -999 )
                          {
                            v45 = i;
                            *((_DWORD *)i + 517) |= 0x400u;
                            rf_ai_route_reset((int)(v45 + 1416));
                            if ( *((_DWORD *)v45 + 1270) )
                            {
                              rf_damage_dispatch(*((_DWORD *)v45 + 11), 100000.0, -1, -1, 4, 0, -1, 0);
                              rf_burn_effect_release_record(*((float **)v45 + 1270), 0);
                              *((_DWORD *)v45 + 1270) = 0;
                            }
                          }
                          goto LABEL_47;
                        }
                      }
                    }
                  }
                  continue;
                case 1:
                  goto LABEL_47;
                case 2:
                  v43 = i;
                  if ( *((_DWORD *)i + 168) != -1 )
                  {
                    rf_gamesound_stop_voice_handle(*((_DWORD *)v43 + 168));
                    *((_DWORD *)v43 + 168) = -1;
                  }
                  if ( *((_DWORD *)v43 + 169) != -1 )
                  {
                    rf_renderer_light_release(*((_DWORD *)v43 + 169), 0);
                    *((_DWORD *)v43 + 169) = -1;
                  }
                  goto LABEL_47;
                case 4:
                  v42 = i;
                  if ( *((_DWORD *)i + 166) != unk_666B64 )
                    continue;
                  if ( *((_DWORD *)v42 + 168) != -1 )
                  {
                    rf_positional_sound_destroy_instance(*((_DWORD *)v42 + 168), 0);
                    *((_DWORD *)v42 + 168) = -1;
                  }
LABEL_47:
                  *((_DWORD *)i + 31) |= 0x800u;
                  v12 = rf_vector_subtract((const float *)i + 15, v31, (const float *)v27 + 16);
                  rf_vector_copy((float *)i + 160, v30, v12);
                  rf_object_queue_model_rebuild((int)i);
                  break;
                case 7:
                  v44 = i;
                  *((_DWORD *)i + 167) |= 0x10u;
                  goto LABEL_47;
                default:
                  continue;
              }
            }
          }
          dword_A704F8 = 0;
          if ( first_dword )
          {
            for ( j = 0; ; ++j )
            {
              v13 = rf_receiver_get_first_dword((void *)(first_dword + 156));
              if ( j >= v13 )
                break;
              lhs = *(float **)rf_inline_dword_array4_element_address_unchecked((void *)(first_dword + 156), j);
              if ( ((_DWORD)lhs[20] & 1) == 0 )
              {
                v40 = -1;
                for ( k = 0; k < dword_A704F8; ++k )
                {
                  if ( *((_DWORD *)lhs + 15) == unk_A704FC[k] )
                  {
                    v40 = k;
                    break;
                  }
                }
                if ( v40 == -1 )
                {
                  source_record_name_pointer = rf_bitmap_get_source_record_name_pointer(*((_DWORD *)lhs + 15));
                  v22 = (char *)source_record_name_pointer;
                  v21 = &unk_A70520[32 * dword_A704F8];
                  v20 = v21;
                  do
                  {
                    v19 = *v22;
                    *v21 = v19;
                    ++v22;
                    ++v21;
                  }
                  while ( v19 );
                  unk_A704FC[dword_A704F8++] = *((_DWORD *)lhs + 15);
                }
                *((_DWORD *)lhs + 20) |= 0x402u;
                v14 = rf_vector_subtract(lhs, v29, (const float *)v27 + 16);
                rf_vector_copy(lhs, v28, v14);
              }
            }
          }
          for ( m = dword_911F74; (_UNKNOWN *)m != &unk_911CE8; m = v37 )
          {
            v37 = *(_DWORD *)(m + 652);
            if ( (*(_DWORD *)(*(_DWORD *)(m + 660) + 612) & 0x40) != 0 && (*(_DWORD *)(m + 124) & 0x800) == 0 )
              *(_DWORD *)(m + 124) |= 0x20000002u;
          }
        }
        if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
          rf_multiplayer_runtime_teardown();
        rf_ui_request_panel_immediate(10, 1);
        LOBYTE(v58) = 1;
        rf_string_destroy_buffer(v54);
        LOBYTE(v58) = 0;
        rf_string_destroy_buffer(v57);
        v58 = -1;
        return rf_vfile_destruct_close_if_open(self);
      }
      else
      {
        rf_ui_request_panel_immediate(13, 0);
        LOBYTE(v58) = 1;
        rf_string_destroy_buffer(v54);
        LOBYTE(v58) = 0;
        rf_string_destroy_buffer(v57);
        v58 = -1;
        return rf_vfile_destruct_close_if_open(self);
      }
    }
  }
}

