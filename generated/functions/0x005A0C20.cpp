// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0C20 rf_binary_stream_serialize_char8
// UNREALRED VERIFIED [stream-serializers-20261029]: Recovered code0x5A0C20..0x5A0C62. Arguments char pointer,minimum version,fallback byte. READ calls0x59F8B0 and stores AL; WRITE loads low8 value and calls0x5A05D0. No encoding conversion. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_char8(void *stream, char *value, int minimum_version, char fallback)
{
  if ( rf_vfile_test_mode_mask(stream, 1) )
    *value = rf_binary_stream_read_char8_versioned((int *)stream, minimum_version, fallback);
  else
    rf_binary_stream_write_char8_host_order(stream, *value);
}

