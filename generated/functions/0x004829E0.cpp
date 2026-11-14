// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004829E0 rf_rfl_clutter_section_load
// UNREALRED VERIFIED [mission-visibility-20261020] Clutter post-placement data is one versioned bool followed by legacy-entry reader0x4826F0, then skin and linked-light IDs at v180. The old five-byte skip is valid only when the four-byte legacy count is zero; nonempty entries cannot be skipped as fixed bytes.
void __cdecl rf_rfl_clutter_section_load(_DWORD *a1)
{
  char *v1; // eax
  int index_by_name; // eax
  _DWORD *v3; // esi
  char *v4; // eax
  int v5; // eax
  char *v6; // [esp-14h] [ebp-98h]
  int m; // [esp+8h] [ebp-7Ch]
  int v8; // [esp+Ch] [ebp-78h]
  int j; // [esp+10h] [ebp-74h]
  int k; // [esp+10h] [ebp-74h]
  int v11; // [esp+14h] [ebp-70h] BYREF
  int v12; // [esp+18h] [ebp-6Ch]
  int v13; // [esp+1Ch] [ebp-68h] BYREF
  int i; // [esp+20h] [ebp-64h]
  int v15[2]; // [esp+24h] [ebp-60h] BYREF
  int int32_versioned; // [esp+2Ch] [ebp-58h]
  int v17[2]; // [esp+30h] [ebp-54h] BYREF
  int v18; // [esp+38h] [ebp-4Ch] BYREF
  float v19[3]; // [esp+3Ch] [ebp-48h] BYREF
  int v20[10]; // [esp+48h] [ebp-3Ch] BYREF
  int v21[2]; // [esp+70h] [ebp-14h] BYREF
  int v22; // [esp+80h] [ebp-4h]

  rf_string_construct_empty(v17);
  v22 = 0;
  rf_string_construct_empty(v21);
  LOBYTE(v22) = 1;
  rf_vector3_default_construct_noop(v19);
  rf_matrix3_construct((char *)v20);
  rf_string_construct_empty(v15);
  LOBYTE(v22) = 2;
  rf_binary_stream_serialize_int32(a1, &v18, 0, 0);
  for ( i = 0; i < v18; ++i )
  {
    int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, v21, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, v19, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned((char *)v20, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a1, v17, 0, nullptr);
    if ( rf_vfile_get_slot_version(a1) < 67 )
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    rf_rfl_discard_legacy_object_entries(a1);
    if ( rf_vfile_get_slot_version(a1) >= 103 && rf_vfile_get_slot_version(a1) < 124 )
      v20[9] = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, v15, 118, nullptr);
    v11 = -1;
    rf_binary_stream_serialize_int32(a1, &v13, 125, 0);
    rf_pointer_array_release_storage((void **)unk_6FCCC8);
    for ( j = 0; j < v13; ++j )
    {
      rf_binary_stream_serialize_int32(a1, &v11, 0, 0);
      rf_pointer_array_append_dword(unk_6FCCC8, v11);
    }
    v6 = (char *)rf_string_object_c_str_or_empty(v17);
    v1 = (char *)rf_string_object_c_str_or_empty(v21);
    index_by_name = rf_clutter_class_find_index_by_name(v1);
    v12 = (int)rf_clutter_runtime_create(index_by_name, v6, -1, v19, (float *)v20, 1);
    if ( v12 )
    {
      for ( k = 0; k < v13; ++k )
      {
        v8 = 0;
        for ( m = 0; m < rf_receiver_get_first_dword(rf_rfl_light_registry); ++m )
        {
          v3 = *(_DWORD **)sub_552200(rf_rfl_light_registry, m);
          if ( *v3 == *(_DWORD *)sub_552200(unk_6FCCC8, k) )
          {
            v8 = *(_DWORD *)sub_552200(rf_rfl_light_registry, m);
            break;
          }
        }
        if ( v8 )
          rf_pointer_array_append_dword((_DWORD *)(v12 + 704), *(_DWORD *)(v8 + 148));
      }
      *(_DWORD *)(v12 + 32) = int32_versioned;
      if ( rf_rf_string_not_equals_cstring_case_insensitive((int)v15, (char *)&byte_63885F) )
      {
        v4 = (char *)rf_string_object_c_str_or_empty(v15);
        v5 = rf_clutter_apply_named_skin((_DWORD *)v12, v4);
        *(_DWORD *)(v12 + 700) = v5;
      }
      rf_progress_update_poll_network_and_callback(0, 0);
    }
  }
  LOBYTE(v22) = 1;
  rf_string_destroy_buffer(v15);
  LOBYTE(v22) = 0;
  rf_string_destroy_buffer(v21);
  v22 = -1;
  rf_string_destroy_buffer(v17);
}

