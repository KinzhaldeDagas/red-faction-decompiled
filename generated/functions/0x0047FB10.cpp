// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047FB10 rf_rfl_load_obb_region_records
// UNREALRED VERIFIED [level-lifecycle-20261028]: Reads signed record count then for each allocates64 bytes and constructs record through0x4839D0. Reads/discards source integer and class string, reads vec3 at+4 and matrix3 at+16, discards another string and, when file version<67, one extra string; discards versioned bool. Stores version96/default1 integer at+0 and final vec3 at+52, appends record to registry0x6FC3E8. Does not check allocation before subsequent writes. Editor-facing field meaning/section ID not established in this pass.
int __cdecl rf_rfl_load_obb_region_records(_DWORD *a1)
{
  int result; // eax
  char *v2; // [esp+4h] [ebp-24h]
  char *v3; // [esp+8h] [ebp-20h]
  int i; // [esp+14h] [ebp-14h]
  int v5; // [esp+18h] [ebp-10h]

  result = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  v5 = result;
  for ( i = 0; i < v5; ++i )
  {
    v3 = (char *)operator new(0x40u);
    if ( v3 )
      v2 = rf_world_obb_region_construct(v3);
    else
      v2 = nullptr;
    rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, (float *)v2 + 1, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(v2 + 16, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    if ( rf_vfile_get_slot_version(a1) < 67 )
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    *(_DWORD *)v2 = rf_binary_stream_read_int32_versioned(a1, 96, 1);
    rf_binary_stream_read_vector3_versioned(a1, (float *)v2 + 13, 0, unk_1C8FBDC);
    rf_pointer_array_append_dword(unk_6FC3E8, (int)v2);
    result = i + 1;
  }
  return result;
}

