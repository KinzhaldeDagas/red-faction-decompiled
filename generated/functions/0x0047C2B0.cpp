// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047C2B0 rf_rfl_target_markers_section_load
// UNREALRED VERIFIED [event-registry-crc-20261028]: CORRECTION to prior hud-world-targets comment: this loader passes EVENT SUBTYPE0x1B to0x4F7780, which creates fixed common object type6. It does not create common object type0x1B. After creation stores authored UID at E+36, position E+64, copies orientation and assigns script string at E+28. Reads/discards class string and version-gated tail bool. Existing descriptive loader label is retained pending broader section semantics.
void __cdecl rf_rfl_target_markers_section_load(_DWORD *a1)
{
  float copy_result[3]; // [esp+4h] [ebp-60h] BYREF
  int v2; // [esp+10h] [ebp-54h]
  float source[3]; // [esp+14h] [ebp-50h] BYREF
  int int32_versioned; // [esp+20h] [ebp-44h]
  int v5; // [esp+24h] [ebp-40h]
  float v6[9]; // [esp+28h] [ebp-3Ch] BYREF
  int i; // [esp+4Ch] [ebp-18h]
  int v8[2]; // [esp+50h] [ebp-14h] BYREF
  int v9; // [esp+60h] [ebp-4h]

  rf_matrix3_construct((char *)v6);
  rf_vector3_default_construct_noop(source);
  rf_string_construct_empty(v8);
  v9 = 0;
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    v5 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, source, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned((char *)v6, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a1, v8, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v2 = rf_mission_event_create_at_position((int)source, 0x1Bu);
    rf_vector_copy((float *)(v2 + 64), copy_result, source);
    *(_DWORD *)(v2 + 36) = v5;
    rf_matrix3_copy((float *)(v2 + 76), v6);
    rf_string_assign_from_object((_DWORD *)(v2 + 28), (int)v8);
  }
  v9 = -1;
  rf_string_destroy_buffer(v8);
}

