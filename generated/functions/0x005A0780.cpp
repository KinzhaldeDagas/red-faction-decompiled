// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0780 rf_binary_stream_write_matrix3_vectors_201
// UNREALRED VERIFIED [binary-fields-20261029]: Actual THISCALL stream in ECX,one stack matrix pointer (existing inferred stdcall omits stream). Saves/restores ECX and writes three12-byte vectors from source+24,then+0,then+12 through0x5A0700. Counterpart reader0x59FBC0 uses same file order. No version header or aggregate error handling; returns final helper incidental result.
int __thiscall rf_binary_stream_write_matrix3_vectors_201(void *this, float *Buffer)
{
  rf_binary_stream_write_vector3(this, Buffer + 6);
  rf_binary_stream_write_vector3(this, Buffer);
  return rf_binary_stream_write_vector3(this, Buffer + 3);
}

