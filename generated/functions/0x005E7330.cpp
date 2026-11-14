// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7330 rf_binary_stream_write_int32_array
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered cdecl stream,int32 source,count. For count>0,copies each source DWORD into scalar writer stack argument with stream inECX,then reads stream status;first nonzero status returned,otherwise0. Count<=0 no stream access. Source passed by value to scalar writer,not bulk output;partial writes remain,individual writer incidental return ignored. No bounds/endianness conversion or rollback.
int __cdecl rf_binary_stream_write_int32_array(void *a1, const int *a2, int a3)
{
  int i; // [esp+0h] [ebp-8h]
  int open_slot_status; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a3; ++i )
  {
    rf_binary_stream_write_int32_host_order(a1, a2[i]);
    open_slot_status = rf_vfile_get_open_slot_status(a1);
    if ( open_slot_status )
      return open_slot_status;
  }
  return 0;
}

