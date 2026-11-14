// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E73E0 rf_binary_stream_write_int16_array
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered cdecl stream,WORD source,count. Signed positive count loops:loads source WORD,passes low16 pattern to scalar thiscall writer with stream inECX,checks stream status afterward. Returns first nonzero status or0;count<=0 no accesses. No source mutation by scalar stack-value writer,bulk transfer,byte swap or rollback of prior elements.
int __cdecl rf_binary_stream_write_int16_array(void *a1, const __int16 *a2, int a3)
{
  int i; // [esp+0h] [ebp-8h]
  int open_slot_status; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a3; ++i )
  {
    rf_binary_stream_write_int16_host_order(a1, a2[i]);
    open_slot_status = rf_vfile_get_open_slot_status(a1);
    if ( open_slot_status )
      return open_slot_status;
  }
  return 0;
}

