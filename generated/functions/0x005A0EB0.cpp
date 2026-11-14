// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0EB0 rf_binary_stream_serialize_matrix3_vectors_201
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments36-byte matrix pointer,minimum version,default matrix. READ0x59FBC0; WRITE0x5A0780. Both stream three vectors in byte-offset order24,0,12. No additional transposition or matrix validation. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
int __thiscall rf_binary_stream_serialize_matrix3_vectors_201(_DWORD *this, float *Buffer, int a3, float *a4)
{
  if ( rf_vfile_test_mode_mask(this, 1) )
    return rf_binary_stream_read_matrix3_vectors_201_versioned(this, Buffer, a3, a4);
  else
    return rf_binary_stream_write_matrix3_vectors_201(this, Buffer);
}

