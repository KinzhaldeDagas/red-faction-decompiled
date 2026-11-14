// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0DE0 rf_binary_stream_serialize_float32
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments float pointer,minimum version,float fallback. READ stores x87 result from0x59FA90; WRITE sends raw IEEE4 bytes through0x5A06D0. No text conversion,range validation or endian swap. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_float32(int *this, float *a2, int a3, float a4)
{
  if ( rf_vfile_test_mode_mask(this, 1) )
    *a2 = rf_binary_stream_read_float_versioned(this, a3, a4);
  else
    rf_binary_stream_write_float32_host_order(this, *a2);
}

