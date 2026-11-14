// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E72D0 rf_binary_stream_read_int32_array
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered cdecl stream,int32 destination,count. Signed count<=0 returns0 without stream access. Each iteration reads int32 with minimum0/default0,STORES result to destination BEFORE querying stream status,returns first nonzero status immediately. Thus failing entry becomes0 and earlier writes remain;no rollback or returned element count. No endian conversion beyond scalar reader,capacity/index validation or bulk read.
int __cdecl rf_binary_stream_read_int32_array(void *a1, int *a2, int a3)
{
  int i; // [esp+0h] [ebp-8h]
  int open_slot_status; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a3; ++i )
  {
    a2[i] = rf_binary_stream_read_int32_versioned((int *)a1, 0, 0);
    open_slot_status = rf_vfile_get_open_slot_status(a1);
    if ( open_slot_status )
      return open_slot_status;
  }
  return 0;
}

