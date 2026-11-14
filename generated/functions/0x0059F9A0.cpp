// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F9A0 rf_binary_stream_read_uint16_versioned
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,minimum version,default16-bit pattern. Below minimum returns default;otherwise reads2 raw bytes(version0),returns default on stream error or host-order WORD on success. Equivalent-width implementation to0x59F950; string readers explicitly zero-extend AX as unsigned length. No length bound,endian swap,error reset or rollback.
__int16 __thiscall rf_binary_stream_read_uint16_versioned(int *this, int a2, __int16 a3)
{
  char v5[4]; // [esp+4h] [ebp-4h] BYREF

  if ( !rf_binary_stream_version_at_least(this, a2) )
    return a3;
  rf_vfile_read_buffered_bytes_versioned(this, v5, 2u, 0, 0);
  if ( rf_vfile_get_open_slot_status(this) )
    return a3;
  else
    return *(_WORD *)v5;
}

