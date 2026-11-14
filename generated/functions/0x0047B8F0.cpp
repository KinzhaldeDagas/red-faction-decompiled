// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047B8F0 rf_rfl_particle_emitters_section_load
// UNREALRED VERIFIED [world-uid-ownership]: Loads section 0xA00 particle emitters, resolves each VBM or mesh source, creates its runtime emitter, and registers the result by UID.
int __cdecl rf_rfl_particle_emitters_section_load(_DWORD *a1)
{
  int result; // eax
  char *v2; // eax
  char *last_dot_or_empty_literal; // eax
  char *v4; // eax
  char *v5; // eax
  float v6; // [esp+Ch] [ebp-104h]
  float v7; // [esp+10h] [ebp-100h]
  float v8; // [esp+14h] [ebp-FCh]
  float v9; // [esp+18h] [ebp-F8h]
  float v10; // [esp+1Ch] [ebp-F4h]
  int v11; // [esp+20h] [ebp-F0h] BYREF
  int v12; // [esp+24h] [ebp-ECh] BYREF
  float copy_result[3]; // [esp+28h] [ebp-E8h] BYREF
  int v14; // [esp+34h] [ebp-DCh] BYREF
  float v15; // [esp+38h] [ebp-D8h]
  float float_versioned; // [esp+3Ch] [ebp-D4h]
  int v17[2]; // [esp+40h] [ebp-D0h] BYREF
  char bool_versioned; // [esp+4Bh] [ebp-C5h]
  int v19; // [esp+4Ch] [ebp-C4h]
  char v20[12]; // [esp+50h] [ebp-C0h] BYREF
  float source[6]; // [esp+5Ch] [ebp-B4h] BYREF
  int v22; // [esp+74h] [ebp-9Ch]
  int i; // [esp+78h] [ebp-98h]
  int self; // [esp+7Ch] [ebp-94h] BYREF
  float v25[3]; // [esp+80h] [ebp-90h] BYREF
  float destination[9]; // [esp+8Ch] [ebp-84h] BYREF
  __int16 int32_versioned; // [esp+B0h] [ebp-60h]
  float v28; // [esp+B4h] [ebp-5Ch]
  float v29; // [esp+B8h] [ebp-58h]
  float v30; // [esp+BCh] [ebp-54h]
  float v31; // [esp+C0h] [ebp-50h]
  float v32; // [esp+C4h] [ebp-4Ch]
  float v33; // [esp+C8h] [ebp-48h]
  float v34; // [esp+CCh] [ebp-44h]
  float v35; // [esp+D0h] [ebp-40h]
  float v36; // [esp+D4h] [ebp-3Ch]
  float v37; // [esp+D8h] [ebp-38h]
  float v38; // [esp+DCh] [ebp-34h]
  int v39; // [esp+E0h] [ebp-30h]
  int v40[8]; // [esp+E4h] [ebp-2Ch] BYREF
  int v41; // [esp+10Ch] [ebp-4h]

  rf_particle_emitter_definition_construct_noop(&self);
  result = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  v22 = result;
  for ( i = 0; i < v22; ++i )
  {
    rf_matrix3_construct(v20);
    self = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, v25, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(v20, 0, (int)unk_1C8FC18);
    rf_vector_copy(destination, copy_result, source);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    if ( rf_vfile_get_slot_version(a1) < 67 )
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    rf_binary_stream_read_int32_versioned(a1, 0, 0);
    destination[8] = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    v2 = (char *)rf_string_object_c_str_or_empty(unk_6FCCC0);
    last_dot_or_empty_literal = rf_path_find_last_dot_or_empty_literal(v2);
    rf_string_construct_from_cstr(v17, last_dot_or_empty_literal);
    v41 = 0;
    if ( rf_string_equals_case_insensitive((int)v17, ".vbm") )
    {
      v4 = (char *)rf_string_object_c_str_or_empty(unk_6FCCC0);
      v39 = rf_bitmap_vbm_sequence_load(v4, v40, &v14);
    }
    else
    {
      v5 = (char *)rf_string_object_c_str_or_empty(unk_6FCCC0);
      v39 = rf_bitmap_load_with_optional_mipmap_generation(v5, (void *)0xFFFFFFFF, 1);
      v40[0] = 1;
    }
    float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v15 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v10 = float_versioned - v15;
    destination[6] = rf_float_maximum_two_values(0.0, v10);
    destination[7] = float_versioned + v15;
    float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v15 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v9 = float_versioned - v15;
    destination[4] = rf_float_maximum_two_values(0.0, v9);
    destination[5] = float_versioned + v15;
    v33 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v15 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v8 = float_versioned - v15;
    v28 = rf_float_maximum_two_values(0.0, v8);
    v29 = float_versioned + v15;
    float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v15 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v7 = float_versioned - v15;
    v30 = rf_float_maximum_two_values(0.0, v7);
    v31 = float_versioned + v15;
    v32 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v34 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v6 = float_versioned * 3.141592741012573 / 180.0;
    destination[3] = rf_cos_float(v6);
    v40[1] = *rf_binary_stream_read_packed4bytes_versioned(a1, &v12, 0, &dword_1C8FC4C);
    v40[2] = *rf_binary_stream_read_packed4bytes_versioned(a1, &v11, 158, &dword_1C8FC4C);
    int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v40[3] = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    bool_versioned = rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v35 = rf_binary_stream_read_float_versioned(a1, 119, 0.0);
    v36 = rf_binary_stream_read_float_versioned(a1, 119, 0.0);
    v37 = rf_binary_stream_read_float_versioned(a1, 119, 0.0);
    v38 = rf_binary_stream_read_float_versioned(a1, 119, 0.0);
    *(float *)&v40[6] = rf_binary_stream_read_float_versioned(a1, 136, 0.0);
    if ( v35 != 0.0 || v36 != 0.0 || v37 != 0.0 || v38 != 0.0 )
      int32_versioned |= 0x20u;
    if ( rf_vfile_get_slot_version(a1) < 101 && bool_versioned )
      int32_versioned |= 0x10u;
    v40[4] = 0;
    v19 = rf_particle_emitter_create(0, (float *)&self, 0, 0, bool_versioned);
    if ( v19 )
      rf_pointer_array_append_dword(rf_particle_emitter_registry, v19);
    v41 = -1;
    rf_string_destroy_buffer(v17);
    result = i + 1;
  }
  return result;
}

