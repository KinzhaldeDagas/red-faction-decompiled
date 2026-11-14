// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0F80 rf_binary_stream_serialize_u16_string_buffer
// UNREALRED VERIFIED [stream-serializers-20261029]: Recovered code0x5A0F80..0x5A0FC3. Arguments char buffer,capacity,minimum version,fallback C string. READ0x59FF90 applies its capacity/truncation and fallback semantics. WRITE0x5A08B0(buffer,-1) uses strlen,ignoring capacity and writing low16 prefix plus full body. No NUL written to stream. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_u16_string_buffer(
        void *stream,
        char *value,
        int capacity,
        int minimum_version,
        const char *fallback)
{
  if ( rf_vfile_test_mode_mask(stream, 1) )
    rf_binary_stream_read_u16_string_to_buffer((int *)stream, value, capacity, minimum_version, (char *)fallback);
  else
    rf_binary_stream_write_u16_length_string(stream, value, -1);
}

