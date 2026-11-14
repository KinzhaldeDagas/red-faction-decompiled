// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0E30 rf_binary_stream_serialize_vector3
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments3-float vector pointer,minimum version,default vector pointer. READ delegates0x59FAE0 (12 bytes or vector fallback); WRITE delegates0x5A0700 (12 bytes). Hidden ECX stream must be retained even when pseudocode presents buffer as this. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
int __thiscall rf_binary_stream_serialize_vector3(_DWORD *this, float *Buffer, int a3, float *a4)
{
  if ( rf_vfile_test_mode_mask(this, 1) )
    return rf_binary_stream_read_vector3_versioned(this, Buffer, a3, a4);
  else
    return rf_binary_stream_write_vector3(this, Buffer);
}

