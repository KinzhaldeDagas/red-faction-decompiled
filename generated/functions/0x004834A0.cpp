// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004834A0 rf_rfl_cutscene_aux_points_load
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Cdecl stream, RFL section0x5000; corrected missing stream argument. Reads signed row count, loops while i<count AND global aux-count6FB248<64. Uses16-byte record
// at6FB270+16*currentCount, increments global count BEFORE reads. Stores idDWORD0 and position3f+4; consumes/discards two strings,full matrix and bool(default1,min0). Matrix is local
// no-op-constructed then read, not stored in record. Does not clear existing aux records/count, validate unique ids or data, or skip remaining record payload after reaching cap;
// leaves that responsibility to outer dispatcher. Lookup476D70 later matches id and returns these records; Bezier path loader consumes their positions.
void __cdecl rf_rfl_cutscene_aux_points_load(_DWORD *stream)
{
  int *v1; // [esp+4h] [ebp-44h]
  int v2[2]; // [esp+8h] [ebp-40h] BYREF
  int i; // [esp+10h] [ebp-38h]
  int int32_versioned; // [esp+14h] [ebp-34h]
  char v5[36]; // [esp+18h] [ebp-30h] BYREF
  int v6; // [esp+44h] [ebp-4h]

  rf_string_construct_empty(v2);
  v6 = 0;
  rf_matrix3_construct(v5);
  int32_versioned = rf_binary_stream_read_int32_versioned(stream, 0, 0);
  for ( i = 0; i < int32_versioned && dword_6FB248 < 64; ++i )
  {
    v1 = &unk_6FB270[4 * dword_6FB248++];
    *v1 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    rf_binary_stream_read_string_object_versioned(stream, v2, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(stream, (float *)v1 + 1, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(v5, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(stream, v2, 0, nullptr);
    rf_binary_stream_read_bool_versioned(stream, 0, 1);
  }
  v6 = -1;
  rf_string_destroy_buffer(v2);
}

