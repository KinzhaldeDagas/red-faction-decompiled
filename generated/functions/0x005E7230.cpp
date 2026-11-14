// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7230 rf_binary_stream_write_vector3_array
// UNREALRED VERIFIED [string-pool-stream-20261028]: cdecl stream,source vector array,signed count. For each of count>0 elements,calls0x5A0700 with stream in ECX and source+12*index,then reads stream status. First nonzero status returned; all success/count<=0 returns0. No rollback,capacity/index validation or separate element-count output. Ignores individual helper incidental returns.
int __cdecl rf_binary_stream_write_vector3_array(_DWORD *a1, int a2, int a3)
{
  int i; // [esp+0h] [ebp-8h]
  int open_slot_status; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a3; ++i )
  {
    rf_binary_stream_write_vector3(a1, (float *)(a2 + 12 * i));
    open_slot_status = rf_vfile_get_open_slot_status(a1);
    if ( open_slot_status )
      return open_slot_status;
  }
  return 0;
}

