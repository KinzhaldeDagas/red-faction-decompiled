// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7380 rf_binary_stream_read_int16_array
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Cdecl stream,int16 destination,count. For signed count>0,reads scalar minimum0/defaultWORD0,stores low16bits BEFORE checking status;first nonzero status returned. Failing entry becomes0,prior values retained;count<=0 returns0 without status read. No bounds/rollback,host WORD pattern preserved. Prototype corrected so destination is16-bit pointer rather than untyped integer.
int __cdecl rf_binary_stream_read_int16_array(void *a1, __int16 *a2, int a3)
{
  int i; // [esp+0h] [ebp-8h]
  int open_slot_status; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a3; ++i )
  {
    a2[i] = rf_binary_stream_read_int16_versioned((int *)a1, 0, 0);
    open_slot_status = rf_vfile_get_open_slot_status(a1);
    if ( open_slot_status )
      return open_slot_status;
  }
  return 0;
}

