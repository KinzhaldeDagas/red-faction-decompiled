// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483280 rf_rfl_pose_records_0400_load
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Cdecl stream, RFL section0x400; corrected missing stream argument in saved prototype. Reads signed count. Normal mode BYTE6FCCB8==0: allocates52-byte pose record, no-op ctor, then
// reads idDWORD0,discarded string,position4,matrix16,discarded string,discarded bool(default1,min0); appends pointer to vector6FB258. No local allocation-failure check, registry
// clear, id uniqueness or row-count cap.
// Alternate mode BYTE6FCCB8 nonzero: if count>0 releases backing storage of vector12 array666AD0 and matrix36 array666AB8 BEFORE rows. Reads same serialized fields, discards
// id/strings/bool, appends position and matrix by VALUE to those arrays, with no52-byte record allocation. If count<=0 does NOT clear prior arrays. No coordinate
// conversion/normalization or interpretation of discarded boolean. This routine's precise record role beyond observed section/pose layout is not assigned from an external format
// guess. Temporary RFString is destroyed; no per-row rollback.
void __cdecl rf_rfl_pose_records_0400_load(_DWORD *stream)
{
  int v1; // eax
  float v2[6]; // [esp-24h] [ebp-8Ch] BYREF
  int v3; // [esp-Ch] [ebp-74h] BYREF
  int v4; // [esp-8h] [ebp-70h]
  int v5; // [esp-4h] [ebp-6Ch]
  char *v6; // [esp+4h] [ebp-64h]
  float *v7; // [esp+8h] [ebp-60h]
  int *v8; // [esp+Ch] [ebp-5Ch]
  void *v9; // [esp+10h] [ebp-58h]
  char *v10; // [esp+14h] [ebp-54h]
  float v11[3]; // [esp+18h] [ebp-50h] BYREF
  char v12[36]; // [esp+24h] [ebp-44h] BYREF
  char *v13; // [esp+48h] [ebp-20h]
  int v14[2]; // [esp+4Ch] [ebp-1Ch] BYREF
  int i; // [esp+54h] [ebp-14h]
  int int32_versioned; // [esp+58h] [ebp-10h]
  int v17; // [esp+64h] [ebp-4h]

  rf_string_construct_empty(v14);
  v17 = 0;
  int32_versioned = rf_binary_stream_read_int32_versioned(stream, 0, 0);
  if ( unk_6FCCB8 && int32_versioned > 0 )
  {
    rf_pointer_array_release_storage((void **)dword_666AD0);
    rf_pointer_array_release_storage((void **)dword_666AB8);
  }
  for ( i = 0; i < int32_versioned; ++i )
  {
    if ( unk_6FCCB8 )
    {
      rf_vector3_default_construct_noop(v11);
      rf_matrix3_construct(v12);
      rf_binary_stream_read_int32_versioned(stream, 0, 0);
      rf_binary_stream_read_string_object_versioned(stream, v14, 0, nullptr);
      rf_binary_stream_read_vector3_versioned(stream, v11, 0, unk_1C8FBDC);
      rf_binary_stream_read_matrix3_vectors_201_versioned(v12, 0, (int)unk_1C8FC18);
      rf_binary_stream_read_string_object_versioned(stream, v14, 0, nullptr);
      rf_binary_stream_read_bool_versioned(stream, 0, 1);
      v8 = &v3;
      rf_vector3_copy_return_destination((float *)&v3, v11);
      rf_vector_array12_append_by_value(dword_666AD0, *(float *)&v3, v4, v5);
      v7 = v2;
      rf_matrix3_copy_construct((int)v2, v12);
      rf_matrix_array36_append_by_value(
        dword_666AB8,
        v2[0],
        SLODWORD(v2[1]),
        SLODWORD(v2[2]),
        SLODWORD(v2[3]),
        SLODWORD(v2[4]),
        SLODWORD(v2[5]),
        v3,
        v4,
        v5);
    }
    else
    {
      v9 = operator new(0x34u);
      LOBYTE(v17) = 1;
      if ( v9 )
        v6 = rf_embedded_vector4_matrix16_construct_noop((char *)v9);
      else
        v6 = nullptr;
      v10 = v6;
      LOBYTE(v17) = 0;
      v13 = v6;
      v1 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)v13 = v1;
      rf_binary_stream_read_string_object_versioned(stream, v14, 0, nullptr);
      rf_binary_stream_read_vector3_versioned(stream, (float *)v13 + 1, 0, unk_1C8FBDC);
      rf_binary_stream_read_matrix3_vectors_201_versioned(v13 + 16, 0, (int)unk_1C8FC18);
      rf_binary_stream_read_string_object_versioned(stream, v14, 0, nullptr);
      rf_binary_stream_read_bool_versioned(stream, 0, 1);
      rf_pointer_array_append_dword(unk_6FB258, (int)v13);
    }
  }
  v17 = -1;
  rf_string_destroy_buffer(v14);
}

