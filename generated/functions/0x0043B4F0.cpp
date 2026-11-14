// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043B4F0 rf_entity_build_animation_tables
// UNREALRED VERIFIED [animation-trigger-decode]: Loads canonical body state/action tables and copies state-owned trigger descriptors into animations.
void __cdecl rf_entity_build_animation_tables(int a1, char *Str)
{
  char *v2; // eax
  char *v3; // eax
  const char *v4; // eax
  int v5; // eax
  const char *v6; // eax
  int v7; // eax
  const char *v8; // eax
  int v9; // eax
  const char *v10; // eax
  const char *v11; // eax
  int v12; // eax
  _DWORD *v13; // eax
  _DWORD *v14; // ecx
  _DWORD *v15; // ecx
  _DWORD *v16; // edx
  int v17; // [esp+10h] [ebp-68h]
  float v18; // [esp+10h] [ebp-68h]
  float sum_result[3]; // [esp+24h] [ebp-54h] BYREF
  int level_record_by_name; // [esp+30h] [ebp-48h]
  int v21; // [esp+34h] [ebp-44h]
  _DWORD v22[2]; // [esp+38h] [ebp-40h] BYREF
  int k; // [esp+40h] [ebp-38h]
  _DWORD *v24; // [esp+44h] [ebp-34h]
  int v25; // [esp+48h] [ebp-30h]
  int j; // [esp+4Ch] [ebp-2Ch]
  _DWORD v27[2]; // [esp+50h] [ebp-28h] BYREF
  int animation_record_by_name; // [esp+58h] [ebp-20h]
  char *last_char_wrapper; // [esp+5Ch] [ebp-1Ch]
  int v30; // [esp+60h] [ebp-18h]
  int i; // [esp+64h] [ebp-14h]
  _DWORD *definition_pointer; // [esp+68h] [ebp-10h]
  int v33; // [esp+74h] [ebp-4h]

  if ( rf_character_cache_contains_filename_adapter((int)Str)
    || rf_v3c_cache_contains_filename_adapter(Str)
    || ((last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 46)) == nullptr
     || _stricmp(last_char_wrapper + 1, off_632FE4)
      ? (*(_DWORD *)(a1 + 128) = rf_model_handle_load_character_instance(Str, 0, 0))
      : (*(_DWORD *)(a1 + 128) = rf_model_handle_load_v3m_mode1(Str, 1, (void *)0xFFFFFFFF)),
        *(_DWORD *)(a1 + 128)) )
  {
    v30 = a1;
    v17 = *(_DWORD *)(*(_DWORD *)(a1 + 660) + 148);
    v2 = (char *)rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(a1 + 660) + 8));
    rf_object_bind_model_filename_by_kind(a1, v2, v17);
    if ( (int)rf_string_length_from_cstr((const char **)(*(_DWORD *)(a1 + 660) + 5068)) > 0 )
    {
      v3 = (char *)rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(v30 + 660) + 5068));
      *(_DWORD *)(v30 + 2124) = rf_vfx_load_instance(v3, (int)byte_98967F);
      rf_model_handle_set_cyclic_mix_adapter(*(int **)(v30 + 2124), 0, 1.0);
    }
    for ( i = 0; i < 23; ++i )
      *(_DWORD *)(v30 + 16 * i + 2276) = -1;
    for ( i = 0; i < 45; ++i )
      *(_DWORD *)(v30 + 16 * i + 2644) = -1;
    definition_pointer = (_DWORD *)rf_model_handle_get_definition_pointer(*(_DWORD *)(v30 + 128));
    for ( i = 0; i < 64; ++i )
    {
      rf_string_construct_empty(v27);
      v33 = 0;
      if ( *(int *)(*(_DWORD *)(v30 + 660) + 4 * i + 1896) > 0 )
      {
        for ( j = 0; j < 23; ++j )
        {
          animation_record_by_name = rf_entity_info_find_animation_record_by_name(
                                       v27,
                                       *(_DWORD *)(v30 + 664),
                                       i,
                                       8 * j + 6829200,
                                       1);
          if ( animation_record_by_name == -1 )
          {
            *(_DWORD *)(16 * j + *(_DWORD *)(v30 + 4 * i + 4452)) = -1;
            *(_DWORD *)(*(_DWORD *)(v30 + 4 * i + 4452) + 16 * j + 4) = -1;
          }
          else
          {
            v4 = rf_string_object_c_str_or_empty(v27);
            v5 = rf_animation_registry_load(definition_pointer, (int)v4, 1u, 1);
            *(_DWORD *)(16 * j + *(_DWORD *)(v30 + 4 * i + 4452)) = v5;
            *(_DWORD *)(*(_DWORD *)(v30 + 4 * i + 4452) + 16 * j + 4) = animation_record_by_name;
          }
          *(_DWORD *)(*(_DWORD *)(v30 + 4 * i + 4452) + 16 * j + 8) = -1;
        }
      }
      if ( *(int *)(*(_DWORD *)(v30 + 660) + 4 * i + 2152) > 0 )
      {
        for ( j = 0; j < 45; ++j )
        {
          animation_record_by_name = rf_entity_info_find_animation_record_by_name(
                                       v27,
                                       *(_DWORD *)(v30 + 664),
                                       i,
                                       8 * j + 6828840,
                                       0);
          if ( animation_record_by_name == -1 )
          {
            *(_DWORD *)(16 * j + *(_DWORD *)(v30 + 4 * i + 4708)) = -1;
            *(_DWORD *)(*(_DWORD *)(v30 + 4 * i + 4708) + 16 * j + 4) = -1;
            *(_DWORD *)(*(_DWORD *)(v30 + 4 * i + 4708) + 16 * j + 8) = -1;
          }
          else
          {
            v6 = rf_string_object_c_str_or_empty(v27);
            v7 = rf_animation_registry_load(definition_pointer, (int)v6, 0, 1);
            *(_DWORD *)(16 * j + *(_DWORD *)(v30 + 4 * i + 4708)) = v7;
            *(_DWORD *)(*(_DWORD *)(v30 + 4 * i + 4708) + 16 * j + 4) = animation_record_by_name;
            *(_DWORD *)(*(_DWORD *)(v30 + 4 * i + 4708) + 16 * j + 8) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v30 + 660)
                                                                                              + 4 * i
                                                                                              + 2664)
                                                                                  + 52 * animation_record_by_name
                                                                                  + 16);
          }
        }
      }
      v33 = -1;
      rf_string_destroy_buffer(v27);
    }
    rf_replicator_arm_milliseconds((int *)(v30 + 4976), 0);
    *(_DWORD *)(v30 + 4964) = -1;
    *(_DWORD *)(v30 + 4968) = -1;
    if ( rf_entity_admits_speech_body_actions(v30) )
    {
      rf_string_construct_empty(v22);
      v33 = 1;
      v24 = (_DWORD *)rf_model_handle_get_definition_pointer(*(_DWORD *)(v30 + 128));
      for ( i = 0; i < 23; ++i )
      {
        v25 = rf_entity_info_find_animation_record_by_name(v22, *(_DWORD *)(v30 + 664), -1, 8 * i + 6829200, 1);
        if ( v25 == -1 )
        {
          *(_DWORD *)(v30 + 16 * i + 2276) = -1;
          *(_DWORD *)(v30 + 16 * i + 2280) = -1;
        }
        else
        {
          v8 = rf_string_object_c_str_or_empty(v22);
          v9 = rf_animation_registry_load(v24, (int)v8, 1u, 1);
          *(_DWORD *)(v30 + 16 * i + 2276) = v9;
          *(_DWORD *)(v30 + 16 * i + 2280) = v25;
          v21 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v30 + 660) + 1884) + 52 * v25 + 20);
          for ( k = 0; k < v21; ++k )
          {
            v18 = *(float *)(52 * v25 + *(_DWORD *)(*(_DWORD *)(v30 + 660) + 1884) + 12 * k + 32);
            v10 = rf_string_object_c_str_or_empty((const void *)(52 * v25
                                                               + *(_DWORD *)(*(_DWORD *)(v30 + 660) + 1884)
                                                               + 12 * k
                                                               + 24));
            rf_animation_trigger_ensure(v24, *(_DWORD *)(v30 + 16 * i + 2276), v10, v18);
          }
        }
      }
      for ( i = 0; i < 45; ++i )
      {
        v25 = rf_entity_info_find_animation_record_by_name(v22, *(_DWORD *)(v30 + 664), -1, 8 * i + 6828840, 0);
        if ( v25 == -1 )
        {
          *(_DWORD *)(v30 + 16 * i + 2644) = -1;
          *(_DWORD *)(v30 + 16 * i + 2648) = -1;
          *(_DWORD *)(v30 + 16 * i + 2652) = -1;
        }
        else
        {
          v11 = rf_string_object_c_str_or_empty(v22);
          v12 = rf_animation_registry_load(v24, (int)v11, 0, 1);
          *(_DWORD *)(v30 + 16 * i + 2644) = v12;
          *(_DWORD *)(v30 + 16 * i + 2648) = v25;
          *(_DWORD *)(v30 + 16 * i + 2652) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v30 + 660) + 1888) + 52 * v25 + 16);
        }
      }
      for ( i = 0; i < 23; ++i )
      {
        v13 = (_DWORD *)(v30 + 16 * i + 2276);
        v14 = (_DWORD *)(v30 + 16 * i + 3364);
        *v14 = *v13;
        v14[1] = v13[1];
        v14[2] = v13[2];
        v14[3] = v13[3];
      }
      for ( i = 0; i < 45; ++i )
      {
        v15 = (_DWORD *)(v30 + 16 * i + 2644);
        v16 = (_DWORD *)(v30 + 16 * i + 3732);
        *v16 = *v15;
        v16[1] = v15[1];
        v16[2] = v15[2];
        v16[3] = v15[3];
      }
      if ( rf_entity_is_dead(v30) )
      {
        level_record_by_name = rf_goal_find_level_record_by_name((int)unk_6FC478);
        if ( level_record_by_name )
        {
          rf_vector_add((const float *)(a1 + 640), sum_result, (const float *)(level_record_by_name + 64));
          rf_object_relocate_reset_pose_and_reactivate(a1, (int)sum_result, a1 + 72);
          if ( rf_receiver_get_first_dword((void *)v30) )
            rf_entity_request_body_action(v30, *(_DWORD *)(v30 + 2084), 1.0, 1, 0);
          else
            rf_object_mark_for_deferred_delete(a1);
        }
        else
        {
          rf_object_set_room_and_cache_position((float *)v30, 0);
        }
      }
      else
      {
        rf_model_handle_get_runtime_pointer(*(int **)(v30 + 128));
        *(_DWORD *)(v30 + 5004) = 0;
        *(_DWORD *)(v30 + 5008) = -1;
        *(float *)(v30 + 5012) = 0.0;
        *(float *)(v30 + 5016) = 0.0;
        if ( *(_DWORD *)(v30 + 676) != *(_DWORD *)(*(_DWORD *)(v30 + 660) + 136) )
          rf_entity_restore_action_tables_and_apply_weapon_overrides(v30, *(_DWORD *)(v30 + 676));
        rf_entity_update_body_state_transition(v30);
        rf_vfx_update_instance(*(int **)(v30 + 128), rf_frame_delta_seconds, 0, 0, 0, 1);
      }
      v33 = -1;
      rf_string_destroy_buffer(v22);
    }
    else
    {
      for ( i = 0; i < 23; ++i )
        *(_DWORD *)(v30 + 16 * i + 2276) = -1;
      for ( i = 0; i < 45; ++i )
        *(_DWORD *)(v30 + 16 * i + 2644) = -1;
    }
  }
  else
  {
    rf_object_mark_for_deferred_delete(a1);
  }
}

