// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0FD0 rf_binary_stream_serialize_raw_bytes
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments mutable buffer,byte count,minimum version. READ calls0x5A0230(buffer,count,minimum,0),returning copied count. Below minimum raw reader returns0 WITHOUT filling buffer with a default. WRITE0x5A0990 uses full count and may temporarily transform buffer for feedback encoding; return not byte count. No fallback argument or size prefix. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
int *__thiscall rf_binary_stream_serialize_raw_bytes(int *this, char *Buffer, size_t Size, int a4)
{
  if ( rf_vfile_test_mode_mask(this, 1) )
    return (int *)rf_vfile_read_buffered_bytes_versioned(this, Buffer, Size, a4, 0);
  else
    return rf_vfile_write_bytes_with_optional_feedback(this, Buffer, Size);
}

