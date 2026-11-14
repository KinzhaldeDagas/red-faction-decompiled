// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0D10 rf_binary_stream_serialize_uint16
// UNREALRED VERIFIED [stream-serializers-20261029]: Recovered code0x5A0D10..0x5A0D53. Arguments WORD pointer,minimum version,fallback16 bits. READ stores AX from0x59F9A0; WRITE sends native2 bytes through0x5A0640. Signedness changes caller interpretation,not emitted bits. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_uint16(
        void *stream,
        unsigned __int16 *value,
        int minimum_version,
        unsigned __int16 fallback)
{
  if ( rf_vfile_test_mode_mask(stream, 1) )
    *value = rf_binary_stream_read_uint16_versioned((int *)stream, minimum_version, fallback);
  else
    rf_binary_stream_write_word_host_order(stream, *value);
}

