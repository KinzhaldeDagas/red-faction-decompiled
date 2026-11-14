// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0E70 rf_binary_stream_serialize_float4
// UNREALRED VERIFIED [stream-serializers-20261029]: Recovered code0x5A0E70..0x5A0EAD. Arguments4-float pointer,minimum version,default4-float pointer. READ0x59FB30; WRITE0x5A0720. No normalization or separate length prefix. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_float4(
        void *stream,
        float *value,
        int minimum_version,
        const float *fallback)
{
  if ( rf_vfile_test_mode_mask(stream, 1) )
    rf_binary_stream_read_float4_versioned((int *)stream, value, minimum_version, (float *)fallback);
  else
    rf_binary_stream_write_float4(stream, value);
}

