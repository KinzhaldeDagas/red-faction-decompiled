// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0EF0 rf_binary_stream_serialize_transposed12_float_block
// UNREALRED VERIFIED [stream-serializers-20261029]: Recovered code0x5A0EF0..0x5A0F2D. Arguments float block,minimum version,default48-byte block. READ0x59FC30 consumes12 floats but overwrites indices3,6,9 with0 and writes index12=1,requiring52 bytes. WRITE0x5A07C0 emits indices0,3,6,1,4,7,2,5,8,9,10,11 only. Does not correct asymmetric reader behavior. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_transposed12_float_block(
        void *stream,
        float *value,
        int minimum_version,
        const void *fallback)
{
  if ( rf_vfile_test_mode_mask(stream, 1) )
    rf_binary_stream_read_transposed12_floats_with_overwrites((int *)stream, value, minimum_version, fallback);
  else
    rf_binary_stream_write_transposed12_floats(stream, value);
}

