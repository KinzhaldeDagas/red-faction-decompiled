// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0CC0 rf_binary_stream_serialize_int16
// UNREALRED VERIFIED [stream-serializers-20261029]: Recovered code0x5A0CC0..0x5A0D03. Arguments16-bit value pointer,minimum version,fallback16 bits. READ stores AX from0x59F950; WRITE sends native2 bytes through0x5A0610. No byte-order conversion. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_int16(void *stream, __int16 *value, int minimum_version, __int16 fallback)
{
  if ( rf_vfile_test_mode_mask(stream, 1) )
    *value = rf_binary_stream_read_int16_versioned((int *)stream, minimum_version, fallback);
  else
    rf_binary_stream_write_int16_host_order(stream, *value);
}

