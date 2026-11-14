// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0D60 rf_binary_stream_serialize_int32
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments DWORD pointer,minimum version,fallback32 bits. READ stores EAX from0x59F9F0; WRITE sends native4 bytes through0x5A0670. Does not convert text or byte order. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
int __thiscall rf_binary_stream_serialize_int32(_DWORD *this, int *a2, int a3, int a4)
{
  int result; // eax

  if ( !rf_vfile_test_mode_mask(this, 1) )
    return rf_binary_stream_write_int32_host_order(this, *a2);
  result = rf_binary_stream_read_int32_versioned(this, a3, a4);
  *a2 = result;
  return result;
}

