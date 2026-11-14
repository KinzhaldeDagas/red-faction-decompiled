// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7280 rf_binary_stream_vector3_array_read_or_write
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered cdecl stream,vector array,signed count,minimum version,default vector. Tests vfile mode bit1 through592440;nonzero delegates versioned vector-array reader5E71D0 with all5 args,zero delegates vector-array writer5E7230 with first3. Returns delegate status. Minimum/default unused on write path. Mode query still occurs for count<=0,then delegate returns0;no array capacity/stream-index validation. Not a fixed-direction file loader.
int __cdecl rf_binary_stream_vector3_array_read_or_write(void *a1, float *a2, int a3, int a4, const float *a5)
{
  if ( rf_vfile_test_mode_mask(a1, 1) )
    return rf_binary_stream_read_vector3_array_versioned(a1, (int)a2, a3, a4, (float *)a5);
  else
    return rf_binary_stream_write_vector3_array(a1, (int)a2, a3);
}

