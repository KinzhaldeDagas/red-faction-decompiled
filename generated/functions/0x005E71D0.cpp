// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E71D0 rf_binary_stream_read_vector3_array_versioned
// UNREALRED VERIFIED [string-pool-stream-20261028]: cdecl arguments stream,destination,count,minimum version,default vector. Signed count<=0 returns0 without stream access. For each index,calls0x59FAE0 with stream in ECX,destination+12*index,minimum,default; then checks rf_vfile_get_open_slot_status(stream). First nonzero status returned immediately; all entries/no error returns0. No rollback,capacity validation or interpreting helper return as status. Same fallback vector applied to every element below minimum version.
int __cdecl rf_binary_stream_read_vector3_array_versioned(_DWORD *a1, int a2, int a3, int a4, float *a5)
{
  int i; // [esp+0h] [ebp-8h]
  int open_slot_status; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a3; ++i )
  {
    rf_binary_stream_read_vector3_versioned(a1, (float *)(a2 + 12 * i), a4, a5);
    open_slot_status = rf_vfile_get_open_slot_status(a1);
    if ( open_slot_status )
      return open_slot_status;
  }
  return 0;
}

