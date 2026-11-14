// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0DA0 rf_binary_stream_serialize_uint32
// UNREALRED VERIFIED [stream-serializers-20261029]: Recovered code0x5A0DA0..0x5A0DE0. Arguments DWORD pointer,minimum version,fallback32 bits. READ stores EAX from0x59FA40; WRITE sends native4 bytes through0x5A06A0. No endian conversion. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_uint32(
        void *stream,
        unsigned int *value,
        int minimum_version,
        unsigned int fallback)
{
  if ( rf_vfile_test_mode_mask(stream, 1) )
    *value = rf_binary_stream_read_uint32_versioned((int *)stream, minimum_version, fallback);
  else
    rf_binary_stream_write_uint32_host_order(stream, *value);
}

