// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00480E50 rf_rfl_player_start_section_load
// UNREALRED VERIFIED [rfl-section-dispatch]: Loads section 0x70000 single-player start records.
int __cdecl rf_rfl_player_start_section_load(void *a1)
{
  rf_binary_stream_read_vector3_versioned(a1, &flt_6FC434, 0, unk_1C8FBDC);
  return rf_binary_stream_read_matrix3_vectors_201_versioned(unk_6FC440, 0, (int)unk_1C8FC18);
}

