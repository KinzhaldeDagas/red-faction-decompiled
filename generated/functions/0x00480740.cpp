// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00480740 rf_rfl_moving_groups_section_load
// UNREALRED VERIFIED [mission-mover-layout-20261013] Verified version-180 serialized group: u16 string name, 2 bool bytes, u32 key count; each key = u32 UID, vec3 position, 9-float basis, u16 editor-name string, bool byte, 5 floats, 3 signed ints, final float angle. Then u32 editor-member count of (UID,vec3,basis), 6 bool bytes, signed mode, signed initial-key index, 4 (u16 string,float volume) sound pairs, and 2 ordered u32 UID arrays. Editor group/key names, their booleans and the first placement-member table are consumed but not retained as mover runtime owners. Modes >=6 normalize to 1. Final angle converts to negative radians. See exact instructions for x87 stores: some decompiler views incorrectly display zero assignments after versioned float reads.
void __cdecl rf_rfl_moving_groups_section_load(_DWORD *a1)
{
  int v1; // eax
  double float_versioned; // st7
  double v3; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7
  int v7; // eax
  int v8; // eax
  int v9; // eax
  float *v10; // eax
  float *v11; // eax
  double v12; // st7
  double v13; // st7
  char *v14; // [esp+10h] [ebp-114h]
  float v15[3]; // [esp+14h] [ebp-110h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-104h] BYREF
  float v17[3]; // [esp+2Ch] [ebp-F8h] BYREF
  float v18[3]; // [esp+38h] [ebp-ECh] BYREF
  void *v19; // [esp+44h] [ebp-E0h]
  char *v20; // [esp+48h] [ebp-DCh]
  float v21[3]; // [esp+4Ch] [ebp-D8h] BYREF
  char v22[36]; // [esp+58h] [ebp-CCh] BYREF
  float v23[3]; // [esp+7Ch] [ebp-A8h] BYREF
  int j; // [esp+88h] [ebp-9Ch]
  int int32_versioned; // [esp+8Ch] [ebp-98h]
  int v26; // [esp+90h] [ebp-94h]
  int v27; // [esp+94h] [ebp-90h]
  char v28[4]; // [esp+98h] [ebp-8Ch] BYREF
  char v29[12]; // [esp+9Ch] [ebp-88h] BYREF
  char v30[12]; // [esp+A8h] [ebp-7Ch] BYREF
  _DWORD v31[3]; // [esp+B4h] [ebp-70h] BYREF
  char bool_versioned; // [esp+C0h] [ebp-64h]
  char v33; // [esp+C1h] [ebp-63h]
  char v34; // [esp+C2h] [ebp-62h]
  char v35; // [esp+C3h] [ebp-61h]
  char v36; // [esp+C4h] [ebp-60h]
  char v37; // [esp+C5h] [ebp-5Fh]
  int v38; // [esp+C8h] [ebp-5Ch]
  int v39; // [esp+CCh] [ebp-58h]
  _QWORD v40[6]; // [esp+D0h] [ebp-54h] BYREF
  int v41; // [esp+104h] [ebp-20h]
  int i; // [esp+108h] [ebp-1Ch]
  int v43; // [esp+10Ch] [ebp-18h]
  int v44; // [esp+110h] [ebp-14h]
  char *v45; // [esp+114h] [ebp-10h]
  int v46; // [esp+120h] [ebp-4h]

  rf_rfl_moving_group_construct(v28);
  v46 = 0;
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v43 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    for ( j = 0; j < v43; ++j )
    {
      v19 = operator new(0x64u);
      LOBYTE(v46) = 1;
      if ( v19 )
        v14 = rf_rfl_moving_group_member_construct_noop((char *)v19);
      else
        v14 = nullptr;
      v20 = v14;
      LOBYTE(v46) = 0;
      v45 = v14;
      v1 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      *(_DWORD *)v45 = v1;
      rf_binary_stream_read_vector3_versioned(a1, (float *)v45 + 1, 0, unk_1C8FBDC);
      rf_binary_stream_read_matrix3_vectors_201_versioned(v45 + 16, 107, (int)unk_1C8FC18);
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 158, (char *)&byte_6387EF);
      rf_binary_stream_read_bool_versioned(a1, 0, 1);
      float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
      *((float *)v45 + 13) = float_versioned;
      v3 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
      *((float *)v45 + 14) = v3;
      v4 = rf_binary_stream_read_float_versioned(a1, 93, *((float *)v45 + 14));
      *((float *)v45 + 15) = v4;
      v5 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
      *((float *)v45 + 16) = v5;
      v6 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
      *((float *)v45 + 17) = v6;
      v7 = rf_binary_stream_read_int32_versioned(a1, 92, -1);
      *((_DWORD *)v45 + 18) = v7;
      v8 = rf_binary_stream_read_int32_versioned(a1, 149, -1);
      *((_DWORD *)v45 + 19) = v8;
      v9 = rf_binary_stream_read_int32_versioned(a1, 149, -1);
      *((_DWORD *)v45 + 20) = v9;
      if ( rf_vfile_get_slot_version(a1) >= 105 && rf_vfile_get_slot_version(a1) < 142 )
      {
        rf_vector3_default_construct_noop(v23);
        v10 = rf_vector3_set_components_return_destination(v18, 0.0, 0.0, 0.0);
        rf_binary_stream_read_vector3_versioned(a1, v23, 105, v10);
        v11 = rf_vector3_set_components_return_destination(v17, 0.0, 0.0, 0.0);
        rf_binary_stream_read_vector3_versioned(a1, v23, 105, v11);
        rf_vector_copy((float *)v45 + 22, copy_result, (const float *)v45 + 7);
        *((float *)v45 + 21) = 0.0;
      }
      v12 = rf_binary_stream_read_float_versioned(a1, 142, 0.0);
      *((float *)v45 + 21) = v12;
      rf_vector_copy((float *)v45 + 22, v15, (const float *)v45 + 7);
      *((float *)v45 + 21) = -(*((float *)v45 + 21) * 3.141592741012573 / 180.0);
      rf_pointer_array_append_dword(v29, (int)v45);
    }
    v44 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    for ( j = 0; j < v44; ++j )
    {
      rf_vector3_default_construct_noop(v21);
      rf_matrix3_construct(v22);
      rf_binary_stream_read_int32_versioned(a1, 0, 0);
      rf_binary_stream_read_vector3_versioned(a1, v21, 0, unk_1C8FBDC);
      rf_binary_stream_read_matrix3_vectors_201_versioned(v22, 0, (int)unk_1C8FC18);
    }
    bool_versioned = rf_binary_stream_read_bool_versioned(a1, 0, 1);
    if ( rf_vfile_get_slot_version(a1) < 104 )
      rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v33 = rf_binary_stream_read_bool_versioned(a1, 105, 0);
    v34 = rf_binary_stream_read_bool_versioned(a1, 92, 0);
    v35 = rf_binary_stream_read_bool_versioned(a1, 155, 0);
    v36 = rf_binary_stream_read_bool_versioned(a1, 156, 0);
    v37 = rf_binary_stream_read_bool_versioned(a1, 174, 0);
    v38 = rf_binary_stream_read_int32_versioned(a1, 90, 1);
    if ( v38 >= 6 )
      v38 = 1;
    v39 = rf_binary_stream_read_int32_versioned(a1, 92, 0);
    for ( j = 0; j < 4; ++j )
    {
      if ( j >= 3 )
      {
        rf_binary_stream_read_string_object_versioned(a1, &v40[j], 103, (char *)&byte_6387F6);
        v13 = rf_binary_stream_read_float_versioned(a1, 103, 1.0);
      }
      else
      {
        rf_binary_stream_read_string_object_versioned(a1, &v40[j], 92, (char *)&byte_6387F5);
        v13 = rf_binary_stream_read_float_versioned(a1, 92, 1.0);
      }
      *((float *)&v40[4] + j) = v13;
    }
    v41 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    for ( j = 0; j < v41; ++j )
    {
      v26 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      rf_pointer_array_append_dword(v30, v26);
    }
    v27 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    for ( j = 0; j < v27; ++j )
    {
      v26 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      rf_pointer_array_append_dword(v31, v26);
    }
    rf_mover_create_from_group((int)v28);
    rf_pointer_array_clear_count_keep_storage(v29);
    rf_pointer_array_clear_count_keep_storage(v30);
    rf_pointer_array_clear_count_keep_storage(v31);
    rf_progress_update_poll_network_and_callback(0, 0);
  }
  v46 = -1;
  rf_rfl_moving_group_destroy((int)v28);
}

