// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059FA40 rf_binary_stream_read_uint32_versioned
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,minimum version,default32-bit pattern. Below minimum returns default;otherwise reads4 raw bytes(version0),returns default when status nonzero,else raw host-order DWORD. Parallel named int32 reader0x59F9F0 has same-width behavior; no numeric conversion,endian swap or status clearing.
int __thiscall rf_binary_stream_read_uint32_versioned(int *this, int a2, int a3)
{
  int v5; // [esp+4h] [ebp-4h] BYREF

  if ( !rf_binary_stream_version_at_least(this, a2) )
    return a3;
  rf_vfile_read_buffered_bytes_versioned(this, (char *)&v5, 4u, 0, 0);
  if ( rf_vfile_get_open_slot_status(this) )
    return a3;
  else
    return v5;
}

