// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0B80 rf_binary_stream_write_packed4bytes
// UNREALRED VERIFIED [binary-fields-20261029]: Actual THISCALL stream in ECX,one stack pointer to4 bytes (inferred stdcall omits stream). Writes bytes0,1,2,3 in order through0x5A05F0,zero-extending each on argument push. No channel permutation,endian swap or aggregate status check. Returns last helper incidental result.
int *__thiscall rf_binary_stream_write_packed4bytes(_DWORD *this, char *a2)
{
  rf_binary_stream_write_byte_host_order(this, *a2);
  rf_binary_stream_write_byte_host_order(this, a2[1]);
  rf_binary_stream_write_byte_host_order(this, a2[2]);
  return rf_binary_stream_write_byte_host_order(this, a2[3]);
}

