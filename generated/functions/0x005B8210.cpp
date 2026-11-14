// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8210 rf_v3c_read_collision_sphere44
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Reads24 raw name bytes into record, int32 at+24, vector3 position at+28, and float radius at+40 using versioned stream helpers. Returns0 unconditionally after reads. Does not append a name terminator, validate radius/index or allocate record. Dispatched for numeric CSPH tag0x43535048.
int __thiscall rf_v3c_read_collision_sphere44(int this, int *a2)
{
  rf_vfile_read_buffered_bytes_versioned(a2, (char *)this, 0x18u, 0, 0);
  *(_DWORD *)(this + 24) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
  rf_binary_stream_read_vector3_versioned(a2, (float *)(this + 28), 0, unk_1C8FBDC);
  *(float *)(this + 40) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
  return 0;
}

