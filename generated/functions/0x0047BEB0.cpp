// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047BEB0 rf_rfl_bolt_emitters_section_load
// UNREALRED VERIFIED [world-uid-ownership]: Loads section 0xE00 bolt emitters, constructs each 0x18C-byte runtime record from the authored transform and source data, and registers it by UID.
int __cdecl rf_rfl_bolt_emitters_section_load(_DWORD *a1)
{
  int result; // eax
  float *v2; // eax
  float *v3; // eax
  char *v4; // eax
  char *last_dot_or_empty_literal; // eax
  char *v6; // eax
  char *v7; // eax
  char *v8; // [esp+10h] [ebp-114h]
  float v9; // [esp+14h] [ebp-110h]
  float v10; // [esp+18h] [ebp-10Ch]
  char *v11; // [esp+1Ch] [ebp-108h]
  int v12; // [esp+24h] [ebp-100h] BYREF
  float v13[3]; // [esp+28h] [ebp-FCh] BYREF
  float v14[3]; // [esp+34h] [ebp-F0h] BYREF
  float v15[3]; // [esp+40h] [ebp-E4h] BYREF
  float scaled_result[3]; // [esp+4Ch] [ebp-D8h] BYREF
  float copy_result[3]; // [esp+58h] [ebp-CCh] BYREF
  int v18; // [esp+64h] [ebp-C0h] BYREF
  float v19; // [esp+68h] [ebp-BCh]
  char *v20; // [esp+6Ch] [ebp-B8h]
  float v21; // [esp+70h] [ebp-B4h]
  int v22; // [esp+74h] [ebp-B0h]
  int v23[2]; // [esp+78h] [ebp-ACh] BYREF
  char bool_versioned; // [esp+83h] [ebp-A1h]
  char v25[12]; // [esp+84h] [ebp-A0h] BYREF
  float source[6]; // [esp+90h] [ebp-94h] BYREF
  float scalar; // [esp+A8h] [ebp-7Ch]
  float float_versioned; // [esp+ACh] [ebp-78h]
  int int32_versioned; // [esp+B0h] [ebp-74h] BYREF
  float v30[3]; // [esp+B4h] [ebp-70h] BYREF
  float destination[3]; // [esp+C0h] [ebp-64h] BYREF
  float v32[3]; // [esp+CCh] [ebp-58h] BYREF
  float v33[11]; // [esp+D8h] [ebp-4Ch] BYREF
  int v34; // [esp+104h] [ebp-20h]
  int v35[2]; // [esp+108h] [ebp-1Ch] BYREF
  int i; // [esp+110h] [ebp-14h]
  int v37; // [esp+114h] [ebp-10h]
  int v38; // [esp+120h] [ebp-4h]

  rf_bolt_emitter_definition_construct_noop((int)&int32_versioned);
  result = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  v37 = result;
  for ( i = 0; i < v37; ++i )
  {
    rf_matrix3_construct(v25);
    int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, v30, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(v25, 0, (int)unk_1C8FC18);
    rf_vector_copy(destination, copy_result, source);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v22 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    scalar = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v2 = rf_vector_multiply_scalar(destination, scaled_result, scalar);
    rf_vector_copy(destination, v15, v2);
    float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v3 = rf_vector3_set_components_return_destination(v14, 0.0, float_versioned, 0.0);
    rf_vector_copy(v33, v13, v3);
    rf_vector3_zero_return_destination(v32);
    v33[3] = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v33[8] = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    LODWORD(v33[9]) = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v21 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v19 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v10 = v21 - v19;
    v33[4] = rf_float_maximum_two_values(0.0, v10);
    v33[5] = v21 + v19;
    v21 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v19 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v9 = v21 - v19;
    v33[6] = rf_float_maximum_two_values(0.0, v9);
    v33[7] = v21 + v19;
    v35[1] = *rf_binary_stream_read_packed4bytes_versioned(a1, &v12, 0, &dword_1C8FC4C);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    v4 = (char *)rf_string_object_c_str_or_empty(unk_6FCCC0);
    last_dot_or_empty_literal = rf_path_find_last_dot_or_empty_literal(v4);
    rf_string_construct_from_cstr(v23, last_dot_or_empty_literal);
    v38 = 0;
    if ( rf_string_equals_case_insensitive((int)v23, ".vbm") )
    {
      v6 = (char *)rf_string_object_c_str_or_empty(unk_6FCCC0);
      v34 = rf_bitmap_vbm_sequence_load(v6, v35, &v18);
    }
    else
    {
      v7 = (char *)rf_string_object_c_str_or_empty(unk_6FCCC0);
      v34 = rf_bitmap_load_with_optional_mipmap_generation(v7, (void *)0xFFFFFFFF, 1);
      v35[0] = 1;
    }
    LODWORD(v33[10]) = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    bool_versioned = rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v11 = (char *)operator new(0x18Cu);
    LOBYTE(v38) = 1;
    if ( v11 )
      v8 = rf_bolt_emitter_construct_from_descriptor(v11, -1, v22, (int)&int32_versioned, bool_versioned);
    else
      v8 = nullptr;
    LOBYTE(v38) = 0;
    v20 = v8;
    rf_pointer_array_append_dword(rf_bolt_emitter_registry, (int)v8);
    v38 = -1;
    rf_string_destroy_buffer(v23);
    result = i + 1;
  }
  return result;
}

